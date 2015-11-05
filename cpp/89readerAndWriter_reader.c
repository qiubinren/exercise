#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
pthread_mutex_t readlock;
pthread_mutex_t writelock;
int read_cnt=0;
char buf[100];
void reader(void* arg)
{
	pthread_mutex_lock(&readlock);
	if(++read_cnt==1)
		pthread_mutex_lock(&writelock);
	pthread_mutex_unlock(&readlock);
	printf("%d读者读取内容：%s\n",pthread_self(),buf);
	pthread_mutex_lock(&readlock);
	if(--read_cnt==0)
		pthread_mutex_unlock(&writelock);
	pthread_mutex_unlock(&readlock);
	pthread_exit((void*)0);
}
void writer(void *arg)
{
	pthread_mutex_lock(&writelock);
	sprintf(buf,"我是%d写者，这是我写的内容",pthread_self());
	printf("%d写者写内容%s\n",pthread_self(),buf);
	sleep(1);
	pthread_mutex_unlock(&writelock);
	pthread_exit((void*)0);
}

int main()
{
	char buf[1000]={0};
	pthread_mutex_init(&readlock,NULL);
	pthread_mutex_init(&writelock,NULL);
	pthread_t tid;
	pthread_create(&tid,NULL,(void*)writer,(void*)buf);
	pthread_create(&tid,NULL,(void*)reader,(void*)buf);
	pthread_create(&tid,NULL,(void*)reader,(void*)buf);
	pthread_create(&tid,NULL,(void*)writer,(void*)buf);
	pthread_create(&tid,NULL,(void*)reader,(void*)buf);
	pthread_create(&tid,NULL,(void*)reader,(void*)buf);
	pthread_create(&tid,NULL,(void*)writer,(void*)buf);
	pthread_create(&tid,NULL,(void*)writer,(void*)buf);
	pthread_create(&tid,NULL,(void*)reader,(void*)buf);
	pthread_exit((void*)pthread_self());
	return 0;
}
