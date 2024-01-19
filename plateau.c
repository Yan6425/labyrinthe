#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>
#include <time.h>

const char* nomLab(int n){
    const char* labyrinthe[]={
        "lab/lab1.txt",
        "lab/lab2.txt",
        "lab/lab3.txt",
        "lab/lab4.txt",
        "lab/lab5.txt",
        "lab/lab6.txt",
        "lab/lab7.txt",
        "lab/lab8.txt",
        "lab/lab9.txt",
        "lab/lab10.txt"
    };
    return labyrinthe[n];
}

void dimensionsLab(const char* nomFichier, int* hauteur, int* largeur){
    int n=150;
    FILE* fichier = fopen(nomFichier,"r");
    int nbColonnesLues=0;
    int nbLignesLues=0;
    char ligne[n];
    char* laLigne;
    laLigne=malloc(sizeof(char)*n);
    if (fichier==NULL){
        printf("Erreur ouverture fichier \n");
    }
    else {
        while(fgets(ligne,n,fichier) !=NULL){
            laLigne=strtok(ligne," ");
            while (laLigne != NULL){
                laLigne = strtok(NULL, " ");
                nbColonnesLues++;
            }
            *largeur=nbColonnesLues;
            nbColonnesLues=0;
            nbLignesLues++;
            *hauteur=nbLignesLues;
        }
        fclose(fichier);
    }
}

int** allouerLabyrinthe(int n, int N){
    int** labyrinthe;
    labyrinthe=malloc(n*sizeof(int*));
    for (int i=0; i<n; i++){
        labyrinthe[i]=malloc(N*sizeof(int));
    }
    return labyrinthe;
}

void initialiserLabyrinthe(int** labyrinthe, int n, int N){
    for (int i=0;i<n;i++){
        for (int j=0;j<N;j++){
            labyrinthe[i][j]=0;
        }
    }
}

void lireTXT(const char* nomFichier,int** labyrinthe){
    int n=150;
	FILE* lab = NULL;
    char ligne[n];
    int nbLignesLues = 0;
    int nbColonnesLues = 0;
    char* laLigne;
    int test=0;
    int i=0;
    int j=0;
    laLigne=malloc(sizeof(char)*n);
    lab = fopen(nomFichier, "r");
    if (lab == NULL) {
        printf("Erreur ouverture fichier \n");
    }
    else {
        while(fgets(ligne,n,lab) !=NULL){
            laLigne=strtok(ligne," ");
            if (laLigne==NULL){
                test++;
            }
            while (laLigne != NULL){
                labyrinthe[i][j]=atoi(laLigne);
                laLigne = strtok(NULL, " ");
                nbColonnesLues++;
                j++;
            }
            nbColonnesLues=0;
            nbLignesLues++;
            i++;
            j=0;
        }
        fclose(lab);
    }
}


Arbre creerArbre(int** labyrinthe, int x, int y, int hauteur, int largeur, int nbCheckpoints){
    Arbre** noeudsDejaVus = initNoeudsDejaVus(hauteur, largeur);
    return creerArbreCache(labyrinthe, x, y, hauteur, largeur, noeudsDejaVus, nbCheckpoints);
}


Arbre** initNoeudsDejaVus(int hauteur, int largeur){
    Arbre** noeudsDejaVus = malloc(largeur * sizeof(Arbre*));
    for (int i = 0; i < largeur; i++) {
        noeudsDejaVus[i] = malloc(hauteur * sizeof(Arbre));
        for (int j = 0; j < hauteur; j++) {
            noeudsDejaVus[i][j] = NULL;
        }
    }
    return noeudsDejaVus;
}


