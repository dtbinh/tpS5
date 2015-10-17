#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef  int (*func_t) (int);

static const int true = 1, false = 0;




int isPair(int i)
{
  if(i % 2 == 0)
    return true;
  return false;
}


int isPos(int i)
{
  if(i >= 0)
    return true;
  return false;
}




int multif (func_t f[], int args[], int n)
{
  int i;
  int ret;
  int status;
  int sol = true;
  
  for(i = 0; i < n; i++){
    switch(fork()) {
    case -1: perror("fork");
      return -1;
    case 0: ret = f[i](args[i]);
      if(ret)
	exit(EXIT_SUCCESS);
      else
	exit(EXIT_FAILURE); 	
    default:;
    }
  }
  for(i = 0; i < n; i++){
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE)
      sol = false;   
  }  
  return sol;
}



int main(int argc, char* argv[])
{


  func_t fct[3];
  int arg[3];
  int ret;
  int a, b, c;

  if(argc != 4){
    perror("3 int en argument sont attendus !");
    return -1;
  }

   a =  atoi(argv[1]);
   b =  atoi(argv[2]);
   c =  atoi(argv[3]);

  
  fct[0]= isPair;
  fct[1]= isPair;
  fct[2]= isPos;
  
  arg[0]= a;
  arg[1]= b;
  arg[2]= c;
  
  ret = multif(fct, arg, 3);
 
 
  if(ret){
    printf("Statut : true\n");
    return 0;
  }
  else{
    printf("Statut : false\n");
    return 1;
  }
  
}
