#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>
#include "funclib.h"
int main(int argc,char **argv)
{
	int fdserver;
	struct list *im=create_list();
	im->next=NULL;	
	if(argc<2)
	{
		printf("./cilent username\n");
		exit(1);
	}	
	if(strlen(argv[1])>4)
	{
		printf("username is too long, 4 Bytes\n");
		exit(1);
	}
	chdir("/home/qiubinren/daydayup/87threefifo/tmp");
	if((fdserver=open("shared",O_WRONLY))<0)
		sys_err("open fdserver");
	change_list(im,1,argv[1],"0");
	if(write(fdserver,im,sizeof(struct list))<0)
		sys_err("write login information");
	be_nonblock(STDIN_FILENO);
	while(1)
	{
		comm_server(im,fdserver);
		sleep(1);
		if(im->id == 4)
		{
			close(fdserver);
			printf("see you\n");
			return 0;
		}
		read_client(argv[1]);
	}
	return 0;
}
