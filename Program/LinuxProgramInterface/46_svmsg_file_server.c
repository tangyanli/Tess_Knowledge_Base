/* A file server using System V message queues */

#include "46_svmsg_file.h"

/* SIGCHLD handler */
static void grimReaper(int sig)
{
    int savedErrno;

    savedErrno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0)
        continue;

    errno = savedErrno;
}

/* Executed in child process: server a single client */
static void serverRequest(const struct requestMsg* req)
{
    int fd;
    ssize_t numRead;
    struct responseMsg resp;

    fd = open(req->pathname, O_RDONLY);
    if (fd == -1)
    {
        resp.mtype = RESP_MT_FAILURE;
        snprintf(resp.data, sizeof(resp.data), "%s", "Couldn't open");
        msgsnd(req->clientId, &resp, strlen(resp.data)+1, 0);
        exit(EXIT_FAILURE);
    }

    resp.mtype = RESP_MT_DATA;
    while((numRead = read(fd, resp.data, RESP_MSG_SIZE)) > 0)
        if (msgsnd(req->clientId, &resp, numRead, 0) == -1)
            break;

    /* Send a message of type RESP_MT_END to signify end-of-file */
    resp.mtype = RESP_MT_END;
    msgsnd(req->clientId, &resp, 0, 0);   /* Zero-length mtext */
}

int main(int argc, char* argv[])
{
    struct requestMsg req;
    pid_t pid;
    ssize_t msgLen;
    int serverId;
    struct sigaction sa;

    /* Create server message queue */
    serverId = msgget(SERVER_KEY, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IWGRP);

    if (serverId == -1)
        errExit("msgget");

    /* Establish SIGGHLD handler to reap terminated children */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
        errExit("sigaction");

    /* Read requests, handle each in a separate child process */

    for (;;)
    {
        msgLen = msgrcv(serverId, &req, REQ_MSG_SIZE, 0, 0);
        if (msgLen == -1)
        {
            if (errno == EINTR)   /* Interrupted by SIGCHLD handler?*/
                continue;
            errMsg("msgrcv");
            break;
        }

        pid = fork();
        if (pid == -1)
        {
            errMsg("fork");
            break;
        }

        if (pid == 0)
        {
            serverRequest(&req);
            _exit(EXIT_SUCCESS);
        }

        /* Parent loops to receive next client request */
    }

    /* If msgrcv() or fork() fails, remove server MQ and exit */
    if (msgctl(serverId, IPC_RMID, NULL) == -1)
        errExit("msgctl");

    exit(EXIT_SUCCESS);
}
