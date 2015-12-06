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
#include <poll.h>
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

void echo_cli(int sock)
{
	char sendbuf[1024],recvbuf[1024];	
	int ret;
	struct pollfd fds[2];
	fds[0].fd = sock;
	fds[0].events = POLLIN;
	fds[1].fd = 0;
	fds[1].events = POLLIN;
	int i;
	int maxi = 1;
	while(1)
	{
		int nready = poll(fds, maxi + 1, -1);
		if(nready == -1)
			ERR_EXIT("poll");
		if(fds[0].revents & POLLIN)
		{
			memset(recvbuf, 0, sizeof(recvbuf));
			int n = readline(fds[0].fd, recvbuf, sizeof(recvbuf));
			if(n == 0)
				break;
			std::cout<<recvbuf;
		}
		if(fds[1].revents & POLLIN)
		{
			memset(sendbuf, 0, sizeof(sendbuf));
			fgets(sendbuf, sizeof(sendbuf), stdin);
			writen(fds[0].fd, sendbuf, strlen(sendbuf));
		}
	}
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
