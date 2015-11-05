#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	}while(0)

void set_nonblock(int fd)
{
	int val = fcntl(fd,F_GETFL,0);
	if(val < 0)
		ERR_EXIT("fcntl");
	val |= O_NONBLOCK;
	int ret = fcntl(fd,F_SETFL,val);
	if(ret < 0)
		ERR_EXIT("fcntl");
}
void set_block(int fd)
{
	int val = fcntl(fd,F_GETFL,0);
	if(val < 0)
		ERR_EXIT("fcntl");
	val &= ~O_NONBLOCK;
	int ret = fcntl(fd,F_SETFL,val);
	if(ret < 0)
		ERR_EXIT("fcntl");
}

int main()
{
	set_nonblock(STDIN_FILENO);
	string a;
	cin >> a;
	set_block(STDIN_FILENO);
	cout<<a<<endl;
	return 0;
}
