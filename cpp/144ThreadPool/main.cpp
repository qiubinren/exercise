#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "CThreadPool.h"

class MyTask
{
public:
	MyTask(){}
	int run(const int p)
	{
		int a = p;
		std::cout<<a*a<<std::endl;
		return 0;
	}
};

int main()
{
	CThreadPool threadPool(10);
	MyTask taskObj[20];
	for(int i=0;i<20;i++)
	{
		threadPool.addTask(std::bind(&MyTask::run,&taskObj[i], i));

	}
	while(1)
	{
		std::cout<<"there are still "<<threadPool.size()<<" tasks need to process"<<std::endl;
		if(threadPool.size() == 0)
		{
			threadPool.stop();
			std::cout<<"NOW I will exit from main"<<std::endl;
			exit(0);
		}
		sleep(2);
	}
	return 0;
}

