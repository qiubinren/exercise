#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
int main()
{
	int id = msgget(0x1234,0);
	int id1 = msgget(0x12345,0);
	int id2 = semget(0x8888,2,0);
	msgctl(id,IPC_RMID,0);
	msgctl(id1,IPC_RMID,0);
	semctl(id2,0,IPC_RMID,0);
	return 0;
}
