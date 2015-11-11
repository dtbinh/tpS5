### Modèle pour vos Makefile

## Compilateur C et éditeur de liens
CC      = gcc

## Options pour la compilation du C show all warnings
CFLAGS  = -Wall 
#  Active les informations de débogage
CFLAGS += -g
#
CFLAGS += -std=c99



## Première cible
#  « make » sans argument construit sa première cible
#  Indiquez en dépendance le ou les binaires à construire
all: testAnalyseur testAnalyseur2 graph2visu


## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<

## Édition de liens
#  Définissez une règle par binaire que vous voulez créer
#  La commande devrait en général être identique pour chaque binaire
graph2visu: genereGraphVisu.o graphe.o
	${CC} ${CFLAGS} -o $@ $^
testAnalyseur: testAnalyseur.o graphe.o
	${CC} ${CFLAGS} -o $@ $^
testAnalyseur2: testAnalyseur2.o graphe.o
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm *.o || true

realclean: clean
	rm graph2visu ||  true
	rm testAnalyseur ||  true
	rm testAnalyseur2 ||  true
## Liste des pseudo-cibles
#  Ces cibles ne correspondent pas à des fichiers que l'on veut créer,
#  juste à des séquences que l'on veut pouvoir déclencher
.PHONY: all clean realclean
