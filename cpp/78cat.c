#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("Usage:./a.out pathname1!\n");
		return -1;
	}
	int fd1=open(argv[1],O_RDONLY);
	if(fd1<0)
	{
		perror("pathname1 openfile");
		return -1;
	}
	char buf[100];
	int len1;
	while((len1=read(fd1,buf,100))>0)
	{
		int len2=write(1,buf,len1);
		if(len1!=len2)
		{
			perror("write");
			return -1;
		}
	}
	close(fd1);
	return 0;
}
