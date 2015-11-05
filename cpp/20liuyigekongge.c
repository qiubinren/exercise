#include <stdio.h>
int main()
{
	char s[100];
	fgets(s,99,stdin);
	int i=0,f=0,k=1;
	while(s[i])
	{
		if(f<1&&s[i]==' ')
			f++;
		else if(f>=2&&s[i+k]!='\0')
		{
			while(s[i+k]==' ')
				k++,f++;
			s[i]=s[i+k];
		}
		else if(f>=1&&s[i]==' '&&s[i+k]!='\0')
		{
			while(s[i+k]==' ')
				k++,f++;
			s[i]=s[i+k];
			f++;
		}
		i++;	
	}
	puts(s);
	return 0;
}
