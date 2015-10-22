
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"

int main(int argc, char *argv[]) {

  tGraphe graphe;
  int i;
  int nb_sommets;
  int nb_voisins;
  tNomSommet nom_sommet;
  int voisins_max;
  
  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }

  
  graphe = grapheAlloue();
  
  grapheChargeFichier(graphe,  argv[1]);

  nb_sommets = grapheNbSommets(graphe);
  voisins_max = 0;
  
  for(i = 0; i < nb_sommets; i++){
    nb_voisins = grapheNbVoisinsSommet (graphe, i);
    if(nb_voisins > voisins_max)
      voisins_max = nb_voisins;
    if(nb_voisins ==  0){
      grapheRecupNomSommet(graphe, i, nom_sommet);
      printf("Sommet sans voisin : %s\n", nom_sommet);
    }  
  }
   for(i = 0; i < nb_sommets; i++){
      nb_voisins = grapheNbVoisinsSommet (graphe, i);
      if(nb_voisins == voisins_max){
	grapheRecupNomSommet(graphe, i, nom_sommet);
	printf("Sommet avec le maximum de voisins : %s \n", nom_sommet);
      } 
   }
 

   grapheLibere(graphe);
   
   exit(EXIT_SUCCESS);
}
