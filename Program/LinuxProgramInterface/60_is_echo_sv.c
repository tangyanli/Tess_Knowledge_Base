/* A concurrent server that implements the TCP echo service */

#include <signal.h>
#include <syslog.h>
#include <sys/wait.h>
#include "become_daemon.h"
#include "59_inet_sockets.h"
#include "tlpi_hdr.h"

#define SERVER  "echo"  /* Name of TCP service */
#define BUF_SIZE 4096

/* SIGCHLD handler to reap dead child processes */
static void grimReaper(int sig)
{
    int savedErrno;

    savedErrno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0)
        continue;
    errno = savedErrno;
}

/* Handle a client request: copy socket input back to socket */
static void handleRequest(int cfd)
{
    char buf[BUF_SIZE];
    ssize_t numRead;

    while((numRead = read(cfd, buf, BUF_SIZE)) > 0)
    {
        if (write(cfd, buf, numRead) != numRead)
        {
            syslog(LOG_ERR, "write() failed: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    if (numRead == -1)
    {
        syslog(LOG_ERR, "Error from read(): %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    int lfd, cfd;   /* Listening and connected sockets */
    struct sigaction sa;

    if (becomeDaemon(0) == -1)
        errExit("becomedaemon");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        syslog(LOG_ERR, "Error from sigaction(): %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    lfd = inetListen(SERVER, 10, NULL);
    if (lfd == -1)
    {
        syslog(LOG_ERR, "Could not create server socket (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        cfd = accept(lfd, NULL, NULL); /* wait for connection */
        if (cfd == -1)
        {
            syslog(LOG_ERR, "Failure in accept() : %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /* Handle each client request in a new child process */
        switch(fork())
        {
        case -1:
            syslog(LOG_ERR, "Can't create child (%s)", strerror(errno));
            close(cfd);
            break;
        case 0:
            close(lfd);
            handleRequest(cfd);
            _exit(EXIT_SUCCESS);
        default:
            close(cfd);
            break;
        }
    }
}
