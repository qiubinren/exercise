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
	printf("rcvbuf = %d bytes\n",rcvbuf);
	printf("sndbuf = %d bytes\n",sndbuf);
	close(fd);
	return 0;
}
