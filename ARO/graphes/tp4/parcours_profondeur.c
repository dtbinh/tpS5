#define _POSIX_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include "graphe.h"

/* Couleurs */
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

int const verbose = 1;
char *output = "visu.ps";



void graphe2visu(tGraphe graphe, char *outfile, tTabCouleurs tabCouleurs)
{
  FILE *fic;
  char commande[80];
  char dotfile[80]; 
  int ret;
  int i;
  int is_oriente = 1;
  int nb_arcs;
  int nb_sommets;

  tNomSommet nom_sommet1;
  tNomSommet nom_sommet2;
  tNomSommet nom_sommet3;
  tArc arc;


 
  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  fic = fopen(dotfile, "w");
  if (fic==NULL)
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);

  is_oriente = grapheEstOriente(graphe);
  nb_arcs = grapheNbArcs(graphe);
  nb_sommets = grapheNbSommets(graphe);

  if(is_oriente)
    fprintf(fic, "digraph {\n");
  else
    fprintf(fic, "graph {\n");
  

  for(i = 0; i < nb_sommets; i++){
    grapheRecupNomSommet(graphe, i, nom_sommet3);
    if(tabCouleurs[i] == VERT)
      fprintf(fic, "%s [color=green];\n", nom_sommet3);
    if(tabCouleurs[i] == BLEU)
      fprintf(fic, "%s [color=blue];\n", nom_sommet3);
    if(tabCouleurs[i] == ROUGE)
      fprintf(fic, "%s [color=red];\n", nom_sommet3);
  }


  for(i = 0; i < nb_arcs; i++){
    
    arc = grapheRecupArcNumero(graphe, i);
    grapheRecupNomSommet(graphe, arc.orig, nom_sommet1);
    grapheRecupNomSommet(graphe, arc.dest, nom_sommet2);
    if(is_oriente)
      fprintf(fic," %s -> %s\n",nom_sommet1, nom_sommet2);
    else
      fprintf(fic," %s -- %s\n", nom_sommet1, nom_sommet2);
  }
  fprintf(fic, "}\n");
 
  
  fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (ret == -1)
    halt("La commande suivante a echouée : %s\n", commande);
  
  
    }



void empile_voisin(){

}


void affiche_parcours_profondeur(tGraphe graphe, tNumeroSommet num_sommet)
{
  tPileSommets pile;
  tNomSommet nom_sommet;
  tNumeroSommet current_voisin;
  tTabCouleurs tab_couleurs;
  int i, nb_sommets, voisins;
  char *argv[3];
  argv[0] = "evince";
  argv[1] = output;
  argv[2] = NULL;
  switch(fork()){
  case -1: perror("fork");
    exit(EXIT_FAILURE);  
  case 0 : execvp(argv[0], argv);
    halt("Error evince");
    exit(EXIT_FAILURE);
  default:
    pile = pileSommetsAlloue();
    nb_sommets = grapheNbSommets(graphe);
    if(verbose)
      printf("Nb sommets : %d\n", nb_sommets);
    
    for(i = 0 ; i < nb_sommets; i++){
      tab_couleurs[i] = BLEU;
    }

    pileSommetsEmpile(pile, num_sommet);
    tab_couleurs[num_sommet] = VERT;
    grapheRecupNomSommet(graphe, num_sommet, nom_sommet);
    printf("Sommet %s empilé\n", nom_sommet);
    graphe2visu(graphe, output, tab_couleurs);

    sleep(2);
    while(!pileSommetsEstVide(pile)){
        
      voisins = grapheNbVoisinsSommet(graphe, num_sommet);
      if(verbose)    
	printf("Nb voisins : %d\n", voisins);
    
      for(i = 0; i < voisins; i++){
	current_voisin = grapheVoisinSommetNumero(graphe, num_sommet, i);
	if(tab_couleurs[current_voisin] == BLEU ){
	  pileSommetsEmpile(pile, current_voisin);
	  tab_couleurs[current_voisin] = VERT;
	  grapheRecupNomSommet(graphe, current_voisin, nom_sommet);
	  printf("Sommet %s empilé\n", nom_sommet);
	  graphe2visu(graphe, output, tab_couleurs);
	  sleep(2);
	  break;
	}
     
	if(verbose)      
	  printf("voisin num %d\n", current_voisin);
      }
      if(i == voisins){
	tab_couleurs[num_sommet] = ROUGE;
	grapheRecupNomSommet(graphe, num_sommet, nom_sommet);
	if(verbose)    
	  printf("Sommet %s depilé\n", nom_sommet);
	pileSommetsDepile(pile);
	graphe2visu(graphe, output, tab_couleurs);
	sleep(2); 
      }
      if(!pileSommetsEstVide(pile))
	num_sommet =  pileSommetsTete(pile);
      grapheRecupNomSommet(graphe, num_sommet, nom_sommet);
    }
  }
  pileSommetsLibere(pile);


  wait(NULL);
  
}




int main(int argc, char * argv[])
{
  tGraphe graphe;
  if(argc < 3){
    perror("Use ./parcours_profondeur \"fichier graphe\" \"numero sommet\"");
    return -1;
  }
  
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);
  affiche_parcours_profondeur(graphe, atoi(argv[2]));
  grapheLibere(graphe);
  
  return 0;
}
