#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>
#include <time.h>



int main(){
    Joueur j;
    int hauteur;
    int largeur;
    const char* nomFichier="lab/lab1.txt";
    dimensionsLab(nomFichier,&hauteur,&largeur);
    printf("%d %d",hauteur,largeur);
    j=malloc(1*sizeof(Joueur));
    j=creerJoueur(j);
    int** labyrinthe;
    labyrinthe=allouerLabyrinthe(hauteur,largeur);
    initialiserLabyrinthe(labyrinthe,hauteur,largeur);
    lireTXT(nomFichier,labyrinthe);
    afficherLabyrinthe(labyrinthe,hauteur,largeur,j);
    Arbre arbre = malloc(sizeof(Noeud));
    creerArbre(arbre, labyrinthe, 1, 1, hauteur, largeur);
    int** dejaVus = malloc(largeur * sizeof(int*));
    initDejaVus(dejaVus, hauteur, largeur);
    //afficherArbre(arbre, dejaVus);
    
    return 0;
}