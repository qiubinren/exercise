#include "CThreadPool.h"
#include <assert.h>
#include <stdio.h>

CThreadPool::CThreadPool(int threadNum)
{
	this->threadNum = threadNum;
	createThreads();
	isRunning = true;
}
CThreadPool::~CThreadPool()
{
	stop();
}
int CThreadPool::createThreads()
{
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	threads = (pthread_t *)malloc(sizeof(pthread_t)*threadNum);
	for(int i=0; i<threadNum;i++)
	{
		pthread_create(&threads[i], NULL, threadFunc, this);
	}
	return 0;
}
size_t CThreadPool::addTask(const Task& task)
{
	pthread_mutex_lock(&mutex);
	taskQueue.push_back(task);
	int size = taskQueue.size();
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
	return size;
}
void CThreadPool::stop()
{
	if(!isRunning)
	{
		return;
	}
	isRunning = false;
	pthread_cond_broadcast(&cond);
	for(int i = 0;i<threadNum;i++)
	{
		pthread_join(threads[i], NULL);
	}
	free(threads);
	threads = NULL;

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}

int CThreadPool::size()
{
	pthread_mutex_lock(&mutex);
	int size = taskQueue.size();
	pthread_mutex_unlock(&mutex);
	return size;
}

CThreadPool::Task CThreadPool::take()
{
	Task task = NULL;
	pthread_mutex_lock(&mutex);
	while(taskQueue.empty() && isRunning)
	{
		pthread_cond_wait(&cond,&mutex);
	}
	if(!isRunning)
	{
		pthread_mutex_unlock(&mutex);
		return task;
	}
	assert(!taskQueue.empty());
	task = taskQueue.front();
	taskQueue.pop_front();
	pthread_mutex_unlock(&mutex);
	return task;
}

void* CThreadPool::threadFunc(void *arg)
{
	pthread_t tid = pthread_self();
	CThreadPool* pool = static_cast<CThreadPool*>(arg);
	while(pool -> isRunning)
	{
		CThreadPool::Task task = pool->take();
		if(!task)
		{
			printf("thread %lu will exit\n",tid);
			break;
		}
		assert(task);
		task();
	}
	return 0;
}
