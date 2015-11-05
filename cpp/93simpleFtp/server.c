#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
struct Param{
	int fc;
	char ip[16];
};
void *func(void *p)
{
	struct Param *r=p;
	char msg[100];
	int len = recv(r->fc,msg,sizeof(msg),0);
	if(msg[0]=='q')
	{
		close(r->fc);
		pthread_exit(NULL);
	}
	puts(msg);
	int fd = open(msg,O_RDONLY);
	if(fd<0)
	{
		perror("open");
		write(r->fc,"open failed!\n",sizeof("open failed!\n"));
		close(r->fc);
		pthread_exit(NULL);
	}
	while((len=read(fd,msg,sizeof(msg)))>0)
	{
		send(r->fc,msg,len,0);
	}
	close(r->fc);
	pthread_exit(NULL);
}
int main()
{
	struct sockaddr_in si; 
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
		perror("socket");
		return -1;
	}
	si.sin_family = AF_INET; 
	si.sin_addr.s_addr = htonl(INADDR_ANY);
	si.sin_port = htons(8888);
	if(bind(fd,(struct sockaddr*)&si,sizeof(si))<0)
	{
		perror("bind");
		return -1;
	}
	listen(fd,10);	
	for(;;)
	{
		struct sockaddr_in c;
		socklen_t len = sizeof(c); 
		int fc = accept(fd,(struct sockaddr*)&c,&len);
		if(fc<0) continue;
		char ip[16];
		inet_ntop(AF_INET,&c.sin_addr,ip,sizeof(ip));
		printf("%s连上服务器\n",ip);	
		pthread_t id;
		struct Param* p = malloc(sizeof(struct Param));
		p->fc = fc;
		strcpy(p->ip,ip);
		pthread_create(&id,NULL,func,p);
	}
}
