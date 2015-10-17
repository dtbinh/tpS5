#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>




int main(int argc, char* argv[])
{

  int i;			
  int ch;
  FILE *file;
	
  if(argc < 2){
    printf("Error need a minimum of 2 arguments");
    return -1;
  }

  for(i = 1 ; i < argc; i++){	
   
    file = fopen(argv[i],"r");

    if(file == NULL){
      perror("fopen");	
      return -1;
    }
    while( (ch=fgetc(file)) != EOF)
      fputc(ch, stdout);

    fclose(file);
    printf("\n");/*Saut de ligne entre les fichiers*/
  
  }
  return 0;
}
