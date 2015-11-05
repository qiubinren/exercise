#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
using namespace std;

ssize_t readn(int fd, void *buf, size_t count)
{
	int nread = 0;
	int nleft = count;
	char *pbuf = static_cast<char*> (buf);
	while(nleft > 0)
	{
		if((nread = read(fd, pbuf, nleft))<0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			return count - nleft; 
		nleft -= nread;
		pbuf += nread;
	}
	return count;
}

ssize_t writen(int fd, void *buf, size_t count)
{
	int nleft = count;
	int nwrite = 0;
	char *pbuf = static_cast<char*>(buf);
	while(nleft >0)
	{
		if((nwrite = write(fd, pbuf, nleft))<0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nwrite == 0)
			return count - nleft;
		nleft -= nwrite;
		pbuf += nwrite;
	}
	return count;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
	int ret;
	while(1)
	{
		ret = recv(sockfd, buf, len, MSG_PEEK);
		if(ret == -1 && errno == EINTR)
			continue;
		return ret;
	}
	return -1;
}

ssize_t readline(int fd, void *buf, size_t maxlen)
{
	int ret;
	int nleft = maxlen;
	int nread = 0;	
	char *pbuf = static_cast<char*>(buf);
	while(nleft > 0)
	{
		ret = recv_peek(fd, pbuf, nleft);
		if(ret <= 0)
			return ret;
		nread = ret;
		for(int i=0;i<nread;i++)
		{
			if(pbuf[i]=='\n')
			{
				ret = readn(fd, pbuf, i+1);
				if(ret != i+1)
					exit(EXIT_FAILURE);
			}
		}
		if(nread > nleft)
			exit(EXIT_FAILURE);
		nleft -= nread;
		ret = readn(fd, pbuf, nread);
		if(ret != nread)
			exit(EXIT_FAILURE);	
		pbuf+=nread;	
	}
	return ret;
}

int main()
{
	return 0;
}
