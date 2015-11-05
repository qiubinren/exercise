int choosesort(int b[],int n)
{
        int i,j;
        for(i=0;i<n;i++)
        {
                int x=i;
                for(j=i+1;j<n;j++)
                        if(b[x]>b[j])
                                x=i;
                if(x!=i)
                {
                        int x1=b[x];
                        b[x]=b[i];
                        b[i]=x1;
                }
        }
        return 0;
}
