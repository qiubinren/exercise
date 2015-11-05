#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
int max_fd(int sock[])
{
	int i;
	int max=0;
	for(i=0;i<50;i++)
		if(max<sock[i])
			max=sock[i];
	return max;
}
int main(int argc,char*argv[])
{
	if(argc!=2){
		printf("Usage:%s port\n",argv[0]);
		return 0;
	}
	int s = socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		perror("socket");
		return 0;
	}
	int i;
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_addr.s_addr = htonl(INADDR_ANY);
	si.sin_port = htons(atoi(argv[1]));
	if(bind(s,(struct sockaddr*)&si,sizeof(si))<0){
		perror("bind");
		return 0;
	}
	if(listen(s,5)<0){
		perror("listen");
		return 0;
	}
	fd_set fd[2];
	FD_ZERO(&fd[0]);
	int sock[50];
	memset(sock,0,50*sizeof(int));
	sock[0]=s;
	FD_SET(sock[0],&fd[0]);
	int count=0;
	while(1){
		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		FD_ZERO(&fd[1]);
		fd[1]=fd[0];
		int ret = select(max_fd(sock)+1,&fd[1],NULL,NULL,&timeout);
		printf("%d\n",max_fd(sock));
		if(ret<0){
			printf("select error\n");
		}
		else if(ret == 0){
			printf("time out\n");
		}
		else{
			if(FD_ISSET(sock[0],&fd[1])&&count<49){
				struct sockaddr_in c;
				bzero(&c,sizeof(c));
				int len = sizeof(c);
				int fc  = accept(sock[0],(struct sockaddr*)&c,&len);
				if(fc<0){
					printf("accept error\n");
				}
				else{
					for(i=1;i<50;i++)
					{
						if(sock[i]==0)
						{
							sock[i]=fc;
							FD_SET(fc,&fd[0]);
							count++;
							break;
						}
					}
				}
			}
			char rcvmsg[1000],sndmsg[1000];
			for(i=1;i<50;i++)
			{
				if(FD_ISSET(sock[i],&fd[1])){
					int n = recv(sock[i],rcvmsg,sizeof(rcvmsg),0);
					if(n<=0){
						printf("recv error\n");
						FD_CLR(sock[i],&fd[0]);
						count--;
						sock[i]=0;
						continue;
					}
					if(rcvmsg[n-1]=='\n')
					{
						rcvmsg[n-1]=0;
						n=n-1;
					}
					if(rcvmsg[n-1]=='\r')
					{
						rcvmsg[n-1]=0;
						n=n-1;
					}
					puts(rcvmsg);
					int fileNo = open(rcvmsg,O_RDONLY);
					if(fileNo<0){
						perror("oepn");
						sprintf(sndmsg,"open failed!\n");
						send(sock[i],sndmsg,13,0);
						FD_CLR(sock[i],&fd[0]);
						count--;
						sock[i]=0;
						continue;
					}
					while((n = read(fileNo,sndmsg,sizeof(sndmsg)))>0)
					{
						if(send(sock[i],sndmsg,n,0)<0){
						FD_CLR(sock[i],&fd[0]);
						count--;
						sock[i]=0;
						break;
						}
					}
					close(fileNo);
				}
			}
		}
	}
	return 0;
}
