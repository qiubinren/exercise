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
int id,id4,id5;
void* func(void* p)
{
	struct sembuf sb; 
	sb.sem_flg=SEM_UNDO;
	Msg msg;
	while(1){
	sb.sem_num=0;
	sb.sem_op=-1;
	while(semop(id5,&sb,1)<0);
	msgrcv(id,&msg,sizeof(msg)-sizeof(long),0,0);
	int fd = open(msg.path,O_RDONLY);
	int len = read(fd,msg.data,sizeof(msg.data));
	msg.len = len;
	msgsnd(id4,&msg,sizeof(msg)-sizeof(long),0);
	sb.sem_num=1;
	sb.sem_op=1;
	semop(id5,&sb,1);
	}
}
int main()
{
	daemon(0,0);
	id = msgget(0x1234,IPC_CREAT|0644);
	id4 = msgget(0x12345,IPC_CREAT|0644);
	id5 = semget(0x8888,2,IPC_CREAT|0644);
	semctl(id5,0,SETVAL,0);
	semctl(id5,1,SETVAL,0);
	pthread_t id1,id2;
	pthread_create(&id1,NULL,func,&id);
	pthread_create(&id2,NULL,func,&id);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	msgctl(id,IPC_RMID,0);
	msgctl(id4,IPC_RMID,0);
}
