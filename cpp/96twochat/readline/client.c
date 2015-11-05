#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
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
                nleft -= nread;
                ret = readn(sockfd,bufp,nread);
                if(ret != nread)
                        exit(EXIT_FAILURE);
                bufp += nread;
        }
        return -1;
}
void func(int sig)
{
	printf("father close\n");
	exit(0);
}
int main()
{
	int s = socket(AF_INET,SOCK_STREAM,0);
	if(s<0)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&si.sin_addr);
	si.sin_port = htons(8888);
	if(connect(s,(struct sockaddr*)&si,sizeof(si))<0)
	{
		perror("connect");
		return -1;
	}
	struct sockaddr_in localaddr;
	socklen_t addrlen = sizeof(localaddr);
	if(getsockname(s, (struct sockaddr*)&localaddr,&addrlen)<0)
	{
		perror("getsockname");
		return -1;
	}
	printf("ip = %s port = %d\n",inet_ntoa(localaddr.sin_addr),ntohs(localaddr.sin_port));
	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		printf("fork failed!\n");
		return -1;
	}
	else if(pid==0)
	{
		char msg[1024];
		while(1)
		{
			memset(msg,0,sizeof(msg));
			int ret = readline(s,msg,sizeof(msg));
			if(ret == -1)
			{
				perror("readline");
				exit(-1);
			}
			if(ret==0)
			{
				printf("server close\n");
				break;
			}
			printf("%s",msg);
		}
		close(s);
		kill(getppid(),SIGUSR1);
		printf("child close\n");
		exit(0);
	}
	else
	{
		signal(SIGUSR1,func);
		char msg[1024];
		int len;
		while(fgets(msg,sizeof(msg),stdin)!=NULL)
		{
			len = strlen(msg);
			writen(s,msg,len);
		}
		close(s);
		printf("father close\n");
		exit(0);	
	}
}
