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

int main()
{
	int sock;
	int i;
	char recvbuf[1024];
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
	fd_set rfd[2];
	FD_ZERO(&rfd[0]);
	FD_SET(sock,&rfd[0]);
	int maxfd = sock;
	int fd[50] = {0};
	int count = 0;
	fd[0] = sock;
	while(1)
	{
		FD_ZERO(&rfd[1]);
		rfd[1] = rfd[0];
		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		int ret = select(maxfd+1, &rfd[1], NULL, NULL, &timeout);
		if(ret == -1)
			ERR_EXIT("select");
		else if(ret == 0)
		{
			std::cout<<"timeout"<<std::endl;
			continue;
		}
		if(FD_ISSET(fd[0], &rfd[1])&&count<49)
		{
			struct sockaddr_in si;
			memset(&si, 0, sizeof(si));
			socklen_t len;
			int tmp = accept(fd[0], (struct sockaddr*)&si, &len);
			FD_SET(tmp, &rfd[0]);
			count++;
			for(i=1;i<50;i++)
				if(fd[i] == 0)
					break;	
			fd[i] = tmp;
			if(maxfd < fd[i])
				maxfd = fd[i];
		}
		for(i=1;i<50;i++)
		{
			if(FD_ISSET(fd[i],&rfd[1]))
			{
				memset(recvbuf, 0, sizeof(recvbuf));
				int ret = readline(fd[i], recvbuf, sizeof(recvbuf));
				if(ret == -1)
					ERR_EXIT("readline");
				if(ret == 0)
				{
					std::cout<<"client close!"<<std::endl;
					FD_CLR(fd[i], &rfd[0]);
					close(fd[i]);
					int t = fd[i];
					fd[i] = 0; 
					if(t == maxfd)
					{
						maxfd = 0;
						for(int j=0; j<50; j++)
							if(maxfd < fd[j])
								maxfd = fd[j];
					}
					continue;
				}
				std::cout<<recvbuf;
				writen(fd[i], recvbuf, strlen(recvbuf));
			}
		}
	}
	return 0;
}
