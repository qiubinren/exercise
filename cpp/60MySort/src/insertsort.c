int insertsort(int b[],int n)
{
        int i=1;
        int j;
        while(i<n)
        {
                j=i-1;
                int x=b[i];
                while(j>=0&&x>b[j])
                {
                        b[j+1]=b[j];
                        --j;
                }
                j=j+1;
                b[j]=x;
                i++;
        }
        return 0;
}
