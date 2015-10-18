#include <stdio.h>
#include <stdio.h>                                                             
#include <unistd.h>                                                            
#include <limits.h>                                                            
#include <sys/types.h>                                                         
#include <dirent.h>                                                            
#include <sys/types.h>                                                         
#include <sys/stat.h>                                                          
#include <assert.h>                                                            
#include <string.h>

static int opt_apparent_size = 0;



int validName(char * name){
  return (strcmp(name, ".") && strcmp(name, ".."));
}


int du_file(const char * pathname)
{
  struct stat st;
  struct dirent* stdir;
  char current [PATH_MAX+1];
  int size;/*count dir size*/
  DIR * dir;
  
  /*Check if the st is init*/
  assert(lstat(pathname, &st) == 0);

  /*if it is a regular file, return the size (using the opt)*/
  if(S_ISREG(st.st_mode) || S_ISLNK(st.st_mode) ){
    return opt_apparent_size ? st.st_size : st.st_blocks;
  }
  
  /*If is a directory*/
  if(S_ISDIR(st.st_mode)){
    /*Open directory*/
    dir = opendir(pathname);
    /*add the directory size (unsing the opt)*/
    size = opt_apparent_size ? st.st_size : st.st_blocks ;
    
    while( (stdir = readdir(dir)) != NULL ){
      /*if the directory is the same or the parent ignore*/
      if(!validName(stdir->d_name)){
	continue;
      }
      /*add the path of the current dir to the given path*/
      snprintf(current,PATH_MAX,"%s/%s",pathname, stdir->d_name);
      size+= du_file(current);  
    }
    closedir(dir);
    return size;
  }

  /*4 autres type possibles*/
  printf("Warning the pathname were ignored because the type of file is not treated");
  return 0;
    
}


int main(int argc, char*argv[])
{
  int size = du_file(argv[1]);
  printf("Size : %d\n", size);
  return 0;
}
  
 
                                                          
