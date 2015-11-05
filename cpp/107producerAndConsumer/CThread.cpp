#include "CThread.h"

CThread::CThread()
{
}
CThread::~CThread()
{
}
void CThread::start()
{
	pthread_create(&m_threadId, NULL, ThreadFunc, this);
}
void* CThread::ThreadFunc(void *arg)
{
	CThread *p = static_cast<CThread*>(arg);
	p->Run();	
}
