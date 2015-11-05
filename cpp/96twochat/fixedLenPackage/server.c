#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
ssize_t readn(int fd, void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nread;
	char *bufp = (char*)buf;
	while(nleft>0)
	{
		if((nread = read(fd, bufp, nleft))<0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			return count - nleft;
		bufp += nread;	
		nleft -=nread;
	}
	return count;
}
ssize_t writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nwrite;
	char* bufp =(char*)buf;
	while(nleft>0)
	{
		if((nwrite=write(fd,bufp,nleft))<0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nwrite == 0)
			return count - nleft;
		bufp += nwrite;
		nleft -=nwrite;
	}
	return count;
}
void func(int sig)
{
	printf("child close\n");
	exit(-1);
}
int main()
{
	int s = socket(AF_INET,SOCK_STREAM,0);
	if(s<0)
	{
		perror("socket");
		exit(-1);
	}
	int reuse=1;
	setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_addr.s_addr = htonl(INADDR_ANY);
	si.sin_port = htons(8888);
	if(bind(s,(struct sockaddr*)&si,sizeof(si))<0){
		perror("bind");
		return -1;
	}
	if(listen(s,SOMAXCONN)<0)
	{
		perror("listen");
		return -1;
	}
	struct sockaddr_in c;
	bzero(&c,sizeof(c));
	socklen_t n = sizeof(c);
	int fc = accept(s,(struct sockaddr*)&c,&n);
	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		printf("fork failed!\n");
		return -1;
	}
	else if(pid == 0)
	{
		close(s);
		signal(SIGUSR1,func);
		char msg[1000];
		while(fgets(msg,sizeof(msg),stdin)!=NULL)
		{
			writen(fc,msg,sizeof(msg));	
		}
		printf("child close\n");
		close(fc);
		exit(0);
	}
	else
	{
		char msg[1000];
		int len;
		while(1)
		{
			len = readn(fc,msg,sizeof(msg));
			if(len < 0)
				break;
			else if(len==0)
				break;
			printf("%s",msg);
		}
		printf("father close\n");
		close(fc);
		close(s);
		kill(pid,SIGUSR1);
	}
	return 0;
}
