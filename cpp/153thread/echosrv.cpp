#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/select.h>
#include <signal.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

ssize_t readn(int fd, void *buf, size_t ncount)
{
	int nread = 0;
	char *p = static_cast<char*>(buf);
	int nsize = ncount;
	while(nsize > 0)
	{
		nread = read(fd, p, nsize);
		if(nread < 0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		if(nread == 0)
			return ncount - nsize;
		nsize -= nread;
		p += nread;
	}
	return ncount; 
}

ssize_t writen(int fd, const void *buf, size_t count)
{
	size_t nwrite = 0;
	size_t nleft = count;
	const char *p = static_cast<const char*>(buf);
	while(nleft > 0)
	{
		nwrite = write(fd, p, nleft);
		if(nwrite < 0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		if(nwrite == 0)
			return count - nleft;
		nleft -= nwrite;
		p += nwrite;
	}
	return count;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
	while(1)
	{
		int ret = recv(sockfd, buf, len, MSG_PEEK);
		if(ret == -1&&errno == EINTR)
			continue;
		return ret;
	}
	return -1;
}

ssize_t readline(int fd, void *buf, size_t maxsize)
{
	size_t nleft = maxsize;
	size_t nread = 0;
	char *p = static_cast<char*>(buf);	
	int ret;
	while(1)
	{
		ret = recv_peek(fd, p, nleft);
		if(ret == -1)
			return ret;
		else if(ret == 0)
			return ret;
		nread = ret;
		for(int i = 0; i < nread; i++)
		{
			if(p[i]=='\n')
			{
				ret = readn(fd, p, i+1);	
				if(ret != i+1)
					exit(EXIT_FAILURE);
				return ret;
			}	
		}
		if(nread > nleft)
			exit(EXIT_FAILURE);
		nleft -= nread;
		ret = readn(fd, p, nread);
		if(ret != nread)
			exit(EXIT_FAILURE);
		p += nread;
	}	
	return -1;
}

void* echosrv(void* arg)
{
	int fd = *(int*)arg;
	int ret = pthread_detach(pthread_self());
	if(ret < 0)
		ERR_EXIT("pthread_detach");
	char recvbuf[1024];
	while(1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		int n = readline(fd, recvbuf, sizeof(recvbuf));
		if(n < 0)
			ERR_EXIT("readline");
		if(n == 0)
		{
			std::cout<<"client close"<<std::endl;
			break;
		}
		std::cout<<recvbuf;
		writen(fd, recvbuf, strlen(recvbuf));
	}
	close(fd);
	delete (int*)arg;
	return NULL;
}

int main()
{
	int sock;
	int i;
	if((sock = socket(AF_INET, SOCK_STREAM, 0))<0)
		ERR_EXIT("socket");
	int reuse = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))< 0)
		ERR_EXIT("setsockopt");
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(5188);
	if(bind(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr))<0)
		ERR_EXIT("bind");
	if(listen(sock,10)<0)
		ERR_EXIT("listen");
	while(1)
	{
		struct sockaddr_in si;
		socklen_t len;
		int fd = accept(sock, (struct sockaddr*)&si, &len);
		if(fd <= 0)
			continue;
		std::cout<<"accept a new connection"<<std::endl;
		pthread_t tid;
		int *arg = new int;
		*arg = fd;
		pthread_create(&tid, NULL, echosrv, (void*)arg);
	}
	return 0;
}
