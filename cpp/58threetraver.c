#include <stdio.h>
#include <stdlib.h>
typedef  struct BiTNode
{    int data;
        struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
BiTree a[100];
int top = -1;
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
        int midtraver(BiTree T)
        {
                if(T==NULL)
                        return 0;
                midtraver(T->lchild);
                printf("%d\n",T->data);
                midtraver(T->rchild);
                return 0;
        }
		int pretraver(BiTree T)
        {
                if(T==NULL)
                        return 0;
					printf("%d\n",T->data);
                pretraver(T->lchild);
                pretraver(T->rchild);
                return 0;
        }
		int posttraver(BiTree T)
        {
                if(T==NULL)
                        return 0;
                posttraver(T->lchild);
                posttraver(T->rchild);
				printf("%d\n",T->data);
                return 0;
        }
		int pretraver1(BiTree T)
		{
			while(T!=NULL||top >=0)
			{
				printf("%d\n",T->data);
				a[++top] = T;
				T = T->lchild;
				while(T==NULL&&top>=0)
				{
					T = a[top--];
					T = T -> rchild;
				}
			}
			return 0;
		}
		int midtraver1(BiTree T)
		{
			while(T != NULL||top >=0)
			{
				if(T -> lchild != NULL)
				{
					a[++top] = T;
					T = T -> lchild;
				}
				else
				{
					printf("%d\n",T->data);
					T = T->rchild;
					while(T  == NULL && top>=0)
					{
						T = a[top--];
						printf("%d\n",T->data);
						T = T->rchild;
					}
				}
			}
			return 0;
		}
			int posttraver1(BiTree T)
			{
				BiTree pre;
				a[++top]=T;
				while(top >= 0)
				{
					T = a[top];
					if((T->lchild == NULL && T->rchild ==NULL) ||(pre != NULL && (pre == T->lchild||pre == T->rchild)))
					{
						printf("%d\n",T->data);
						pre = T;
						top--;
					}
					else
					{
						if(T->rchild !=NULL)
							a[++top] = T->rchild;
						if(T ->lchild != NULL)
							a[++top] = T->lchild;
					}
				}
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
		printf("pre:\n");
        pretraver(p);
		pretraver1(p);
		printf("mid:\n");
		midtraver(p);
		midtraver1(p);
		printf("post:\n");
        posttraver(p);
		posttraver1(p);
        return 0;
}
