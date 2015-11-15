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
 
int pid, i, j; 
 int **pipefd;
 
  if(verbose)
    printf("do_pipe: entering\n");

  if((pipefd = malloc((nbcmd - 1) * sizeof(int*))) == NULL){
    if(verbose)
      printf("do_pipe: malloc of rows failed\n");
    return;
  }

  for(i = 0 ; i < nbcmd - 1 ; i++){
    if ((pipefd[i] = malloc(2 * sizeof(int))) == NULL){
      if(verbose)
	printf("do_pipe: malloc of columns failed\n");
      return;
    }
  }

  for(i = 0 ; i < nbcmd - 1 ; i++)
    pipe(pipefd[i]);

  
  switch(pid = fork()){
  case -1:
    if(verbose)
      perror("do_pipe: fork\n");
    return;
  case 0:
    if(dup2(pipefd[0][1], STDOUT_FILENO) == -1){
      if(verbose)
	perror("do_pipe: first dup2 failed\n");
      return;
    }
    for(i = 0 ; i < nbcmd - 1 ; i++){
      close(pipefd[i][0]);
      close(pipefd[i][1]);
    }
    if(execvp(cmds[0][0], cmds[0]) != 0){
      printf("Command '%s'", cmds[0][0]);
      return;
    }
  }

  for(i = 1 ; i < nbcmd - 1 ; i++){
   
    switch(fork()){
    case -1:
      if(verbose)
	printf("do_pipe: middle fork failed\n");
      return;
    case 0:
      if(dup2(pipefd[i-1][0], STDIN_FILENO) == -1){
	perror("do_pipe: middle (1) dup2 failed\n");
	return;
      }
      if(dup2(pipefd[i][1], STDOUT_FILENO) == -1){
	perror("do_pipe: middle (2) dup2 failed\n");
	return;
      }
      for(j = 0 ; j < nbcmd-1 ; j++){
	close(pipefd[j][0]);
	close(pipefd[j][1]);
      }
      if(execvp(cmds[i][0], cmds[i]) != 0){
	printf("Command '%s'", cmds[i][0]);
	return;
      }
    }
  }

  if(verbose)
    printf("do_pipe: last case\n");
  switch(fork()){
  case -1:
    if(verbose)
      perror("do_pipe: fork failed\n");
    return;
  case 0:
    if(dup2(pipefd[nbcmd - 2][0], STDIN_FILENO) == -1 ){
      if(verbose)
	perror("do_pipe: last dup2 failed\n");
      return;
    }
    for(i = 0 ; i < nbcmd - 1 ; i++){
      close(pipefd[i][0]);
      close(pipefd[i][1]);
    }
    if(execvp(cmds[nbcmd - 1][0], cmds[nbcmd - 1]) != 0){
      printf("Command '%s'", cmds[nbcmd - 1][0]);
      return;
    }
  }

  for(i = 0 ; i < nbcmd - 1 ; i++){
    close(pipefd[i][0]);
    close(pipefd[i][1]);
  }

  for(i = 0 ; i < nbcmd ; i++){
    if(bg)
      waitpid(-1, NULL, WNOHANG);
    else
      wait(NULL);
  }

  free(pipefd);

  if(verbose)
    printf("do_pipe: exiting\n");
  return;
}
