<<<<<<< HEAD
### Modèle pour vos Makefile

## Compilateur C et éditeur de liens
CC      = gcc

## Options pour la compilation du C
CFLAGS  = -Wall -Werror -ansi -pedantic
#  Spécifie la version de la norme POSIX à respecter
CFLAGS += -D_XOPEN_SOURCE=500
#  Active les informations de débogage
CFLAGS += -g

## Options de l’édition de liens
LDFLAGS  = -g

## Première cible
#  « make » sans argument construit sa première cible
#  Indiquez en dépendance le ou les binaires à construire
do: do


## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<

## Édition de liens
#  Définissez une règle par binaire que vous voulez créer
#  La commande devrait en général être identique pour chaque binaire
do: do.o makeargv.o
	${CC} ${LDFLAGS} -o $@ $^


clean:
	rm *.o || true

realclean: clean
	rm maccess || true

## Liste des pseudo-cibles
#  Ces cibles ne correspondent pas à des fichiers que l'on veut créer,
#  juste à des séquences que l'on veut pouvoir déclencher
.PHONY: all clean realclean
=======
# mshell - a job manager

CC      = gcc
CFLAGS  = -g
CFLAGS += -Wall -Werror -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
LDFLAGS = -g
SRCS    = common.c sighandlers.c jobs.c cmd.c pipe.c mshell.c
OBJS    = common.o sighandlers.o jobs.o cmd.o pipe.o mshell.o
EXEC    = mshell

# main entries
all: $(EXEC)

mshell: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# gcc -MM generated dependencies
cmd.o: cmd.c jobs.h common.h
common.o: common.c
jobs.o: jobs.c jobs.h common.h
mshell.o: mshell.c cmd.h sighandlers.h jobs.h common.h
sighandlers.o: sighandlers.c jobs.h common.h sighandlers.h

# misc
.PHONY: clean realclean
clean:
	rm -f $(OBJS) *~

realclean: clean
	rm -f $(EXEC)
>>>>>>> 1b88963a6d493532b85a5a6b3ab78a5ff3764412
