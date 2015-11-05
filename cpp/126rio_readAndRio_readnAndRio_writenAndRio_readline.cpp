#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <string>
#include <cstring>

using namespace std;
#define BUF_LEN 8192

typedef struct{
	int fd_;//要读取的fd
	size_t nleft_;//缓冲区剩余可用的数据字节数
	char *bufptr_;//指向剩余可用数据的起止地址
	char buffer_[BUF_LEN];
}Rio_t;
void rio_init(Rio_t *rp, int fd)
{
	rp->fd_ = fd;
	rp->nleft_ = 0;
	rp->bufptr_ = rp->buffer_;
}
ssize_t rio_read(Rio_t *rp, void *buf, size_t count)
{
	int nread;
	while(rp->nleft_ == 0)
	{
		if((nread = read(rp->fd_,rp->buffer_,sizeof(rp->buffer_)))<0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)
			return 0;
		rp->nleft_ = nread;
		rp->bufptr_ = rp->buffer_;
	}
	int cnt = count;
	if(rp->nleft_ < cnt)
		cnt = rp->nleft_;
	memcpy(buf, rp->bufptr_, cnt);
	rp->nleft_ -= cnt;
	rp->bufptr_ += cnt;
	return cnt;
}

ssize_t rio_readn(Rio_t *rp, void *buf, size_t count)
{
	int nleft = count;
	int nread = 0;
	char *pbuf = static_cast<char*>(buf);
	while(nleft > 0)
	{
		if((nread = rio_read(rp, pbuf, nleft))<0)
			return -1;
		else if(nread == 0)
			break;
		nleft -= nread;
		pbuf += nread;
	}
	return (count-nleft);
}
ssize_t rio_writen(int fd, void *buf, size_t count)
{
	int nleft = count;
	int nwrite = 0;
	char *pbuf = static_cast<char*>(buf);
	while(nleft > 0)
	{
		if((nwrite = write(fd, pbuf, nleft))<0)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nwrite == 0)
			break;
		nleft -= nwrite;
		pbuf += nwrite;
	}
	return (count-nleft);
}
ssize_t rio_readline(Rio_t *rp, void *buf, size_t maxlen)
{
	int ret;
	int nread = 0;
	int nleft = maxlen - 1;
	char *pbuf = static_cast<char*>(buf);
	char c;
	while(nleft > 0)
	{
		ret = rio_readn(rp, &c, maxlen);
		if(ret <0)
			return -1;
		else if(ret == 0)
			break;
		*pbuf++ = c;
		nleft --;
		if(c == '\n')
			break;
	}
	*pbuf = '\0';
	return (maxlen - nleft -1);
}

int main()
{
	return 0;
}
