#ifndef __fonctions_H_
#define __fonctions_H_


// joueur.c
Joueur creerJoueur(Joueur j);
int caseLibre(int** labyrinthe,int x, int y);
int victoire(int** labyrinthe,Joueur j);
void emptyBuffer();
Joueur haut(Joueur j);
Joueur bas(Joueur j);
Joueur droite(Joueur j);
Joueur gauche(Joueur j);
Joueur degat(Joueur j,int damage);
Joueur soin(Joueur j, int heal);
Joueur bouclierPlus(Joueur j, int shield);
Joueur bouclierMoins(Joueur j, int shield);
int estMort(Joueur j);
int valeurCase(int** labyrinthe,Joueur j);
void retirerPotion(int** labyrinthe, Joueur j);
void actionCase(int** labyrinthe,Joueur j);
int deplacement(int** labyrinthe,Joueur j);


// affichage.c
void afficherLabyrinthe(int** labyrinthe,int a, int b, Joueur u);
void afficherVie(Joueur j);


// plateau.c
int** allouerLabyrinthe(int n, int N);
void initialiserLabyrinthe(int** labyrinthe, int n, int N);
void lireTXT(int** labyrinthe);


#endif