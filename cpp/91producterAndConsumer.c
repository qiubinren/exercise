#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <string.h>
sem_t full;
sem_t empty;
pthread_mutex_t	m;
int buf[10]={0};
int n=0;
int print()
{
	int i;
	for(i=0;i<10;i++)
		printf("%d ",buf[i]);
	printf("\n");
	return 0;
}
void *producter(void* p)
{
	int i;
	for(i=0;i<20;i++)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&m);
		buf[n++]=1;
		printf("%d生产了第%d个产品\n",pthread_self(),n-1);
		print();
		pthread_mutex_unlock(&m);
		sem_post(&full);
		sleep(1);
	}
	pthread_exit((void*)0);
}
void *consumer(void* p)
{
	int i;
	for(i=0;i<20;i++)
	{
		sem_wait(&full);
		pthread_mutex_lock(&m);
		buf[--n]=0;
		printf("%d消费了第%d个产品\n",pthread_self(),n);
		print();
		pthread_mutex_unlock(&m);
		sem_post(&empty);
		sleep(2);
	}
	pthread_exit((void*)0);
}
int main()
{
	memset(buf,0,sizeof(buf));
	pthread_t pid1,pid2,cid1,cid2;
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	pthread_mutex_init(&m,NULL);
	pthread_create(&pid1,NULL,producter,NULL);
	pthread_create(&cid1,NULL,consumer,NULL);
	pthread_create(&pid2,NULL,producter,NULL);
	pthread_create(&cid2,NULL,consumer,NULL);
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	pthread_join(cid1,NULL);
	pthread_join(cid2,NULL);
	return 0;	
}
