#include <iostream>
#include <cstdio>
#include <pthread.h>

using namespace std;

void* func(void *arg)
{
	const char *s = "dfsadfsaf";
	char *ss = const_cast<char*>(s);
	pthread_exit(static_cast<void*>(ss));
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, func, NULL);
	void* a;
	pthread_join(tid, &a);
	cout<<(char*)a<<endl;
	return 0;
}
