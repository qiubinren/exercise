#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/time.h>
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Usage:./server pathname1 pathname2\n");
		return -1;
	}
	int rfd;
	int wfd;
	char buf[100];
	if((wfd=open(argv[1],O_WRONLY))<0)
	{
		perror("file1");
		return -1;
	}
	if((rfd=open(argv[2],O_RDONLY))<0)
	{
		perror("file2");
		return -1;
	}
	printf("rfd %d wfd %d\n",rfd,wfd);
	fd_set rfds;
	struct timeval	timeout={5,0};
	while(1)
	{
		FD_ZERO(&rfds);
		FD_SET(rfd,&rfds);
		FD_SET(fileno(stdin),&rfds);
		memset(buf,0,sizeof(buf));
		if(select(rfd+1,&rfds,NULL,NULL,&timeout)<=0)
			continue;
		if(FD_ISSET(rfd,&rfds))
		{
			printf("-----------------\n");
			read(rfd,buf,sizeof(buf));
			puts(buf);
		}
		if(FD_ISSET(fileno(stdin),&rfds))
		{
			printf("-----------------\n");
			gets(buf);
			int i=strlen(buf);
			write(wfd,buf,i);
		}
	}
	return 0;
}
