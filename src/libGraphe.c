/*
*
*Auteurs: Coulibaly Sidiki, David Esale, Alexi
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/libGraphe.h"
#define EOL '\n'

/*
* Fonction : creation
*
* Parametres : pointeur de type typeGraphe, int sommet,int type
*
* Retour : void
*
* Description : cette fonction permet de créer un graphe avec le nombre max de sommet.
*/
void creation(typeGraphe* graphe,int nbSommets,int type){
	graphe->nbMaxSommets = nbSommets;
	graphe->listesAdjacences = malloc(graphe->nbMaxSommets*sizeof(listeChainee));
	if(graphe->listesAdjacences != NULL){
		graphe->type = type;
		int i;
		for(i = 0;i<graphe->nbMaxSommets;i++){
			graphe->listesAdjacences[i] = NULL;	
		}
		printf("Graphe créé !\n");
	}
	else{
		printf("ERREUR: une erreur est survenue lors de la creation du graphe !\n");
	}
}

/*
* Fonction : areteExiste
*
* Parametres : pointeur de type typeGraphe, int sommet,int voisin, double poids
*
* Retour : int (1 si arete existe 0 sinon)
*
* Description : cette fonction permet de verifier l'existence d'une arete.
*/
int areteExiste(typeGraphe* g, int sommet, int voisin, double poids){
	if(elementExiste(g->listesAdjacences[sommet - 1], voisin,poids)){
		return 1;
	}
	return 0;	
}

/*
* Fonction : insertionArete
*
* Parametres : pointeur de type typeGraphe, int sommet,int voisin, double poids
*
* Retour : void
*
* Description : cette fonction permet d'inserer une arete dans le graphe.
*/
void insertionArete(typeGraphe* g,int sommet,int voisin,double poids){
	if(areteExiste(g,sommet, voisin, poids)){
		printf("Erreur: Cette arete existe deja dans le graphe !\n");
		return;
	}
	if(voisin > 0){
		if(g->listesAdjacences[sommet - 1] == NULL){
			insertionSommet(g,sommet);
		}
		if(g->listesAdjacences[voisin - 1] == NULL){
			insertionSommet(g,voisin);
		}
	}
	g->listesAdjacences[sommet - 1] = ajouterDebut(g->listesAdjacences[sommet - 1],voisin,poids);
	
	if(g->type != 1){//si le graphe n'est pas orienté on ajoute le sommet depart à la liste du voisin
		listeChainee listeDuVoisin = ajouterDebut(g->listesAdjacences[voisin - 1], sommet, poids);
		g->listesAdjacences[voisin - 1] = listeDuVoisin;
	}
}

/*
* Fonction : insertionSommet
*
* Parametres : pointeur de type typeGraphe, int sommet
*
* Retour : void
*
* Description : cette fonction permet d'ajouter un sommet au graphe.
*/
void insertionSommet(typeGraphe* g,int sommet){
	if(sommet > g->nbMaxSommets){
		printf("Erreur: Le numero du sommet (%d) est superieur au nombre maximal (%d) de sommets.\n",sommet,g->nbMaxSommets);
	}
	else if(g->listesAdjacences[sommet - 1] != NULL){
		printf("Erreur: Le sommet (%d) existe deja.\n",sommet);
	}
	else{
		insertionArete(g,sommet,-1,0);	
	}	

}
/*
* Fonction : affichage
*
* Parametres : pointeur de type typeGraphe
*
* Retour : void
*
* Description : cette fonction permet d'afficher le graphe.
*/
void affichage(typeGraphe* g){
	if(g == NULL){
		printf("ERREUR: Le graphe n'existe pas.\n");
		return;
	}
	int i = 0;
	printf("# nombre maximum de sommets\n");
	printf("%d\n",g->nbMaxSommets);
	printf("# sommets : voisins\n");
	for(i = 0; i < g->nbMaxSommets;i++){
		if(g->listesAdjacences[i] != NULL){
			printf("%d:",i+1);
			afficherListe(g->listesAdjacences[i]);
		}	
	}
}

/*
* Fonction : sommetExiste
*
* Parametres : pointeur de type typeGraphe, int sommet
*
* Retour : int (1 si le sommet existe 0 sinon)
*
* Description : cette fonction permet de verifier l'existence d'un sommet.
*/
int sommetExiste(typeGraphe *g, int sommet){
	return (g->listesAdjacences[sommet - 1] != NULL);
}

/*
* Fonction : supprimerSommet
*
* Parametres : pointeur de type typeGraphe, int sommet
*
* Retour : void
*
* Description : cette fonction permet de supprimer un sommet.
*/
void supprimerSommet(typeGraphe* g,int sommet){
	if((sommet > 0 && sommet < g->nbMaxSommets) && g->listesAdjacences[sommet - 1] != NULL){	
		//printf("nb : %d \n",nombreElements(g->listesAdjacences[sommet - 1]));
		listeChainee tmp = g->listesAdjacences[sommet - 1];
		while(tmp != NULL && tmp->voisin != -1){
			supprimerArete(g,tmp->voisin,sommet,tmp->poidsVoisin);
			tmp = tmp->voisinSuivant;
		}
		g->listesAdjacences[sommet - 1] = supprimerListe(g->listesAdjacences[sommet - 1]);
		printf("Sommet supprimé !\n");
	}
}

