/*client.c*/

#include "wrap.h"

int main(int argc, char*argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, n;
	
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	Connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
		
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		Write(sockfd, buf, strlen(buf));
		n = Read(sockfd, buf, MAXLINE);
		if (n == 0)
			printf("The other size has been closed.\n");
		else
			Write(STDOUT_FILENO, buf, n);
	}

	close(sockfd);
	return 0;
}	
