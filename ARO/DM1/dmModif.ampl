set DIVISION;
set REGIONS;
set CATEGORIE;
set DETAILLANTS;


/* Paramètres de départ */
param nb_pts_vente{DETAILLANTS} >= 0; #nombre de points de vente par detaillant
param huile{REGIONS, DETAILLANTS} >= 0; #nombre d'huile par region et par detaillant
param spiritueux{DETAILLANTS} >= 0; #nombre de spiritueux par detaillant
param categorie{DETAILLANTS};


/* Variables intermédiares */
/* Paramètres calculés */
param nb_total_pts_ventes := sum{det in DETAILLANTS} nb_pts_vente[det]; #nombre total de point de vente 
param total_huile{r in REGIONS} :=  sum{det in DETAILLANTS} huile[r,det] ; #nombre total d'huile par region
param total_spiritueux := sum{det in DETAILLANTS} spiritueux[det] ; #nombre total de spiritueux
param nb_detaillants_categories{c in CATEGORIE} :=  sum{det in DETAILLANTS : categorie[det] = c }; #nombre de detaillants par catégories



/* Variables à trouver */
var pts_vente_division {div in DIVISION} >=0;
var spiritueux_division {div in DIVISION} >=0;
var huile_division {div in DIVISION, r in REGIONS} >= 0;
var detaillants_division {div in DIVISION, c in CATEGORIE} >=0;
var div{DETAILLANTS};

/*
On doit rajouter une variable intermediare (ou non) qui va affecter un detaillant a une et une seule division.
Pour le resoudre, on pourrait utiliser un champs binaire comme dans l'exemple du probleme d'emploi du temps.
Si le detaillant est affecte, le champs est a 1, sinon il est a 0.
(possiblite qu'il y ait l'addition de plusieurs champs qui doivent valoir 1)
 */



/*Contraintes*/
/* Determiner si on doit garder DIVISION car differentes formules pour les deux. */

subject to division_pts_de_vente_D1{DIVISION div} :
	pts_vente_division[div] >= 0.35 * nb_total_pts_ventes, <= 0.45 * nb_total_pts_ventes;

subject to division_pts_de_vente_D2 :
	pts_vente_division[div]  >= 0.55 * nb_total_pts_ventes, <= 0.65 * nb_total_pts_ventes;


subject to division_spiritueux_D1 :
	spiritueux_division[div] >= 0.35 * total_spiritueux, <= 0.45 * total_spiritueux;

subject to division_spiritueux_D2 :
	spiritueux_division[div] >= 0.55 * total_spiritueux, <= 0.65 * total_spiritueux;


subject to division_huile_D1{r in REGIONS} :
	huile_division[div, r] >= 0.35 * total_huile[r], <= 0.45 * total_huile[r];

subject to division_huile_D2{r in REGIONS} :
	huile_division[div, r] >= 0.55 * total_huile[r], <= 0.65 * total_huile[r];


subject to division_detaillants_D1 {c in CATEGORIE} :
	detaillants_division[r] >= 0.35 * nb_detaillants_categories[c], <= 0.45 * nb_detaillants_categories[c];

subject to division_detaillants_D1 {c in CATEGORIE} :
	detaillants_division[r] >= 0.55 * nb_detaillants_categories[c], <= 0.65 * nb_detaillants_categories[c];



maximize truc :
	sum {g,r} huile_division[g,r] = total_huile[r];

maximize bidule :
	sum {g,r} huile_division[g,r] = total_huile[r];

maximize machin :
	sum {g,r} huile_division[g,r] = total_huile[r];

maximize chouette :
	sum {g,r} huile_division[g,r] = total_huile[r];




/*
subject to vente_minimale{DIVISION};

subject to division_huile_D1{r in REGIONS} :
sum {r in REGIONS} huile[r] >=0.35*total_huile[r], <= 0.45*total_huile[r];


subject to division_total{REGION};


subject nb_detaillants{CATEGORIE};*/











