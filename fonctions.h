#ifndef __fonctions_H_
#define __fonctions_H_


// joueur.c

/* Crée le joueur et initialise ses paramètres*/
Joueur creerJoueur(Joueur j,int difficulte);

/* Vérifie si le joueur possède un avion */
int verifierAvion(Joueur j);

/* Vérifie si la case est libre */
int caseLibre(Joueur j, char* sens);

/* Vérifie si le joueur a gagné */
int victoire(int** labyrinthe,Joueur j);

/* Vide le buffer */
void emptyBuffer();

/* Déplacement vers le haut du joueur */
void haut(Joueur j);

/* Déplacement vers le bas du joueur */
void bas(Joueur j);

/* Déplacement vers la droite du joueur */
void droite(Joueur j);

/* Déplacement vers la gauche du joueur */
void gauche(Joueur j);

/* Enlève de l'énergie au joueur */
Joueur degat(Joueur j,int damage);

/* Rajoute de l'énergie au joueur */
Joueur soin(Joueur j, int heal);

/* Donne un avion au joueur */
Joueur avionPlus(Joueur j, int shield);

/* Enlève l'avion au joueur */
Joueur avionMoins(Joueur j, int shield);

/* Fonction qui gère l'éta de fatigue du joueur quand il a pris un somnifere */
void somnifere(Joueur j,int* som);

/* Vérifie si le joueur est mort */
int estMort(Joueur j);

/* Regarde la valeur de la case sur laquelle le joueur est */
int valeurCase(int** labyrinthe,Joueur j);

/* Retire les potions prise par le joueur sur le plateau */
void retirerPotion(int** labyrinthe, Joueur j);

/* Effectue l'action de la case sur laquelle le joueur est */
void actionCase(int** labyrinthe, Joueur j, int hauteur, int largeur);

/* Fonction principale du jeu qui permet d'utiliser les flèches du clavier pour se déplacer et d'autres touches (voir README) */
int deplacement(int** labyrinthe, int n, Joueur j, int hauteur, int largeur, int* fin);


// affichage.c

/* Affiche le labyrinthe */
void afficherLabyrinthe(int** labyrinthe,int a, int b, Joueur u);

/* Affiche le labyrinthe en entier quand on prend l'objet carte */
void afficherMap(int** labyrinthe,int hauteur, int largeur);

/* Affiche l'énergie restante du joueur */
void afficherVie(Joueur j);

/* Affiche la barre de sommeil après avoir pris l'objet somnifere */
void afficherSomnifere(Joueur j,int n);

/* Affiche le niveau actuel du jeu */
void afficherNiveau(int n);

/* Affiche le message de défaite en fonction de la manière dont le joueur a perdu */
void afficherMort(int n,int** labyrinthe, int hauteur, int largeur, Joueur j,int som);

/* Affiche le message de victoire à la fin de chaque labyrinthe */
void afficherVictoire(int n,int** labyrinthe, int hauteur, int largeur, Joueur j);

// plateau.c

/* Donne le nom du .txt du labyrinthe numéro n */
const char* nomLab(int n);

/* Donne les dimensions du labyrinthe mis en paramètres */
void dimensionsLab(const char* nomFichier,int* hauteur,int* largeur);

/* Alloue la matrice du labyrinthe */
int** allouerLabyrinthe(int n, int N);

/* Initialise la matrice du labyrinthe */
void initialiserLabyrinthe(int** labyrinthe, int n, int N);

/* Lis le fichier .txt pour le transférer dans la matrice */
void lireTXT(const char* nomFichier, int** labyrinthe);
Arbre initArbre(int x, int y, int valeur, int nbCheckpoints);
Arbre** initNoeudsDejaVus(int hauteur, int largeur);
int** initDejaVus(int hauteur, int largeur);
Arbre creerArbre(int** labyrinthe, int x, int y, int hauteur, int largeur, int nbCheckpoints);
Arbre creerArbreCache(int** labyrinthe, int x, int y, int hauteur, int largeur, Arbre** noeudsDejaVus, int nbCheckpoints);
void afficherArbre(Arbre arbre, int hauteur, int largeur);
void afficherArbreCache(Arbre arbre, int** dejaVus);
void calculDistances(Arbre arbre, int hauteur, int largeur, int** coordsCheckpoints, int nbCheckpoints);
Arbre trouverCheckpoints(int* coordsCheckpoints, Arbre arbre, int** dejaVus);
void calcDistance(Arbre arbre, int numCheckpoint, int hauteur, int largeur);
void calcDistanceCache(Arbre arbre, int numCheckpoint, int** dejaVus);
int** fCoordsCheckpoints(int numLab);
int nbCheckpoints(int numLab);


// menu.c

/* Affiche le menu du jeu */
void afficherMenu(int positionMenu);

/* Affiche les règles du jeu dans le menu */
void afficherRegles();

/* Affiche les difficultés dans le menu */
void afficherDifficulte(int positionMenu);

/* Affiche le message de lancement du jeu */
void debut();

/* Affiche le message de fin de menu */
void affichageFinMenu();

/* Déplacement dans le menu vers le haut */
void hautMenu(int* positionMenu);

/* Déplacement dans le menu vers le bas */
void basMenu(int* positionMenu);

/* Exécute l'action lorsque la flèche de droite est saisi dans le menu */
void entreeMenu(int* positionMenu,int* start,int* difficulte);

/* Fonction principale du menu qui permet d'utiliser les flèches pour se déplacer et d'autres touches (voir README) */
void deplacementMenu(int* fin,int* difficulte);

#endif