/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


#include "jobs.h"
#include "common.h"
#include "sighandlers.h"

/*
 * wrapper for the sigaction function
 */
int sigaction_wrapper(int signum, handler_t * handler) {

  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  if(sigaction(signum, &action, NULL) < 0){
    unix_error("sigaction");
    return -1;
  }

  
    return 1;
}

/*
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children
 */
void sigchld_handler(int sig) {
  int status;
  pid_t pid;
  struct job_t * job;
 
  if (verbose)
        printf("sigchld_handler: entering\n");
  while(( pid = waitpid(-1, & status, WUNTRACED | WNOHANG)) > 0){
    if(WIFEXITED(status)){
      jobs_deletejob(pid);
      if(verbose)
	printf("sigchld_handler: %d exited", (int) pid);
    }
    else if(WIFEXITED(status)){
      jobs_deletejob(pid);
      if(verbose)
	printf("sigchld_handler: %d signaled", (int) pid);
    }
    else if(WIFEXITED(status)){
      job = jobs_getjobpid(pid);
      job-> jb_state = ST;
      if(verbose)
	printf("sigchld_handler: %d stopped", (int) pid);
    }   
  }
    if (verbose)
        printf("sigchld_handler: exiting\n");

    return;
}

/*
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.
 */
void sigint_handler(int sig) {
  int pid;
  if (verbose)
    printf("sigint_handler: entering\n");


  if( (pid = jobs_fgpid()) != 0){

    if(kill(pid, SIGINT) < 0){
      if(verbose)
	unix_error("signal kill");
    }
    else if(verbose){
      printf("sigint_handler: signal SIGINT sent\n");
    }
  }  
  if (verbose)
    printf("sigint_handler: exiting\n");
  return;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.
 */
void sigtstp_handler(int sig) {
  int pid;
  if (verbose)
    printf("sigtstp_handler: entering\n");

  if( (pid = jobs_fgpid()) != 0){

    if(kill(pid, SIGTSTP) < 0){
      if(verbose)
	unix_error("signal kill");
    }
    else if(verbose){
      printf("sigtstp_handler: signal SIGINT sent\n");
    }
  }  
  if (verbose)
    printf("sigtstp_handler: exiting\n");
  return;
}