/*
* Fonction : supprimerArete
*
* Parametres : pointeur de type typeGraphe, int sommet,int voisin, double poids
*
* Retour : void
*
* Description : cette fonction permet de supprimer une arete du graphe
*/
void supprimerArete(typeGraphe* g,int s,int v,double p){
	double poid = (double)p;
	g->listesAdjacences[s - 1] = supprimerElement(g->listesAdjacences[s - 1],v,poid);
	g->listesAdjacences[v - 1] = supprimerElement(g->listesAdjacences[v - 1],s,poid);
	printf("Arete supprimée !\n");
}

/*
* Fonction : sauvegarde
*
* Parametres : pointeur de type typeGraphe
*
* Retour : void
*
* Description : cette fonction permet d'ecrire le graphe dans un fichier.
*/
void sauvegarde(typeGraphe* g,const char* nomFichier){
	FILE* fichier = fopen(nomFichier,"w");	
	if(fichier){	
		fprintf(fichier,"# nombre maximum de sommets\n");
		fprintf(fichier,"%d\n",g->nbMaxSommets);
		fprintf(fichier,"# sommets : voisins\n");
		int i = 0;
		for(i = 0; i<g->nbMaxSommets;i++){
			if(g->listesAdjacences[i] != NULL){
				fprintf(fichier,"%d : ",i+1);
				listeChainee l = g->listesAdjacences[i];
				while(l->voisin != -1){	
					fprintf(fichier, "(%d/%d) ",l->voisin,(int)l->poidsVoisin);	
					l = l->voisinSuivant;
				}
				fprintf(fichier, "\n");
			}
		}
		fclose(fichier);
		printf("Graphe enregistré ! \n");
	}	

}

/*
* Fonction : fichierExiste
*
* Parametres : pointeur chaine de caractères
*
* Retour : int
*
* Description : cette fonction permet de verifier l'existence d'un fichier.
*/
int fichierExiste(char *nomfichier)
{
     	FILE *fichier = fopen(nomfichier, "rt" );
     	if (fichier == NULL) {
        	printf("\nErreur ouverture\n");
        	return 0;
     	}
     	else{
        	return 1;
        }
}

/*
* Fonction : lireEntier
*
* Parametres : pointeur de type FILE
*
* Retour : int
*
* Description : cette fonction permet de lire les caractères du fichier.
*/
int lireEntier(FILE* fichier) {

	const int entierTailleMax = 64;
	char entierLu [65]; 
	int compteur = 0;
	char caractereLu;

	caractereLu = fgetc(fichier);

	while((caractereLu < '0' || caractereLu > '9') && caractereLu != EOF && caractereLu != EOL){
		caractereLu = fgetc(fichier);
	}

	if (caractereLu == EOL){
		return -32;
	}else if (caractereLu == EOF){
		return -64;
	}

	entierLu[compteur] = caractereLu;
	++ compteur;

	do { 
		caractereLu = fgetc(fichier);
		entierLu[compteur] = caractereLu;
		++compteur;
	}while ((caractereLu > '0' && caractereLu < '9') && compteur < entierTailleMax);
	entierLu[compteur] = '\0';
	if(caractereLu == EOF){
		return -64;
	}
	else{
		return atoi(entierLu);
	}
}

/*
* Fonction : lecture
*
* Parametres : pointeur de type typeGraphe
*
* Retour : typeGraphe
*
* Description : cette fonction permet de lire le graphe à partir d'un fichier.
*/
typeGraphe* lecture(const char* nomFichier){
	FILE* fichier = fopen(nomFichier, "r");
	typeGraphe* graphe = (typeGraphe*) malloc(sizeof(typeGraphe));
	while(lireEntier(fichier) != -32);
	int nbMaxSommets = lireEntier(fichier);
	creation(graphe, nbMaxSommets,-1);
	int entierLu;
	int numeroSommet;
	int creerSommet = 1;
	int poids;

	entierLu = lireEntier(fichier); // EOL
	entierLu = lireEntier(fichier);
	while(entierLu != -64){
		if(creerSommet){
			numeroSommet = entierLu;
			if(!sommetExiste(graphe, numeroSommet)){
				insertionSommet(graphe, numeroSommet);
			}
			creerSommet = 0;
		}else{
			if(entierLu == -32 || poids == -32){
				creerSommet = 1;
			}else{
			   	poids	= lireEntier(fichier);
			   	if(!areteExiste(graphe,numeroSommet,entierLu,poids)){
					insertionArete(graphe, numeroSommet, entierLu, poids);
				}
			}
		}
		entierLu = lireEntier(fichier);
	}

	fclose(fichier);
	return graphe;
}
