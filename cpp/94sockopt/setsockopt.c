#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int rcvbuf=0;
	int sndbuf=0;
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0){
		perror("socket");
		return -1;
	}
	int rcvlen=sizeof(rcvbuf);
	int sndlen=sizeof(sndbuf);
	getsockopt(fd,SOL_SOCKET,SO_RCVBUF,&rcvbuf,&rcvlen);
	getsockopt(fd,SOL_SOCKET,SO_SNDBUF,&sndbuf,&sndlen);	
	printf("old rcvbuf = %d bytes\n",rcvbuf);
	printf("old sndbuf = %d bytes\n",sndbuf);
	rcvbuf=10000;
	sndbuf=10000;
	setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&rcvbuf,sizeof(rcvbuf));
	setsockopt(fd,SOL_SOCKET,SO_SNDBUF,&sndbuf,sizeof(sndbuf));
	int newrcvbuf=0;
	int newsndbuf=0;
	getsockopt(fd,SOL_SOCKET,SO_RCVBUF,&newrcvbuf,&rcvlen);
	getsockopt(fd,SOL_SOCKET,SO_SNDBUF,&newsndbuf,&sndlen);	
	printf("new rcvbuf = %d bytes\n",newrcvbuf);
	printf("new sndbuf = %d bytes\n",newsndbuf);
	int reuse = 1;
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));	
	close(fd);
	return 0;
}
