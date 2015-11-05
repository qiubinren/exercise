#include "CCondition.h"

CCondition::CCondition(CMutex &mutex):m_mutex(mutex)
{
	pthread_cond_init(&m_cond, NULL);
}
CCondition::~CCondition()
{
	pthread_cond_destroy(&m_cond);
}
void CCondition::init(CMutex &mutex)
{
	m_mutex = mutex;
}
void CCondition::wait()
{
	pthread_cond_wait(&m_cond, &m_mutex.getMutex());
}
void CCondition::signal()
{
	pthread_cond_signal(&m_cond);
}
