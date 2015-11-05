#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
void mySleep(int time)
{
	while(time > 0)
	{
		time = sleep(time);
	}
}
void handle(int sig)
{
	cout<<"haha"<<endl;
}
int main()
{
	signal(SIGINT, handle);
	mySleep(10);
	return 0;
}
