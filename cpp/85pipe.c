#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd1[2];
	int fd2[2];
	int *writefd1=&fd1[1];
	int *readfd1=&fd1[0];
	int *writefd2=&fd2[1];
	int *readfd2=&fd2[0];
	int result1=pipe(fd1);
	int result2=pipe(fd2);
	if(result1<0)
	{
		perror("pipe1");
		return -1;
	}
	if(result2<0)
	{
		perror("pipe2");
		return -1;
	}
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		char buf[100];
		close(*readfd1);
		close(*writefd2);
		write(*writefd1,"give you,My Son!!",sizeof("give you,My Son!!"));
		read(*readfd2,buf,sizeof(buf));
		printf("this is father:");
		puts(buf);
	}
	else
	{
		char buf[100];
		close(*writefd1);
		close(*readfd2);
		result1=read(*readfd1,buf,sizeof(buf));
		if(result1>0)
		{
			printf("this is son:");
			printf("receive %d bytes data:%s\n",result1,buf);
			write(*writefd2,"I receive!!",sizeof("I receive!!"));
		}
	}
	return 0;
}
