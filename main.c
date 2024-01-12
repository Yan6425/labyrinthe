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
    debut();
    const char* nomFichier=labAleatoire();
    dimensionsLab(nomFichier,&hauteur,&largeur);
    j=malloc(1*sizeof(Joueur));
    j=creerJoueur(j);
    int** labyrinthe;
    labyrinthe=allouerLabyrinthe(hauteur,largeur);
    initialiserLabyrinthe(labyrinthe,hauteur,largeur);
    lireTXT(nomFichier,labyrinthe);
    deplacement(labyrinthe,j,hauteur,largeur);
    return 0;
}