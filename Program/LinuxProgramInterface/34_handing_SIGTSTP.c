/* --------------------  */
/* Handing SIGSTP */
/*---------------------  */

#include <signal.h>
#include "tlpi_hdr.h"

static void tstpHandler(int sig)
{
    sigset_t tstpMask, prevMask;
    int savedErrno;
    struct sigaction sa;

    savedErrno = errno;

    printf("Caught SIGTSTP\n");

    if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
        errExit("signal");

    raise(SIGTSTP);   /* Generate a further SIGTSTP */

    /* Unblock SIGTSTP; the pending SIGTSTP immediately suspends the program */
    sigemptyset(&tstpMask);
    sigaddset(&tstpMask, SIGTSTP);
    if (sigprocmask(SIG_UNBLOCK, &tstpMask, &prevMask) == -1)
        errExit("sigprocmask");

    /* Execution resumes here after SIGCONT */
    if (sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1)
        errExit("sigprocmask");   /* Reblock SIGTSTP */

    sigemptyset(&sa.sa_mask);  /* Reestablish handler */
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = tstpHandler;
    if (sigaction(SIGTSTP, &sa, NULL) == -1)
        errExit("sigaction");

    printf("Exiting SIGTSTP handler\n");
    errno = savedErrno;
}

int main(int argc, char* argv[])
{
    struct sigaction sa;

    /* Only establish handler for SIGTSTP if it is not being ignored */
    if (sigaction(SIGTSTP, NULL, &sa) == -1)
        errExit("sigaction");

    if (sa.sa_handler != SIG_IGN)
    {
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = tstpHandler;

        if (sigaction(SIGTSTP, &sa, NULL) == -1)
            errExit("sigaction");
    }

    for (;;)
    {
        pause();
        printf("Main\n");
    }
}
