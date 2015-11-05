#include <iostream>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
using namespace std;

int main()
{
	int fd = open("test",O_RDWR|O_CREAT|O_TRUNC,0644);
	int len = lseek(fd, 1023999999, SEEK_CUR);
	char a;
	write(fd,"0",1);
	printf("len = %d \n", len); 
	close(fd);
	return 0;
}
