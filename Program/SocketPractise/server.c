/*server.c*/

#include "wrap.h"

int main(void)
{
	int i, maxi, maxfd, listenfd, connfd, sockfd;	
	int nready, client[FD_SETSIZE];
	ssize_t n;
	fd_set rset, allset;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];	
	socklen_t cliaddr_len;
	struct sockaddr_in servaddr, cliaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	printf("Listenfd is %d.\n", listenfd);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	Listen(listenfd, 20);
	
	maxfd = listenfd;	/* initialize */
	maxi = -1;		/* index into client[] array */
	
	for (i = 0; i < FD_SETSIZE; i++)
	{
		client[i] = -1;		/* -1 indicates available entry */
	}
	
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	printf("Size of fd_set is %d byte.\n", (int)sizeof(rset));
	
	for(;;)
	{
		rset = allset;		/* structure assignment */
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if (nready < 0)
			perr_exit("select error");
		
		if (FD_ISSET(listenfd, &rset))	/* new client connection */
		{
			cliaddr_len = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
			printf("Received from %s at PORT %d, connfd is %d.\n", 
				inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
				ntohs(cliaddr.sin_port),
				connfd);

			for (i = 0; i<FD_SETSIZE; i++)
			{
				if (client[i] < 0)
				{	
					client[i] = connfd;	/* save descriptor */
					break;
				}			
			}
			
			if (i == FD_SETSIZE)
			{
				fputs("Too many client.\n", stderr);
				exit(1);
			}
			
			FD_SET(connfd, &allset);	/* add new scriptor to set */
			
			if (connfd > maxfd)
				maxfd = connfd;		/* for select */
			if (i > maxi)
				maxi = i;		/* max index in client[] array */
			if (--nready == 0)
				continue;		/* no more readable descriptors */
		}
			
		
		/* check all clients for data */
		for (i = 0; i <= maxi; i++)
		{
			if ((sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset))
			{
				printf("sockfd %d has data to read.\n", sockfd);
				
				if ((n = Read(sockfd, buf, MAXLINE)) == 0)
				{
					/* connection closed by client*/
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}
				else
				{
					int j;
					for (j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
					Write(sockfd, buf, n);
				}
					
				if (--nready == 0)
					break;	/* no more readable descriptors*/
			}
		}
	}
}
