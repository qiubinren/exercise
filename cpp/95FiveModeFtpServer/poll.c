#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <poll.h>
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
	struct pollfd client[1024];
	for(i=0;i<1024;i++)
		client[i].fd = -1;
	int maxi=0;
	client[0].fd = s;
	client[0].events = POLLIN;	
	while(1){
		int ret = poll(client,maxi+1,60*5);
		if(ret<0){
			printf("poll error\n");
			break;
		}
		else if(ret == 0){
			printf("time out\n");
		}
		else{
			if(client[0].revents & POLLIN){
				struct sockaddr_in c;
				bzero(&c,sizeof(c));
				int len = sizeof(c);
				int fc  = accept(client[0].fd,(struct sockaddr*)&c,&len);
				if(fc<0){
					printf("accept error\n");
					break;
				}
				else{
					for(i=1;i<1024;i++)
					{
						if(client[i].fd==-1)
						{
							client[i].fd = fc;
							client[i].events = POLLIN;
							if(i>maxi)
								maxi=i;
							break;
						}
					}
				}
			}
			char rcvmsg[1000],sndmsg[1000];
			for(i=1;i<=maxi;i++)
			{
				if(client[i].fd == -1)
					continue;
				if(client[i].revents & POLLIN){
					int n = recv(client[i].fd,rcvmsg,sizeof(rcvmsg),0);
					if(n<=0){
						printf("recv error\n");
						client[i].fd=-1;
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
						send(client[i].fd,sndmsg,13,0);
						client[i].fd=-1;
						continue;
					}
					while((n = read(fileNo,sndmsg,sizeof(sndmsg)))>0)
					{
						if(send(client[i].fd,sndmsg,n,0)<0){
						client[i].fd=0;
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
