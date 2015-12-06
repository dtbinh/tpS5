#! /bin/sh -uf
#
# compteur-gc -- campagne d'appels à compteur-gc
#
# squelette de shell script

# La commande à tester
CMD=./compteur-gc
# le fichier à lui mettre en entrée
CMD_INPUT="alea.txt" 
# Le fichier de temps à générer
TIME_FILE="compteur-gc.dat"


# la commande gnu time
TIME_CMD="/usr/bin/time"
# les options de cette commande	
TIME_OPT="-f %e "

# initialisation du fichier de résultats
rm -f $TIME_FILE && echo "# size_genome nb_threads time" > $TIME_FILE

# un autre exemple de boucle
for size in `awk 'BEGIN { for( i=100; i<=1000000000; i*=2 ) print i }'`; do
	echo "Genome size : "$size" octet(s)" #affichage pour l'utilisateur de la taille courante
	
	#creation du genome ici
	./aleazard $size > $CMD_INPUT;
	
	for size2 in `awk 'BEGIN { for( i=1; i<=35; i*=2 ) print i }'`; do
	    echo "Nb threads : "$size2
	    echo -n $size" " >> $TIME_FILE
	    echo -n $size2" " >> $TIME_FILE	
	    $TIME_CMD $TIME_OPT $CMD $CMD_INPUT $size2 2>> $TIME_FILE
	    done
done

# un exemple de redirection des sorties standard et d'erreur
#$TIME_CMD "$TIME_OPT" ls > /dev/null 2>> $TIME_FILE

# eof
