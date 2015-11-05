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
int strlener(struct Node* a)
{
	int i=0;
	while(a!=NULL)
	{	
		i++;
		a=a->next;
	}	
	return i;
}
int jiao(struct Node* a,struct Node* b,int n,int m)
{
	int i=abs(n-m);
	if(n>m)
		while(i--)
			a=a->next;
	else
		while(i--)
			b=b->next;
	i=abs(n-m)+1;
	while(a!=NULL&&a!=b)
	{
		a=a->next;
		b=b->next;
		i++;
	}
	if(a==NULL)
		return -1;
	else
		return i;
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
	for(i=10;i>8;i--)
		insert(b,i);
	b->next->next->next=a->next->next->next->next->next;
	print(b);
	int n1,n2;
	n1=strlener(a);
	n2=strlener(b);
	printf("%d\n",jiao(a,b,n1,n2));
        return 0;
}
