/*
 ***********************************************************
 *
 * Programme : pert.h
 *
 * ecrit par : Sophian Boulekroune et Renaud Garigues
 *
 * resume :    Bibliotheque pour la manipulation des diagrammes PERT
 *
 * date :      18/03/2010
 *
 ***********************************************************
 */


#ifndef PERT_H
#define PERT_H

#define INFINI 100000

#include <math.h>
#include "./graph.h"
#include "./linkedList.h"
#include "./stack.h"

/*
 * Structure d'un graphe
 */
typedef struct Date {
    int*   tot;       /* tableau des dates au plus tot*/
    int * tard;      /* tableau  des dates au plus tard*/
} Date ;

/*
 * Fonction :    initDate
 * Parametres :  Date *d (parametre pointeur sur date)
 * Retour :      Date*
 * Description : Initialise la date passe en parametre.
 */
Date* initDate( Date *, int );

/*
 * Fonction :    displayDate
 * Parametres :  Date *d (parametre pointeur sur date)
 *               int size (taille du tableau de dates)
 * Retour :      Code d'erreur/succes
 * Description : Initialise la date passe en parametre.
 */
int displayDate( Date *, int );

/*
 * Fonction :    dateTot
 * Parametres :  Date *d (parametre pointeur sur date)
 * Retour :      Date*
 * Description : Initialise la date passe en parametre.
 */
int dateTot( TypGraphe *, int, int, Date * );

/*
 * Fonction :    dateTard
 * Parametres :  Date *d (parametre pointeur sur date)
 * Retour :      Code d'erreur/succes
 * Description : Initialise la date passe en parametre.
 */
int dateTard( TypGraphe *, int, int, Date * );

/**
 * Fonction    : getTotalWorkingTime
 * Parametres  : Date* d (pointeur sur les dates au plus tot et au plus tard
 *               int size (taille du tableau de dates) 
 * Retour      : Code d'erreur/succes
 * Description : Affiche la duree totale du chantier
 **/
int getTotalWorkingTime( Date*, int );

/**
 * Fonction    : displayCriticalPath
 * Parametres  : TypGraphe* g (pointeur sur le graphe)
 *               Date* (pointeur sur le chemin critique du diagramme)
 *               int sommet (sommet courant du graphe) 
 *               Pile p (pile contenant un chemin critique)
 * Retour      : Code d'erreur/succes
 * Description : Affiche les chemins critiques
 **/
int displayCriticalPath( TypGraphe*, Date*, int, Pile );

/**
 * Fonction    : getCriticalPath
 * Parametres  : TypGraphe* g (pointeur sur le graphe)
 *               Date* (pointeur sur le chemin critique du diagramme)
 *               int size (taille du tableau de dates) 
 * Retour      : Code d'erreur/succes
 * Description : Lance le calcul et l'affichage des chemins critiques
 **/
int getCriticalPath( TypGraphe*, Date*, int );

#endif /* PERT_H */
