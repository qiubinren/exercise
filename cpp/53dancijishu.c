#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
	char c[100];
	int count;
}Node;
Node hash[100]={0};;
int cmp( const void *a ,const void *b)

{ return (*(Node *)a).count > (*(Node *)b).count ? -1 : 1; }
int add(char* a,int len,int hashcode)
{
		if(hash[hashcode%100].count==0)
			{
				strcpy(hash[hashcode%100].c,a);
				hash[hashcode%100].count++;
			}
			else
				hash[hashcode%100].count++;
		return 0;
}
int main()
{
		char a[100]="wo shi ni baba.wo ren ni zuo er zi,wo baba shi ni yeye";
		char buffer[20];
		int i=0,j=0,sum=0;
		while(a[i]!='\0')
		{
			if(isupper(a[i]))
			{
					buffer[j++]=a[i]+32;
					sum+=a[i]+32+j;
				}
			else if(islower(a[i]))
				{
					buffer[j++]=a[i];
					sum+=a[i]+j;
				}
			else
			{
				buffer[j]='\0';
				add(buffer,j,sum);
				j=0;
				sum=0;
			}
			i++;
		}
		add(buffer,j,sum);
		qsort(hash,100,sizeof(Node),cmp);
		for(i=0;i<10;i++)
		{
				printf("%s:%d\n",hash[i].c,hash[i].count);
	}
		return 0;
}
