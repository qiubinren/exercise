int bubblesort(int b[],int n)
{
        int i,j;
        for(i=1;i<n;i++)
        {
                for(j=0;j<n-i;j++)
                        if(b[j]>b[j+1])
                        {
                                int x=b[j];
                                b[j]=b[j+1];
                                b[j+1]=x;
                        }
        }
        return 0;
}
