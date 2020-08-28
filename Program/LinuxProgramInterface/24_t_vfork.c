#include "tlpi_hdr.h"

int main(int argc, char*argv[])
{
    int istack = 222;  /* Allocated in stack segment */

    switch(vfork())
    {
    case -1:
        errExit("vfork");
    case 0:
        /* CHild executes first, in parent's memory space */
        /* Even if we sleep for a while, parent still is not scheduled */
        sleep(3);
        write(STDOUT_FILENO, "child executing\n", 16);
        istack *= 3;
        _exit(EXIT_SUCCESS);
    default:
        /* Parent is blocked until child exits */
        write(STDOUT_FILENO, "parent executing\n", 17);
        printf("istack=%d\n", istack);
        exit(EXIT_SUCCESS);
     }
}
