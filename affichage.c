#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

void afficherLabyrinthe(int** labyrinthe,int hauteur, int largeur, Joueur joueur){
    printf("\n\r");
    for (int i=(joueur->x)-(joueur->vision);i<=(joueur->x)+(joueur->vision);i++){
        for (int j=(joueur->y)-(joueur->vision); j<=(joueur->y)+(joueur->vision); j++){
            if ((i<0) || (j<0) || (i>=hauteur) || (j>=largeur)){
                printf(" ");
            }
            else if (labyrinthe[i][j]==2){
                printf("█");
            }
            else if ((joueur->x==i) && (joueur->y==j)){
                printf("\033[1;33m☺\033[0m");
            }
            else if (labyrinthe[i][j]==4){
                printf("p");
            }
            else if (labyrinthe[i][j]==3){
                printf("v");
            }
            else if (labyrinthe[i][j]==0){
                printf("O");
            }
            else if (labyrinthe[i][j]==1){
                printf(" ");
            }
        }
        printf("\n\r");
    }
}

void afficherVie(Joueur j){
    printf("Vie : ");
    printf("\033[1;31m");
    for (int i=0;i<j->vie;i++){
        printf("♥");
    }
}