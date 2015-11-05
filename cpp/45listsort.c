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
struct Node* listsort(struct Node* a)
{
	struct Node* p3=a;
	struct Node *p2,*p1,*p4,*p5;
	while(p3->next->next!=NULL)
	{
		p2=p3->next;
		p5=p2;
		p1=p2;
		bool flag=false;
		while(p1->next!=NULL)
		{
			if(p5->data>p1->next->data)
			{
				p5=p1->next;
				p4=p1;
				flag=true;
			}
			p1=p1->next;
		}
		if(flag)
		{
			if(p2==p4)
			{
				p2->next=p5->next;
				p5->next=p2;
				p3->next=p5;
			}
			else
			{
				Node* temp=p5->next;
				p5->next=p2->next;
				p3->next=p5;
				p4->next=p2;
				p2->next=temp;
			}
		}
		p3=p3->next;
	}
	return a;
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
	a=listsort(a);
        print(a);
        return 0;
}
