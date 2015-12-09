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
#include <signal.h>
#include <sys/epoll.h>
#include <fcntl.h>
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
		ret = readn(fd, p, nread);
		if(ret != nread)
			exit(EXIT_FAILURE);
		nleft -= nread;
		p += nread;
	}	
	return -1;
}
void setnonblocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if(flags < 0)
		ERR_EXIT("fcntl");
	flags |=O_NONBLOCK;
	int s = fcntl(fd, F_SETFL, flags);
	if(s < 0)
		ERR_EXIT("fcntl");
	
}

void echo_cli(int sock)
{
	setnonblocking(sock);
	setnonblocking(0);
	char sendbuf[1024],recvbuf[1024];	
	int ret;
	struct epoll_event events;
	int epollfd = epoll_create1(0);
	events.data.fd = sock;
	events.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &events);
	events.data.fd = 0;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, 0, &events);
	struct epoll_event tmpep[2];
	while(1)
	{
		int done = 0;
		int nready = epoll_wait(epollfd, tmpep, 2, -1);
		if(nready <= 0)
			ERR_EXIT("epoll_wait");
		for(int i=0; i<nready; i++)
		{
			if(tmpep[i].events & EPOLLERR ||
			   tmpep[i].events & EPOLLHUP ||
			   !(tmpep[i].events & EPOLLIN))
			{
				ERR_EXIT("epoll_wait");
			}
			else if(tmpep[i].data.fd == sock)
			{
				while(1)
				{
					int count = readline(sock, recvbuf, sizeof(recvbuf));
					if(count < 0)
						break;
					else if(count == 0)
					{
						done = 1;
						break;
					}
					write(0, recvbuf, count);
				}
			}
			else if(tmpep[i].data.fd == 0)
			{
				while(1)
				{
					int count = read(0, recvbuf, sizeof(recvbuf));
					if(count < 0)
						break;
					else if(count == 0)
					{
						done = 1;
						break;
					}
					writen(sock, recvbuf, count);
				}
			}
			if(done)
				break;
		}
		if(done)
			break;
	}
	close(epollfd);
	shutdown(sock,1);
}
int main()
{
	int sock;
	signal(SIGPIPE,SIG_IGN);
	if((sock = socket(AF_INET, SOCK_STREAM, 0))<0)
		ERR_EXIT("socket");
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(5188);
	if(connect(sock, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr))<0)
		ERR_EXIT("connect");
	echo_cli(sock);
	return 0;
}
