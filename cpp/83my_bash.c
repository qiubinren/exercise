#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
char command[100];
char argv1[50][50];
int count;
int analysis();
int do_command();
int find_command(char *command);
int analysis()
{
	char *s=command;
	int i;
	count=0;
	int j=0;
	while(*s!=0)
	{
		if(*s==' ')
		{
			if(j>0)
			{
				argv1[count++][j]=0;
				j=0;
			}
		}
		else
		{
			argv1[count][j++]=*s;	
		}
		++s;
	}
	if(j>0)
	{
		argv1[count++][j]=0;
		j=0;
	}
	if(strcmp(argv1[0],"logout")==0||strcmp(argv1[0],"exit")==0)
		exit(0);
	if(!find_command(argv1[0]))
	{
		puts("error:can't find command");
		return 0;
	}
	strcpy(argv1[count],"NULL");
	if(count==0)
		return 0;
	
	return 1;
}
int find_command(char *command)
{
	DIR* d;
	struct dirent *ptr;
	char temp[100];
	char* path=getenv("PATH");
	strcpy(temp,path);
	char* dir=strtok(temp,":");
	while(dir!=NULL)
	{
		d=opendir(dir);
		while((ptr=readdir(d))!=NULL)
		if(strcmp(ptr->d_name,command)==0)
		{
			closedir(d);
			return 1;	
		}
		closedir(d);
		dir=strtok(NULL,":");
	}
	return 0;
}
int do_command()
{
	int i,j;
	char *arg[50];
	int pid;
	for(i=0;i<count;i++)
	{
		arg[i]=argv1[i];
	}
	arg[i]=NULL;
	pid=vfork();
	if(pid<0)
	{
		perror("fork error");
		exit(0);
	}
	else if(pid==0)
	{
		execvp(arg[0],arg);
	}
	else
	{
		waitpid(pid,NULL,0);
	}
	return 1;
}
int main(int argc,char** argv)
{
	while(1)
	{
		printf("$my_shell:");
		command[0]=0;
		gets(command);
		if(!analysis())
			continue;
		do_command();
	}				
	return 0;
}
