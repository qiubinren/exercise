#include<stdio.h>
#include"student.h"
#include<string.h>  


int main_menu(stu_node *head)
{
	int i;            
	int n;            
	while(i!=3)
	{
		printf("\t   --------------------\n");
		printf("\n");
		printf("\t    welcome to student info system\n");
		printf("\t      1.admin\n");
		printf("\t      2.student\n");
		printf("\t      3.exit\n");
		printf("\n");
		printf("\t  ----------------------\n");
		printf("\t    please select your identity:");
		scanf("%d", &i);
		getchar();
		switch(i)
		{ 
  		case 1:
      				if(confirm_admin()==1)   
      				{  
          			printf("admin enter success\n");
								admin_menu(head);     
							}	              
							else
							{
								n = 2;      
								printf("your password is wrong,you also try twice\n"); 
								while(n!=0)
								{
									if(confirm_admin()==1)
									{  
										printf("admin enter success\n");
										admin_menu(head);
										break;
									}
									else
									{
										n--;
										if(n==0)
										{
											destroy_list(head);  
											return 0;
										}
										printf("your enter username or password is wrong,you can try twice\n",n);
									}
								}
							}
						 	break;

			case 2: 
							stu_menu(head);      
							break; 
			case 3:
							quit(head);          
							return 0;
			default:
							printf("your enter is wrong\n");
		}
	}
	return 0;
}

int admin_menu(stu_node *head)
{
	int num;     
	int a=0;         
	load_stu_info(head);
	while(a!=9)
	{
		printf("\t    -------------------\n");
		printf("\n");
		printf("\t    welcome admin login\n");
		printf("\t      1.input student info\n");
		printf("\t      2.delete student info\n");
		printf("\t      3.update student info\n");
		printf("\t      4.search student info\n");
		printf("\t      5.print student info\n");
		printf("\t      6.save student info\n");
		printf("\t      7.load student info\n");
		printf("\t      8.update password\n");
		printf("\t      9.back\n");
		printf("\n");
		printf("\t    ------------------\n");
		printf("\t    please enter:");
		scanf("%d",&a);
		getchar();
		switch(a)
		{
			case 1:
							add_stu(input_info(),head);    
							break;
			case 2:
							printf("input want delete student info");
							scanf("%d",&num);
							delete_stu(head,num);				
							break;
			case 3:																									
							modify_stu_menu(head);	
							break;													
			case 4:	
							search_stu_menu(head);										
							break;								
			case 5:						
							print_stu_menu(head);		
							break;																		
			case 6:	
							printf("is save?");			
							if(confirm())
							{
								save_stu_info(head);      
								printf("save success\n");
							}
							break;																			
			case 7: 
							printf("is load student info?");    
							if(confirm())
							{ 
								destroy_list(head);         
								load_stu_info(head);      
								printf("load success\n");
							}
							break;
			case 8:
							set_admin_psw();         
							break;
			case 9:			
							return 0;					
			default:												
							printf("input wrong\n");												
		}
	}
	return 0;
}

int stu_menu(stu_node *head)
{
	stu_node *p = head ;
	char stu_name[20];             
	char stu_pwd[10];              
	int flag = 0;           
	int n = 2;             
	int a;                 
	sort_rank(head);       
	load_stu_info(head); 
	loop:printf("please enter username:");
	scanf("%s",stu_name);
	printf("please input password:");
	scanf("%s",stu_pwd);
	p = head->next;
	while(p!=NULL)
	{
		if((strcmp(p->info.base.name,stu_name)==0) && (strcmp(p->info.base.psw,stu_pwd)==0))
		{
			while(a!=3)
			{
				printf("\t    -----------------\n");
				printf("\t    welcome %s student login\n",stu_name);
				printf("\t      1.update password\n");
				printf("\t      2.print info\n");
				printf("\t      3.back\n");
				printf("\n");
				printf("\t    -----------------\n");
				printf("\t    please input:");
				scanf("%d",&a);
				getchar();
				switch(a)
				{
					case 1:  
									modify_stu(head,stu_name);      
									break;
					case 2:
									printf("id  name        password  age  class  math  C-language  chinese  rank\n");
									printf("%-6d%-13s%-6s%-6d%-6d%-10d%-10d%-10d%-10d\n",p->info.base.num,p->info.base.name,p->info.base.psw,p->info.base.age,p->info.base.clazz,p->info.score.math,p->info.score.c,p->info.score.chinese,p->info.score.rank);
									break;
					case 3:
									return 0;
					default:
									printf ("input wrong\n");
				}
			}
			flag = 1;
			break;
			}  
			else
				p=p->next; 	
	}	
			if(flag == 0)
			{
				if(n==0)  
				{
					return 0;
				}
				printf("your input username or password is wrong,also have %d input",n);
				n--;
				goto loop;
			}
	return 0;
}

