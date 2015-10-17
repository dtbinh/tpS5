#! /bin/sh -uf
#
# mcat -- campagne d'appels à mcat-scd
#
# squelette de shell script

# La commande à tester
MCAT=./mcat-scd
# le fichier à lui mettre en entrée
MCAT_INPUT=entree.txt 
# Le fichier de temps à générer
TIME_FILE=mcat-tm.dat

# Le fichier ou ecrire le cat
CAT_FILE=sortie.txt

# la commande gnu time
TIME_CMD="/usr/bin/time"
# les options de cette commande	
TIME_OPT="-f %e "

# initialisation du fichier de résultats
rm -f $TIME_FILE && echo "# size real user sys" > $TIME_FILE

# un autre exemple de boucle
for size in `awk 'BEGIN { for( i=1; i<=8388608; i*=2 ) print i }'`; do
	export MCAT_BUFSIZ=$size #export de la nouvelle size
	echo "Tampon de taille : "$MCAT_BUFSIZ" octet(s)" #affichage pour l'utilisateur de la taille courante
	echo -n $MCAT_BUFSIZ " " >> $TIME_FILE	
	$TIME_CMD $TIME_OPT $MCAT $MCAT_INPUT > $CAT_FILE  2>> $TIME_FILE	
	
done

# un exemple de redirection des sorties standard et d'erreur
#$TIME_CMD "$TIME_OPT" ls > /dev/null 2>> $TIME_FILE

# eof
