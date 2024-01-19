#ifndef __structure_H_
#define __structure_H_


// affichage.c


// plateau.c
typedef struct noeud{
    int x;
    int y;
    int valeur;
    int* distances;
    int nbCheckpoints;
    struct noeud* haut;
    struct noeud* bas;
    struct noeud* gauche;
    struct noeud* droite;
} Noeud;
typedef Noeud* Arbre;


// joueur.c
typedef struct humain{
    Arbre arbre;
    int x;
    int y;
    int vie;
    int avion;
    int vision;
    int ivre;
    int somnifere;
}humain;
typedef humain* Joueur;


#endif