#define _GNU_SOURCE  /* Get strsignal() declaration from <string.h> */
#include <string.h>
#include <sys/wait.h>
#include "print_wait_status.h"  /* Declaration of printWaitStatus() */

void printWaitStatus(const char* msg, int status)
{
    if (msg != NULL)
        printf("%s", msg);

    if (WIFEXITED(status))
    {
        printf("Child exited, status=%d\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {
        printf("Child killed by signal %d (%s)",
               WTERMSIG(status),
               strsignal(WTERMSIG(status)));
        #ifdef WCOREDUMP
        if(WCOREDUMP(status))
            printf("(core dumped)");
        #endif
        printf("\n");
    }
    else if(WIFSTOPPED(status))
    {
        printf("Child stopped by signal %d (%s)\n",
               WSTOPSIG(status),
               strsignal(WSTOPSIG(status)));
        #ifdef WIFCONTINUED
    }else if(WIFCONTINUED(status))
    {
        printf("Child continued\n");
	#endif

    }
    else
    {
        printf("What happended to this child? (status=%x)\n", (unsigned int)status);
    }
}
