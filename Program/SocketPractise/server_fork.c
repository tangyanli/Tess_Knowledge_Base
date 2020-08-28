/*server.c*/

#include "wrap.h"

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, n, childProcessID;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	Listen(listenfd, 20);
	
	printf("Accepting Connecting...\n");
	while(1)
	{
		cliaddr_len = sizeof(cliaddr);
		connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);	
		childProcessID = fork();

		if (childProcessID == -1)
		{
			perror("call to fork");
			exit(1);
		}
		else if (childProcessID == 0)
		{
			close(listenfd);
			
			while(1)
			{
				n = Read(connfd, buf, MAXLINE);
				if (n == 0)
				{
					printf("The other side has been closed.\n");
					break;
				}
			
				printf("Receieved from %s at PORT %d\n",
					inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
					ntohs(cliaddr.sin_port));

				for (i = 0; i < n; i++)
					buf[i] = toupper(buf[i]);
				Write(connfd, buf, n);
			}
			
			close(connfd);
			exit(0);			
		}
		else
			close(connfd);
		
		
	}
}
