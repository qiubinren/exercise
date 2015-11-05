#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Usage:./client ip port\n");
		return -1;
	}
	struct sockaddr_in si;	
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
		perror("socket");
		return -1;
	}
	si.sin_family=AF_INET;
	inet_pton(AF_INET,argv[1],&si.sin_addr.s_addr);
	int port = atoi(argv[2]);
	si.sin_port=htons(port);
	if(connect(fd,(struct sockaddr*)&si,sizeof(si))<0)
	{
		printf("connect failed!\n");
		return -1;
	}
	printf("please input the file path:\n");
	char path[100];
	fgets(path,sizeof(path),stdin);
	int n=strlen(path);
	path[n-1]='\0';
	send(fd,path,n,0);
	char buf[100];
	while((n = recv(fd,buf,sizeof(buf),0))>0)
	{
		write(STDOUT_FILENO,buf,n);
	}
	close(fd);
	return 0;
}
