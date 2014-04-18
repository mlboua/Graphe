
/*
*
*Auteurs: Coulibaly Sidiki, David Esale, Alexi
*
*/
#include <stdio.h>
#include "../include/libGraphe.h"

int typeG;

/*
*******************************************************
*
*
*SOUS MENU
*
*cette fonction affiche le menu des actions sur une liste deja créée
*
*****************************
*/
void sousMenu(typeGraphe* graphe)
{
   int choix,quit=0,valide;
   int sommet,voisin;
   double poids;  
   char nomFichier[100];
	


    do{
        printf("\n");
        printf("--------MANIPULATION DU GRAPHE --------------------------------------\n");
        printf("|  1 :  Afficher le graphe                                          |\n");
        printf("|  2 :  Sauvegarder le graphe                                       |\n");
        printf("|  3 :  Inserer un sommet                                           |\n");
        printf("|  4 :  Inserer une arete                                           |\n");
        printf("|  5 :  Supprimer un sommet                                         |\n");
        printf("|  6 :  Supprimer une arete                                         |\n");
        printf("|  7 :  Quitter                     								|\n");
        printf("--------------------------------------------------------------------|\n");
        printf("\nChoisissez une option :\t ");
        valide=scanf("%d",&choix);
        if(valide==0){
        	printf("EERREUR: Veuillez saisir un chiffre entre 1 et 7\n");
		}
        switch(choix){
        case 1:{
                    affichage(graphe);
            break;
        }
        case 2: {
                printf("\nSauvegarde du graphe dans un fichier ");
                printf("\nDonnez le nom du fichier :\n");
            valide = scanf("%s",nomFichier);
            if(valide == 0){
                printf("ERREUR: Donnez un nom de fichier correct");
            }
             sauvegarde(graphe,nomFichier);
            break;
        }
            case 3: {
		        printf("\nAjout d'un sommet \t ");
		        printf("\nNumero du sommet : \t ");
		        valide = scanf("%d",&sommet);
		        if(valide == 0){
		            printf("ERREUR: Les données ne sont pas correctes");
		        }
		        else{
		        	insertionSommet(graphe,sommet);
		        }
            break;
        }
        case 4: {
            printf("\nAjout d'une arete\n");
            printf("\nSommet de depart : \t ");
            valide=valide*scanf("%d",&sommet);
            printf("\nNumero du sommet d'arrivee : \t ");
            valide=valide*scanf("%d",&voisin);
           	printf("\nPoids de l'arrete : \t ");
            valide=valide*scanf("%lf",&poids);
            if(valide==0){
                printf("ERREUR: Les données ne sont pas correctes");
            }
			else{
                 insertionArete(graphe,sommet,voisin,poids);
            }
            break;
        }
        case 5: {
             printf("\nSuppression de sommet: \t ");
             printf("\nNumero du sommet a supprimer : \t ");
             valide = scanf("%d",&sommet);
             if(valide==0){
                printf("ERREUR: Le numero de sommet n'est pas correct\n");
              }
              else{
                   supprimerSommet(graphe,sommet);
              }
             break;
        }
            case 6: {
                     printf("\nSuppression d'arrete");
                     printf("\nNumero du sommet de depart : \t ");
				     valide= scanf("%d",&sommet);
				     printf("\nNumero du sommet d'arrivee : \t ");
				     valide = valide*scanf("%d",&voisin);
				     printf("\nPoids de l'arrete : \t ");
				     valide = valide*scanf("%lf",&poids);
				     if(valide==0){
				     	printf("ERREUR: Donnees invalides\n");
				     }
				     else{
				     	supprimerArete(graphe,sommet,voisin,poids);
				     }
             break;
        } 
            case 7: {
                     quit = 1;
                  
                     break;
            }
        }
    }while(quit!=1);
}


/*
*******************************************************
*
*
*MENU PRICIPAL
*
*
*cette fonction affiche le menu principale du programme
*****************************
*/
void menuPrincipal(typeGraphe* graphe)
{
    int choix = -1, nbSommet, max = 156;
    char nomFichier[100];
    int qt=0, valide;

    printf("\n");
    printf("|-------- MENU CREATION DE GRAPHES --------|\n");
    printf("|   Choix 1 : Charger le graphe            |\n");
    printf("|   Choix 2 : Creer un graphe              |\n");
    printf("|   Choix 3 : Quitter                      |\n");
    printf("|----------------------------------------  |\n");
    printf("|----------------------------------------  |\n");
    do{
    	printf("\nChoisissez une option :\t ");
    	valide = scanf("%d",&choix);
	if(valide == 0){
		printf("ERREUR: veuillez entrer un nombre entre 1 et 3");
	}
    }while(choix<1 || choix>3);

    switch(choix){
	case 1: {
         printf("\nChargement du graphe a partir d'un fichier...");
		 printf("\nSaisissez le nom du fichier : \t");
		 do{
				valide = scanf("%s",nomFichier);
				if(valide == 0){
					printf("ERREUR: Veuillez un nom de fichier correct");
					qt=-1;
				}
		    }while(fichierExiste(nomFichier)==0 && qt!=10);
		    
		    if(qt!=10){
		         graphe=lecture(nomFichier);
		         sousMenu(graphe);
		     }
		  menuPrincipal(graphe);
		  break;
	}
	case 2:{
		printf("\nCreation du graphe \n");
 		do{
		    printf("\nDonnez le nombre maximum de sommet du graphe :\t");
            valide=scanf("%d",&nbSommet);
		    if(valide==0){
				printf("ERREUR: Entrez un nombre entre 1 et %d.",max);
			} 
            printf("\nDonnez le type du graphe(Oriente = 1, non oriente = 0)\n");
            valide = scanf("%d",&typeG);
            if(valide==0){
                printf("Erreur de lecture des données introduites");
             } 
             
           }while(nbSommet>max || nbSommet< 1);
                creation(graphe,nbSommet,typeG);
                sousMenu(graphe);
		menuPrincipal(graphe);
        break;
	}
	case 3:{
		
		break;
	}

	}	
}
