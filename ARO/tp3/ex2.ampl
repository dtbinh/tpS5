set USINE;
set PAPIER;

param cout_prod_j {USINE} >= 0; /* cout de production total par jour par usine*/
param prod_jour {USINE,PAPIER} >= 0; /* production par jour par usine par type de papier*/
param prod_min {PAPIER} >= 0; /*production minimal de chaque type de papier*/


var nb_jour {u in USINE} >= 0;
/*nombre de jour de mise en marche de chaque usine*/



minimize cout :
sum {u in USINE} cout_prod_j [u] * nb_jour[u];
/*minimise le cout d'utilisation des usines par jour*/


subject to prod_minimal {p in PAPIER} : /* production minimal par type de papier*/
sum {u in USINE} prod_jour[u,p] * nb_jour[u]  >= prod_min[p];
/*production par jour de chaque usine de chaque type de papier * le nb de jour*/

data;

set PAPIER := inf moy sup;
set USINE := A B;

param: prod_min :=
inf     16
moy     5
sup     20;

param prod_jour : /*definition d'un param à deux variable*/
  inf moy sup :=
A 8   1   2
B 2   1	  7;


param: cout_prod_j :=
A      1000    
B      2000    ;
      
