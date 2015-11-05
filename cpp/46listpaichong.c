#include<cstdio>
#include <cstdlib>
#include <cmath>
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
struct Node* paichong(struct Node* a)
{
	int b[100];
	int i=0;
	struct Node *q=a;
	struct Node *x;
	b[i++]=a->data;
	while(a->next!=NULL)
	{
		x=a;
		a=a->next;
		int j=0;
		while(j<i)
			if(b[j++]==a->data)
				break;
		if(i==j)
			b[i++]=a->data;
		else
		{
			struct Node* p=a;
			x->next=a->next;
			free(p);
			a=x;
		}
	}
	int j=0;
	while(j<i)
		if(b[j++]==a->data)
			break;
	if(i!=j)
		x->next=NULL;
	return q;
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
	a=paichong(a);
	print(a);
        return 0;
}
