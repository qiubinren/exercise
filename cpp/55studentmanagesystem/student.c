

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"student.h"
#include<ctype.h>


stu_node *init_stu()
{
  stu_node *Pstu=NULL;
	Pstu=(stu_node *)malloc(sizeof(stu_node));   
	if(Pstu == NULL)
	{
		printf("error!\n");
	}
	Pstu->next = NULL;    
	return Pstu;
}


stu_info input_info()
{
	stu_info stu;                  
	char name[20];                   
	char psw[10];                  
	printf("please input name:");
	scanf("%s",name);
	strcpy(stu.base.name,name);    

	printf("please input password:");
	scanf("%s",psw);
	strcpy(stu.base.psw,psw);      


	printf("please input age(20~30):");
	scanf("%d",&stu.base.age);                      
	while(stu.base.age < 20 || stu.base.age > 30)
	{
		printf("please input age between 20 and 30,try again\n");
		scanf("%d",&stu.base.age);  
	}

	printf("please input class:");
	scanf("%d",&stu.base.clazz);   

	printf("please input math(0~100):");
	scanf("%d",&stu.score.math);         
	while(stu.score.math < 0 || stu.score.math >100)
  {
		printf("please input math between 0 and 100,try again\n");
		scanf("%d",&stu.score.math);  
	}

	printf("please input C-language(0~100):"); 
	scanf("%d",&stu.score.c);      
	while(stu.score.c < 0 || stu.score.c >100)
	{
		printf("please input c-language between 0 and 100,try again\n");
		scanf("%d",&stu.score.c);
	}

	printf("please input chinese(0~100):");
	scanf("%d",&stu.score.chinese); 
	while(stu.score.chinese < 0 || stu.score.chinese >100)
	{
		printf("please input chinese between 0 and 100,try again\n");
		scanf("%d",&stu.score.chinese);
	}

	count++;                        
	stu.base.num = count;           
	return stu;                   
}

void add_stu(stu_info stu,stu_node *head)
{
	save = 0;                            
	while(head->next!=NULL)              
	{
		head=head->next;
	}
	stu_node *newstu=NULL;                           
	newstu = (stu_node *)malloc(sizeof(stu_node)); 
	if(newstu!=NULL)
	{
		newstu->info=stu;             
		newstu->next=NULL;            
	}
	head->next=newstu;             
}


void save_stu_info(stu_node *head)
{
	FILE *fp;        
  FILE *count_fp;  
  save = 0;            
	if((fp=fopen("save_stu","wt"))==NULL)   
	{
		printf("cannot open file!");
	}
	head =head ->next;                   
	while(head!=NULL)                  
	{ 
		fwrite(&head->info,sizeof(head->info),1,fp);  
		head = head->next;
	}
	if((count_fp=fopen("save_count","wt"))==NULL)
	{
		printf("cannot open file!");
	}
	fwrite(&count,sizeof(int),1,count_fp);    
	fclose(count_fp);    
	fclose(fp);          
}


void load_stu_info(stu_node *head)
{
	FILE *fp;
	FILE *count_fp;
	save = 0;
	if((fp = fopen("save_stu","rt"))==NULL)  
	{
		printf("can not open file\n");
	}
	if(head!=NULL)
	{
		stu_node *newstu = (stu_node *)malloc(sizeof(stu_node));  
		if(newstu==NULL)
		{
			printf("memory error");
		}
		newstu->next = NULL;         
		while(fread(&newstu->info,sizeof(head->info),1,fp)!=0)  
		{
			head->next=newstu;                      
			newstu->next = NULL;                    
			head= head->next;                       
			newstu = (stu_node *)malloc(sizeof(stu_node));
			if(newstu==NULL)
			{
				printf("memory error");
			} 
		}
		free(newstu);
	}
	if((count_fp = fopen("save_count","rt"))==NULL)
	{
		printf("can not open file\n");
	}
	fread(&count,sizeof(int),1,count_fp);    
	fclose(count_fp);                        
	fclose(fp);                              
}


void destroy_list(stu_node *h)
{
  stu_node *q = h;                     
	stu_node *p = h->next;             
  while(p!=NULL)                       
  {
	  h = p;
    p = p->next;
		free(h);
  }
	q->next = NULL;                     
}

