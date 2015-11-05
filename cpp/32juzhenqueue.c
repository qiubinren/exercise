#include <stdio.h>
int queue[100];
int front=0,rear=-1;
int empty()
{
	if(rear<front)
		return 1;
	return 0;
}
int length()
{
	return rear-front+1;
}
int push(int x)
{
	queue[++rear]=x;
	return 0;
}
int pop()
{
	++front;
	return 0;
}
int clear()
{
	while(front<=rear)
		++front;
	return 0;
}
int first()
{
	return queue[front];
}
int main()
{
	int x;
	do
	{
		scanf("%d",&x);	
		push(x);
	}while(x!=0);
	while(!empty())
	{
		printf("%d",first());
		pop();
	}
	return 0;
}
