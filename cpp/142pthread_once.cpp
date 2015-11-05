#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void func1()
{
	cout<<"func1"<<endl;
}
void* func2(void *arg)
{
	cout<<"func2"<<endl;
	return NULL;
}
int main()
{
	pthread_once_t once_control = PTHREAD_ONCE_INIT;
	pthread_once(&once_control,func1);
	pthread_once(&once_control,func1);
	pthread_once(&once_control,func1);
	pthread_once(&once_control,func1);
	pthread_once(&once_control,func1);
	pthread_once(&once_control,func1);
	pthread_t tid;
	pthread_create(&tid, NULL, func2, NULL);
	pthread_create(&tid, NULL, func2, NULL);
	sleep(2);

	return 0;
}
