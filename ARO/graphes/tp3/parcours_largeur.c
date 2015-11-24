#define _POSIX_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include "graphe.h"
#include <sys/time.h>


/* Couleurs */
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

int const verbose = 0;


void parcours_largeur(tGraphe graphe, tNumeroSommet num_sommet)
{
  tFileSommets file;
  tNomSommet nom_sommet;
  tNumeroSommet current_voisin;
  tTabCouleurs tab_couleurs;
  int i, nb_sommets, voisins, cpt;
  int d[MAX_SOMMETS];
  int predecesseur[MAX_SOMMETS];
  
  file = fileSommetsAlloue();
  nb_sommets = grapheNbSommets(graphe);
  if(verbose)
    printf("Nb sommets : %d\n", nb_sommets);
  for(i = 0 ; i < nb_sommets; i++){
    tab_couleurs[i] = BLEU;
  }

  fileSommetsEnfile(file, num_sommet);
  tab_couleurs[num_sommet] = VERT;
  grapheRecupNomSommet(graphe, num_sommet, nom_sommet);
  if(verbose)
    printf("Sommet %s empilé\n", nom_sommet);

  while(!fileSommetsEstVide(file)){
      voisins = grapheNbVoisinsSommet(graphe, num_sommet);
      cpt++;
    if(verbose)    
      printf("Nb voisins : %d\n", voisins);
    
    for(i = 0; i < voisins; i++){
      current_voisin = grapheVoisinSommetNumero(graphe, num_sommet, i);
      if(tab_couleurs[current_voisin] == BLEU ){
	fileSommetsEnfile(file, current_voisin);
	tab_couleurs[current_voisin] = VERT;
	grapheRecupNomSommet(graphe, current_voisin, nom_sommet);

	d[current_voisin] = cpt;
	predecesseur[current_voisin] = num_sommet; 
	if(verbose)
	  printf("Sommet %s empilé\n", nom_sommet);
      }
      if(verbose)      
	printf("voisin num %d\n", current_voisin);
    }
    tab_couleurs[num_sommet] = ROUGE;
    num_sommet = fileSommetsDefile(file);
    grapheRecupNomSommet(graphe, num_sommet, nom_sommet);
    if(verbose)    
      printf("Sommet %s depilé\n", nom_sommet);     
  }
  
  fileSommetsLibere(file);
  
}
  





long nbMicroSecondesDepuisDebutHeure() {
  struct timeval tv;
  long us;
  gettimeofday(&tv, NULL);
  // tv.tv_sec : nbre de secondes depuis Epoch
  // tv.tv_usec : compl´ement en microsecondes
  tv.tv_sec = tv.tv_sec % 3600; // on fait un modulo une heure (=3600s)
  us = (tv.tv_sec*1000000)+tv.tv_usec;
  return us;
}



int main(int argc, char * argv[])
{
  tGraphe graphe;
  int nb_graph, nb_sommets, is_oriente;
  double proba_arc;
  long start, end;
  int i;
  
  if(argc < 5){
    perror("Use ./parcours_largeur \"nb_graph\" \"nb_sommets\" \"is_oriente\" \"proba_arc\"");
    return -1;
  }
  graphe = grapheAlloue();

  nb_graph = atoi(argv[1]);
  nb_sommets = atoi(argv[2]);
  is_oriente = atoi(argv[3]);
  proba_arc = atof(argv[4]);

  
  for(i = 0; i < nb_graph; i++){
    start =  nbMicroSecondesDepuisDebutHeure();
    grapheAleatoire(graphe, nb_sommets, is_oriente, proba_arc);
    parcours_largeur(graphe, 0);
    end =  nbMicroSecondesDepuisDebutHeure();
    printf("Time taken : %lu microsecondes for graphe number %d\n", end-start, i+1);
  }
  
  
  grapheLibere(graphe);
  
  return 0;
}
