#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
}Node;
int main()
{
	struct Node* a=NULL;
	int n;
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		struct Node* b;
		b=(struct Node*)malloc(sizeof(struct Node));
		b->data=i;
		b->next=a;
		a=b;
	}
	while(a!=NULL)
	{
		printf("%d\n",a->data);
		struct Node* b=a;
		a=a->next;
		free(b);
	}
	struct Node* c=a;
	for(i=0;i<n;i++)
	{
		struct Node* b;
		b=(struct Node*)malloc(sizeof(struct Node));
		b->data=i;
		b->next=NULL;
		if(c==NULL)
		{
			a=b;
			c=b;
		}
		else
		{
			c->next=b;
			c=c->next;
		}
	}
	while(a!=NULL)
	{
		printf("%d\n",a->data);
		struct Node* b=a;
		a=a->next;
		free(b);
	}
	return 0;
}
