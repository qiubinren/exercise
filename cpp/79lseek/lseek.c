#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd = open("/home/qiubinren/daydayup/79lseek/a.txt",O_WRONLY);
	if(fd<0)
	{
		perror("openfile");
		return -1;
	}
	lseek(fd,2,SEEK_SET);
	char buf[100]="345678";
	write(fd,buf,6);
	lseek(fd,2,SEEK_CUR);
	write(fd,buf,6);
	close(fd);
	return 0;
}
