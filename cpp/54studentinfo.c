#include <stdio.h>
#include <stdlib.h>
typedef struct strudent{
	char name[20];
	int language;
	int math;
	int english;
	int ave;
}student;
int getline_(char s[],int lim){
    int c,i;
    i=0;
    while((c=getchar())!=EOF&&c!='\n'&&i<lim-1)
        s[i++]=c;
    s[i]='\0';
    return i;
}
int main()
{
	student a[100];
	char buffer[100];
	int m=0;
	while(getline_(buffer,100)!=0)
	{
			int i=0,j=0;
			int k=0;
			char s[4][100];
			while(buffer[i]!=0)
			{
				if(buffer[i]!=',')
					{
						s[k][j++]=buffer[i];
					}
					else
						{
							s[k][j]='\0';
							k++;
							j=0;
						}
				++i;
			}
			s[k][j]='\0';
                        j=0;
			strcpy(a[m].name,s[0]);
			a[m].language=atoi(s[1]);
			a[m].math=atoi(s[2]);
			a[m].english=atoi(s[3]);
			a[m].ave=(a[m].language+a[m].math+a[m].english)/3;
			++m;
	}
	int i=0;
	for(i=0;i<m;i++)
	{
		sprintf(buffer,"%s,%d,%d,%d,%d\n",a[i].name,a[i].language,a[i].math,a[i].english,a[i].ave);
		fwrite(buffer,sizeof(char),strlen(buffer),stdout);
	}
	return 0;
}
