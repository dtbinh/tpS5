#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>




struct cpt_gc_arg
{
  char *bloc;
  unsigned long taille;
  sem_t sem;
  unsigned long cpt;
};



void * compteur_gc(void * arg2)
{
   unsigned long i, taille, cptr = 0;

   struct cpt_gc_arg *arg = (struct cpt_gc_arg *)arg2;

  taille = arg->taille;

  printf("dans le thread\n");

  for (i = 0; i < taille; i++)
    if (arg->bloc[i] == 'G' || arg->bloc[i] == 'C')
      cptr++;

  printf("fin thread\n");
  sem_wait(&arg->sem);
  arg->cpt += cptr;
  sem_post(&arg->sem);

 
  pthread_exit(NULL);


}

int main(int argc, char *argv[]) {
  struct stat st;
  int fd;
  char *tampon;
  int lus, nb_threads, i;
  off_t taille = 0;
  struct timespec debut, fin;
  struct cpt_gc_arg arg;
  pthread_t  * t_tab;

  if(argc < 3){
    printf("Usage %s \"fichier\" \"nombre de threads\"", argv[0]);
    return -1;
  }
  assert(argv[1] != NULL);

  nb_threads = atoi(argv[2]);
    
  /* Quelle taille ? */
  assert(stat(argv[1], &st) != -1);
  tampon = malloc(st.st_size);
  assert(tampon != NULL);

  /* Chargement en mémoire */
  fd = open(argv[1], O_RDONLY);
  assert(fd != -1);
  while ((lus = read(fd, tampon + taille, st.st_size - taille)) > 0)
    taille += lus;
  assert(lus != -1);
  assert(taille == st.st_size);/*verification de la taille du fichier*/
  close(fd);
  printf("Size = %ld\n", taille);

  /*init la semaphore*/
  sem_init(&arg.sem, 1, 1);

  /*init le compteur*/
  arg.cpt = 0;
  arg.taille = taille/nb_threads;

  /* Calcul proprement dit */
  assert(clock_gettime(CLOCK_MONOTONIC, &debut) != -1);
    
  t_tab = malloc(sizeof(pthread_t) *  nb_threads);

  for(i = 0; i < nb_threads; i++){
    printf("i : %d ", i);
    pthread_t  thread;
    t_tab[i] = thread;
    arg.bloc = &tampon[i * arg.taille];
   
    printf("bloc index : %ld\n", i * arg.taille);

    if(taille%nb_threads != 0 && i == nb_threads - 1){
      printf("Modulo\n");
      arg.taille = arg.taille + (taille%nb_threads);
    }
    printf("Taille : %ld\n", arg.taille );

    pthread_create (&thread, NULL, compteur_gc, &arg); 
  }

   /*On attends tout les threads*/
   for(i = 0; i < nb_threads; i++){
     pthread_join(t_tab[i], NULL);
   }
   printf("apres creation attente des threads\n");

   assert(clock_gettime(CLOCK_MONOTONIC, &fin) != -1);

   

  /* Affichage des résultats */
  printf("Nombres de GC:   %ld\n", arg.cpt);
  printf("Taux de GC:      %lf\n", ((double) arg.cpt) / ((double) taille));

  fin.tv_sec  -= debut.tv_sec;
  fin.tv_nsec -= debut.tv_nsec;
  if (fin.tv_nsec < 0) {
    fin.tv_sec--;
    fin.tv_nsec += 1000000000;
  }
  printf("Durée de calcul: %ld.%09ld\n", fin.tv_sec, fin.tv_nsec);
  printf("(Attention: très peu de chiffres après la virgule sont réellement significatifs !)\n");

  return 0;
}
