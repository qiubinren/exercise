#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
void my_wc(int current[],char c)
{
	int flag;
	current[2]++;
	if(c=='\n')
		current[0]++;
	if(c=='\t'||c==' '||c=='\n')
	{
		if(flag==0)
		{
			flag=1;
			current[1]++;
		}
	}
	else
		flag=0;
}
int main(int argc,char** argv)
{
	FILE *fp;
	int total[3]={0};
	int current[3]={0};
	char c;
	int i,j;
	if(argc==1)
	{
		while((c=getchar())!=EOF)
			my_wc(total,c);
		printf("\t%d\t%d\t%d\n",total[0],total[1],total[2]);
	}
	else
	{
		j=0;
		while(++j<argc)
		{
			if((fp = fopen(argv[j],"r"))==NULL)
			{
				printf("Can not open the file:%s\n",argv[j]);
				exit(0);
			}
			c=fgetc(fp);
			while(c!=EOF)
			{
				my_wc(current,c);
				c=fgetc(fp);
			}
			fclose(fp);
			printf("%d\t%d\t%d\n",current[0],current[1],current[2]);
			for(i=0;i<3;i++)
			{
				total[i]+=current[i];
				current[i]=0;
			}
		}
		printf("%d %d %d total\n",total[0],total[1],total[2]);
	}
	return 0;
}

