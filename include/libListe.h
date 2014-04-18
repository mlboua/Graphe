/*
*
*Auteur: Coulibaly Sidiki, David Esale, Alexi
*
*/
#ifndef LIBLISTE_H_INCLUDED
#define LIBLISTE_H_INCLUDED
typedef struct typVoisin{
	int voisin;
	double poidsVoisin;
	struct typVoisin* voisinSuivant;
}typVoisin;

typedef typVoisin* listeChainee;
typedef listeChainee* listeVoisin;

listeChainee ajouterDebut(listeChainee l,int val,double poids);

listeChainee ajouterFin(listeChainee v,int val,double poids);

void afficherListe(listeChainee l);

void ecrireListe(listeChainee l, const char* nomFichier);

int elementExiste(listeChainee l, int voisin, double poids);

int estVide(listeChainee l);

listeChainee supprimerListe(listeChainee v);

int nombreElements(listeChainee l);

listeChainee supprimerElement(listeChainee l,int val,double poids);

#endif
