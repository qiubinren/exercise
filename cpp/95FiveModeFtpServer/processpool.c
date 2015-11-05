#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
void func(int fd)
{
	char rcvmsg[1000],sndmsg[1000];
	while(1){
		struct sockaddr_in c;
		bzero(&c,sizeof(c));
		int len = sizeof(c);
		int fc = accept(fd,(struct sockaddr*)&c,&len);
		if(fc<0){
			perror("accept");
			exit(0);
		}
		int n;
		while(1){
		if((n=recv(fc,rcvmsg,sizeof(rcvmsg),0))<=0)
		{
			printf("recv error\n");
			close(fc);
			break;
		}
		if(rcvmsg[n-1]=='\n'){
			rcvmsg[n-1]=0;
			--n;
		}
		if(rcvmsg[n-1]=='\r')
			rcvmsg[--n]=0;
		if(rcvmsg[0]=='q'&&rcvmsg[1]==0){
			close(fc);
			break;
		}
		int fileNo = open(rcvmsg,O_RDONLY);
		if(fileNo<0){
			perror("open");
			close(fc);
			break;
		}
		while((n=read(fileNo,sndmsg,sizeof(sndmsg)))>0){
			if(send(fc,sndmsg,n,0)<0){
				close(fc);
				break;
			}
		}
	}
	}
	exit(0);
}
int main(int argc,char *argv[])
{
	if(argc!=2){
		printf("usage:%s port\n",argv[0]);
		return 0;
	}
	int s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		perror("socket");
		return -1;
	}
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_addr.s_addr = htonl(INADDR_ANY);
	si.sin_port = htons(8888);
	if(bind(s,(struct sockaddr*)&si,sizeof(si))){
		perror("bind");
		return -1;
	}
	if(listen(s,5)<0){
		perror("listen");
		return -1;
	}
	int i;
	for(i=0;i<5;i++)
	{
		int fd = fork();
		if(fd<0){
			i--;
		}
		else if(fd==0){
			func(s);
			exit(0);
		}
	}
	while(wait(NULL)!=-1);
	return 0;
}
