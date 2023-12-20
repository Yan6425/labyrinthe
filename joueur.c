#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

Joueur creerJoueur(Joueur j){
    j->x=1;
    j->y=1;
    j->vie=3;
    j->bouclier=0;
    j->vision=2;
    return j;
}

int caseLibre(int** labyrinthe,int x, int y){
    if (labyrinthe[x][y]==2){
        return 0;
    }
    else{
        return 1;
    }
}

int victoire(int** labyrinthe,Joueur j){
    if (labyrinthe[j->x][j->y]==0){
        return 1;
    }
    else {
        return 0;
    }
}

void emptyBuffer() {
  char c;
  while (((c = getchar()) != '\n') && (c != EOF));
}

Joueur haut(Joueur j){
    (j->x)++;
    return j;
}

Joueur bas(Joueur j){
    (j->x)--;
    return j;
}

Joueur droite(Joueur j){
    (j->y)++;
    return j;
}

Joueur gauche(Joueur j){
    (j->y)--;
    return j;
}

Joueur degat(Joueur j,int damage){
    j->vie=(j->vie)-damage;
    return j;
}

Joueur soin(Joueur j, int heal){
    j->vie=(j->vie)+heal;
    return j;
}

Joueur bouclierPlus(Joueur j, int shield){
    j->bouclier=(j->bouclier)+shield;
    return j;
}

Joueur bouclierMoins(Joueur j, int shield){
    j->bouclier=(j->bouclier)-shield;
    return j;
}

int estMort(Joueur j){
    if (j->vie==0){
        return 1;
    }
    else {
        return 0;
    }
}

int valeurCase(int** labyrinthe,Joueur j){
    return labyrinthe[j->x][j->y]; 
}

void actionCase(int** labyrinthe, Joueur j){
    int cellule=valeurCase(labyrinthe,j);
    switch(cellule){
        case 6: 
            if(j->vie < 3){
                j->vie=(j->vie)+1;
                retirerPotion(valeurCase(labyrinthe));
            }
            break;
        case 3:
            j->vision=(j->vision)+2;
        case 1:
            break;
    }
}

int deplacement(int** labyrinthe,Joueur j){
    struct termios tty_opts_backup, tty_opts_raw;
    char c;
    int pastermine=1;//par défaut on le met à vrai

    /* on est obligé d'appuyer sur la touche entrée */
    c =getchar();
    printf("on est obligé d'appuyer sur entrée : vous avez écrit %d \n", c);

    /* ON VIDE LE BUFFER*/
    emptyBuffer();

    // Back up current TTY settings
    tcgetattr(STDIN_FILENO, &tty_opts_backup);


    // Change TTY settings mode
    cfmakeraw(&tty_opts_raw);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);

    while (pastermine){
        printf("\x1b[2J\x1b[H");
        afficherLabyrinthe(labyrinthe,3,7,j);
        afficherVie(j); 
        // ZQSD
        c =getchar();
        switch(c){
            case 27:
                c=getchar();
                if (c=='['){
                    c=getchar();
                    int a=j->x;
                    int b=j->y;
                    switch(c){
                        case 'A':
                            if (caseLibre(labyrinthe,a-1,b)){
                                haut(j);
                            }
                            else{
                                degat(j,1);
                            }
                            break;
                        case 'B':
                            if (caseLibre(labyrinthe,a+1,b)){
                                bas(j);
                            }
                            else{
                                degat(j,1);
                            }
                            break;
                        case 'C':
                            if (caseLibre(labyrinthe,a,b+1)){
                                droite(j);
                            }
                            else{
                                degat(j,1);
                            }
                            break;
                        case 'D':
                            if (caseLibre(labyrinthe,a,b-1)){
                                gauche(j);
                            }
                            else{
                                degat(j,1);
                            }
                            break;
                        default :
                            break;
                    }
                }
                break;
            case 97:
                pastermine=0;
                break;
            default:
                break;
        }
        actionCase(labyrinthe,j);
        if (estMort(j)){
            pastermine=0;
            printf("\n\rTu es mort !");
        }
        if (victoire(labyrinthe,j)){
            printf("\x1b[2J\x1b[H");
            pastermine=0;
            afficherLabyrinthe(labyrinthe,3,7,j);
            printf("Win");
        }
    }


    /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
    // Restore previous TTY settings
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);

    printf("\n");
    return 0;
}