int modify_stu_menu(stu_node *head)
{
	int i=0;             
	while(i!=7)
	{
		printf("\t      --------------------\n");
		printf("\n");
		printf("\t      1.update student password\n");
		printf("\t      2.update student age\n");
		printf("\t      3.update student class\n");
		printf("\t      4.update student math\n");
		printf("\t      5.update student C-language\n");
		printf("\t      6.update student chinese\n");
		printf("\t      7.exit update menu\n");
		printf("\n");
		printf("\t      --------------------\n");
		printf("\t      please select type:");
		scanf("%d",&i);
		getchar();
		switch(i)
		{
			case 1:    
							modify_stu_psw(head); 
							break;
			case 2: 
							modify_stu_age(head);  
							break;
			case 3: 
			        modify_stu_clazz(head);  
							break;
			case 4:
							modify_stu_math(head);   
							break;
			case 5:
							modify_stu_c(head);       
							break;
			case 6:
							modify_stu_chinese(head);  
							break;
			case 7:
							return 0;
			default:
							printf("input wrong\n");			
		}
	}
	return 0;	
}	
    
int  print_stu_menu(stu_node *head)
{
	int i=0;               
	while(i!=7)
	{
		printf("\t      --------------------\n");
		printf("\n");
		printf("\t      1.id sort print\n");
		printf("\t      2.rank sort print\n");
		printf("\t      3.math sort print\n");
		printf("\t      4.C-language sort print\n");
		printf("\t      5.chinese sort print\n");
		printf("\t      6.exit\n");
		printf("\n");
		printf("\t      --------------------\n");
		printf("\t      select print type:");
		scanf("%d",&i);
		getchar();
 		switch(i)
		{
			case 1:
							print_stu_num(head);    
							break;
			case 2:
							print_stu_rank(head);   
							break;
			case 3:
							print_stu_math(head);   
							break;
			case 4:
							print_stu_c(head);    
							break;
			case 5:
							print_stu_chinese(head);
							break;
			case 6:
							return 0;
			default:
							printf("输入错误\n");
		}
	}
	return 0;
}

int search_stu_menu(stu_node *head)
{
	int b=0;               
	int c=0;             
	int d=0;            
	char name[20];      
	while(b!=4)
	{
		printf("\t      ------------------\n");
		printf("\n");
		printf("\t      1.id search\n");
		printf("\t      2.name search\n");
		printf("\t      3.class search\n");
		printf("\t      4.exit search menu\n");
		printf("\n");
		printf("\t      ------------------\n");
		printf("\t      select search type:");
		scanf("%d",&b);
		getchar();
		switch(b)
		{
			case 1:
							printf("please input search id:");
							scanf("%d",&c);
							search_stu_num(head,c);        
							break;
			case 2:
							printf("please input search name:");
							scanf("%s",name);
							search_stu_name(head,name);   
							break;
			case 3:
							printf("please input search class:");
							scanf("%d",&d);
							search_stu_clazz(head,d);   
							break;
			case 4:
							return 0;
			default:
							printf("input wrong\n");
		}
	}
	return 0;
}
