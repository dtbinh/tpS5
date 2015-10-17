#include <limits.h> 
#include <unistd.h>
#include <stdio.h> 
#include <errno.h> 


int main( int argc, char *argv[])
{
  int rflag,wflag,xflag,vflag = 0;
  int i;
  int cpt;
  int mode;
  char* character;
  cpt = 0;
  mode = 0;

  if(argc < 2){
    printf("Invalid arguments (minimum 1 arg)\n");
    return -1;
  }

  for(i = 2; i < argc; i++){
    for(character = argv[i] ; *character != '\0'; character++){
      if(cpt == 0 && *character != '-' ){
	printf("Invalid arguments (need -)\n");
	return -1;
      }
      if(cpt != 0){
	switch(*character){
	case('r'): rflag = 1;break;
	case('w'): wflag = 1;break;
	case('x'): xflag = 1;break;
	case('v'): vflag = 1;break;
	default: printf("Error in the argumentation (unknow char)\n");return-1;
	}
      }
      cpt++;
    }
  }
  if(rflag)
    mode = mode | R_OK;
  if(wflag)
    mode = mode | W_OK;
  if(xflag)
    mode = mode | X_OK;

  if(access(argv[1], mode) != 0){
    if(vflag){
      perror("Access");
      printf("Erreur numero : %d\n",errno);
    }
    return -1;
  }	

  return 0;
}

