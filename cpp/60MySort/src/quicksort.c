int quicksort(int a[],int l,int r)
{
        if(l>=r)
        {
                int mid=(l+r)/2;
                int x=a[mid];
                a[mid]=a[l];
                int i=l,j=r;
                while(i<j)
                {
                        while(i<j&&a[j]>x)
                                j--;
                        if(i<j)
                                a[i]=a[j];
                        while(i<j&&a[i]<x)
                                i++;
                        if(i<j)
                                a[j]=a[i];
                }
                a[i]=x;
                quicksort(a,l,i-1);
                quicksort(a,i+1,r);
        }
        return 0;
}
