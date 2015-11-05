#include <stdio.h>
#include <stdlib.h>
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
int rebuild(BiTree* T,char* a,char* b,int len)
{
	if(len == 0)
		return 0;
	*T = (BiTree)malloc(sizeof(BiTNode));
	(*T)->data = *a;
	int i=0;
	while(i<len)
	{
		if(*a==*(b+i))
			break;
		++i;
	}
	rebuild(&(*T)->lchild,a+1,b,i);
	rebuild(&(*T)->rchild,a+i+1,b+i+1,len-i-1);
	return 0;
}
int houxu(BiTree T)
	{
		if(T==NULL)
			return 0;
		houxu(T->lchild);
		houxu(T->rchild);
		printf("%c",T->data);
		return 0;
	}
int main()
{
	char a[100]="GDAFEMHZ",b[100]="ADEFGHMZ";
	BiTree T=NULL;
	rebuild(&T,a,b,8);
	houxu(T);
	printf("\n");
	return 0;
}
