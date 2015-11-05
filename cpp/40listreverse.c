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
int reverser(struct Node*& a)
{
	struct Node* p=NULL,*q=a;
	while(q!=NULL)
	{
		a=q->next;
		q->next=p;
		p=q;
		q=a;
	}
	a=p;
	return 0;
}
struct Node* reverse(struct Node* a)
{
	struct Node* p=a;
	if(p==NULL)
		return 0;
	struct Node* q=p->next;
	if(q==NULL)
		return p;
	else
		a=reverse(q);
	q->next=p;
	p->next=NULL;
	return a;	
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
	reverser(a);
	print(a);
	a=reverse(a);
	print(a);
        return 0;
}     
