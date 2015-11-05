#include <cstdio>
#include <cstdlib>
typedef struct Node
{
	int data;
	struct Node* next;	
}Node;
int push(struct Node*& s,int x)
{
	struct Node *s1;
	s1=(struct Node*)malloc(sizeof(struct Node));
	s1->data=x;
	s1->next=s;
	s=s1;
	return 0;
}
int pop(struct Node*& s)
{
	struct Node* s1=s->next;
	free(s);
	s=s1;
	return 0;
}
int top(struct Node*& s)
{
	return s->data;
}
int empty(struct Node*& s)
{
	if(s==NULL)
		return 1;
	return 0;
}
int clear(struct Node*& s)
{
	while(!empty(s))
		pop(s);
	return 0;
}
int main()
{
	int x;
	struct Node* s=NULL;
	scanf("%d",&x);
	while(x!=0)
	{
		push(s,x);
		scanf("%d",&x);
	}
	while(!empty(s))
	{
		printf("%d\n",top(s));
		pop(s);
	}
	clear(s);
	return 0;
}