Arbre creerArbreCache(int** labyrinthe, int x, int y, int hauteur, int largeur, Arbre** noeudsDejaVus, int nbCheckpoints){
    Arbre arbre = initArbre(x, y, labyrinthe[y][x], nbCheckpoints);
    noeudsDejaVus[x][y] = arbre;

    if (x - 1 >= 0 && labyrinthe[y][x - 1] != 2) {
        if (arbre->gauche == NULL) {
            arbre->gauche = noeudsDejaVus[x - 1][y];
            if (arbre->gauche != NULL) {
                arbre->gauche->droite = arbre;
            }
        }
        if (arbre->gauche == NULL) {
            arbre->gauche = creerArbreCache(labyrinthe, x - 1, y, hauteur, largeur, noeudsDejaVus, nbCheckpoints);
        }
    }
    if (x + 1 < largeur && labyrinthe[y][x + 1] != 2) {
        if (arbre->droite == NULL) {
            arbre->droite = noeudsDejaVus[x + 1][y];
            if (arbre->droite != NULL) {
                arbre->droite->gauche = arbre;
            }
        }
        if (arbre->droite == NULL) {
            arbre->droite = creerArbreCache(labyrinthe, x + 1, y, hauteur, largeur, noeudsDejaVus, nbCheckpoints);
        }
    }
    if (y - 1 >= 0 && labyrinthe[y - 1][x] != 2) {
        if (arbre->haut == NULL) {
            arbre->haut = noeudsDejaVus[x][y - 1];
            if (arbre->haut != NULL) {
                arbre->haut->bas = arbre;
            }
        }
        if (arbre->haut == NULL) {
            arbre->haut = creerArbreCache(labyrinthe, x, y - 1, hauteur, largeur, noeudsDejaVus, nbCheckpoints);
        }
    }
    if (y + 1 < hauteur && labyrinthe[y + 1][x] != 2) {
        if (arbre->bas == NULL) {
            arbre->bas = noeudsDejaVus[x][y + 1];
            if (arbre->bas != NULL) {
                arbre->bas->haut = arbre;
            }
        }
        if (arbre->bas == NULL) {
            arbre->bas = creerArbreCache(labyrinthe, x, y + 1, hauteur, largeur, noeudsDejaVus, nbCheckpoints);
        }
    }
    return arbre;
}


Arbre initArbre(int x, int y, int valeur, int nbCheckpoints){
    Arbre arbre = malloc(sizeof(Noeud));
    arbre->gauche = NULL;
    arbre->droite = NULL;
    arbre->haut = NULL;
    arbre->bas = NULL;
    arbre->distances = malloc(nbCheckpoints * sizeof(int));
    for (int i = 0; i < nbCheckpoints; i++) {
        arbre->distances[i] = 999999;
    }
    arbre->x = x;
    arbre->y = y;
    arbre->valeur = valeur;
    return arbre;
}


void afficherArbre(Arbre arbre, int hauteur, int largeur){
    if (arbre != NULL){
        int** dejaVus = initDejaVus(hauteur, largeur);
        afficherArbreCache(arbre, dejaVus);
    }
}


void afficherArbreCache(Arbre arbre, int** dejaVus) {
    if (arbre == NULL) {
        return;
    }
    if (dejaVus[arbre->x][arbre->y]) {
        return;
    }
    dejaVus[arbre->x][arbre->y] = 1;
  
    printf("Node content: %d distance : %d (%d, %d) ", arbre->valeur, (arbre->distances == NULL) ? 0 : arbre->distances[arbre->nbCheckpoints - 1], arbre->x, arbre->y);
    if (arbre->gauche != NULL) {
        printf("g(%d, %d) ", arbre->gauche->x, arbre->gauche->y);
    } 
    if (arbre->droite != NULL) {
        printf("d(%d, %d) ", arbre->droite->x, arbre->droite->y);
    }
    if (arbre->haut != NULL) {
        printf("h(%d, %d) ", arbre->haut->x, arbre->haut->y);
    }
    if (arbre->bas != NULL) {
        printf("b(%d, %d) ", arbre->bas->x, arbre->bas->y);
    }
    printf("\n");
    afficherArbreCache(arbre->gauche, dejaVus);
    afficherArbreCache(arbre->droite, dejaVus);
    afficherArbreCache(arbre->haut, dejaVus);
    afficherArbreCache(arbre->bas, dejaVus);
}