void sort_rank(stu_node *head)
{
  stu_sort stu[100];           
	stu_sort temp;               
  stu_node *p = head;
	int i;     
	int j;
	int len = length(head);   
	p = p->next;              
	for(i=0;i<len;i++)
	{
	  stu[i].num = p->info.base.num;       
		stu[i].total = p->info.score.math + p->info.score.c + p->info.score.chinese;
		p = p->next;
	}

	for(i=0;i<len;i++)                    
	{
	  for(j=i+1;j<len;j++)
		{
		  if(stu[i].total<stu[j].total)
			{
			  temp = stu[i];
			  stu[i] = stu[j];
				stu[j] = temp;
			}
		}
      stu[i].rank = i+1;          
	}
	for(i=0;i<len;i++)
  {
	  p=head->next;
		while(p!=NULL)  
		{
		  if(p->info.base.num == stu[i].num)
			{
			  p->info.score.rank = stu[i].rank;
		  }
			p = p->next;
		}
	}
}


void print_stu_num(stu_node *head)
{
  stu_node *p = head;
	sort_rank(head);           
  p=p->next;
  printf("id  name        password  age  class  math  C-language  chinese   rank\n");
  while(p!=NULL)        
  {
    printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
    p=p->next;
		       
  }
  printf("\n");
}


void print_stu_rank(stu_node *head)
{
	int i;
  stu_node *p = head;
	int len = length(head);  
	sort_rank(head);         
	p = p->next;
	printf("id  name        password  age  class  math  C-language  chinese  rank\n");
	for(i=1;i<len+1;i++)
  {
	  p=head->next;
		while(p!=NULL)
		{
		  if(p->info.score.rank == i)
			{
        printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
		  }
			p = p->next;
		}
	}
}

void print_stu_math(stu_node *head)
{
	sort_score stu[100];
	sort_score temp;
	stu_node *p = head;
	int i;
	int j;
	int len = length(head);
	sort_rank(head);
	p = p->next;
	for(i=0;i<len;i++)
	{
		stu[i].math = p->info.score.math;
		stu[i].num = p->info.base.num;
		p = p->next;
	}
	for(i=0;i<len;i++)             
	{
		for(j=i+1;j<len;j++)
		{
			if(stu[i].math<stu[j].math)
			{
				temp = stu[i];
				stu[i] = stu[j];
				stu[j] = temp;
			}
		}
	}
	printf("id  name        password  age  class  math  C-language  chinese  rank\n");
	for(i=0;i<len;i++)
	{
		p=head->next;
		while(p!=NULL)
		{
			if(p->info.base.num == stu[i].num)
			{
				printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
			}
			p = p->next;
		}
	}
}


void print_stu_c(stu_node *head)
{
	sort_score stu[100];
	sort_score temp;
	stu_node *p = head;
	int i;
	int j;
	int len = length(head);
	sort_rank(head);           
	p = p->next;
	for(i=0;i<len;i++)
	{
		stu[i].c = p->info.score.c;
		stu[i].num = p->info.base.num;
		p = p->next;
	}
	for(i=0;i<len;i++)                   
	{
		for(j=i+1;j<len;j++)
		{
			if(stu[i].c<stu[j].c)
			{
				temp = stu[i];
				stu[i] = stu[j];
				stu[j] = temp;
			}
		}
	}
	printf("id  name        password  age  class  math  C-language  chinese  rank\n");
	for(i=0;i<len;i++)
	{
		p=head->next;
		while(p!=NULL)
		{
			if(p->info.base.num == stu[i].num)
			{
				printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
			}
			p = p->next;
		}
	}
}


void print_stu_chinese(stu_node *head)
{
	sort_score stu[100];
	sort_score temp;
	stu_node *p = head;
	int i;
	int j;
	int len = length(head);
	sort_rank(head);
	p = p->next;
	for(i=0;i<len;i++)
	{
		stu[i].chinese = p->info.score.chinese;
		stu[i].num = p->info.base.num;
		p = p->next;
	}
	
	for(i=0;i<len;i++)                      
	{
		for(j=i+1;j<len;j++)
		{
			if(stu[i].chinese<stu[j].chinese)
			{
				temp = stu[i];
				stu[i] = stu[j];
				stu[j] = temp;
			}
		}
	}
	printf("id  name        password  age  class  math  C-language  chinese  rank\n");
	for(i=0;i<len;i++)
	{
		p=head->next;
		while(p!=NULL)
		{
			if(p->info.base.num == stu[i].num)
			{
				printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
			}
			p=p->next;
		}
	}	
}


