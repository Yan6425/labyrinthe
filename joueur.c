#include "structure.h"
#include "fonctions.h"
#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>
#include <string.h>

Joueur creerJoueur(Joueur j,int difficulte){
    j=malloc(sizeof(humain));
    j->arbre=NULL;
    j->x=1;
    j->y=1;
    j->vie=3;
    j->avion=0;
    j->vision=2;
    j->ivre=0;
    j->somnifere=1;
    return j;
}

int verifierAvion(Joueur j){
    if(j->avion>0){
        return 1;
    }
    else{
        return 0;
    }
}

int caseLibre(Joueur j, char* sens){
    switch (sens[0]){
        case 'g':
            return j->arbre->gauche != NULL;
            break;
        case 'd':
            return j->arbre->droite != NULL;
            break;
        case 'h':
            return j->arbre->haut != NULL;
            break;
        case 'b':
            return j->arbre->bas != NULL;
            break;
        default:
            return 0;
            break;
    }
}

int victoire(Joueur j){
    return !(j->arbre->valeur);
}

void emptyBuffer() {
  char c;
  while (((c = getchar()) != '\n') && (c != EOF));
}

void haut(Joueur j){
    if (j->arbre->haut != NULL){
        j->arbre = j->arbre->haut;
        j->y--;
    }
}

void bas(Joueur j){
    if (j->arbre->bas != NULL){
        j->arbre = j->arbre->bas;
        j->y++;
    }
}

void droite(Joueur j){
    if (j->arbre->droite != NULL){
        j->arbre = j->arbre->droite;
        j->x++;
    }
}

void gauche(Joueur j){
    if (j->arbre->gauche != NULL){
        j->arbre = j->arbre->gauche;
        j->x--;
    }
}

Joueur degat(Joueur j,int damage){
    if(j->avion>0){
        j->avion=0;
    }
    else{
        j->vie=(j->vie)-damage;
    }
    return j;
}

Joueur soin(Joueur j, int heal){
    j->vie=(j->vie)+heal;
    return j;
}

Joueur avionPlus(Joueur j, int shield){
    j->avion=(j->avion)+shield;
    return j;
}

Joueur avionMoins(Joueur j, int shield){
    j->avion=(j->avion)-shield;
    return j;
}

void somnifere(Joueur j,int* som){
    if ((j->somnifere)>1){
        afficherSomnifere(j,*som);
        *som=(*som)+1;
        if (j->somnifere>2){
            (j->somnifere)--;
        }
        else{
            j->somnifere=0;
        }
    }
}

int estMort(Joueur j){
    if ((j->vie<=0) || (j->somnifere<=0)){
        return 1;
    }
    else {
        return 0;
    }
}

int valeurCase(int** labyrinthe,Joueur j){
    return labyrinthe[j->y][j->x]; 
}

void retirerPotion(int** labyrinthe, Joueur j){
    labyrinthe[j->y][j->x]=1;
    j->arbre->valeur=1;
}

void actionCase(int** labyrinthe, Joueur j, int hauteur, int largeur){
    int cellule=j->arbre->valeur;
    switch(cellule){
        case 1:
            break;
        case 3:
            j->vision=(j->vision)+1;
            retirerPotion(labyrinthe,j); 
            break;
        case 4:
            if(j->vie < 3){
                j->vie=(j->vie)+1;
                retirerPotion(labyrinthe,j);
            }            
            break;
        case 5:
            if (!verifierAvion(j)){
                j->vie=0;
            }
            break;
        case 6:
            j->vie=j->vie-1;
            break;
        case 7:
            avionPlus(j,1);
            retirerPotion(labyrinthe,j);
            break;
        case 8:
            j->ivre=1;
            retirerPotion(labyrinthe,j);
            break;
        case 9:
            retirerPotion(labyrinthe,j);
            afficherMap(labyrinthe,hauteur,largeur);
            sleep(5);
            break;        
        case 10:
            retirerPotion(labyrinthe,j);
            (j->somnifere)=50;
            break;
        default : 
            break;
    }
}

