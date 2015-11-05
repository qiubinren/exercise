#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main()
{
	int fd1 = open("test",O_RDONLY);
	int fd2 = open("test",O_WRONLY);	
	int fd3 = open("test",O_WRONLY|O_CREAT|0644);
	int fd4 = open("test",O_WRONLY|O_APPEND);
	int fd5 = open("test",O_WRONLY|O_TRUNC);
	return 0;
}