int delete_stu(stu_node *head,int num)
{
	
	int flag = 0;
	stu_node *p;          
	p=head;
	p=head->next;
	while(p!=NULL)
	{
		if(p->info.base.num == num)   
		{
			printf("id  name        password  age  class  math  C-language  chinese\n");	
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese);
			printf("delete?");
			if(confirm())
			{
				head->next=p->next;         
				free(p);                 
				flag = 1;
				save = 1;
				p=NULL;
				printf("delete success!\n");
			}
			else
			{
				printf("no delete\n");
			}
			return 0;
		}
		else
		{
			p=p->next;
			head=head->next;
		}
	}
	if(flag ==0)
	{
		printf("don't find the deleted student\n");
	}
	return 0;
}


void modify_stu_psw(stu_node *head)
{
	
	int num;
	 
	char new_psw[10];  
	
	int flag = 0; 
	stu_node *p = head;
	p = p->next;
	printf("please input the updated student id");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->info.base.num == num)  
		{
			printf("id  name        password  age  class  math  C-language  chinese\n");
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese);
			printf("please enter new password");
			scanf("%s",new_psw);
			strcpy(p->info.base.psw,new_psw);                
			printf("update password success\n");
			save = 1;
			flag = 1;
			break;
		}
		else
		{
			p=p->next;
		}
	}
	if(flag == 0)	
	{
		printf("no the student info!\n");
	}
}


void modify_stu_age(stu_node *head)
{
	int num;
	int  new_age;
	int flag = 0;
	stu_node *p = head;
	p = p->next;
	printf("please input the updated age student id:");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->info.base.num == num)
		{
			printf("id  name        password  age  class  math  C-language  chinese\n");
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese);
			printf("please input new age:");
			scanf("%d",&new_age);
			p->info.base.age = new_age;
			printf("age update success\n");
			save = 1;
			flag = 1;
			break;
		}
		else
		{
			p=p->next;
		}
	}
	if(flag == 0)
	{
		 printf("no the student info!\n");
	}
}


void modify_stu_clazz(stu_node *head)
{
	int num;
	int  new_clazz;
	int flag = 0;
	stu_node *p = head;
	p = p->next;
	printf("please input the updated student id:");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->info.base.num == num)
		{
			printf("id  name        password  age  class  math  C-language  chinese\n");
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese);
			printf("please input new class:");
			scanf("%d",&new_clazz);
			p->info.base.clazz = new_clazz;
			printf("class update success\n");
			save = 1;
			flag = 1;
			break;
		}
		else
		{
			p=p->next;
		}
	}
	if(flag == 0)
	{
		printf("no the student info!\n");
	}
}

			  
void modify_stu_math(stu_node *head)
{
	int num;
	int  new_math;
	int flag = 0;
	stu_node *p = head;
	p = p->next;
	printf("please input the updated age student id:");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->info.base.num == num)
		{
			printf("id  name        password  age  class  math  C-language  chinese\n");
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese);
			printf("please new math:");
			scanf("%d",&new_math);
			p->info.score.math = new_math;
			printf("math update success\n");
			save = 1;
			flag = 1;
			break;
		}
		else
		{
			p=p->next;
		}
	}
	if(flag == 0)
	{
		printf("no the student info\n");
	}
}


void modify_stu_c(stu_node *head)
{
	int num;
	int  new_c;
	int flag = 0;
	stu_node *p = head;
	p = p->next;
	printf("please input the updated age student id:");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->info.base.num == num)
		{
			printf("id  name        password  age  class  math  C-language  chinese\n");
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese);
			printf("input new c-language:");
			scanf("%d",&new_c);
			p->info.score.c = new_c;
			printf("c-language update success\n");
			save = 1;
			flag = 1;
			break;
		}
		else
		{
			p=p->next;
		}
	}
	if(flag == 0)
	{
		printf("no the student\n");
	}
}


void modify_stu_chinese(stu_node *head)
{
	save = 1;
	int num;
	int  new_ch;
	int flag = 0;
	stu_node *p = head;
	p = p->next;
	printf("please input the updated age student id:");
	scanf("%d",&num);
	while(p!=NULL)
	{
		if(p->info.base.num == num)
		{
			printf("id  name        password  age  class  math  C-language  chinese\n");
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese);
			printf("input new chinese:");
			scanf("%d",&new_ch);
			p->info.score.chinese = new_ch;
			printf("chinese update success\n");
			save = 1;
			flag = 1;
			break;
		}
		else
		{
			p=p->next;
		}
	}
	if(flag == 0)
	{
		printf("no the student\n");
	}
}


