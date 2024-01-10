#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

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