int deplacement(int** labyrinthe,int n,Joueur j,int hauteur, int largeur,int* fin){
    struct termios tty_opts_backup, tty_opts_raw;
    char c;
    int pastermine=1;//par défaut on le met à vrai
    int som=1;

    /* ON VIDE LE BUFFER*/
    emptyBuffer();

    // Back up current TTY settings
    tcgetattr(STDIN_FILENO, &tty_opts_backup);


    // Change TTY settings mode
    cfmakeraw(&tty_opts_raw);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);

    while (pastermine){
        printf("\x1b[2J\x1b[H");
        afficherNiveau(n);
        afficherLabyrinthe(labyrinthe,hauteur,largeur,j);
        afficherVie(j); 
        somnifere(j,&som);
        c =getchar();
        switch(c){
            case 27:
                c=getchar();
                if (c=='['){
                    c=getchar();
                    switch(c){
                        case 'A':
                            if(j->ivre){
                                if(caseLibre(j, "bas")){
                                    bas(j);
                                }
                            }
                            else if(caseLibre(j, "haut")){
                                haut(j);
                            }
                            break;
                        case 'B':
                            if(j->ivre){
                                if (caseLibre(j, "haut")){
                                    haut(j);
                                } 
                            }
                            else if(caseLibre(j, "bas")){
                                bas(j);
                            }
                            break;
                        case 'C':
                            if(j->ivre){
                                if (caseLibre(j, "gauche")){
                                    gauche(j);
                                } 
                            }
                            else if (caseLibre(j, "droite")){
                                droite(j);
                            }
                            break;
                        case 'D':
                            if(j->ivre){
                                if (caseLibre(j,"droite")){
                                    droite(j);
                                } 
                            }
                            else if (caseLibre(j, "gauche")){
                                gauche(j);
                            }
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
        actionCase(labyrinthe, j, hauteur, largeur);
        if (estMort(j)){   
            afficherMort(n,labyrinthe,hauteur,largeur,j,som);
            sleep(1);
            pastermine=0;
            *fin=2;
        }
        if (victoire(j)){
            afficherVictoire(n,labyrinthe,hauteur,largeur,j);
            pastermine=0;
        }
    }


    /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
    // Restore previous TTY settings
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);

    printf("\n");
    return 0;
}


void parcoursAuto(Joueur j, int** checkpoints, int nbCheckpoints, int** labyrinthe, int hauteur, int largeur){
    for (int i=0; i<nbCheckpoints; i++){
        parcoursAutoCache(j, i, checkpoints[i][0], checkpoints[i][1], labyrinthe, hauteur, largeur);
    }
}

void parcoursAutoCache(Joueur j, int numCheckpoint, int x, int y, int** labyrinthe, int hauteur, int largeur){
    afficherLabyrinthe(labyrinthe, hauteur, largeur, j);
    if (j->x == x && j->y == y){
        return;
    }
    char* sens = (j->arbre->gauche->distances[numCheckpoint] < j->arbre->droite->distances[numCheckpoint]) ? "gauche" : "droite";
    sens = (j->arbre->droite->distances[numCheckpoint] < j->arbre->haut->distances[numCheckpoint]) ? "droite" : "haut";
    sens = (j->arbre->haut->distances[numCheckpoint] < j->arbre->bas->distances[numCheckpoint]) ? "haut" : "bas";
    switch (sens[0]){
        case 'g':
            gauche(j);
            break;
        case 'd':
            droite(j);
            break;
        case 'h':
            haut(j);
            break;
        case 'b':
            bas(j);
            break;
        default:
            break;
    }
    actionCase(labyrinthe, j, hauteur, largeur);
    parcoursAutoCache(j, numCheckpoint, x, y, labyrinthe, hauteur, largeur);
}