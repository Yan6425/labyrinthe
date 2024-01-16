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
    j->sens=1;
    return j;
}

int verifierBouclier(Joueur j){
    if(j->bouclier>0){
        return 1;
    }
    else{
        return 0;
    }
}

int caseLibre(int** labyrinthe,int hauteur, int largeur, int x, int y,Joueur j){
    if ((x>=0) && (y>=0) && (x<hauteur) && (y<largeur)){
        if (labyrinthe[x][y]==2){
            return 0;
        }
        else if(labyrinthe[x][y]==5){
            if(verifierBouclier(j)){
                j->bouclier=0;
            }
            else{
                j->vie=0;
            }
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        return 0;
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
    (j->x)--;
    return j;
}

Joueur bas(Joueur j){
    (j->x)++;
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
    if(j->bouclier>0){
        j->bouclier=0;
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

Joueur bouclierPlus(Joueur j, int shield){
    j->bouclier=(j->bouclier)+shield;
    return j;
}

Joueur bouclierMoins(Joueur j, int shield){
    j->bouclier=(j->bouclier)-shield;
    return j;
}

int estMort(Joueur j){
    if (j->vie<=0){
        return 1;
    }
    else {
        return 0;
    }
}

int valeurCase(int** labyrinthe,Joueur j){
    return labyrinthe[j->x][j->y]; 
}

void retirerPotion(int** labyrinthe, Joueur j){
    labyrinthe[j->x][j->y]=1;  
}

void actionCase(int** labyrinthe, Joueur j){
    int cellule=valeurCase(labyrinthe,j);
    switch(cellule){
        case 4: 
            if(j->vie < 3){
                j->vie=(j->vie)+1;
                retirerPotion(labyrinthe,j);
            }
            
            break;
        case 3:
            j->vision=(j->vision)+2;
            retirerPotion(labyrinthe,j); 
        case 6:
            if(verifierBouclier(j)){
                j->bouclier=0;
            }
            else{
                j->vie=j->vie-1;
            }
            break;
        case 7:
            j->bouclier=j->bouclier+4;
            break;
        case 8:
            j->sens=0;
            break;
        case 1:
            break;
        default : 
            break;
    }
}

int deplacement(int** labyrinthe,int n,Joueur j,int hauteur, int largeur){
    struct termios tty_opts_backup, tty_opts_raw;
    char c;
    int pastermine=1;//par défaut on le met à vrai

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
                            if(j->sens==0){
                                if(caseLibre(labyrinthe,hauteur,largeur,a+1,b,j)){
                                    bas(j);
                                }
                            }
                            else if(caseLibre(labyrinthe,hauteur,largeur,a-1,b,j)){
                                haut(j);
                            }
                            break;
                        case 'B':
                            if(j->sens==0){
                                if (caseLibre(labyrinthe,hauteur,largeur,a-1,b,j)){
                                    haut(j);
                                } 
                            }
                            else if(caseLibre(labyrinthe,hauteur,largeur,a+1,b,j)){
                                bas(j);
                            }
                            break;
                        case 'C':
                            if(j->sens==0){
                               if (caseLibre(labyrinthe,hauteur,largeur,a,b-1,j)){
                                    gauche(j);
                                } 
                            }
                            else if (caseLibre(labyrinthe,hauteur,largeur,a,b+1,j)){
                                droite(j);
                            }
                            break;
                        case 'D':
                            if(j->sens==0){
                               if (caseLibre(labyrinthe,hauteur,largeur,a,b+1,j)){
                                    droite(j);
                                } 
                            }
                            else if (caseLibre(labyrinthe,hauteur,largeur,a,b-1,j)){
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
                break;
            default:
                break;
        }
        actionCase(labyrinthe,j);
        if (estMort(j)){
            printf("\x1b[2J\x1b[H");
            afficherNiveau(n);
            afficherLabyrinthe(labyrinthe,hauteur,largeur,j);
            afficherVie(j);
            sleep(1);
            j=creerJoueur(j);
        }
        if (victoire(labyrinthe,j)){
            printf("\x1b[2J\x1b[H");
            pastermine=0;
            afficherNiveau(n);
            afficherLabyrinthe(labyrinthe,hauteur,largeur,j);
            printf("Labyrinthe fini ! Appuyez sur entrée pour continuer !");
        }
    }


    /* NE PAS OUBLIER : sinon on ne peut plus écrire dans le terminal */
    // Restore previous TTY settings
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);

    printf("\n");
    return 0;
}