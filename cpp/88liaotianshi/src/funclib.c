#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/param.h>
#include <string.h>
struct list{
	int id;
	char src[5];
	char data[100];
	struct list *next;
};
struct list* create_list()
{
	return calloc(sizeof(struct list),1);
}
void sys_err(char* message)
{
	perror(message);
	exit(-1);
} 
int add_list(struct list *login,int id,char* src,char* data)
{
	struct list *tmp=create_list();
	struct list *p=login;
	while(p->next)
	{
		p=p->next;
	}
	tmp->next=p->next;
	p->next=tmp;
	tmp->id=id;
	strcpy(tmp->src,src);
	strcpy(tmp->data,data);
	return 0;
}
int del_list(struct list *login,char* src)
{
	struct list* p=login;
	while(p->next)
	{
		if(strcmp(p->next->src,src)==0)
			break;
		p=p->next;
	}
	struct list *tmp=p->next;
	p->next=p->next->next;
	free(tmp);
	return 0;
}
int change_list(struct list *im,int id,char *src,char *data)
{
	struct list *tmp=im;
	tmp->id = id;
	strcpy(tmp->src,src);
	strcpy(tmp->data,data);
	return 0;
}
void send(struct list *login,char *buf,struct list *im)
{
	struct list *p=login;
	while(p->next)
	{
		if(strcmp(p->next->src,im->src)==0)
		{
			p=p->next;
			continue;
		}
		int fd=open(p->next->src,O_WRONLY);
		write(fd,buf,strlen(buf));
		close(fd);
		p=p->next;
	}
}
int resolve(int id,struct list *im,struct list *login)
{
	char buf[105];
	switch(id)
	{
		case 1:
			sprintf(buf,"%s is login\n",im->src);
			send(login,buf,im);
			add_list(login,im->id,im->src,im->data);
			if(mkfifo(im->src,0644)<0)
				sys_err("mkfifo");
			break;
		case 2:
			sprintf(buf,"%s:%s",im->src,im->data);
			send(login,buf,im);
			break;
		case 4:
			unlink(im->src);
			del_list(login,im->src);
			sprintf(buf,"%s is logout\n",im->src);
			send(login,buf,im);
			im->id=0;
			break;	
	}
	return 0;
}
void be_nonblock(int fd)
{
	int flags;
	if((flags=fcntl(fd,F_GETFL))<0)
		sys_err("fcntl");
	flags|=O_NONBLOCK;
	if(fcntl(fd,F_SETFL,flags)<0)
		sys_err("fcntl");
}
int comm_server(struct list *im,int fdserver)
{
	char buf[100];
	int len;
	if((len=read(STDIN_FILENO,buf,sizeof(buf)))<0)
	{
		if(errno!=EAGAIN)
			sys_err("read user input");
	}
	else
	{
		if(strcmp(buf,"quit\n")==0||strcmp(buf,"exit\n")==0)
		{
			im->id=4;
			write(fdserver,im,sizeof(struct list));
			return 0;
		}
		im->id=2;
		strcpy(im->data,buf);
		write(fdserver,im,sizeof(struct list));
	}
	return 0;
}
void read_client(char *client_fifo)
{
	int len;
	char buf[100];
	int fdclient;
	if((fdclient=open(client_fifo,O_RDONLY|O_NONBLOCK))<0)	
		sys_err("open userfifo");
	if((len=read(fdclient,buf,sizeof(buf)))<0)
	{
		if(errno!=EAGAIN)
			sys_err("read data");
	}
	else
		write(STDIN_FILENO,buf,strlen(buf));
	return;
}
