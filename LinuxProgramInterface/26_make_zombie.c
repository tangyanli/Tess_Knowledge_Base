#include <signal.h>
#include <libgen.h>
#include "tlpi_hdr.h"  /* Declaration of printWaitStatus() */

#define CDM_SIZE 200

void handler(int sig)
{
    printf("\nCatch signal: %d\n", sig);
}

int main(int argc, char* argv[])
{
    char cmd[CDM_SIZE];
    pid_t childPid;
    struct sigaction ac;
    sigset_t mask;

    setbuf(stdout, NULL);  /* Disable buffering of stdout */
    printf("Parent PID = %ld\n", (long)getpid());

    switch(childPid = fork())
    {
    case -1:
        errExit("fork");

    case 0: /* Child: immediately exits to become zombie */
        sleep(3);
        printf("child (PID=%ld) exiting\n",(long)getpid());
        _exit(EXIT_SUCCESS);

    default:
        sigemptyset(&ac.sa_mask);
        ac.sa_handler = handler;
        if(sigaction(SIGCHLD, &ac, NULL) == -1)
           exit(EXIT_FAILURE);

        sigfillset(&mask);
        sigdelset(&mask, SIGCHLD);
        sigsuspend(&mask);

        snprintf(cmd, CDM_SIZE, "ps|grep %s", basename(argv[0]));
        cmd[CDM_SIZE-1] = '\0';  /* Ensure string is null-terminated*/
        system(cmd);  /* view zombie child */

        /* Now send the "sure kill" signal to the zombie*/
        if (kill(childPid, SIGKILL) == -1)
            errMsg("Kill");
        sleep(3);   /* Give child a chance to react to signal */
        printf("\nAfter sending SIGKILL to zombie (PID=%ld):\n", (long)childPid);
        system(cmd);   /* View zombie child again */
        exit(EXIT_SUCCESS);
    }
}
