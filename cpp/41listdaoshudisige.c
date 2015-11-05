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
int daoshudisige(struct Node* a)
{
	struct Node *p=a,*q;
	int i=0;
	while(p!=NULL&&i<4)
	{
		p=p->next;
		i++;
	}
	if(i<4)
		return -1;
	q=a;
	while(p!=NULL)
	{
		p=p->next;
		q=q->next;
	}
	return q->data;
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
	printf("%d\n",daoshudisige(a));
        return 0;
}
