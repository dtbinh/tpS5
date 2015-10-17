#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void count()
{
  int i;
  for(i = 0; i < 1000000000; i++);
}


int main(int argc, char* argv[])
{
  int i;
  int statut;
  pid_t numero;
  
  for(i = 0; i < 10; i++){
    
    switch(fork()) {
    case -1: perror("Fork");
      return -1;

    case 0: 
      count();
      printf("Fils num %d  à mi-chemin\n", getpid());
      count();      
      exit(EXIT_SUCCESS);
    default:;
    }
  }
  for(i = 0; i < 10; i++){
    numero = wait(&statut);
    printf("Arrivée du fils numero %d\n", numero);
  }
  
  return 0;
}
