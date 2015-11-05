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
struct packet
{
	int len;
	char buf[1024];
};
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
	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		printf("fork failed!\n");
		return -1;
	}
	else if(pid==0)
	{
		int len;
		struct packet msg;
		while(1)
		{
			memset(&msg,0,sizeof(msg));
			int ret = readn(s,&msg.len,4);
			if(ret < 0)
			{
				perror("read");
				exit(-1);
			}
			if(ret<4)
			{
				printf("server close\n");
				break;
			}
			len = ntohl(msg.len);
			ret = readn(s,msg.buf,len);
			if(ret < 0)
			{
				perror("read");
				exit(-1);
			}
			if(ret<len)
			{
				printf("server close\n");
				break;
			}
			printf("%s",msg.buf);
		}
		close(s);
		kill(getppid(),SIGUSR1);
		printf("child close\n");
		exit(0);
	}
	else
	{
		signal(SIGUSR1,func);
		struct packet msg;
		memset(&msg,0,sizeof(msg));
		int len;
		while(fgets(msg.buf,sizeof(msg.buf),stdin)!=NULL)
		{
			len = strlen(msg.buf);
			msg.len = htonl(len);
			writen(s,&msg,4+len);
		}
		close(s);
		printf("father close\n");
		exit(0);	
	}
}
