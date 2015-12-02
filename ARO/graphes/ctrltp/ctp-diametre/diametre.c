
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"

/* Couleurs */
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

int verbose = 0;

/* Fonction qui renvoie le maximum des deux entiers x et y 
   (question facile, ne pas chercher de complications) */

int max(int x, int y) {
  if(x > y)
    return x;
  return y;
}

/* Parcours en largeur 
Entrée :
- graphe : le graphe à parcourir, supposé *connexe* et *non orienté*
- s : numéro du sommet de départ
Sortie :
- d : tableau d'entiers tel que
      d[i] = distance de s au sommet i

Remarque: nous n'avons pas besoin du tableau pred du poly.

*/
void plusCourteChaine(tGraphe graphe, tNumeroSommet s,
		      int d[MAX_SOMMETS]) {

 tFileSommets file;
  tNomSommet nom_sommet;
  tNumeroSommet current_voisin;
  tTabCouleurs tab_couleurs;
  int i, nb_sommets, voisins, cpt;


  /*je reset le tableau d à chaque depart de la focntion*/
  for(i = 0 ; i < MAX_SOMMETS; i++){
    d[i] = 0;
  }

  
  cpt = 0;
  file = fileSommetsAlloue();
  nb_sommets = grapheNbSommets(graphe);
  if(verbose)
    printf("Nb sommets : %d\n", nb_sommets);
  
  for(i = 0 ; i <  MAX_SOMMETS; i++){/*au depart je met tout le tableau en bleu*/
    tab_couleurs[i] = BLEU;
  }

  fileSommetsEnfile(file, s);
  tab_couleurs[s] = VERT;/*j'enfile le premier sommet et je lance la boucle*/
  grapheRecupNomSommet(graphe, s, nom_sommet);
  if(verbose)
    printf("Sommet %s enfilé\n", nom_sommet);

  while(!fileSommetsEstVide(file)){
      voisins = grapheNbVoisinsSommet(graphe, s);
      if(voisins > 0)//si il existe au moins un voisin
      	cpt++;/*j'incremente la dist entre s et ce(s) sommet(s)*/
    if(verbose)    
      printf("Nb voisins : %d\n", voisins);
    
    for(i = 0; i < voisins; i++){/*pour tout les voisins de s*/
      current_voisin = grapheVoisinSommetNumero(graphe, s, i);
      if(tab_couleurs[current_voisin] == BLEU ){/*si je n'y suis pas deja passé*/
	fileSommetsEnfile(file, current_voisin);
	tab_couleurs[current_voisin] = VERT;
	grapheRecupNomSommet(graphe, current_voisin, nom_sommet);

	d[current_voisin] = cpt; /*j'assigne la distance entre ce sommet et la source s*/

	if(verbose)
	  printf("Sommet %s enfilé\n", nom_sommet);
      }
      if(verbose)      
	printf("voisin num %d\n", current_voisin);
    }
    tab_couleurs[s] = ROUGE;
    s = fileSommetsDefile(file);
    grapheRecupNomSommet(graphe, s, nom_sommet);
    if(verbose)    
      printf("Sommet %s defilé\n", nom_sommet);     
  }
  /* printf(" ICI %d \n",cpt);*/
  fileSommetsLibere(file);
    
}




/*
Calcule et renvoie le diamètre du graphe
Entrée :
- graphe : le graphe supposé *connexe* et *non orienté*
Sortie :
- le diamètre du graphe
*/
int calculeDiametre(tGraphe graphe) {
  int diametre, nb_sommets, i, j;
  int d[MAX_SOMMETS];
  
  diametre = 0;
  
  nb_sommets = grapheNbSommets(graphe);

  for(i = 0; i < nb_sommets; i++){
    plusCourteChaine(graphe, i, d); /*On modifie le tableau d pour chaque sommet*/
    for(j = 0; j < MAX_SOMMETS; j++){/*On parcours le tableau d en entier pour chaque sommet*/
      if(diametre < d[j]){/*si la valeur de la case du tableau est supérieure à notre diametre*/
	diametre = d[j];/*on affecte cette valeur à notre diametre*/
      }
    }
    
  }

  return diametre;
}

  

/////////////////////////////////////////////////////////////
// Sauf mention contraire, vous ne devez pas modifier le main
/////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

  tGraphe graphe;
  char *fic;
  int diametre;
  
  /* Traitement des arguments */
  if (argc!=2) 
    halt("Usage : %s <fichier_graphe>\n", argv[0]);
  
  fic = argv[1];

  /* Chargement du graphe */
  graphe = grapheAlloue();
  grapheChargeFichier(graphe, fic);
  if (grapheEstOriente(graphe)) 
    halt("Le graphe doit être non orienté\n");

  /* Calcul du diamètre */
  diametre = calculeDiametre(graphe);

  /* Affichage du résultat */
  printf("Le diamètre du graphe est : %d\n", diametre);

  /* Libération du graphe */
  grapheLibere(graphe);
  exit(EXIT_SUCCESS);
}

