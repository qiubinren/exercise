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
struct Node* merge(struct Node* a,struct Node* b)
{
	struct Node* c=NULL;
	struct Node* p=(struct Node*)malloc(sizeof(struct Node));
	while(a!=NULL&&b!=NULL)
	{
		if(a->data>=b->data)
		{
			p->next=a;
			a=a->next;
		}
		else
		{
			p->next=b;
			b=b->next;
		}
		if(c==NULL)
			c=p;
		p=p->next;
	}
	while(a!=NULL)
	{
		p->next=a;
		a=a->next;
		p=p->next;
	}
	while(b!=NULL)
	{
		p->next=b;
		b=b->next;
		p=p->next;
	}
	return c->next;
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
        for(i=0;i<10;i++)
        {
                insert(b,i);

}
        print(a);
	print(b);
	c=merge(a,b);
	print(c);
        return 0;
}
