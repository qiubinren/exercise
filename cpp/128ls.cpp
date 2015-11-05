#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main(int argc,char *argv[])
{
	const char* path;
	if(argc<2)
		path = ".";	
	path = argv[1];
	execlp("ls","ls","-l",path,NULL);
	return 0;
}
