/* An iterative server that uses a stream socket to communicate with clients */

#define _BSD_SOURCE

#include <netdb.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include "59_is_seqnum.h"

#define BACKLOG 50

int main(int argc, char* argv[])
{
    uint32_t seqNum;
    char reqLenStr[INT_LEN];
    char seqNumStr[INT_LEN];
    struct sockaddr_storage claddr;
    int lfd, cfd, optval, reqLen;
    socklen_t addrlen;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
#define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
    char addrStr[ADDRSTRLEN];
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    uint16_t portNum;
    uint32_t ip;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [init-seq-num]\n", argv[0]);

    seqNum = (argc > 1) ? getInt(argv[1], 0, "init-seq-num") : 0;

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        errExit("signal");

    /* Call getaddrinfo() to obtain a list of addresses that we can try binding to */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;   /* Allow IPv4 and IPv6 */
    hints.ai_flags = AI_PASSIVE  | AI_NUMERICSERV; /* Wildcard IP address; service name is numeric */

    if (getaddrinfo(NULL, PORT_NUM, &hints, &result) != 0)
        errExit("getaddrinfo");

    /* Walk through returned list until we find an address structre
       that can be used to successfully create and bind a socket */

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        if (rp->ai_addr->sa_family == AF_INET )
        {
            struct sockaddr_in *p = (struct sockaddr_in*)rp->ai_addr;
            portNum = ntohs(p->sin_port);
            printf("Get AF_INET services with port number %d\n", portNum);

            char des[30];
            if(inet_ntop(AF_INET, &(p->sin_addr.s_addr), des, 30) != NULL)
            {
                printf("Get AF_INET services with IP %s\n", des);
            }
        }
        else if (rp->ai_addr->sa_family == AF_UNIX)
        {
            struct sockaddr_un *t = (struct sockaddr_un*)rp->ai_addr;
            printf("Get AF_UNIX services with path %s\n", t->sun_path);
        }
        else if (rp->ai_addr->sa_family = AF_INET6)
        {
            struct sockaddr_in6 *p = (struct sockaddr_in6*)rp->ai_addr;
            portNum = ntohs(p->sin6_port);
            printf("Get AF_INET6 services with port number %d\n", portNum);

            char des[30];
            if(inet_ntop(AF_INET, &(p->sin6_addr.s6_addr), des, 30) != NULL)
            {
                printf("Get AF_INET6 services with IP %s\n", des);
            }
        }
    }

    optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (lfd == -1)
            continue;

        if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
            errExit("setsockopt");

        if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;   /* success */

        /* bind() failed: close this socket and try next address */
        printf("Bind failed with errno %d\n", errno);
        close(lfd);
    }

    if (rp == NULL)
        fatal("Could not bind socket to any address\n");

    if (listen(lfd, BACKLOG) == -1)
        errExit("listen");

    freeaddrinfo(result);

    for(;;)    /* Handle clients iteratively */
    {
        /* Accept a client connection, obtaining client's address */

        addrlen = sizeof(struct sockaddr_storage);
        cfd = accept(lfd, (struct sockaddr*)&claddr, &addrlen);
        if (cfd == -1)
        {
            errMsg("accept");
            continue;
        }

        if (getnameinfo((struct sockaddr*)&claddr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
            snprintf(addrStr, ADDRSTRLEN, "(%s, %s)", host, service);
        else
            snprintf(addrStr, ADDRSTRLEN, "(?UNKNOWN?)");
        printf("Connection from %s\n", addrStr);

        /* Read client request, send sequence number back */
        if (readLine(cfd, reqLenStr, INT_LEN) <= 0)
        {
            close(cfd);
            continue;
        }

        reqLen = atoi(reqLenStr);
        if (reqLen <= 0)
        {
            close(cfd);
            continue;
        }

        snprintf(seqNumStr, INT_LEN, "%d\n", seqNum);
        if (write(cfd, &seqNumStr, strlen(seqNumStr)) != strlen(seqNumStr))
            fprintf(stderr, "Error on write");

        seqNum += reqLen;

        if (close(cfd) == -1)
            errMsg("close");
    }
}
