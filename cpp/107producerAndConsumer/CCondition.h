#ifndef _CCONDITION_H_
#define _CCONDITION_H_

#include <pthread.h>
#include "CMutex.h"


class CCondition
{
public:
	CCondition(CMutex &mutex);
	~CCondition();
	void init(CMutex &mutex);
	void wait();
	void signal();
private:
	pthread_cond_t m_cond;
	CMutex &m_mutex;
};


#endif
