#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
}Node;
struct Node* queue=NULL;
struct Node* p=NULL;
int push(int x)
{
	struct Node* q=(struct Node*)malloc(sizeof(struct Node));
	q->data=x;
	q->next=NULL;
	if(queue==NULL)
	{
		queue=q;
		p=queue;
	}
	else
	{
		p->next=q;
		p=p->next;
	}
	return 0;
}
int pop()
{
	struct Node* q;
	q=queue;
	queue=queue->next;
	free(q);
	return 0;
}
int empty()
{
	if(queue==NULL)
		return 1;
	else
		return 0;
}
int first()
{
	return queue->data;
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
