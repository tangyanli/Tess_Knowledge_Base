/*---------------------------------------------------------------*/
/* Header file for fifo_seqnum_server.c and fifo_seqnum_client.c */
/*---------------------------------------------------------------*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define SERVER_FIFO "/tmp/seqnum_sv"             /* Well-known name for server's FIFO */

#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_c1.%ld"  /* Template for building client FIFO name */

#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20) /* Space required for client FIFO pathname*/
/*(+20 as generous allowance for the PID)*/

struct request         /* Request (client --> server) */
{
    pid_t pid;         /* PID of client */
    int seqLen;        /* Length of desired sequence */
};

struct response        /* Response (server --> client) */
{
    int seqNum;        /* Start of sequence */
};
