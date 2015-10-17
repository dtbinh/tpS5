set PROD;
param budget >= 0;
param employe_dispo >= 0;

param prix_production{PROD} >= 0;
param employe_production{PROD} >= 0;
param production_min{PROD} >= 0;
param audience{PROD} >= 0;


var qte_produite {p in PROD} >= production_min [p];

maximize profit :
sum {p in PROD} qte_produite [p] * audience[p];

subject to employe_limitee :
sum {p in PROD} qte_produite[p]*employe_production[p] <= employe_dispo;

subject to production_limitee :
sum {p in PROD}
(qte_produite [p] * prix_production[p]) <= budget;

data;

set PROD := tv mag radio;
param budget := 8000000;
param employe_dispo := 700;
param: audience prix_production production_min employe_production :=
tv     1800000  20000           10             7
mag    1000000  10000           0              21
radio  250000   2000            0              1;
