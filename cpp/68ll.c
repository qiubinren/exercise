#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
void printtype(int mode)
{
	if(S_ISREG(mode)) putchar('-');
	else if(S_ISDIR(mode)) putchar('d');
	else if(S_ISLNK(mode)) putchar('|');
	else if(S_ISFIFO(mode)) putchar('p');
	else if(S_ISSOCK(mode)) putchar('s');
	else if(S_ISCHR(mode)) putchar('c');
	else if(S_ISBLK(mode)) putchar('b');
}
void printaccess(int mode)
{
	int i;
	for(i=0;i<9;i++)
	{
		if(mode&0400)
		{
			if(i%3==0)
				putchar('r');
			else if(i%3==1)
				putchar('w');
			else
				putchar('x');
		}
		else
			putchar('-');
		mode=mode<<1;
	}
}
void showdetail(const char* name)
{
	struct stat s;
	lstat(name,&s);
	printtype(s.st_mode);	
	printaccess(s.st_mode&0777);
	printf("%2d",s.st_nlink);
	printf("%10s",getpwuid(s.st_uid)->pw_name);
	printf("%10s",getgrgid(s.st_gid)->gr_name);
	printf("%10d",s.st_size);
	char buf[20];
	strftime(buf,sizeof(buf),"%F %T",localtime(&s.st_mtime));
	printf("%20s %s\n",buf,name);
}
void listdetail(void)
{
	DIR* p=opendir(".");
	if(p==NULL)
	{
		perror("opendir");
		return;
	}
	struct dirent *q=NULL;
	while((q=readdir(p))!=NULL)
	{
		if(q->d_name[0]=='.')
			continue;
		showdetail(q->d_name);
	}
}
int main(int argc,char** argv)
{
	if(argc==1)
	{
		listdetail();	
	}
	else
	{
		int i;
		char path[100];
		char oldpath[100];
		for(i=1;i<argc;i++)
		{
			getcwd(oldpath,100);
			if(argv[i][0]!='/')
			{
				strcpy(path,oldpath);
				strcat(path,"/");
				strcat(path,argv[i]);
			}
			else
				strcpy(path,argv[i]);
			struct stat s;
			lstat(path,&s);
			if(S_ISREG(s.st_mode))
			{
				char filename[100];
				int j=strlen(path)-1;
				while(j>=0&&path[j]!='/')
					j--;
				if(j<0)
					strcpy(filename,path);
				else
					strcpy(filename,path+j+1);
				showdetail(filename);
			}
			else
			{
				chdir(path);
				listdetail();
				chdir(oldpath);
			}
		}		
	}	
	return 0;
}
