#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <wait.h>
#include "makeargv.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>


static const int true = 1, false = 0;



int isOpt(char * s){
  if(strcmp(s,"--or") == 0 || strcmp(s,"--and") == 0 || strcmp(s,"--kill") == 0 || strcmp(s,"--cc") == 0 )
    return true;
  return false;
}

int main(int argc, char* argv[])
{
  char **cmdargv;
  char **arg;
 
  int i, and, idx, nb_cmd, ret, status, success, cc, kill;
  int *pid;
  char cmd[PATH_MAX+1];

  and = -1;
  cc = false;
  kill = false;
  nb_cmd = argc -2;
  idx = 0;

  if(argc < 3){
    printf("Au moins un argument est attendu (--and/--or) suivi d'au moins une commande !\n");
    return -1;
  }

  for (i = 1; i < argc; i++) {
    if(strcmp(argv[i],"--or") == 0){
      and = false;
      success = false;   
    }
    else if(strcmp(argv[i],"--and") == 0){
      and = true; 
      success = true;
    }
    else if(strcmp(argv[i],"--cc") == 0)
      cc = true;  
    
    else if(strcmp(argv[i],"--kill") == 0)
      kill = true;
  }

  if(cc)
    nb_cmd--;
  if(kill)
    nb_cmd--;
   
  pid = malloc(nb_cmd * sizeof(int));

  if(and < 0){
    printf("Au moins un argument est attendu (--and/--or) suivi d'au moins une commande !\n");
    return -1;
  }


  for (i = 1; i < argc; i++) { /* traiter argv[i] */
       
    if(!isOpt(argv[i])){
  
      /* création du argv de l'argument i */
      status = makeargv(argv[i], " \t", &cmdargv);
      assert(status > 0);

      /* test: affichage */
      fprintf(stderr, "[%s]\t%% ", cmdargv[0]);
      for (arg=cmdargv; *arg; arg++){
	fprintf(stderr, "%s ", *arg);
      }
      fprintf(stderr, "\n");
  
      switch(pid[idx] = fork())
	{
	case -1: perror("fork"); return -1;

	case 0 : sprintf(cmd, "/bin/%s", cmdargv[0]);   
	  ret = execv(cmd, cmdargv);
	  if(ret == -1){
	    sprintf(cmd, "/usr/bin/%s", cmdargv[0]);	   
	    ret = execv(cmd, cmdargv);
	  }
	  if(ret == -1){	   
	    exit(EXIT_FAILURE);
	  }
	  else{
	   
	    exit(EXIT_SUCCESS);
	  }
	default:;	  
	}
      idx++;
    }
  }
  

    

  /* libération mémoire */
  freeargv(cmdargv);
 
  for (i = 0; i < nb_cmd; i++) {
    wait(&status);
    if(and){/* --and version*/
 
      if(WEXITSTATUS(status) == EXIT_FAILURE){
	success = false;
	if(cc){
	  if(kill){
	    for(i = 0; i < nb_cmd; i++){
	      sprintf(cmd, "kill -kill %d  >/dev/null 2>&1", pid[i]);
	      system(cmd);
	    }
	    free(pid);
	  }
	  return -1;  
	}
	 
      }
    }
    else{/* --or version*/
      if(WEXITSTATUS(status) == EXIT_SUCCESS){
	success = true;
	if(cc){
	  if(kill){
	    for(i = 0; i <nb_cmd; i++){
	      sprintf(cmd, "kill -kill %d  >/dev/null 2>&1", pid[i]);
	      system(cmd);
	    }
	    free(pid);
	  }
	  return 0;  
	}
      }
    }
   
  }
  
  if(success){
    printf("Success\n");
    return 0;
  }
  else{
    printf("Fail\n");
    return -1;
  }
  
}
