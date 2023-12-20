#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

int main(){
    joueur j;
    j=malloc(1*sizeof(joueur));
    j=creerJoueur(j);
    int** labyrinthe;
    labyrinthe=allouerLabyrinthe(3,7);
    initialiserLabyrinthe(labyrinthe,3,7);
    lireTXT(labyrinthe);
    afficherLabyrinthe(labyrinthe,3,7,j);
    deplacement(labyrinthe,j);
    return 0;
    return 0;
}