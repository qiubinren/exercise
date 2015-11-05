#include "CMutex.h"

CMutex::CMutex()
{
	pthread_mutex_init(&m_mutex,NULL);	
}
CMutex::~CMutex()
{
	pthread_mutex_destroy(&m_mutex);
}
void CMutex::lock()
{
	pthread_mutex_lock(&m_mutex);
}
void CMutex::unlock()
{
	pthread_mutex_unlock(&m_mutex);
}
pthread_mutex_t& CMutex::getMutex()
{
	return m_mutex;
}
