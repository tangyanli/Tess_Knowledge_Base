/* -------------------------  */
/* Setting the RLIMIT_NPROC resource limit */
/* ------------------------*/

#include <sys/resource.h>
#include "print_rlimit.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    struct rlimit r1;
    int j;
    pid_t childPid;

    if (argc < 2 || argc > 3)
        usageErr("%s soft-limit [hard-limt]\n", argv[0]);

    printRlimit("Initial maximum process limit: ", RLIMIT_NPROC);


    /* Set new process limit (hard == soft if not specified) */
    r1.rlim_cur = (argv[1][0] == 'i') ? RLIM_INFINITY : getInt(argv[1], 0, "soft-limit");
    r1.rlim_max = (argc == 2) ? r1.rlim_cur : (argv[2][0] =='i') ? RLIM_INFINITY : getInt(argv[2], 0, "hard-limit");

    if(setrlimit(RLIMIT_NPROC, &r1) == -1)
        errExit("setrlimit");

    printRlimit("New maximum process limit:   ", RLIMIT_NPROC);

    /* Create as many children as possible */
    for (j=1;; j++)
    {
        switch(childPid = fork())
        {
        case -1: errExit("fork");
        case 0: _exit(EXIT_SUCCESS);   /* child */
        default:
            /* Parent: display message about each new child and let the resulting zombies accumulate */
            printf("child %d (PID=%ld) started\n", j, (long)childPid);
            break;
        }
    }

    exit(EXIT_SUCCESS);
}
