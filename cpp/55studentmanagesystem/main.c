#include<stdio.h>
#include"student.h"
int count = 0;    
int save = 0;     


int main()
{
  stu_node *head=NULL;
  head = init_stu();   
	main_menu(head);   
	return 0;
}
