/*server.c*/

#include "wrap.h"

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int sockfd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, n;
	
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	Bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	printf("Accepting connections...");
	
	while(1)
	{
		cliaddr_len = sizeof(cliaddr);
		n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr*)&cliaddr, &cliaddr_len);
		
		if (n == -1)
			perr_exit("recvfrom error");
		
		printf("Received from %s at PORT %d.\n",
			inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
			ntohs(cliaddr.sin_port));
		
		for (i = 0; i<n; i++)
			buf[i] = toupper(buf[i]);
		
		n = sendto(sockfd, buf, n, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
		
		if (n == -1)
			perr_exit("Sendto error");
	}
}