void modify_stu(stu_node *head,char name[])
{
	
	char old_psw[10];
	
	char new1_psw[10];
	
	char new2_psw[10];
	stu_node *p=head;   
	p = p->next;        
	while(p!=NULL)
	{  
		
		if(strcmp(p->info.base.name,name) == 0)
		{ 
			printf("input old password");
			scanf("%s",old_psw);
			
			if(strcmp(p->info.base.psw,old_psw) == 0)  
			{
				printf("please input new password:");       
				scanf("%s",new1_psw);
				printf("please input new password again:");   
				scanf("%s",new2_psw);
				if(strcmp(new1_psw,new2_psw)==0)         
				{
					strcpy(p->info.base.psw,new1_psw);     
					printf("new password success!\n");
					save = 1;
					break;
				}
			}	
			else
			printf("input password wrong\n");
			break;
		}
		else
		
		p=p->next;         
	} 
}


int length(stu_node *head)
{

  int length = 0;     
  head = head->next;            
  while(head!=NULL)            
  {
    length++;                   
    head = head->next;         
  }
  return length;             
}


void search_stu_num(stu_node *head,int c)
{
	int flag = 0;  
	stu_node *p=head;
	sort_rank(head);
	p = p->next;
	printf("id  name        password  age  class  math  C-language  chinese  名次\n");
	while(p!=NULL)
	{
		if(p->info.base.num == c)
		{
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
			flag = 1;
			break;
		}
		p=p->next;
	}
	if(flag == 0)
	{
		printf("no the student\n");
	}
}

void search_stu_name(stu_node *head,char name[])
{
	int flag = 0;  
	stu_node *p=head;
	sort_rank(head);
	p = p->next;
	printf("id  name        password  age  class  math  C-language  chinese  名次\n");
	while(p!=NULL)
	{
		if(strcmp(p->info.base.name,name) == 0)
		{
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
		flag = 1;
		}
		p=p->next;

	}
	if(flag == 0)
	{
		printf("no the student\n");
	}
}


void search_stu_clazz(stu_node *head,int d)
{
	int flag = 0;
	stu_node *p=head;
	sort_rank(head);
	p = p->next;
	printf("id  name        password  age  class  math  C-language  chinese  名次\n");
	while(p!=NULL)
	{
		if(p->info.base.clazz == d)
		{
			printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
			flag = 1;
		}
		p=p->next;
	}
	if(flag == 0)
	{
		printf("no the class's student info\n");
	}
}


int confirm_admin()
{
	FILE *fp;                   
	char ad1_name[20];             
	char ad1_psw[10];              
	char ad2_name[20] = {"admin"};
	char ad2_psw[10] = {"123"};    
	printf("please input admin username:");
	scanf("%s", ad1_name); 
	printf("please input admin password:");
	scanf("%s", ad1_psw);
	if((fp=fopen("admin.txt","r+")) == NULL) 
	{
		printf("can't open admin.txt!\n");
	}
	fread(ad2_psw,sizeof(ad2_psw),1,fp);  
	if((strcmp(ad2_name,ad1_name)==0) && (strcmp(ad2_psw,ad1_psw)==0) ) 
	{
		return 1; 
	}
	else
	{
		return 0;
	}
}


void set_admin_psw()
{
	char ad_psw[10];         
	char ch;                   
	FILE *fp;                 
	printf("are you sure update admin password？yes Y，else back\n");
	scanf("%c", &ch);
	if((ch=='y') || (ch=='Y'))
	{
		if((fp=fopen("admin.txt","w+")) == NULL) 
		{
			printf("can't open admin.txt!\n");
		}
		printf("new password:\n");
		scanf("%s",ad_psw);
		fwrite(ad_psw,sizeof(ad_psw),1,fp); 
		printf("password update success\n");
		fclose(fp);                        
	}
	else
	printf("password no update\n");
}

int confirm()
{
	int c;
	printf("confirm?(y/n):");
	while(isspace(c=getchar())); 
	if(c=='y') return 1;         
	else return 0;
}


void quit(stu_node *head)
{
	if(save == 1)            
	{ 
	  printf("save info?");  
		if(confirm())         
		{
      save_stu_info(head);   
		}	
	}  
   destroy_list(head);      
}
