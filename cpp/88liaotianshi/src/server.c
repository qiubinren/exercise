#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/param.h>
#include "funclib.h"
#include <string.h>
int main(int argc,char **argv)
{
	pid_t pc;
	pc=fork();
	if(pc<0)
	{
		printf("fork error\n");
		exit(-1);
	}
	else if(pc>0)
		exit(0);
	setsid();
	pc=fork();
	if(pc<0)
	{
		printf("fork error\n");
		exit(-1);
	}
	else if(pc>0)
		exit(0);
	int i;
	for(i=0;i<NOFILE;++i)
		close(i);
	chdir("/home/qiubinren/daydayup/87threefifo/tmp");
	umask(0);
	if(mkfifo("shared",0666)<0)
		sys_err("mkfifo");
	int fd1;
	if((fd1=open("shared",O_RDONLY|O_NONBLOCK))<0)
		sys_err("open shared");
	int len;
	struct list *login = create_list(); 
	login->next = NULL;
	struct list *im = create_list();
	im->next=NULL;
	while(1)
	{
		len=read(fd1,im,sizeof(struct list));
		if(len<0)
		{	
			if(errno!=EAGAIN)
				sys_err("read fdserver");
		}
		else
			resolve(im->id,im,login);
		sleep(1);
	}
	close(fd1);
	return 0;
}
