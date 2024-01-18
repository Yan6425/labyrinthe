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
    int difficulte=2;
    int fin=0;
    deplacementMenu(&fin,&difficulte);
    if (fin==1){
        exit(fin);
    }
    for (int i=0;i<10;i++){
        const char* nomFichier=nomLab(i);
        dimensionsLab(nomFichier,&hauteur,&largeur);
        j=malloc(1*sizeof(Joueur));
        j=creerJoueur(j,difficulte);
        int** labyrinthe;
        labyrinthe=allouerLabyrinthe(hauteur,largeur);
        initialiserLabyrinthe(labyrinthe,hauteur,largeur);
        lireTXT(nomFichier,labyrinthe);
        j->arbre = creerArbre(labyrinthe, 1, 1, hauteur, largeur);
        deplacement(labyrinthe,i+1,j,hauteur,largeur,&fin);
        if (fin==1){
            break;
        }
        else if (fin==2){
            i--;
        }
        fin=0;
    }
    if (!fin){
        printf("\nBravo vous avez réussi !\n");
    }
    return 0;
}