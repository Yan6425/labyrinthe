#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>
#include <time.h>

const char* labAleatoire(){
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
    srand(time(NULL));
    return labyrinthe[rand()%6];
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
    for (int x=0;x<n;x++){
        for (int y=0;y<N;y++){
            labyrinthe[x][y]=0;
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


void creerArbre(Arbre arbre, int** labyrinthe, int x, int y, int hauteur, int largeur){
    Arbre** noeudsDejaVus = malloc(largeur * sizeof(Arbre*));
    initNoeudsDejaVus(noeudsDejaVus, hauteur, largeur);
    creerArbreCache(arbre, labyrinthe, x, y, hauteur, largeur, noeudsDejaVus);
}


void creerArbreCache(Arbre arbre, int** labyrinthe, int x, int y, int hauteur, int largeur, Arbre** noeudsDejaVus){
    printf("appel x : %d, y : %d\n", x, y);
    arbre->x = x;
    arbre->y = y;
    arbre->valeur = labyrinthe[y][x];
    noeudsDejaVus[x][y] = arbre;

    if (x - 1 >= 0 && labyrinthe[y][x - 1] != 2) {
        printf("gauche\n");
        if (arbre->gauche == NULL) {
            arbre->gauche = noeudsDejaVus[x - 1][y];
            if (arbre->gauche != NULL) {
                arbre->gauche->droite = arbre;
            }
        }
        if (arbre->gauche == NULL) {
            arbre->gauche = malloc(sizeof(Noeud));
            arbre->gauche->droite = arbre;
            creerArbreCache(arbre->gauche, labyrinthe, x - 1, y, hauteur, largeur, noeudsDejaVus);
        }
    }
    if (x + 1 < largeur && labyrinthe[y][x + 1] != 2) {
        printf("droite\n");
        if (arbre->droite == NULL) {
            arbre->droite = noeudsDejaVus[x + 1][y];
            if (arbre->droite != NULL) {
                arbre->droite->gauche = arbre;
            }
        }
        if (arbre->droite == NULL) {
            arbre->droite = malloc(sizeof(Noeud));
            arbre->droite->gauche = arbre;
            creerArbreCache(arbre->droite, labyrinthe, x + 1, y, hauteur, largeur, noeudsDejaVus);
        }
    }
    if (y - 1 >= 0 && labyrinthe[y - 1][x] != 2) {
        printf("haut\n");
        if (arbre->haut == NULL) {
            arbre->haut = noeudsDejaVus[x][y - 1];
            if (arbre->haut != NULL) {
                arbre->haut->bas = arbre;
            }
        }
        if (arbre->haut == NULL) {
            arbre->haut = malloc(sizeof(Noeud));
            arbre->haut->bas = arbre;
            creerArbreCache(arbre->haut, labyrinthe, x, y - 1, hauteur, largeur, noeudsDejaVus);
        }
    }
    if (y + 1 < hauteur && labyrinthe[y + 1][x] != 2) {
        printf("bas\n");
        if (arbre->bas == NULL) {
            arbre->bas = noeudsDejaVus[x][y + 1];
            if (arbre->bas != NULL) {
                arbre->bas->haut = arbre;
            }
        }
        if (arbre->bas == NULL) {
            arbre->bas = malloc(sizeof(Noeud));
            arbre->bas->haut = arbre;
            creerArbreCache(arbre->bas, labyrinthe, x, y + 1, hauteur, largeur, noeudsDejaVus);
        }
    }
}


void initNoeudsDejaVus(Arbre** noeudsDejaVus, int hauteur, int largeur){
    for (int i = 0; i < largeur; i++) {
        noeudsDejaVus[i] = malloc(hauteur * sizeof(Arbre));
        for (int j = 0; j < hauteur; j++) {
            noeudsDejaVus[i][j] = NULL;
        }
    }
}


void initDejaVus(int** dejaVus, int hauteur, int largeur){
    for (int i = 0; i < largeur; i++) {
        dejaVus[i] = malloc(hauteur * sizeof(int));
        for (int j = 0; j < hauteur; j++) {
            dejaVus[i][j] = 0;
        }
    }
}


void afficherArbre(Arbre arbre, int** dejaVus) {
    if (arbre == NULL) {
        return;
    }
    if (dejaVus[arbre->x][arbre->y]) {
        return;
    }
    dejaVus[arbre->x][arbre->y] = 1;
    printf("Node content: %d (%d, %d) ", arbre->valeur, arbre->x, arbre->y);
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
    if (arbre->gauche != NULL) {
        afficherArbre(arbre->gauche, dejaVus);
    } 
    if (arbre->droite != NULL) {
        afficherArbre(arbre->droite, dejaVus);
    }
    if (arbre->haut != NULL) {
        afficherArbre(arbre->haut, dejaVus);
    }
    if (arbre->bas != NULL) {
        afficherArbre(arbre->bas, dejaVus);
    }
}