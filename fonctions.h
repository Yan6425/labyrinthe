#ifndef __fonctions_H_
#define __fonctions_H_


// joueur.c
joueur creerJoueur(joueur j);
int caseLibre(int** labyrinthe,int x, int y);
int victoire(int** labyrinthe,joueur j);
void emptyBuffer();
joueur haut(joueur j);
joueur bas(joueur j);
joueur droite(joueur j);
joueur gauche(joueur j);
joueur degat(joueur j,int damage);
joueur soin(joueur j, int heal);
joueur bouclierPlus(joueur j, int shield);
joueur bouclierMoins(joueur j, int shield);
int estMort(joueur j);
int valeurCase(int** labyrinthe,joueur j);
void retirerPotion(int cellule)
void actionCase(int** labyrinthe,joueur j);
int deplacement(int** labyrinthe,joueur j);


// affichage.c
void afficherLabyrinthe(int** labyrinthe,int a, int b, joueur u);
void afficherVie(joueur j);
void afficherVision(joueur j);


// plateau.c
int** allouerLabyrinthe(int n, int N);
void initialiserLabyrinthe(int** labyrinthe, int n, int N);
void lireTXT(int** labyrinthe);


#endif