#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

void debut(){
    printf("\x1b[2J\x1b[H");
    printf("███████████████████████████\n");
    printf("█                         █\n");
    printf("█    Bienvenue dans le    █\n");
    printf("█    Jeu du Labyrinthe    █\n");
    printf("█                         █\n");
    printf("███████████████████████████\n");
    sleep(2);
    printf("\x1b[2J\x1b[H");
    printf("███████████████████████████████████████████████████\n");
    printf("█                                                 █\n");
    printf("█    Règles :                                     █\n");
    printf("█    -trouver le $ dans chacun des labyrinthes    █\n");
    printf("█    -10 labyrinthes à compléter                  █\n");
    printf("█    -utiliser les flèches pour se déplacer       █\n");
    printf("█                                                 █\n");
    printf("███████████████████████████████████████████████████\n");
    sleep(4);
    printf("\x1b[2J\x1b[H");
    printf("███████████████████████████████████████████████\n");
    printf("█                                             █\n");
    printf("█    Appuyez sur entrée pour lancer le jeu    █\n");
    printf("█                                             █\n");
    printf("███████████████████████████████████████████████\n");
}

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
            else if (labyrinthe[i][j]==6){
                printf("A");
            }
            else if (labyrinthe[i][j]==8){
                printf("I");
            }
            else if (labyrinthe[i][j]==0){
                printf("$");
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
    printf("\033[0m");
    for (int i=j->vie;i<3;i++){
        printf("♥");
    }
}