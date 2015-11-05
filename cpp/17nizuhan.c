#include <stdio.h>
#include <string.h>
int main()
{
	char s[100];
	gets(s);
	int i=0,flag=0,j,k;
	while(s[i])
        {
                if(flag==0&&s[i]!=' ')
                {
                        flag=1;
                        j=i;
                }
                else if(flag==1&&s[i]==' ')
                {
			for(k=j;k<(i-j)/2+j;k++)
			{
				int g=1;
				char x;
				x=s[k];
				s[k]=s[i-g];
				s[i-g]=x;
				g++;
			}
                        flag=0;
                }
                i++;
        }
        if(flag==1)
        {
		for(k=j;k<(i-j)/2+j;k++)
		{
			int g=1;
			char x;
			x=s[k];
			s[k]=s[i-g-1];
			s[i-g-1]=x;
			g++;
		}
        }
	puts(s);
}