int** initDejaVus(int hauteur, int largeur){
    int** dejaVus = malloc(largeur * sizeof(int*));
    for (int i = 0; i < largeur; i++) {
        dejaVus[i] = malloc(hauteur * sizeof(int));
        for (int j = 0; j < hauteur; j++) {
            dejaVus[i][j] = 0;
        }
    }
    return dejaVus;
}


void calculDistances(Arbre arbre, int hauteur, int largeur, int** coordsCheckpoints, int nbCheckpoints){
    int** dejaVus = initDejaVus(hauteur, largeur);
    for (int i = 0; i < nbCheckpoints; i++){
        calcDistance(trouverCheckpoints(coordsCheckpoints[i], arbre, dejaVus), i, hauteur, largeur);
    }
}


Arbre trouverCheckpoints(int* coordsCheckpoints, Arbre arbre, int** dejaVus){
    if (arbre == NULL){
        return NULL;
    }
    if (dejaVus[arbre->x][arbre->y]){
        return NULL;
    }
    dejaVus[arbre->x][arbre->y] = 1;

    if (arbre->x == coordsCheckpoints[0] && arbre->y == coordsCheckpoints[1]){
        return arbre;
    }
    Arbre res = trouverCheckpoints(coordsCheckpoints, arbre->gauche, dejaVus);
    res = (res == NULL) ? trouverCheckpoints(coordsCheckpoints, arbre->droite, dejaVus) : res;
    res = (res == NULL) ? trouverCheckpoints(coordsCheckpoints, arbre->haut, dejaVus) : res;
    res = (res == NULL) ? trouverCheckpoints(coordsCheckpoints, arbre->bas, dejaVus) : res;
    return res;
}


void calcDistance(Arbre arbre, int numCheckpoint, int hauteur, int largeur){
    int** dejaVus = initDejaVus(hauteur, largeur);
    arbre->distances[numCheckpoint] = 0;
    calcDistanceCache(arbre, numCheckpoint, dejaVus);
}


void calcDistanceCache(Arbre arbre, int numCheckpoint, int** dejaVus){
    if (arbre == NULL){
        return;
    }
    if (dejaVus[arbre->x][arbre->y]){
        return;
    }
    dejaVus[arbre->x][arbre->y] = 1;

    if (arbre->gauche != NULL && arbre->gauche->distances[numCheckpoint] > (arbre->distances[numCheckpoint] + 1)) {
        arbre->gauche->distances[numCheckpoint] = arbre->distances[numCheckpoint] + 1;
    } 
    if (arbre->droite != NULL && arbre->droite->distances[numCheckpoint] > (arbre->distances[numCheckpoint] + 1)) {
        arbre->droite->distances[numCheckpoint] = arbre->distances[numCheckpoint] + 1;
    }
    if (arbre->haut != NULL && arbre->haut->distances[numCheckpoint] > (arbre->distances[numCheckpoint] + 1)) {
        arbre->haut->distances[numCheckpoint] = arbre->distances[numCheckpoint] + 1;
    }
    if (arbre->bas != NULL && arbre->bas->distances[numCheckpoint] > (arbre->distances[numCheckpoint] + 1)) {
        arbre->bas->distances[numCheckpoint] = arbre->distances[numCheckpoint] + 1;
    }
    calcDistanceCache(arbre->gauche, numCheckpoint, dejaVus);
    calcDistanceCache(arbre->droite, numCheckpoint, dejaVus);
    calcDistanceCache(arbre->haut, numCheckpoint, dejaVus);
    calcDistanceCache(arbre->bas, numCheckpoint, dejaVus);
}


int** fCoordsCheckpoints(int numLab){
    switch (numLab){
        case 0:
            return {{6, 1}};
        case 1:
            return {{1, 3}};
        case 2:
            return {{3, 3}};
        case 3:
            return {{1, 5}};
        case 4:
            return {{3, 5}, {5, 9}};
        case 5:
            return {{3, 7}};
        case 6:
            return {{9, 9}, {1, 15}};
        case 7:
            return {{5, 6}, {}}
    }
}