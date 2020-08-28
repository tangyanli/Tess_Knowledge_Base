/* Header file for svmsg_file_server.c and svmsg_file_client.c */

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

#define SERVER_KEY 0x1aaaaaa1  /* Key for server's message queue */

/* Requests (client to server) */
struct requestMsg
{
    long mtype;
    int clientId;             /* ID of client's message queue */
    char pathname[PATH_MAX];  /* File to be returned */
};

/* REQ_MSG_SIZE computes size of 'mtext' part of 'requestmsg' structure
   we use offsetof() to handle the possibility that there are padding bytes between
   the 'clientId' and 'pathname' fields */
#define REQ_MSG_SIZE (offsetof(struct requestMsg, pathname) - \
                      offsetof(struct requestMsg, clientId) + PATH_MAX)

#define RESP_MSG_SIZE 8192

/* Response (server to client)*/
struct responseMsg
{
    long mtype;
    char data[RESP_MSG_SIZE];   /* File content */
};

/* Types for response message sent from server to client */
#define RESP_MT_FAILURE  1   /* File couldn't be opened */
#define RESP_MT_DATA     2   /* Message contains file data */
#define RESP_MT_END      3   /* File data complete */
