#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const int BUF_SIZE = 2048;





/*
void tail_before_pos(int fd, int pos, int ntail)
{


}
*/




int index_tail_buffer(const char * buffer, int bufsize, int ntail, int * nlines)
{
	int i;
	int nb_ligne;

	nb_ligne = 0;


	for(i = bufsize; i > ntail; i--){
		if(buffer[i] == '\n')
			nb_ligne++;
	}
			

	if(ntail > nb_ligne){
		nline = bufsize;
		return -1;
	}

	return nb_ligne;
}




int mtail(const char *path, int ntail) 
{
  
	int index;
  int fd;
  int nb_chars;
  int nb_lines = 0;
  int read_lines = 0;
	char* tmp;  
	
  fd = open(path,O_RDONLY);
	tmp = malloc(BUF_SIZE);
  nb_chars = read(fd,tmp,BUF_SIZE);

  for(index = 0; index < nb_chars; index++) {
    if(tmp[index] == '\n') {
      nb_lines++;
    }

  }

  if(ntail > nb_lines) {
    perror("Erreur : le nombre de lignes spécifié est supérieur au nombre de lignes du fichier");
    return -1;
  }

  for(index = 0; index < nb_chars; index++) {
    if(read_lines >= nb_lines - ntail) {
      printf("%c", tmp[index]);
    }
    if(tmp[index] == '\n') {
      read_lines++;
    }

  }

  return 0;
}

int main(int argc, char* argv[])
 {
	char *pathname;  
	int ntail = 10;
  int c; 
  while((c = getopt(argc, argv, "n:")) != -1) {
    switch(c) {

    case 'n' :
      ntail = atoi(optarg);
      break;
    case '?' :
	printf("Bad argument: %s -n [nb_lines] file\n", argv[0]);
      return -1;

    }
  }
  if(optind != argc) {
    pathname = argv[optind];
  } else {
    printf("Bad argument: %s -n [nb_lines] file\n", argv[0]);
    return -1;
  }
  mtail(pathname, ntail);
  return 0;
}
