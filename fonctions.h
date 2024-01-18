#ifndef __fonctions_H_
#define __fonctions_H_


// joueur.c
Joueur creerJoueur(Joueur j);
int verifierAvion(Joueur j);
int caseLibre(Joueur j, char* sens);
int victoire(int** labyrinthe,Joueur j);
void emptyBuffer();
Joueur haut(Joueur j);
Joueur bas(Joueur j);
Joueur droite(Joueur j);
Joueur gauche(Joueur j);
Joueur degat(Joueur j,int damage);
Joueur soin(Joueur j, int heal);
Joueur avionPlus(Joueur j, int shield);
Joueur avionMoins(Joueur j, int shield);
int estMort(Joueur j);
int valeurCase(int** labyrinthe,Joueur j);
void retirerPotion(int** labyrinthe, Joueur j);
void actionCase(int** labyrinthe,Joueur j);
int deplacement(Arbre arbre, int** labyrinthe,int n,Joueur j,int hauteur, int largeur,int* fin);


// affichage.c
void debut();
void afficherLabyrinthe(int** labyrinthe,int a, int b, Joueur u);
void afficherVie(Joueur j);
void afficherNiveau(int n);


// plateau.c
const char* nomLab(int n);
void dimensionsLab(const char* nomFichier,int* hauteur,int* largeur);
int** allouerLabyrinthe(int n, int N);
void initialiserLabyrinthe(int** labyrinthe, int n, int N);
void lireTXT(const char* nomFichier, int** labyrinthe);
void creerArbre(Arbre* arbre, int** labyrinthe, int x, int y, int hauteur, int largeur);
void creerArbreCache(Arbre* arbre, int** labyrinthe, int x, int y, int hauteur, int largeur, Arbre** noeudsDejaVus);
Arbre** initNoeudsDejaVus(int hauteur, int largeur);
int** initDejaVus(int hauteur, int largeur);
void initArbre(Arbre* arbre);
void afficherArbre(Arbre arbre, int hauteur, int largeur);
void afficherArbreCache(Arbre arbre, int** dejaVus);


#endif