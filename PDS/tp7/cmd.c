/* mshell - a job manager */

#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jobs.h"

#define BOLD "\033[00;01m"
#define NORM "\033[00;00m"

void do_help() {
    printf("available commands are:\n");
    printf(" exit - cause the shell to exit\n");
    printf(BOLD "\t exit\n" NORM);
    printf(" jobs - display status of jobs in the current session\n");
    printf(BOLD "\t jobs\n" NORM);
    printf(" fg   - run a job identified by its pid or job id in the foreground\n");
    printf(BOLD "\t fg " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" bg   - run a job identified by its pid or job id in the background\n");
    printf(BOLD "\t bg " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" stop - stop a job identified by its pid or job id\n");
    printf(BOLD "\t stop " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" kill - kill a job identified by its pid or job id\n");
    printf(BOLD "\t kill " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" help - print this message\n");
    printf(BOLD "\t help\n" NORM);
    printf("\n");
    printf("ctrl-z and ctrl-c can be used to send a SIGTSTP and a SIGINT, respectively\n\n");
}

/* treat_argv - Determine pid or jobid and return the associated job structure */
struct job_t *treat_argv(char **argv) {
    struct job_t *jobp = NULL;

    /* Ignore command if no argument */
    if (argv[1] == NULL) {
        printf("%s command requires PID or %%jobid argument\n", argv[0]);
        return NULL;
    }

    /* Parse the required PID or %JID arg */
    if (isdigit((int) argv[1][0])) {
        pid_t pid = atoi(argv[1]);
        if (!(jobp = jobs_getjobpid(pid))) {
            printf("(%d): No such process\n", (int) pid);
            return NULL;
        }
    } else if (argv[1][0] == '%') {
        int jid = atoi(&argv[1][1]);
        if (!(jobp = jobs_getjobjid(jid))) {
            printf("%s: No such job\n", argv[1]);
            return NULL;
        }
    } else {
        printf("%s: argument must be a PID or %%jobid\n", argv[0]);
        return NULL;
    }

    return jobp;
}


/* do_bg - Execute the builtin bg command */
void do_bg(char **argv) {
    struct job_t *job;
    if(verbose)
        printf("do_bg: entering\n");

    job = treat_argv(argv);
    if(job == NULL){
        if(verbose)
            printf("do_bg: job not found\n");
        return;
    }
    job->jb_state = BG;

    if(verbose)
        printf("do_bg: exiting\n");
    return;
}

/* waitfg - Block until process pid is no longer the foreground process */
void waitfg(pid_t pid) {
    struct job_t *job;
    if(verbose)
        printf("waitfg: entering\n");

    job = jobs_getjobpid(pid);
    while(job->jb_state == FG){
        sleep(1);
        if(verbose)
            printf("waitfg: job state %d { 0: UNDEF, 1: BG, 2: FG, 3: ST }\n", job->jb_state);
    }

    if(verbose)
        printf("waitfg: exiting\n");
    return;
}

/* do_fg - Execute the builtin fg command */
void do_fg(char **argv) {
    struct job_t *job;
    if(verbose)
        printf("do_fg: entering\n");

    job = treat_argv(argv);
    if(job == NULL){
        if(verbose)
            printf("do_fg: job not found\n");
        return;
    }
    job->jb_state = FG;
    while(job->jb_state != BG)
        sleep(1);

    if(verbose)
        printf("do_fg: exiting\n");
    return;
}

/* do_stop - Execute the builtin stop command */
void do_stop(char **argv) {
    struct job_t *job;
    if(verbose)
        printf("do_stop: entering\n");

    job = treat_argv(argv);
    if(job == NULL){
        if(verbose)
            printf("do_stop: job not found\n");
        return;
    }
    if(kill(job->jb_pid, SIGTSTP) != 0 && verbose)
        printf("do_stop: stop failed\n");

    if(verbose)
        printf("do_stop: exiting\n");
    return;
}

/* do_kill - Execute the builtin kill command */
void do_kill(char **argv) {
    struct job_t *job;
    if(verbose)
        printf("do_kill: entering\n");

    job = treat_argv(argv);
    if(job == NULL){
        if(verbose)
            printf("do_kill: job not found\n");
        return;
    }
    if(kill(job->jb_pid, SIGKILL) != 0 && verbose)
        printf("do_kill: kill failed\n");

    if(verbose)
        printf("do_kill: exiting\n");
    return;
}

/* do_exit - Execute the builtin exit command */
void do_exit() {
    struct job_t *job;
    if(verbose)
        printf("do_exit: entering\n");

    while((job = jobs_getstoppedjob()) != NULL){
        if(kill(job->jb_pid, SIGKILL) != 0 && verbose)
            printf("do_exit: kill failed\n");
    }

    if(verbose)
        printf("do_exit: exiting\n");
    exit(EXIT_SUCCESS);
}

/* do_jobs - Print the job list */
void do_jobs() {
    if(verbose)
        printf("do_jobs: entering\n");

    jobs_listjobs();

    if(verbose)
        printf("do_jobs: exiting\n");
    return;
}
