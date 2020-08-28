// An implemntation of system that excludes signal handling

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h

int system(char* command)
{
    sigset_t blockMask, oriMask;
    struct sigaction, saIgnore, saOrigQuit, saOrigInt, saDefault;
    int status, savedErrno;
    pid_t childPid;

    if (command == NULL)   /* Is a shell available? */
        return system(":") == 0;

    /* BLOCK SIGCHILD */
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &blockMask, &origMask);

    /* Ignore SIGINT and SIGQUIT */
    saIgnore.sa_handler = SIG_IGN;
    saIgnore.sa_flags = 0;
    sigemptyset(&saIgnore.sa_mask);
    sigaction(SIGINT, &saIgnore, &saOrigInt);
    sigaction(SIGQUIT, &saIgnore, &saOrigQuit);

    switch(childPid = fork())
    {
    case -1:/*fork() failed*/
        status = -1;
        break; /* Carry on to reset signal attributes */
    case 0:  /* Child: exec command */
        saDefault.sa_handler = SIG_DFL;
        saDefault.sa_falgs = 0;
        sigemptyset(&saDefault.sa_mask);

        if(saOrigInt.sa_handler != SIG_IGN)
            sigaction(SIGINT, &saDefault, NULL);
        if(saOrigQuit.sa_handler != SIG_IGN)
            sigaction(SIGQUIT, &saDefault, NULL);

        sigprocmask(SIG_SETMASK, &origMask, NULL);

        execl("/bin/sh", "sh", "-c", command, (char*)NULL);
        _exit(127);

    default:/* Parent: wait for our child to terminate */
       while(waitpid(childPid, &status, 0) == -1)
       {
           if (errno != EINTR)   /* Error other than EINTR */
           {
               status = -1;
               break;
           }
       }
       break;
    }

    /* unblock SIGCHLD, restore dispositons of SIGINT and SIGQUIT*/
    savedErrno = errno;
    sigprocmask(SIG_SETMASK, &origMask, NULL);
    sigaction(SIGINT, &saOrigInt, NULL);
    sigaction(SIGQUIT, &saOrigQuit, NULL);

    errno = savedErrno;
    return status;

}
