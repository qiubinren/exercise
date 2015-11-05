#include <stdio.h>
#include <stdlib.h>
typedef  struct BiTNode
{    int data;       
	struct BiTNode *lchild, *rchild; 
} BiTNode, *BiTree;
	int searchBST(BiTree T,int x,BiTree f,BiTree *p)
	{
		if(!T)
			{
				*p=f;
				return 0;
			}
			else if(T->data==x)
				{
					*p=T;
					return 1;
				}
				else if(T->data<x)
					{
						return searchBST(T->rchild,x,T,p);
					}
					else
						return searchBST(T->lchild,x,T,p);
	}
	int insertBST(BiTree *T,int x)
	{
		BiTree p,s;
		if(!searchBST(*T,x,NULL,&p))
		{
			s=(BiTree)malloc(sizeof(BiTree));
			s->data=x;
			s->lchild=NULL;
			s->rchild=NULL;
			if(!p)
				*T=s;
			else if(x < p->data)
				p->lchild=s;
			else
				p->rchild=s;
		}
		else
		{
			return 0;
		}
	}
	int Delete(BiTree *T)
	{
		BiTree q,s;
		if((*T)->lchild==NULL)
		{
			q=*T;
			*T=(*T)->rchild;
			free(q);
		}
		else if((*T)->rchild==NULL)
		{
			q=*T;
			*T=(*T)->lchild;
			free(q);
		}
		else
		{
			q=*T;
			s=(*T)->lchild;
			while(s->rchild)
			{
				q=s;
				s=s->lchild;
			}
			(*T)->data=s->data;
			if(q!=*T)
			{
				q->rchild=s->lchild;
			}
			else
				q->lchild=s->lchild;
			free(s);
				
		}
	}
	int deleteBST(BiTree *T,int x)
	{
		if(!T)
		{
			return 0;
		}
		else if((*T)->data == x)
			return Delete(T);
		else if(x<(*T)->data)
			return deleteBST(&(*T)->lchild,x);
		else
			return deleteBST(&(*T)->rchild,x);
	}
	int zhongxu(BiTree T)
	{
		if(T==NULL)
			return 0;
		zhongxu(T->lchild);
		printf("%d\n",T->data);
		zhongxu(T->rchild);
		return 0;
	}
int main()
{
	BiTree p=NULL;
	insertBST(&p,2);
	insertBST(&p,1);
	insertBST(&p,4);
	insertBST(&p,5);
	insertBST(&p,3);
	zhongxu(p);
	deleteBST(&p,2);
	zhongxu(p);
	deleteBST(&p,4);
	zhongxu(p);
	return 0;
}
