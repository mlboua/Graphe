/*
*
*Auteurs: Coulibaly Sidiki, David Esale, Alexi
*
*/
#ifndef LIBGRAPH_H_INCLUDED
#define LIBGRAPH_H_INCLUDED
#include "libListe.h"

typedef struct typeGraphe{
	int nbMaxSommets;
	listeChainee* listesAdjacences;
	int type;
}typeGraphe;

void creation(typeGraphe* graphe,int nbSommets, int type);
void insertionSommet(typeGraphe* g,int sommet);
void insertionArete(typeGraphe* g,int sommet,int voisin,double poids);
void supprimerSommet(typeGraphe* g,int sommet);
void supprimerArete(typeGraphe* g,int sommet,int voisin,double poids);
void affichage(typeGraphe* g);
int fichierExiste(char *nomfichier);
int sommetExiste(typeGraphe *g, int sommet);
int areteExiste(typeGraphe* g, int sommet, int voisin, double poids);
int lireEntier(FILE* fichier);
typeGraphe* lecture(const char* nomFichier);
void sauvegarde(typeGraphe* g, const char* nomFichier);
#endif
