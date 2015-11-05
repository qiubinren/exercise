#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
typedef struct Msg{
	long mtype;
	char path[100];
	char data[1000];
	int len;
}Msg;
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("usage:./client path\n");
		return -1;
	}	
	struct stat  buf;
	lstat(argv[1],&buf);
	if(S_ISREG(buf.st_mode)==0)
	{
		printf("这不是一个普通文件！\n");
		return -1;
	}
	char dir[100];
	if(argv[1][0]!='/')
	{
		getcwd(dir,sizeof(dir));
		strcat(dir,"/");
		strcat(dir,argv[1]);
	}
	else
		strcpy(dir,argv[1]);
	Msg msg;
	int id = msgget(0x1234,0);
	int id2 = msgget(0x12345,0);
	int id3 = semget(0x8888,2,0);
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=SEM_UNDO;
	msg.mtype=getpid();
	strcpy(msg.path,dir);
	msgsnd(id,&msg,sizeof(msg)-sizeof(long),0);
	semop(id3,&sb,1);
	sb.sem_num=1;
	sb.sem_op=-1;
	while(semop(id3,&sb,1)<0);
	msgrcv(id2,&msg,sizeof(msg)-sizeof(long),getpid(),0);
	printf("%d",msg.len);
	write(STDOUT_FILENO,msg.data,msg.len);
	return 0;	
}
