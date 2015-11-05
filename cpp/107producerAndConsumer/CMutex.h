#ifndef _CMUTEX_H_
#define _CMUTEX_H_

#include <pthread.h>

class CMutex
{
public:
	CMutex();
	~CMutex();	
	void lock();
	void unlock();
	pthread_mutex_t& getMutex();
private:
	pthread_mutex_t m_mutex;
};

#endif /*_CMUTEX_H_*/
