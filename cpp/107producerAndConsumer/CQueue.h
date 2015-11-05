#ifndef _CQUEUE_H_
#define _CQUEUE_H_

#include <string>
using namespace std;

template <typename T>
class CQueue
{
	struct node{
  		T a;
  		node* next;
 	};
 	node *front,*rear;
 	int size;
public:
 	CQueue()
	{
        	front=NULL;
        	rear = NULL;
        	size = 0;
	}
 	CQueue(const CQueue<T> &temp)
	{
        	front=NULL;
        	rear=NULL;
        	size = 0;
       		if(temp.size != 0)
        	{	
                	node *p = temp.front;
                	while(p)
                	{
                        	this->Enqueue(p->a);
                        	p=p->next;
                	}
        	}
	}
 	int Enqueue(T a)
	{
        	if(front == NULL)
        	{
               		front=rear=new(node);
                	if(!front)
                        	return -1;
                	front->next=NULL;
                	front->a=a;
                	++size;
        	}
        	else
        	{
                	rear->next = new(node);
                	rear=rear->next;
                	rear->a = a;
                	rear->next = NULL;
                	++size;
        	}
         	return 1;
	}
 	T Dequeue()
	{ 
        	if(front == NULL)
                	return -1;
        	else    
        	{
                	node *temp = front;
                	T result = temp->a;
                	front = front->next;
                	delete temp;
                	temp = NULL;
                	--size;
                	if(size == 0)
                        	rear = NULL;
                	return result; 
        	}       
	}  
 	int isEmpty()
	{
        	if(size > 0)
                	return 0;
        	else
                	return 1;
	}
 	int Clear()
	{
        	while(front != rear)
        	{
                	node *temp = front;
                	front = front -> next;
                	delete(temp);
        	}
        	delete front;
        	front = rear = NULL;
        	size =0;
        	return 1;
	}
 	int GetLength()
	{
        	return size;
	}
}; 

#endif /*_CQUEUE_H_*/
