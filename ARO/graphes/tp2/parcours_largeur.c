#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"

/* Couleurs */
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];




void affiche_parcours_largeur(tGraphe graphe, tNumeroSommet num_sommet)
{
  tFileSommets file;
  struct tTabCouleurs tab_couleurs;
  int i, nb_sommets, voisins;
   
  nb_sommets = grapheNbSommets(graphe);
  file = fileSommetsAlloue ();

  fileSommetsEnfile(file, num_sommet);
  tab_couleurs[num_sommet] = VERT;

  while(!fileSommetsEstVide(file)){
    num_sommet = fileSommetsDefile(file);
    printf("sommet numero %d\n", num_sommet);
    voisins = grapheNbVoisinsSommet(graphe, num_sommet);
    for(i = 0; i < voisins; i++){
      if(tab_couleurs[i] == BLEU ){
	fileSommetsEnfile(file, num_sommet);
	tab_couleurs[i] = VERT;
      }
    }
  }
  
  for(i = 0 ; i < nb_sommets; i++){
    tab_couleurs[i] = BLEU;
  }
  for(i = 0 ; i < nb_sommets; i++){
    if( tab_couleurs[i] == BLEU){
      fileSommetsEnfile (file, i);
    }
    else if( tab_couleurs[i] == VERT){

    }
    else if( tab_couleurs[i] == ROUGE){

    }
  }
  
   fileSommetsLibere(file);
}




int main(int argc, char * argv[])
{
  tGraphe graphe;
  if(argc < 3){
    perror("Use ./parcours_largeur \"fichier graphe\" \"numero sommet\"");
    return -1;
  }
  
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);
  affiche_parcours_largeur(graphe, atoi(argv[2]));
  grapheLibere(graphe);
  
  return 0;
}
