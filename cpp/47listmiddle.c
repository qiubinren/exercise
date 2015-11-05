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
int middle(struct Node* a)
{
	struct Node* p,*q;
	p=a;q=a;
	int i=0;
	while(p!=NULL)
	{
		p=p->next;
		i++;
		if(i==2)
		{
			i=0;
			q=q->next;
		}
	}
	return q->data;
}
int main()
{
        struct Node* a=(struct Node*)malloc(sizeof(struct Node));
        a->data=0;
        a->next=NULL;
        int i=0;
        for(i=0;i<9;i++)

    {
                insert(a,i);
}
        print(a);
	printf("%d\n",middle(a));
        return 0;
}
