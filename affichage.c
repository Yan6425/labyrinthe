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
                printf("  ");
            }
            else if (labyrinthe[i][j]==2){
                printf("⬛");
            }
            else if ((joueur->x==i) && (joueur->y==j) && (labyrinthe[i][j]!=5)){
                printf("🦥");
            }
            else if (labyrinthe[i][j]==3){
                printf("👓");
            }
            else if (labyrinthe[i][j]==4){
                printf("☕");
            }
            else if (labyrinthe[i][j]==5){
                if (verifierAvion(joueur) && (joueur->x==i) && (joueur->y==j)){
                    printf("🛩️ ");
                }
                else {
                    printf("🕳️ ");
                }
            }
            else if (labyrinthe[i][j]==6){
                printf("💤");
            }
            else if (labyrinthe[i][j]==7){
                printf("🛩️ ");
            }
            else if (labyrinthe[i][j]==8){
                printf("🍺");
            }
            else if (labyrinthe[i][j]==9){
                printf("🗺️ ");
            }
            else if (labyrinthe[i][j]==10){
                printf("🧪 ");
            }
            else if (labyrinthe[i][j]==0){
                printf("🛏️ ");
            }
            else if (labyrinthe[i][j]==1){
                printf("  ");
            }
        }
        printf("\n\r");
    }
}

void afficherMap(int** labyrinthe,int hauteur, int largeur){
    printf("\x1b[2J\x1b[H");
    printf("\n\r");
    for (int i=0;i<hauteur;i++){
        for (int j=0;j<largeur;j++){
            if (labyrinthe[i][j]==2){
                printf("⬛");
            }
            else if (labyrinthe[i][j]==0){
                printf("🛏️ ");
            }
            else {
                printf("  ");
            }
        }
    printf("\n\r");
    }
}

void afficherVie(Joueur j){
    printf("Energie : ");
    for (int i=0;i<j->vie;i++){
        printf("🔋");
    }
}

void afficherSomnifere(Joueur j,int n){
    printf("\n\rFlash s'endort : [");
    for (int i=0;i<n;i++){
        printf("🫧");
    }
    for (int i=n;i<5;i++){
        printf("  ");
    }
    printf("]\n");
}

void afficherNiveau(int n){
    if (n<10){
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐ Niveau %d ▌\n\r",n);
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀");
    }
    else {
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐ Niveau %d ▌\n\r",n);
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀");
    }
}

void afficherMort(int n,int** labyrinthe, int hauteur, int largeur, Joueur j,int som){
    printf("\x1b[2J\x1b[H");
    afficherNiveau(n);
    afficherLabyrinthe(labyrinthe,hauteur,largeur,j);
    afficherVie(j);
    if (labyrinthe[j->x][j->y]==5){
        printf("\n\rVous êtes mort ! Pour réessayer appuyer sur entrée !");
    }
    else if (j->somnifere<=0){
        afficherSomnifere(j,som);
        printf("\n\rVous vous êtes endormi ! Pour réessayer appuyer sur entrée !");
    }
    else {
        printf("\n\rVous vous êtes endormi ! Pour réessayer appuyer sur entrée !");
    }
}

void afficherVictoire(int n,int** labyrinthe, int hauteur, int largeur, Joueur j){
    printf("\x1b[2J\x1b[H");
    afficherNiveau(n);
    afficherLabyrinthe(labyrinthe,hauteur,largeur,j);
    printf("Labyrinthe fini ! Appuyez sur entrée pour continuer !");
}