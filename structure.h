#ifndef __structure_H_
#define __structure_H_


// joueur.c
typedef struct humain{
    int x;
    int y;
    int vie;
    int bouclier;
    int vision;
}humain;
typedef humain* Joueur;


// affichage.c


// plateau.c
typedef struct noeud{
    int x;
    int y;
    int valeur;
    int distance;
    struct noeud* haut;
    struct noeud* bas;
    struct noeud* gauche;
    struct noeud* droite;
} Noeud;
typedef Noeud* Arbre;


#endif