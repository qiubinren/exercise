#ifndef CTHREADPOOL_H_
#define CTHREADPOOL_H_
#include <deque>
#include <pthread.h>
#include <functional>


class CThreadPool
{
public:
	typedef std::function<void()> Task;
public:
	CThreadPool(int threadNum = 10);
	~CThreadPool();
public:
	size_t addTask(const Task& task);
	void stop();
	int size();
	Task take();

private:
	int createThreads();
	static void* threadFunc(void* threadData);

private:
	CThreadPool& operator = (const CThreadPool&);
	CThreadPool(const CThreadPool&);

private:
	int threadNum;
	volatile bool isRunning;
	pthread_t* threads;
	std::deque<Task> taskQueue;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};


#endif
