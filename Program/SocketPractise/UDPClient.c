/*client.c*/

#include "wrap.h"

int main(int argc, char*argv[])
{
	struct sockaddr_in servaddr;
	int sockfd, n;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	socklen_t servaddr_len;
	
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		//Write(sockfd, buf, strlen(buf));
		//n = Read(sockfd, buf, MAXLINE);
		//if (n == 0)
		//	printf("The other size has been closed.\n");
		//else
		//	Write(STDOUT_FILENO, buf, n);
		
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
		if (n == -1)
			perr_exit("sendto error");
		
		n = recvfrom(sockfd, buf, MAXLINE, 0, NULL, 0);
		if (n == -1)
			perr_exit("Recefrom error");
		
		Write(STDOUT_FILENO, buf, n);
	}

	close(sockfd);
	return 0;
}	
