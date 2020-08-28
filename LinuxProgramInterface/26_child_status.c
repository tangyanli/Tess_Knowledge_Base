#include <sys/wait.h>
#include "print_wait_status.h"
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    int status;
    pid_t childPid;
    siginfo_t info;

    if(argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [exit-status]\n", argv[0]);

    switch(fork())
    {
    case -1:
        errExit("fork");
        /* Child: either exits immediately with given status or loops waiting for signals */
    case 0:
        printf("child started with PID=%ld\n", (long)getpid());
        if(argc > 1)
            exit(getInt(argv[1], 0, "exit-status"));
        else    /* Otherwise, wait for signals */
            for(;;)
                pause();
        exit(EXIT_FAILURE);
    default:
        for(;;)
        {
            //childPid = waitpid(-1, &status, WUNTRACED
//#ifdef WCONTINUED
//                               | WCONTINUED
//#endif
//               );

            if (waitid(P_ALL, -1, &info, WEXITED | WSTOPPED | WCONTINUED) == 0)
            {
                /* Print status in hex, and as separate decimal bytes */
                printf("Waitpid() returned: PID=%ld; status=0x%04x (%d,%d)\n",
                       (long)info.si_pid,
                       (unsigned int)info.si_status, (info.si_status)>>8, (info.si_status)&0xff);
                printWaitStatus(NULL, info.si_status);

                switch(info.si_code)
                {
                case CLD_EXITED:
                    printf("The child terminated by calling _exit.\n");
                    break;
                case CLD_KILLED:
                    printf("The child was killed by a signal\n");
                    break;
                case CLD_STOPPED:
                    printf("The child was topped by a signal\n");
                    break;
                default:
                    printf("The child resumed execution as a consequence of receiving a SIGCOUNT signal\n");
                    break;
                }

                if (WIFEXITED(info.si_status) || WIFSIGNALED(info.si_status))
                    exit(EXIT_SUCCESS);
            }
        }
    }
}
