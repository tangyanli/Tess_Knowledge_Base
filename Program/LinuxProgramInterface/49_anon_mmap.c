/* The program demonstrate the use of either MAP_ANONYMOUS or /dev/zero to share*/
/* a mapped region between parent and child processes  */
/* Sharing an anonymous mapping between parent and child processes */

#ifdef USE_MAP_ANON
#define _BSD_SOURCE   /* Get MAP_ANONYMOUS definition */
#endif
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    int *addr;     /* Pointer to shared memory region */

#ifdef USE_MAP_ANON
    printf("Define the macro: USE_MAP_ANON");
    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
#else
    int fd;
    fd = open("/dev/zero", O_RDWR);
    if (fd == -1)
        errExit("open");

    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    if (close(fd) == -1)
        errExit("close");
#endif

    *addr = 1; /* Initialize integer in mapped region*/
    switch(fork())
    {
    case -1:
        errExit("fork");
    case 0:
        printf("Child started, value = %d\n", *addr);
        (*addr)++;

        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");
        exit(EXIT_SUCCESS);
    default:
        if (wait(NULL) == -1)
            errExit("wait");
        printf("In parent, value = %d\n", *addr);
        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");
        exit(EXIT_SUCCESS);
    }
}
