#ifndef __LIST_H_
#define __LIST_H_
struct list{
	int id;
	char src[5];
	char data[100];
	struct list *next;
};
struct list* create_list();
int sys_err(char *message);
int resolve(int id,struct list *im,struct list *login);
int change_list(struct list *im,int id,char *src,char *data);
int comm_client(struct list *im,int fdserver);
void read_client(char *client_fifo);
#endif
