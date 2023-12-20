#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

void afficherLabyrinthe(int** labyrinthe,int a, int b, joueur u){
    printf("\n\r");
    for (int i=0;i<a;i++){
        for (int j=0; j<b; j++){
            if (labyrinthe[i][j]==-1){
                printf("█");
            }
            else if ((u->x==i) && (u->y==j)){
                printf("\033[1;33m☺\033[0m");
            }
            else if (labyrinthe[i][j]==1){
                printf("[");
            }
            else if (labyrinthe[i][j]==2){
                printf("]");
            }
            else if (labyrinthe[i][j]==0){
                printf(" ");
            }
        }
        printf("\n\r");
    }
}

void afficherVie(joueur j){
    printf("Vie : ");
    printf("\033[1;31m");
    for (int i=0;i<j->vie;i++){
        printf("♥");
    }
    printf("\033[0m");
}