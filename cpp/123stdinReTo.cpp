#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

int main()
{
	int fd = open("test",O_RDONLY);
	int stdinfd = dup(STDIN_FILENO);	
	dup2(fd, STDIN_FILENO);
	string a;
	cin >> a;
	cout<<a<<endl;
	dup2(stdinfd, STDIN_FILENO);
	return 0;
}
