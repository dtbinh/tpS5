#include <limits.h> 
#include <unistd.h>
#include <stdio.h> 
#include <errno.h> 


int main( int argc, char *argv[])
{
  int rflag,wflag,xflag,vflag = 0;
  int mode;
  char opt;
  mode = 0;

  if(argc < 2){
    printf("Invalid arguments (minimum 1 arg)\n");
    return -1;
  }
  while ((opt = getopt(argc, argv, "rwxv")) != -1) {
    switch (opt) {
    case 'r':rflag = 1;break;
    case 'w':wflag = 1;break;
    case 'x':xflag = 1;break;
    case 'v':vflag = 1;break;
    default:
      printf("Arguments: %s [-r] [-w] [-x] [-v]\n", argv[0]);
      return -1;
    }
  }

  if(rflag)
    mode = mode | R_OK;
  if(wflag)
    mode = mode | W_OK;
  if(xflag)
    mode = mode | X_OK;
  printf("Mode : %d\n", mode);
  
  if(access(argv[2], mode) != 0 ){
    if(vflag){
      perror("Access");
      printf("Erreur numero : %d\n",errno);
    }
    return -1;
  }
	
    return 0;
}

