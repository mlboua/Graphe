 /*
 ***********************************************************
 *
 * Programme : pert.c
 *
 * ecrit par : Sophian Boulekroune et Renaud Garigues
 *
 * resume :    Bibliotheque pour la manipulation des diagrammes PERT
 *
 * date :      4/04/2010
 *
 ***********************************************************
 */

#include "../include/chantier.h"

/*
 * Fonction :    initDate
 * Parametres :  Date *d (parametre pointeur sur date)
 *               int size (taille du tableau de dates)
 * Retour :      Date*
 * Description : Initialise la date passe en parametre.
 */
Date* initDate( Date* d, int size ) {

    int i = 0;

    d        = (Date *) malloc (sizeof( Date ));
    d->tot   = (int*) malloc(sizeof(int) * size);
    d->tard  = (int*) malloc(sizeof(int) * size);

    for( i = 0; i < size; i++ ) {
        
        d->tot[ i ]  = 0;
        d->tard[ i ] = INFINI;     // le vrai infini serait idéal
    }

    return d;
}

/*
 * Fonction :    displayDate
 * Parametres :  Date *d (parametre pointeur sur date)
 *               int size (taille du tableau de dates)
 * Retour :      Code d'erreur/succes
 * Description : Affiche les dates au plus tot et au plus tard.
 */
int displayDate( Date* d, int size ) {

    if ( d ) {

        printf("  Tache  : Date tot Date tard\n");

        for( int i = 1; i < size; i++ ) {
            
            printf("%8c : %8d %8d\n", i+64, d->tot[ i ], d->tard[ i ]);
        }
        return OK;
    }
    else {

        return NULL_POINTER_EXCEPTION;
    }
}

/*
 * Fonction :    min
 * Parametres :  int x
 *               int y
 * Retour :      entier
 * Description : Retourne le maximun entre x et y.
 */
int max( int x, int y ) {

    return ( x > y ) ? x : y;
}

/*
 * Fonction :    min
 * Parametres :  int x
 *               int y
 * Retour :      entier
 * Description : Retourne le minimun entre x et y.
 */
int min( int x, int y ) {

    return ( x < y ) ? x : y;
}

/*
 * Fonction :    dateTot
 * Parametres :  Date *d (parametre pointeur sur date)
 * Retour :      Code d'erreur/succes
 * Description : Initialise la date passe en parametre.
 */
int dateTot( TypGraphe* g, int sommetCourant, int tempsJusquIci, Date* d ) {

    if ( g != NULL ) {

        int tempsFin;
        int tempsExec ;
        if ( g->listesAdjacences[sommetCourant] != NULL ) {


            dblist *liste = (dblist*) g->listesAdjacences[sommetCourant];
            TypVoisins *fils = liste->first;

            if ( fils != NULL ) {

                tempsExec = fils->ponderation;
                tempsFin = tempsJusquIci + tempsExec;
                d->tot[sommetCourant] = max(d->tot[sommetCourant],tempsJusquIci);

                while( fils != NULL ) {

                    dateTot ( g, fils->voisin, tempsFin, d );
                    tempsFin = d->tot[fils->voisin];
                    
                    if( fils->voisinSuivant != NULL ) {

                        fils = fils->voisinSuivant;
                    }
                    else {

                        return OK;
                    }
                }
            }
            else {

                d->tot[sommetCourant] = max(d->tot[sommetCourant],tempsJusquIci);
                return OK;
            }
        }
    }
    else {

        return NULL_POINTER_EXCEPTION;
    }
    return OK;
}

/*
 * Fonction :    dateTard
 * Parametres :  Date *d (parametre pointeur sur date)
 * Retour :      Code d'erreur/succes
 * Description : Initialise la date passe en parametre.
 */
int dateTard( TypGraphe* g, int sommetCourant, int tempsJusquIci, Date* d ) {

    if ( g != NULL ) {

        int tempsFin;
        int tempsExec ;

        if ( g->listesAdjacences[sommetCourant] != NULL ) {

            dblist *liste = (dblist*) g->listesAdjacences[sommetCourant];
            TypVoisins *fils = liste->first;

            if ( fils != NULL ) {

                tempsExec = fils->ponderation;
                tempsFin = tempsJusquIci - tempsExec;
                d->tard[sommetCourant] = min( tempsJusquIci,
                                             d->tard[sommetCourant] );

                while( fils != NULL ) {

                    dateTard ( g, fils->voisin, tempsFin, d);
                    tempsFin = d->tard[fils->voisin];
                    
                    if( fils->voisinSuivant != NULL ) {

                        fils = fils->voisinSuivant;
                        tempsFin = tempsJusquIci - fils->ponderation;
                    }
                    else {

                        return OK;
                    }
            }
                }
            else {

                d->tard[sommetCourant] = min( tempsJusquIci, 
                                             d->tard[sommetCourant] );
                return OK;
            }
        }
    }
    else {

        return NULL_POINTER_EXCEPTION;
    }
    return OK;
}

/**
 * Fonction    : getTotalWorkingTime
 * Parametres  : Date* d (pointeur sur les dates au plus tot et au plus tard
 *               int size (taille du tableau de dates) 
 * Retour      : Code d'erreur/succes
 * Description : Affiche la duree totale du chantier
 **/
int getTotalWorkingTime( Date* d, int size ) {

    if( d == NULL ) {

        return NULL_POINTER_EXCEPTION;
    }
    else {

        printf("Duree totale du chantier : %d unite(s) de temps\n",
               d->tot[size-1]);
        return OK;
    }
}

/**
 * Fonction    : displayCriticalPath
 * Parametres  : TypGraphe* g (pointeur sur le graphe)
 *               Date* (pointeur sur le chemin critique du diagramme)
 *               int sommet (sommet courant du graphe) 
 *               Pile p (pile contenant un chemin critique)
 * Retour      : Code d'erreur/succes
 * Description : Affiche les chemins critiques
 **/
int displayCriticalPath( TypGraphe* g, Date* d, int sommet, Pile p ) {

    if ( g != NULL ) {

        Pile* tmp = NULL;
        empiler( sommet,&p );
        
        if ( g->listesAdjacences[sommet] != NULL ) {

            dblist *liste = (dblist*) g->listesAdjacences[sommet];
            TypVoisins *fils = liste->first;

            if ( fils != NULL ) {

                while( fils != NULL ) {

                    if( d->tot[fils->voisin] == d->tard[fils->voisin] ) {
                    
                        displayCriticalPath ( g, d, fils->voisin, p );
                    }
                    
                    if( fils->voisinSuivant != NULL ) {

                        fils = fils->voisinSuivant;
                    }
                    else {

                        return OK;
                    }
                }
            }
            else {

                depiler( &p );
                tmp = inverse_pile( &p );
                depiler( tmp );
                affiche_pile( tmp );
                return OK;
            }
        }
    }
    else {

        return NULL_POINTER_EXCEPTION;
    }
    return OK;
}

/**
 * Fonction    : getCriticalPath
 * Parametres  : TypGraphe* g (pointeur sur le graphe)
 *               Date* (pointeur sur le chemin critique du diagramme)
 *               int size (taille du tableau de dates) 
 * Retour      : Code d'erreur/succes
 * Description : Lance le calcul et l'affichage des chemins critiques
 **/
int getCriticalPath( TypGraphe* g, Date* d , int size ) {

    if ( g != NULL ) {

        Pile* p = NULL;
        p = creer_pile();
        
        displayCriticalPath( g, d, 0, *p );
        return OK;
    }
    else {

        return NULL_POINTER_EXCEPTION;
    }
}

