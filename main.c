#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

int main(){
    Joueur j;
    j=malloc(1*sizeof(Joueur));
    j=creerJoueur(j);
    int** labyrinthe;
    labyrinthe=allouerLabyrinthe(11,11);
    initialiserLabyrinthe(labyrinthe,11,11);
    lireTXT(labyrinthe);
    afficherLabyrinthe(labyrinthe,11,11,j);
    deplacement(labyrinthe,j);
    return 0;
    return 0;
}