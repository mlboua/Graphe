/*
*
*Auteurs: Coulibaly Sidiki, David Esale, Alexi
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/libListe.h"

/*
* Fonction : ajouterDebut
*
* Parametres : listeChainée, int, double
*
* Retour :listeChainée
*
* Description : cette fonction permet d'ajouter un élément au debut de la liste chainée.
*/
listeChainee ajouterDebut(listeChainee l,int val,double poids){
 	listeChainee tmp = malloc(sizeof(typVoisin));
	tmp->voisin = val;
	tmp->poidsVoisin = poids;	
	tmp->voisinSuivant = l;
	return tmp;
}

/*
* Fonction : ajouterFin
*
* Parametres : listeChainée, int, double
*
* Retour :listeChainée
*
* Description : cette fonction permet d'ajouter un élément à la fin de la liste chainée.
*/
listeChainee ajouterFin(listeChainee v,int val,double poids){
	listeChainee tmp = malloc(sizeof(typVoisin));
	listeChainee t = v;	
	tmp->voisin = val;
	tmp->poidsVoisin = poids;
	tmp->voisinSuivant = NULL;
	if(v == NULL){
		return tmp;
	}
	while(t->voisinSuivant != NULL){
		t = t->voisinSuivant;
	}
	t->voisinSuivant = tmp;
	return v;	
}

/*
* Fonction : afficher
*
* Parametres : listeChainée
*
* Retour : void
*
* Description : cette fonction permet d'afficher une liste chainée.
*/
void afficherListe(listeChainee lc){
	listeChainee l = lc;
	if(l == NULL){
		printf("Liste vide !\n ");
		return;
	}
	while(l != NULL && l->voisin != -1){
		printf("(%d/%d) ",l->voisin,(int)l->poidsVoisin);//revoir le cast (int)
		l = l->voisinSuivant;
	}
	printf("\n");
}

/*
* Fonction : ecrireListe
*
* Parametres : listeChainée, char*
*
* Retour : void
*
* Description : cette fonction permet d'ecrire une liste chainée dans un fichier
*/
void ecrireListe(listeChainee l, const char* nomFichier){
	if(l == NULL){return;}
	listeChainee tmp = l;	
	FILE* fichier = fopen(nomFichier, "w");
	while(tmp != NULL ){
		fprintf(fichier, "(%d/%f)",tmp->voisin,tmp->poidsVoisin);
		tmp = tmp->voisinSuivant;
	}	
		fprintf(fichier,"\n");
	fclose(fichier);
}

/*
* Fonction : elementExiste
*
* Parametres : listeChainée, int, double
*
* Retour : int
*
* Description : cette fonction permet de verifier l'existence d'un élément dans la liste chainée.
*/
int elementExiste(listeChainee l, int voisin, double poids){
	listeChainee tmp = l;
	while(tmp != NULL){
		if(tmp->voisin == voisin && tmp->poidsVoisin == poids){
			return 1;
		}
		tmp = tmp->voisinSuivant;
	}
	return 0;
}

/*
* Fonction : estVide
*
* Parametres : listeChainée
*
* Retour : int
*
* Description : cette fonction permet de verifier si une liste est vide
*/
int estVide(listeChainee l){
	return l == NULL ? 1:0;
}

/*
* Fonction : supprimerListe
*
* Parametres : listeChainée
*
* Retour :listeChainée
*
* Description : cette fonction permet de supprimer une liste chainée
*/
listeChainee supprimerListe(listeChainee v){
	listeChainee tmp = v;
	listeChainee nxt = NULL;
	if(tmp == NULL){
		return NULL ;
	}
	while(tmp != NULL){	
		nxt = tmp->voisinSuivant;
		free(tmp);
		tmp=nxt;	
	}
	return NULL;
}

/*
* Fonction : nombreElements
*
* Parametres : listeChainée
*
* Retour :int
*
* Description : cette fonction permet de compter le nombre d'élément dans une liste.
*/
int nombreElements(listeChainee l){
	int nbre = 0;
	listeChainee tmp=l;
	while(tmp != NULL){
		nbre++;
		tmp = tmp->voisinSuivant;
	}
	return nbre;
}

/*
* Fonction : supprimerElement
*
* Parametres : listeChainée, int, double
*
* Retour :listeChainée
*
* Description : cette fonction permet de supprimer un element de la liste chainée.
*/
listeChainee supprimerElement(listeChainee l,int val,double poids){
	if(estVide(l)){
		return NULL;
	}
	if(l->voisin == val && l->poidsVoisin == poids){
		listeChainee tmp = l->voisinSuivant;
		free(l);
		tmp = supprimerElement(tmp,val,poids);
		return tmp;
	}
	else{
		l->voisinSuivant = supprimerElement(l->voisinSuivant,val,poids);
		return l;
	}
}
