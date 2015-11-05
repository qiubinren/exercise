#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define SMSG 700
#define MSG 600
#define REQ 500
#define ACC 400
#define USR 300
#define QUIT 200
#define REJ 100
struct userinfo{
	char name[50];
	char ip[16];
	struct sockaddr_in si;
	struct userinfo* next;
};
struct udppackage{
	int type;
	struct userinfo src;
	struct userinfo desc;
	char msg[1000];
};
int main(int argc,char *argv[])
{
	struct udppackage udp;
	if(argc!=4){
		printf("usage:%s serverip serverport yourname",argv[0]);
		return 0;
	}
	int s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(s<0){
		perror("socket");
		return -1;
	}
	struct sockaddr_in si;
	si.sin_family=AF_INET;
	inet_pton(AF_INET,argv[1],&si.sin_addr);
	si.sin_port = htons(atoi(argv[2]));
	if(connect(s,(struct sockaddr*)&si,sizeof(si))<0){
		perror("connect");
		return 0;
	}
	fd_set fd;
	char msg[1000];
	char ip[16];
	udp.type = htons(REQ);
	strcpy(udp.src.name,argv[3]);
	udp.src.si.sin_port = htons(8000);
	send(s,&udp,sizeof(udp),0);
	recv(s,&udp,sizeof(udp),0);
	if(ntohs(udp.type)==ACC)
	{
		printf("登陆成功！\n");
	}
	else
	{
		printf("登陆失败！\n");
		return 0;
	}
	while(1){
		FD_ZERO(&fd);
		FD_SET(STDIN_FILENO,&fd);
		FD_SET(s,&fd);
		struct timeval timeout = {2,0};
		int ret = select(s+1,&fd,NULL,NULL,&timeout);
		if(ret<0)
		{
			printf("select error\n");
			continue;
		}
		else if(ret == 0)
		{
			continue;
		}
		else{
			if(FD_ISSET(s,&fd))
			{
				int n = recv(s,&udp,sizeof(udp),0);
				if(n<=0){
					printf("recv failed\n");
					continue;
				}
				switch(htons(udp.type)){
					case MSG:
						sprintf(msg,"(聊天室)%s:%s\n",udp.src.name,udp.msg);
						printf("%s",msg);
						break;
					case SMSG:
						sprintf(msg,"(私聊)%s:%s\n",udp.src.name,udp.msg);
						printf("%s",msg);
						break;
					default:
						printf("接受错误\n");
						break;
				}
			}
			if(FD_ISSET(STDIN_FILENO,&fd))
			{
				scanf(" %[^\n]%*c",msg);
				int n = strlen(msg);
				if(msg[n-1]=='\r')
				{
					msg[n-1]=0;
					n--;
				}
				if(strcmp(msg,"quit")==0)
				{
					udp.type=htons(QUIT);
					send(s,&udp,sizeof(udp),0);
					recv(s,&udp,sizeof(udp),0);
					break;
				}
				int i;
				for(i=0;i<n;i++)
				{
					if(i<16)
						ip[i]=msg[i];
					if(msg[i]==':'&&msg[i+1]!=0)
					{
						udp.type = htons(SMSG);
						ip[i]=0;
						strcpy(udp.desc.ip,ip);
						udp.desc.si.sin_port = htons(8000);
						udp.desc.si.sin_family = AF_INET;
						inet_pton(AF_INET,ip,&udp.desc.si.sin_addr);
						strcpy(msg,msg+i+1);
						break;
					}
				}
				if(udp.type!=htons(SMSG))
				{
					udp.type=htons(MSG);
				}
				strcpy(udp.msg,msg);
				send(s,&udp,sizeof(udp),0);
				recv(s,&udp,sizeof(udp),0);
				if(udp.type==htons(REJ))
				{
					printf("发送失败，用户不存在\n");
					continue;
				}
			}
		}
	}
	close(s);
	return 0;
}
