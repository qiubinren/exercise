#include<cstdio>
#include <cstdlib>
typedef struct Node{
	int data;
	struct Node* next;
}Node;
int insert(struct Node*& a,int i)
{
	struct Node* b=(struct Node*)malloc(sizeof(struct Node));
	b->data=i;
	b->next=a;
	a=b;
	return 0;
}
int ddelete(struct Node*& a,int x)
{
	struct Node* b=a;
	struct Node* c=a;
	while(b->next!=NULL)
	{
		if(b->next->data==x)
			break;
		b=b->next;
	}
	c=b->next;
	b->next=b->next->next;
	free(c);
	return 0;
}
int search(struct Node*& a,int x)
{
	struct Node* b=a;
	int i=0;
	while(b!=NULL)
	{
		if(b->data==x)
			return i;
		i++;
		b=b->next;
	}
	return -1;
}
int update(struct Node*& a,int x,int y)
{
	struct Node* b=a;
	int i=0;
	while(b!=NULL)
	{
		if(b->data==x)
			b->data=y;
		b=b->next;
	}
	return 0;
}
int print(struct Node* a)
{
	struct Node* b=a;
	int i=0;
	while(b!=NULL)
	{
		printf("%d\n",b->data);
		b=b->next;
	}
	return 0;
}
int main()
{
	struct Node* a=(struct Node*)malloc(sizeof(struct Node));
	a->data=0;
	a->next=NULL;
	int i=0;
	for(i=0;i<10;i++)
	{
		insert(a,i);
	}
	print(a);
	ddelete(a,2);
	print(a);
	update(a,3,4);
	print(a);
	printf("%d\n",search(a,7));
	return 0;
}
