#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#define ERR_EXIT(m)	\
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)
void echo_cli(int sock)
{
	struct sockaddr_in servaddr;
        memset(&servaddr, 0,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(5188);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr));
	int ret;
	int n,m;
	
	char sendbuf[1024],recvbuf[1024];
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)
	{
		n = sizeof(sendbuf);
		m = htonl(n);
		write(sock, &n, sizeof(n));
		write(sock, sendbuf, n);
		read(sock, &m, sizeof(m));
		n = ntohl(m);
		read(sock, recvbuf, n);
		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(sendbuf));
		memset(recvbuf,0,sizeof(recvbuf));
	}
}
int main(void)
{
	int sock;
	if((sock = socket(AF_INET,SOCK_STREAM,0))<0)
		ERR_EXIT("socket");
	echo_cli(sock);
	return 0;
}
