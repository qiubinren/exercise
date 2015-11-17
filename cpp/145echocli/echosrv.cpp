#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#define ERR_EXIT(m)	\
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)
void echo_serv(int sock)
{
	char recvbuf[1024]={0};
	int n;
	while(1)
	{
		memset(recvbuf,0,sizeof(recvbuf));
		int k = read(sock, &n, sizeof(n));
		if(k == 0)
		{
			printf("client close\n");
			break;
		}
		int m = ntohl(n);
		n = read(sock, recvbuf, m);
		fputs( recvbuf,stdout);
		write(sock, &n, sizeof(n));
		write(sock, recvbuf, m);
	}
	close(sock);
}
int main(void)
{
	int sock;
	if((sock = socket(AF_INET,SOCK_STREAM,0))<0)
		ERR_EXIT("socket");
	
	struct sockaddr_in servaddr;
	memset(&servaddr, 0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int reuse = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	
	if(bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
		ERR_EXIT("bind");
	if(listen(sock,10)<0)
		ERR_EXIT("listen");
	int c;
	struct sockaddr_in cliaddr;
	socklen_t socklen;
	memset(&cliaddr, 0, sizeof(cliaddr));
	while((c = accept(sock, (struct sockaddr*)&cliaddr, &socklen)))
	{
		if(c <= 0)
			continue;
		int pid;
		pid = fork();
		if(pid < 0)
			ERR_EXIT("fork");
		else if(pid == 0)
		{
			echo_serv(c);
			return -1;
		}
		close(c);
	}
	return 0;
}
