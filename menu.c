#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

void afficherMenu(int positionMenu){
    if (positionMenu==1){
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐                         ▌\n\r");
        printf("▐         \e[1mStart\e[0m           ▌\n\r");
        printf("▐         Règles          ▌\n\r");
        printf("▐       Difficulté        ▌\n\r");
        printf("▐                         ▌\n\r");
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n\r");
    }
    else if (positionMenu==2){
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐                         ▌\n\r");
        printf("▐         Start           ▌\n\r");
        printf("▐         \e[1mRègles\e[0m          ▌\n\r");
        printf("▐       Difficulté        ▌\n\r");
        printf("▐                         ▌\n\r");
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n\r");
    }
    else{
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐                         ▌\n\r");
        printf("▐         Start           ▌\n\r");
        printf("▐         Règles          ▌\n\r");
        printf("▐       \e[1mDifficulté\e[0m        ▌\n\r");
        printf("▐                         ▌\n\r");
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n\r");
    }
}

void afficherRegles(){
    printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
    printf("▐                                               ▌\n\r");
    printf("▐   Règles :                                    ▌\n\r");
    printf("▐   -trouver le lit avant que le paresseux      ▌\n\r");
    printf("▐    ne s'endorme                               ▌\n\r");
    printf("▐   -10 labyrinthes à compléter                 ▌\n\r");
    printf("▐   -utiliser les flèches pour se déplacer      ▌\n\r");
    printf("▐                                               ▌\n\r");
    printf("▐                   \e[1mRetour\e[0m                      ▌\n\r");
    printf("▐                                               ▌\n\r");
    printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n\r");
}

void afficherDifficulte(int positionMenu){
    if (positionMenu==1){
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐                         ▌\n\r");
        printf("▐         \e[1mFacile\e[0m          ▌\n\r");
        printf("▐         Normal          ▌\n\r");
        printf("▐        Difficile        ▌\n\r");
        printf("▐                         ▌\n\r");
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n\r");
    }
    else if (positionMenu==2){
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐                         ▌\n\r");
        printf("▐         Facile          ▌\n\r");
        printf("▐         \e[1mNormal\e[0m          ▌\n\r");
        printf("▐        Difficile        ▌\n\r");
        printf("▐                         ▌\n\r");
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n\r");
    }
    else{
        printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n\r");
        printf("▐                         ▌\n\r");
        printf("▐         Facile          ▌\n\r");
        printf("▐         Normal          ▌\n\r");
        printf("▐        \e[1mDifficile\e[0m        ▌\n\r");
        printf("▐                         ▌\n\r");
        printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n\r");
    }
}

void debut(){
    printf("\x1b[2J\x1b[H");
    printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n");
    printf("▐                       ▌\n");
    printf("▐   Bienvenue dans le   ▌\n");
    printf("▐   Jeu du Labyrinthe   ▌\n");
    printf("▐                       ▌\n");
    printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n");
    sleep(2);
    printf("\x1b[2J\x1b[H");
    printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n");
    printf("▐                                           ▌\n");
    printf("▐  Appuyez sur entrée pour accéder au menu  ▌\n");
    printf("▐                                           ▌\n");
    printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n");
}

void affichageFinMenu(){
    printf("\x1b[2J\x1b[H");
    printf("🬞🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬭🬏\n");
    printf("▐                                           ▌\n");
    printf("▐  Appuyez sur entrée pour accéder au jeu   ▌\n");
    printf("▐                                           ▌\n");
    printf("🬁🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬂🬀\n");
}


void hautMenu(int* positionMenu){
    if (*positionMenu==1){
        *positionMenu=3;
    }
    else {
        *positionMenu=*positionMenu-1;
    }
}

void basMenu(int* positionMenu){
    if (*positionMenu==3){
        *positionMenu=1;
    }
    else {
        *positionMenu=*positionMenu+1;
    }
}

void entreeMenu(int* positionMenu,int* start,int* difficulte){
    switch(*start){
        case 0:
            if (*positionMenu==1){
                *start=1;
            }
            else if (*positionMenu==2){
                *start=2;
            }
            else{
                *start=3;
                *positionMenu=1;
            }
            break;
        case 2:
            *positionMenu=2;
            *start=0;
            break;
        case 3:
            if (*positionMenu==1){
                *difficulte=3;
            }
            else if (*positionMenu==2){
                *difficulte=2;
            }
            else {
                *difficulte=1;
            }
            *start=0;
            break;
        default:
            break;        
    }
}

void deplacementMenu(int* fin,int* difficulte){
    struct termios tty_opts_backup, tty_opts_raw;
    char c;
    int pastermine=1;//par défaut on le met à vrai
    int positionMenu=1;
    int start=0;
    debut();
    /* ON VIDE LE BUFFER*/
    emptyBuffer();

    // Back up current TTY settings
    tcgetattr(STDIN_FILENO, &tty_opts_backup);


    // Change TTY settings mode
    cfmakeraw(&tty_opts_raw);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);
    while (pastermine){
        printf("\x1b[2J\x1b[H");
        if(start==0){
            afficherMenu(positionMenu);
        }
        else if (start==2){
            afficherRegles();
        }
        else if (start==3) {
            afficherDifficulte(positionMenu);
        }    
        c =getchar();    
        switch(c){
            case 27:
                c=getchar();
                if (c=='['){
                    c=getchar();
                    switch(c){
                        case 'A':
                            if ((!start) || (start==3)){   
                                hautMenu(&positionMenu);
                                break;
                            }
                        case 'B':
                            if ((!start) || (start==3)){ 
                                basMenu(&positionMenu);
                                break;
                            }
                        case 'C':
                            entreeMenu(&positionMenu,&start,difficulte);
                            break;                        
                        default :
                            break;
                    }
                }
                break;
            case 97:
                pastermine=0;
                *fin=1;
                break;
            default:
                break;
        }
        if (start==1){
            pastermine=0;
        }
    }
    /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
    // Restore previous TTY settings
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);
    affichageFinMenu();
}