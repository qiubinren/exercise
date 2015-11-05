#include <cstdio>
#include <cstdlib>
#include <ctime>
typedef struct Node{
	int data;
	struct Node* next;
}Node;
Node* print(Node* a)
{
        Node* b;
        while(a!=NULL)
        {
                printf("%d ",a->data);
                b=a;
                a=a->next;
        }
        printf("\n");
        return b;
}
Node* quicksort(Node* a,Node* b)
{
	if(a==b)
		return a;
	Node* first=a->next,*second=a;
	int x=a->data;
	Node* p=a;
	while(first!=b)
	{
		if(first->data<x)
		{
			second=second->next;
			int z;
			z=second->data;
			second->data=first->data;
			first->data=z;
		}
		first=first->next;
	}
	int y=second->data;
	second->data=a->data;
	a->data=y;
	quicksort(a,second);
	quicksort(second->next,b);
	return a;
}
int main()
{
	int i;
	Node* a=NULL;
	Node* p=NULL;
	srand(time(NULL));
	for(i=0;i<100;i++)
	{
		if(a==NULL)
		{
				a=(Node*)malloc(sizeof(Node));
				a->data=rand()%100;
				a->next=NULL;
				p=a;
		}
		else
		{
				p->next=(Node*)malloc(sizeof(Node));
				p=p->next;
				p->data=rand()%100;
				p->next=NULL;
			}
	}
	p=print(a);
	a=quicksort(a,NULL);
	p=print(a);
	return 0;
}
