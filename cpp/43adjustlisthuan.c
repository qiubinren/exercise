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
int adjust(struct Node* a)
{
	struct Node* p=a,*q=a;
	int i=0;
	while(q!=NULL)
	{
		q=q->next;
		i++;
		if(p==q)
			break;
		if(i==2)
		{
			p=p->next;
			i=0;
		}
	}
	if(q!=NULL)
		return 1;
	return 0;
		
}
int main()
{
        struct Node* a=(struct Node*)malloc(sizeof(struct Node));
        struct Node* b=(struct Node*)malloc(sizeof(struct Node));
        struct Node* c;
        a->data=0;
        a->next=NULL;
        b->data=0;
        b->next=NULL;
        int i=0;
        for(i=0;i<10;i++)
        {
                insert(a,i);
}
        print(a);
	struct Node* p=a;
	while(p->next!=NULL)
		p=p->next;
	p->next=a;
	printf("%d\n",adjust(a));
        return 0;
}         
