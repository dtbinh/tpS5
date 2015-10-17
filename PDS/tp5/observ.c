#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void boucle()
{
  while(1){
    printf("Fils numero %d\n",getpid());
    sleep(5);
  }
}



int main(int argc, char* argv[])
{
  int i;
  pid_t numero;

  for(i = 0; i < 10; i++){
    
    switch(fork()) {
    case -1: perror("Fork");
      return -1;

    case 0: boucle();
    default:;
   
    }
  }

  system("ps");
  for(i = 0; i < 10; i++){
    /*getchar();    Pour tester si le père n'attend pas son fils*/
    numero = wait(NULL);
    printf("Fils numero %d terminé\n", numero);
  }

  return 0;
}
