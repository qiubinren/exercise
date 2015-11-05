#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <stdlib.h>
int main(int argc,char** argv)
{
	fd_set fds;
	struct timeval timeout={3,0};	
	char buf[100];
	FD_ZERO(&fds);
	FD_SET(0,&fds);
	switch(select(1,&fds,NULL,NULL,&timeout))
	{
		case -1: exit(-1); break;
		case 0:break;
		default:
		if(FD_ISSET(0,&fds))
		{
			int a=read(0,buf,100);
			buf[a-1]=0;
			puts(buf);
		}
	}
	return 0;
}
