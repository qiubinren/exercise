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
#include <errno.h>

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
void insertlist(struct userinfo* list,struct userinfo src)
{
	struct userinfo *q=(struct userinfo*)malloc(sizeof(struct userinfo));
	strcpy(q->name,src.name);
	strcpy(q->ip,src.ip);
	q->si.sin_family = src.si.sin_family;
	q->si.sin_addr=src.si.sin_addr;
	q->si.sin_port=src.si.sin_port;
	q->next=list->next;
	list->next=q;
}
void deletelist(struct userinfo* list,struct userinfo src)
{
	struct userinfo* l;
	for(l=list;l->next!=NULL;l=l->next)
	{
		if(strcmp(l->next->ip,src.ip)==0)
		{
			struct userinfo* c=l->next;
			l->next=l->next->next;
			free(c);
			break;
		}
	}
}

void func(int s,struct userinfo* list)
{
	struct udppackage udp;
	while(1){
		struct timeval timeout = {2,0};
		int n;
		struct sockaddr_in c;
		bzero(&c,sizeof(c));
		int len = sizeof(c);
		if((n=recvfrom(s,&udp,sizeof(udp),0,(struct sockaddr*)&c,&len))>0)
		{
			printf("%d进程接受消息\n",getpid());
			udp.src.si.sin_family = c.sin_family;
			udp.src.si.sin_addr.s_addr=c.sin_addr.s_addr;
			udp.src.si.sin_port = c.sin_port;
			inet_ntop(AF_INET,&udp.src.si.sin_addr,udp.src.ip,16);
			struct userinfo* i;
			int f;
			switch(ntohs(udp.type))
			{
				case MSG:
					printf("%s:%s\n",udp.src.name,udp.msg);
					f=0;
					for(i=list->next;i!=NULL;i=i->next)
					{
						if(strcmp(i->ip,udp.src.ip)!=0)
						{
							if(f==0)
							{
								udp.type=htons(MSG);
								sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(udp.src.si),sizeof(udp.src.si));
								f=1;
							}
							sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(i->si),sizeof(i->si));
						}
					}
					if(f==0)
					{	
						udp.type=htons(MSG);
								sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(udp.src.si),sizeof(udp.src.si));
					}
					break;
				case REQ:
					insertlist(list,udp.src);
					printf("insertlist\n");
					udp.type = htons(ACC);
					sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(udp.src.si),sizeof(udp.src.si));
					break;
				case QUIT:
					deletelist(list,udp.src);
					printf("deletelist\n");
					udp.type = htons(ACC);
					sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(udp.src.si),sizeof(udp.src.si));
					break;
				case SMSG:
					printf("%s:%s\n",udp.src.name,udp.msg);
			//		sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(udp.desc.si),sizeof(udp.desc.si));
			//		break;
					for(i=list->next;i!=NULL;i=i->next)
					{
						puts(i->ip);
						puts(udp.desc.ip);
						if(strcmp(i->ip,udp.desc.ip)==0)
						{
							udp.type = htons(ACC);
							sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(udp.src.si),sizeof(udp.src.si));
							udp.type = htons(SMSG);
							sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(i->si),sizeof(i->si));
							break;
						}
					}
					if(i==NULL)
					{
						udp.type = htons(REJ);
						sendto(s,&udp,sizeof(udp),0,(struct sockaddr*)&(udp.src.si),sizeof(udp.src.si));
					}
					break;
				default:
					printf("非法消息\n");
			}
		}
		
	}
}
int main()
{
	struct userinfo* list = (struct userinfo*)malloc(sizeof(struct userinfo));
	list->next = NULL;
	int s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(s<0){
		perror("socket");
		return -1;
	}
	int reuse = 1;
	setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(8888);
	si.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(s,(struct sockaddr*)&si,sizeof(si))<0){
		perror("bind");
		return -1;
	}
	int i;
	for(i=0;i<3;i++)
	{
		pid_t pid = fork();
		if(pid<0)
		{
			printf("fork error");
			return -1;
		}
		else if(pid == 0)
		{
			func(s,list);
			exit(0);
		}
	}
	while(wait(NULL)!=-1);
	return 0;
}
