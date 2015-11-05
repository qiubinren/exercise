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
#include <sys/wait.h>
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
ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
	while(1)
	{
		int ret = recv(sockfd,buf,len,MSG_PEEK);
		if(ret==-1&&errno == EINTR)
			continue;
		return ret;
	}
	return -1;
}
ssize_t readline(int sockfd, void *buf, size_t maxline)
{
	int ret;
	int nread;
	char *bufp = buf;
	int nleft = maxline;
	while(1)
	{
		ret = recv_peek(sockfd,bufp,nleft);
		if(ret<0)
			return ret;
		else if(ret == 0)
			return ret;
		nread = ret;
		int i;
		for(i=0; i<nread; i++)
		{
			if(bufp[i]=='\n')
			{
				ret = readn(sockfd,bufp,i+1);
				if(ret != i+1)
					exit(EXIT_FAILURE);
				return ret;
			}
		}
		if(nread > nleft)
			exit(EXIT_FAILURE);
		nleft -=nread;
		ret = readn(sockfd,bufp,nread);
		if(ret != nread)
			exit(EXIT_FAILURE);
		bufp +=nread;
	}
	return -1;
}
void func(int sig)
{
	printf("child close\n");
	exit(-1);
}
void handle_sigchld(int sig)
{
	while(waitpid(-1,NULL,WNOHANG)>0);
}
int main()
{
	//signal(SIGCHLD, SIG_IGN);
	signal(SIGCHLD,handle_sigchld);
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
		char msg[1024];
		while(fgets(msg,sizeof(msg),stdin)!=NULL)
		{
			int len = strlen(msg);
			writen(fc,msg,len);	
		}
		printf("child close\n");
		close(fc);
		exit(0);
	}
	else
	{
		char msg[1024];
		int ret;
		while(1)
		{
			memset(msg,0,sizeof(msg));
			ret = readline(fc,msg,sizeof(msg));
			if(ret == -1)
			{
				perror("readline");
				break;
			}
			if(ret == 0)
			{
				printf("client close\n");
				break;
			}
			printf("%s",msg);
		}
		printf("father close\n");
		close(fc);
		close(s);
		kill(pid,SIGUSR1);
	}
	return 0;
}
