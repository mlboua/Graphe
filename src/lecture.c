#include <stdio.h>
#include <stdlib.h>
#include "../include/libGraphe.h"
typeGraphe* lectureEss(char *nom_fichier){
	typeGraphe* graphe = (typeGraphe*) malloc(sizeof(typeGraphe));

   	//int n = 0,s=0,s1=0,s2=0,i=0,j=0,err=0,val=0;
   	int s = 0;
   	char sommet;
   	int dep[126];
   	char intitul[126];
   	int poids[256];
   	char p = '#';
   	char ligne[256],tmp[255];
	int init = 0;
	const int NB_MAX = 28;
	char verif[NB_MAX];
	for(init = 0; init< NB_MAX; init++){
		verif[init] = '0';
	}
   	FILE *f = fopen(nom_fichier, "rt" );
   	if(f != NULL){
   		creation(graphe,NB_MAX);
		insertionSommet(graphe, '0');
		insertionSommet(graphe, '#');
    	while (fgets( ligne, 256, f ) != NULL){ /* essai lecture ligne */
    		if(ligne[0] != '#'){
    			sommet = ligne[0];
    			insertionSommet(graphe,sommet);
    			int i = 1;
    			while(ligne[i]!='\''){
                  	tmp[i]=ligne[i];
                  	i++;
                }
                s=atoi(tmp);
                i++;
                int j=0;
    			while(ligne[i] != '\'' && i < 256 && ligne[i] != '\n'){
    				intitul[j] = ligne[i];
    				i++;
    				j++;
    			}
    			intitul[j] = '\0';

    			int k = 0;
    			while(ligne[i] != '\n'){
    					if(ligne[i] != ',' && ligne[i] != ' ' && ligne[i] != '\''){
    						dep[k] = ligne[i];
    						k++;
    					}
    					i++;
    			}
    			dep[k] = '\0';
    			poids[sommet] = dep[0];
    			if(dep[1] == '-'){
				insertionArete(graphe, '0', sommet, 0);
			}
			else{

    				int v = 0;
    				for(v = 1; v < k; v++){
    					insertionArete(graphe, dep[v],sommet, poids[dep[v]] - '0');
					verif[dep[v]] = dep[v];	
				}
			}
    		}
			
    	}
		int r = 0;
		for( r= 0; r<NB_MAX; r++){
			printf("VERIF\n");
			if(verif[r] != '0'){
			//	insertionArete(graphe,verif[r],'#',0);
				printf("# %d : %d\n", verif[r],r);
			}
		}
    }
    return graphe;
}

int main(){
	typeGraphe* g = lectureEss("chantier.txt");
	//creation(&g,10);
	 //insertionArete(g, 'A','F',7);
	affichage(g);
	return 0;
}
