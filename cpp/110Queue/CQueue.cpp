#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Queue
{
	struct node{
		T a;
		node* next;
	};
	node *front,*rear;
	int size;
public:
	Queue();
	Queue(const Queue<T> &temp);
	int Enqueue(T a);
	int Dequeue();
	int isEmpty()const;
	int Clear();
	int Getlength();
	Queue<T>& operator = (const Queue<T> &temp);
}; 
template <typename T>
Queue<T>::Queue()
{
	front=NULL;
	rear = NULL;
	size = 0;
}
template <typename T>
Queue<T>::Queue(const Queue<T> &temp)
{
	front=NULL;
	rear=NULL;
	size = 0;
	if(!temp.isEmpty())
	{
		node *p = temp.front;
		while(p)
		{
			this->Enqueue(p->a);
			p=p->next;
		}
			
	}
}
template <typename T>
int Queue<T>::Enqueue(T a)
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
template <typename T>
int Queue<T>::Dequeue()
{
	if(front == NULL)
		return -1;
	else
	{
		node *temp = front;	
		int result = temp->a;
		front = front->next;
		delete temp;
		temp = NULL;
		--size;
		if(size == 0)
			rear = NULL;
		return result;
	}	
}
template <typename T>
int Queue<T>::isEmpty()const
{
	if(size > 0)
		return 0;
	else
		return 1;
}
template <typename T>
int Queue<T>::Clear()
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
template <typename T>
int Queue<T>::Getlength()
{
	return size;
}
template <typename T>
Queue<T>& Queue<T>::operator = (const Queue<T> &temp)
{
	if(&temp==this)
		return *this;	
	this->Clear();
	front=NULL;
	rear=NULL;
	size = 0;
	if(!temp.isEmpty())
	{
		node *p = temp.front;
		while(p)
		{
			this->Enqueue(p->a);
			p=p->next;
		}
			
	}
	return *this;
	
}
int main()
{
	Queue<int> a;
	a.Enqueue(4);
	a.Enqueue(5);
	a.Enqueue(2);
	Queue<int> b(a);
	while(!a.isEmpty())
	{	
		cout<<a.Getlength()<<endl;
		int c=a.Dequeue();
		cout<<c<<endl;
	}
	while(!b.isEmpty())
	{
		cout<<b.Getlength()<<endl;
		int c=b.Dequeue();
		cout<<c<<endl; 
	}	
	Queue<int> c;
	c=a;
	while(!c.isEmpty())
	{
		cout<<c.Getlength()<<endl;
		int d=c.Dequeue();
		cout<<d<<endl; 
	}	
	a.Clear();
	a.Enqueue(3);
	a.Clear();
	if(a.isEmpty())
		cout<<1<<endl;
	else
		cout<<0<<endl;
	return 0;
}

