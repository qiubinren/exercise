#include "insertsort.h"
#include "bubblesort.h"
#include "choosesort.h"
#include "quicksort.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
        size_t t1;
        size_t t2;
        srand(time(NULL));
        int i;
	int a[1000],b[1000];
        for(i=0;i<1000;i++)
        {
                a[i]=rand();
                b[i]=a[i];
        }
        for(i=0;i<1000;i++)
        {
                b[i]=a[i];
        }
        t1=time(NULL);
        insertsort(b,1000);
        t2=time(NULL);
        printf("insert:%d\n",t2-t1);
        for(i=0;i<1000;i++)
                b[i]=a[i];
        for(i=0;i<1000;i++)
        {
                b[i]=a[i];
        }
         t1=time(NULL);
        bubblesort(b,1000);
        t2=time(NULL);
        printf("bubble:%d\n",t2-t1);
        for(i=0;i<1000;i++)
        {
                b[i]=a[i];
        }
        t1=time(NULL);
        choosesort(b,1000);
        t2=time(NULL);
        printf("choose:%d\n",t2-t1);
        for(i=0;i<1000;i++)
        {
                b[i]=a[i];
        }
        t1=time(NULL);
        quicksort(b,0,1000);
        t2=time(NULL);
        printf("quick:%d\n",t2-t1);
        return 0;
}
