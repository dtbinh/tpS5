set DIVISION;
set REGIONS;
set CATEGORIE;
set DETAILLANTS;



param nb_pts_vente >= 0;

param huile{DETAILLANTS} >= 0;
param spiritueux{DETAILLANTS} >= 0;




var total_huile{r in REGIONS} =  sum{d in DETAILLANTS} huile[r,d] ;

var total_huile{r in REGIONS,} =  sum{d in DETAILLANTS} huile[r,d] ;



subject to division_huile_D1{r in REGIONS} :
total_huile[r] >= 0.35 * total_huile[r], <= 0.45 * total_huile[r];





/*
subject to vente_minimale{DIVISION};

subject to division_huile_D1{r in REGIONS} :
sum {r in REGIONS} huile[r] >=0.35*total_huile[r], <= 0.45*total_huile[r];


subject to division_total{REGION};


subject nb_detaillants{CATEGORIE};*/











