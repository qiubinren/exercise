#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "CBuffer.h"
#include "CThread.h"

using namespace std;

template <typename T>
class CConsumer:public CThread
{
public:
	CConsumer(CBuffer<T> &buf)
	{
		pBuf = &buf;
	}
	virtual void Run() 
	{
		while(1)
		{
                	cout<<" consuming"<<endl;
			pBuf->pop(); 
			sleep(1);
		}	
	}
private:
	CBuffer<T> *pBuf;	
};	 

template <typename T>
class CProducer:public CThread
{
public:
	CProducer(CBuffer<T> &buf,T product)
	{
		pBuf = &buf;
		m_product = product;
	}
	virtual void Run() 
	{
        	while(1)
        	{
                	cout<<" producing"<<endl;
                	pBuf->push(m_product);
               		sleep(1);
        	}	
	}
private:
	CBuffer<T>* pBuf;	
	T m_product; 
};
int main()
{
	CBuffer<int> buf(10);
	int a=1;
	CConsumer<int> c1(buf);	
	CProducer<int> p1(buf,a);
	CProducer<int> p2(buf,a);
	c1.start();
	p1.start();
	p2.start();
	sleep(10);
	return 0;
}
