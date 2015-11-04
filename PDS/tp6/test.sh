#!/bin/bash


# ce qui se passe quand vous exécutez une seule commande ;
./do --and true || echo "Erreur: true a renvoyé false"
./do --and false && echo "Erreur: false a renvoyé true"
echo

# ce qui se passe quand vous êtes en mode and et qu’au moins l’une des commandes échoue ;
./do --and true false true && echo "Erreur: and true false true a renvoyé true"
echo

# ce qui se passe quand vous êtes en mode and et que toutes les commandes réussissent ;
./do --and true true true || echo "Erreur: and true true true a renvoyé false"
echo

# les cas similaires quand vous êtes en mode or ;
./do --or false false && echo "Erreur: or false false a renvoyé true"
./do --or true  true  || echo "Erreur: or true true a renvoyé false"
echo

# ce qui se passe quand vous êtes en mode and cc et que l’une des commandes échoue plus vite que la terminaison des autres ;
./do --and --cc false xterm && echo "Erreur: and false xterm a renvoyé true"
echo

# les cas similaires quand elles n’échouent pas ou que le mode est or cc ;
./do --or --cc true xterm || echo "Erreur: or true xterm a renvoyé false"
echo

# les cas similaires en ajoutant kill au mode.
./do --and --cc --kill false xterm && echo "Erreur: and false xterm a renvoyé true"
./do --or --cc --kill true xterm || echo "Erreur: or true xterm a renvoyé false"
echo

echo "A l'issue des tests, seuls 2 xterm sont censés être toujours présents (4 ont été lancés, dont 2 tués avec --kill)."
