
static const int true = 1, false = 0;


int main(int argc, char* argv[])
{
  char opt;
  int and;
  int i, and, ret, status,success;

  i = 2; /*start with the first command on the line*/
  and = true;



  if(argc < 3){
    perror("Au moins un argument est attendu (--and/--or) suivi d'au moins une commande !");
    return -1;
  }

  /*get the opt*/

  if(and){
    success = true;

    while(i < argc){
     
      switch(fork())
	{
	case -1: perror("fork"); return -1;
	case 0 :ret = system(argv[i]);
	  if(ret == -1)
	    exit(EXIT_FAILURE); 
	  else 
	    exit(EXIT_SUCCESS);
	default:;	  
	}
      wait(&status);
      if(WEXITSTATUS(status) == EXIT_FAILURE)
	return -1;  
      i++; 
    }

  }

  else{
    success = false;
    
    while(i < argc-2){
      
      switch(fork())
	{
	case -1: perror("fork"); return -1;
	case 0 :ret = system(argv[i]);
	  if(ret == -1)
	    exit(EXIT_FAILURE); 
	  else 
	    exit(EXIT_SUCCESS);
	default:;	  
	}
      wait(&status);
      if(WEXITSTATUS(status) == EXIT_SUCCESS)
	return 0;  
      i++; 
    }


  }

  return success;
}
