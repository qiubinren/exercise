#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <sys/select.h>
#include <pthread.h>
struct buf{
	int n;
	int buf[50];
};
pthread_mutex_t m;
void *func(void *p)
{
	int i;
	char msg[100];
	char buf[100];
	struct buf *r = p;
	while(1)
	{
		for(i=0;i<r->n;i++)
		{
			int len = recv(r->buf[i],msg,sizeof(msg),MSG_DONTWAIT);
			if(len<=0) continue;
			if(msg[0]=='q')
			{
				close(r->buf[i]);
				r->buf[i]=-1;
				continue;
			}
			puts(msg);
			int fd = open(msg,O_RDONLY);
			if(fd<0){
				perror("open");
				send(r->buf[i],"open failed!\n",sizeof("open failed!\n"),0);
				continue;
			}
			while((len=read(fd,buf,sizeof(buf)))>0)
			{
				send(r->buf[i],buf,len,0);
			}
			close(fd);
			pthread_mutex_lock(&m);
			close(r->buf[i]);
			r->buf[i]=-1;
			pthread_mutex_unlock(&m);
		}
	}
}
int main()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0){
		perror("socket");
		return -1;
	}
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_addr.s_addr = htonl(INADDR_ANY);
	si.sin_port = htons(8888);	
	int tmp=1;
	if(bind(fd,(struct sockaddr*)&si,sizeof(si))<0){
		perror("bind");
		return -1;
	}
	listen(fd,10);
	pthread_mutex_init(&m,NULL);
	struct buf Buf;
	Buf.n=50;
	memset(Buf.buf,-1,sizeof(Buf.buf));
	pthread_t id;
	pthread_create(&id,NULL,func,&Buf);
	int i=0;
	for(;;)
	{
		struct sockaddr_in c;
		socklen_t len = sizeof(c);
		int fc = accept(fd,(struct sockaddr*)&c,&len);	
		if(fc < 0) continue;
		char ip[16];
		inet_ntop(AF_INET,&c.sin_addr,ip,sizeof(ip));
		printf("%s连上服务器\n",ip);
		while(Buf.buf[i]!=-1)
		{	
			printf("0");
			i++;
			if(i==50)
				i=0;
		}
		pthread_mutex_lock(&m);
		Buf.buf[i++]=fc;
		pthread_mutex_unlock(&m);
	}	
	return 0;
}
