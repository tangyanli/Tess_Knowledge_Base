/*---------------------------------------------------- */
/* Using select() to monitor multiple file descriptors */
/* ----------------------------------------------------*/

#include <sys/time.h>
#define _GNU_SOURCE
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>
#include "tlpi_hdr.h"

static int pfd[2];

static void handler(int sig)
{
    int savedErrno;

    savedErrno = errno;
    if (write(pfd[1], "x", 1) == -1 && errno != EAGAIN)
        errExit("write");
    errno = savedErrno;
}

int main(int argc, char* argv[])
{
    //fd_set readfds;
    int ready, nfds, flags;
    struct timeval timeout;
    struct timeval *pto;
    struct sigaction sa;
    char ch;
    struct pollfd fd;

    /*... Initialize timeout, readfds, and nfds for select() */
    if (pipe(pfd) == -1)
        errExit("pipe");

    //FD_SET(pfd[0], &readfds);
    nfds = pfd[0] + 1;
    flags = fcntl(pfd[0], F_GETFL);
    if (flags == -1)
        errExit("fcntl-F_GETFL");
    flags |= O_NONBLOCK;
    if (fcntl(pfd[0], F_SETFL, flags) == -1)
        errExit("fcntl-F_SETFL");

    flags = fcntl(pfd[1], F_GETFL);
    if (flags == -1)
        errExit("fcntl-F_GETFL");
    flags |= O_NONBLOCK;
    if (fcntl(pfd[1], F_SETFL, flags) == -1)
        errExit("fcntl-F_SETFL");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");

    fd.fd = pfd[0];
    fd.events = POLLIN;

    while((ready = poll(&fd, 1, -1) == -1) && errno == EINTR)
    {
        continue;    /* Restart if interrupted by signal*/
    }

    if (ready == -1)
        errExit("select");

    /* Handler was called*/
    if (fd.revents & POLLIN)
    {
        printf("A signal was caught\n");

        for(;;)  /* Consume bytes from pipe */
        {
            if (read(pfd[0], &ch, 1) == -1)
            {
                if (errno == EAGAIN)
                    break;
                else
                    errExit("read");
            }

            printf("Catch character %c\n", ch);

            /* Perform any actions that should be taken in response to signal */
        }
    }

    /*Examine file descriptor sets returned by select() to see which other file descriptor are ready*/
}
