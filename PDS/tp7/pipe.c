/* mshell - a job manager */
#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "pipe.h"


/*bg variable bool qui sert à savoir si on lance en avant/arriere plan*/
void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
 
  int i, pid, statut;
  int pipefd[2];

  /*pipefd = malloc(sizeof(int) * (nbcmd - 1)); passer pipefd en pointeur*/


  
  statut = pipe(pipefd);
  assert(statut == 0);

  for(i = 0; i < nbcmd; i++){
    /*mettre le code dans la boucle plus tard*/
  }
  
  switch(pid = fork()){
  case -1 : perror("fork\n"); return;
  case 0 : close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    execvp(&cmds[0][0][0],&cmds[0][0]);
    perror("La commande xxx n'a pas pu etre traité\n");
    exit(EXIT_FAILURE);
  default:;
  }

  switch(pid = fork()){
  case -1 : perror("fork\n"); return;
  case 0 : close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    execvp(&cmds[0][1][0],&cmds[0][1]);
    perror("La commande xxx n'a pas pu etre traité\n");
    exit(EXIT_FAILURE);
  default:;
  }

  
  /*free(pipefd)*/
  close(pipefd[0]);
  close(pipefd[1]);
  wait(NULL);
  wait(NULL);
  /*for(i = 0; i < nbcmd, i++)
    wait(NULL);*/
  
  exit(EXIT_SUCCESS);
  return;
}
