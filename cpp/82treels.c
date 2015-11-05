#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
void showdetail(char* name)
{
	DIR* p=opendir(".");
	char buf[100];
	char old_path[100];
	char dir[100][100];
	int top = -1;
	getcwd(buf,100);
	printf("./%s:\n",name);
	if(p==NULL)
	{
		perror("opendir");
		exit(-1);
	}
	struct dirent* q=NULL;
	while((q=readdir(p))!=NULL)
	{
		if(q->d_name[0]=='.')
			continue;
		printf("%s\t",q->d_name);
		struct stat s;
		lstat(q->d_name,&s);
		if(S_ISDIR(s.st_mode))
		{
			strcpy(dir[++top],q->d_name);
		}
	}
	printf("\n\n");
	while(top>=0)
	{
		getcwd(old_path,100);
		strcpy(buf,old_path);
		strcat(buf,"/");
		strcat(buf,dir[top]);
		chdir(buf);
		char b[100];
		strcpy(b,name);
		strcat(b,"/");
		strcat(b,dir[top--]);
		showdetail(b);
		chdir(old_path);
	}
}
int main(int argc,char** argv)
{
	int i;
	char buf[100];
	if(argc==1)
	{
		DIR* p=opendir(".");
		if(p==NULL)
		{
			perror("opendir");
			return -1;
		}
		struct dirent* q=NULL;
		while((q=readdir(p))!=NULL)
		{
			if(q->d_name[0]=='.')
				continue;
			struct stat s;
			lstat(q->d_name,&s);
			if(S_ISDIR(s.st_mode))
			{
				char old_path[100];
				getcwd(old_path,100);
				strcpy(buf,old_path);
				strcat(buf,"/");
				strcat(buf,q->d_name);
				chdir(buf);
				showdetail(q->d_name);
				chdir(old_path);
			}
		}
	}
	else
	{
		int i;
		char old_path[100];
		char b[100];
		getcwd(old_path,100);
		for(i=1;i<argc;i++)
		{
			if(argv[i][0]!='/')
			{
				strcpy(buf,old_path);
				strcat(buf,"/");
				strcat(buf,argv[i]);
			}
			else
				strcpy(buf,argv[i]);
			int j=0;
			int k=0;
			while(buf[j]!=0)
			{
				if(buf[j]=='/'&&buf[j+1]!=0)
					k=j;
				j++;
			}
			strcpy(b,buf+k+1);
			chdir(buf);
			showdetail(b);
			chdir(old_path);
		}
	}
	return 0;
}
