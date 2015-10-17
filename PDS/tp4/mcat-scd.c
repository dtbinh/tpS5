
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>




int main(int argc, char* argv[])
{

	int i;		
	char * size_buf_c ;
	int size_buf;
	int fd;
	int nb_char;
	char * buffer;
	

	size_buf_c = getenv("MCAT_BUFSIZ");
	assert(size_buf_c);
	size_buf = atoi(size_buf_c);
	
	buffer = malloc(size_buf*sizeof(char));
	
	if(argc < 2){
		printf("Error need a minimum of 2 arguments");
        return -1;
	}

	for(i = 1 ; i < argc; i++){	
    fd = open(argv[i], O_RDONLY, S_IRUSR);
		
    if(fd == -1){
	    printf("Error while opening the file %s\n", argv[i]);
	    return -1;		
	}
    while ( (nb_char = read(fd, buffer, sizeof(buffer))) > 0 )
       write(STDOUT_FILENO, buffer, nb_char);
	
    close(fd);		
		printf("\n");/*Saut de ligne entre les fichiers*/
	}
	free(buffer);
	return 0;
}
