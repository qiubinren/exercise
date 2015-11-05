#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

void handle(int sig)
{
	cout<<"ahaha!"<<endl;
	alarm(2);
}
int main()
{
	signal(SIGALRM,handle);
	alarm(2);
	while(1)
	{
		sleep(10);
	}
	return 0;
} 
