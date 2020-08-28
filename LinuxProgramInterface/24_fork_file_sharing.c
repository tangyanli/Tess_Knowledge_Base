/* Sharing of file offset and open file status flags between parent and child*/
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

int main(int argc, char*argv[])
{
    int fd, flags;
    char temp[] = "/tmp/textXXXXXX";

    setbuf(stdout, NULL);  /* Disable buffering of stdout */

    fd = mkstemp(temp);
    if (fd == -1)
        errExit("mkstemp");

    printf("File offset before fork(): %lld\n", (long long)lseek(fd, 0, SEEK_CUR));
    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        errExit("fcntl - F_GETFL");
    printf("O_APPEND flag before fork is : %s\n", (flags & O_APPEND)? "ON" : "OFF");

    switch(fork())
    {
    case -1:
        errExit("fork");
    case 0:   /* Child: change file offset and status flags */
        if (lseek(fd, 1000, SEEK_SET) == -1)
            errExit("lseek");

        flags = fcntl(fd, F_GETFL);
        if (flags == -1)
            errExit("fcntl-F_GETFL");
        flags |= O_APPEND;
        if (fcntl(fd, F_SETFL, flags) == -1)
            errExit("fcntl-F_SETFL");
        _exit(EXIT_SUCCESS);
    default:   /*Parent: can see file change made by child */
        if (wait(NULL) == -1)
            errExit("wait");     /* wait for child exit */
        printf("child has exited\n");

        printf("File offset in parent: %lld\n", (long long)lseek(fd, 0, SEEK_CUR));

        flags = fcntl(fd, F_GETFL);
        if (flags == -1)
            errExit("fcntl- F_GETFL");
        printf("O_APPEND flag in parent is : %s\n", (flags & O_APPEND)? "ON":"OFF");
        exit(EXIT_SUCCESS);
    }
}
