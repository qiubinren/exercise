#ifndef _CTHREAD_H_
#define _CTHREAD_H_

#include <pthread.h>

class CThread
{
public:
	CThread();
	virtual ~CThread();
	void start();
	virtual void Run() = 0;	
	static void *ThreadFunc(void *arg);
private:
	pthread_t m_threadId;
};


#endif /*_CTHREAD_H_*/
