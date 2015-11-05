#ifndef _CBUFFER_H_
#define _CBUFFER_H_

#include "CQueue.h"
#include "CMutex.h"
#include "CCondition.h"

template <typename T>
class CBuffer
{
public:
	CBuffer(int size)
	{
        	m_buffer.Clear();
        	m_bufferSize = size;
        	m_notEmpty = new CCondition(m_mutex);
        	m_notFull = new CCondition(m_mutex);
	}
	~CBuffer()
	{
        	delete m_notEmpty;
        	delete m_notFull;
	}
	int push(T a)
	{
        	m_mutex.lock();
        	while(m_buffer.GetLength() == m_bufferSize)
        	{
                	m_notFull->wait();
        	}
        	int ret = m_buffer.Enqueue(a);
        	m_notEmpty->signal();
        	m_mutex.unlock();
        	return ret;
	}
 	T pop()
	{
        	m_mutex.lock();
        	while(m_buffer.isEmpty())
        	{
                	m_notEmpty->wait();
        	}
        	T ret = m_buffer.Dequeue();
        	m_notFull->signal();
        	m_mutex.unlock();
        	return ret;
	}
 	bool isEmpty()
	{
        	if(m_buffer.isEmpty())
                	return true;
        	return false;
	}
 	int Clear()
	{
        	return m_buffer.Clear();
	}
 	int Getlength()
	{
        	return m_buffer.GetLength();
	}       
private:
	CMutex m_mutex;
	CCondition* m_notEmpty;
	CCondition* m_notFull;
	CQueue<T> m_buffer;	
	int m_bufferSize;
};


#endif /*_CBUFFER_H_*/
