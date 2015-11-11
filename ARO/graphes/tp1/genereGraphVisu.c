
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphe.h"
#include "sys/wait.h"
/*N´ecessaire pour la macro WEXITSTATUS */



void graphe2visu(tGraphe graphe, char *outfile)
{
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour créer le ps */
  int ret;
  int i;
  int is_oriente = 1;
  int nb_arcs;
  tNomSommet nom_sommet1;
  tNomSommet nom_sommet2;
  tArc arc;
  /* on va cr´eer un fichier pour graphviz, dans le fichier "outfile".dot */
  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  fic = fopen(dotfile, "w");
  if (fic==NULL)
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);

  is_oriente = grapheEstOriente(graphe);
  nb_arcs = grapheNbArcs(graphe);

  if(is_oriente)
    fprintf(fic, "digraph {\n");
  else
    fprintf(fic, "graph {\n");
  
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
  
  /**/
  
  fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret))
    halt("La commande suivante a ´echou´e\n%s\n", commande);
 
}



int main(int argc, char *argv[]) {

  tGraphe graphe;


  if (argc<3) {
    halt("Usage : %s FichierGraphe fichier vizu\n ", argv[0]);
  }

  
  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);

  graphe2visu(graphe, argv[2]);
  grapheLibere(graphe);
  return 0;
}
