/***********************************
**Copyright (c) 2011,上海海同科技有限公司
**All rights reserved
**
**file name: student.h
**summary: 学生管理系统中结构体和函数声明
**version: 1.0
**author:赵龙 
**date: 2011-8-4
************************************/

#ifndef STUDENT_H
#define STUDENT_H
typedef struct stu_score            //声明学生成绩结构体 
{ 
	int math;                        //数学成绩
	int c;                           //c语言成绩          
	int chinese;                     //语文成绩
	int rank;
}stu_score;

typedef struct stu_base             //声明学生基本信息结构体  
{
	int num;                          //学号
	char name[20];                    //姓名
	char psw[10];                     //密码 
	int age;                          //年龄  
	int clazz;         	              //班级
}stu_base;

typedef struct stu_info             //声明学生信息结构体 
{
	stu_base base;                    
	stu_score score;
}stu_info;

typedef struct stu_node            //声明学生信息节点
{
	stu_info info;
	struct stu_node *next;
}stu_node;

typedef struct stu_sort           //定义用来排名的结构体 
{
	int num;
	int total;                        //总成绩和 
	int rank;
}stu_sort;

typedef struct stu_sort_score     //定义用来单科成绩排名的结构体
{
	int math;
	int c;
	int chinese;
	int num;
}sort_score;

stu_info input_info();//录入学生信息
stu_node *init_stu();//初始化头节点
void add_stu(stu_info stu,stu_node *head);//添加学生信息
void save_stu_info(stu_node *head);//保存学生信息
void load_stu_info(stu_node *head);//加载学生信息
int delete_stu(stu_node *head,int num);//删除学生
int length(stu_node *head);//计算链表长度
int modify_stu_menu(stu_node *head);//修改菜单
void modify_stu(stu_node *head,char name[]);//学生修改密码
void modify_stu_psw(stu_node *head);//修改学生密码
void modify_stu_age(stu_node *head);//修改学生年龄
void modify_stu_clazz(stu_node *head);//修改学生班级
void modify_stu_math(stu_node *head);//修改学生数学成绩
void modify_stu_c(stu_node *head);//修改学生C语言成绩
void modify_stu_chinese(stu_node *head);//修改学生语文成绩
void sort_rank(stu_node *head);//学生成绩排名
void print_stu_rank(stu_node *head);//按名次显示学生信息
int  print_stu_menu(stu_node *head);//显示学生信息菜单
void print_stu_num(stu_node *head);//按学号顺序显示学生信息
void print_stu_math(stu_node *head);//按数学成绩顺序显示学生信息
void print_stu_c(stu_node *head);//按c语言成绩顺序显示学生信息
void print_stu_chinese(stu_node *head);//按语文成绩顺序显示学生信息
int search_stu_menu(stu_node *head);//查找学生信息菜单
void search_stu_num(stu_node *head,int c);//按学号查找学生
void search_stu_name(stu_node *head,char name[]);//按学生名字查找学生
void search_stu_clazz(stu_node *head,int d); //按班级查找学生
int confirm_admin(); //管理员登录确认
int main_menu(stu_node *head);//主菜单
int admin_menu(stu_node *head);//管理员菜单
int stu_menu(stu_node *head); //学生菜单
void destroy_list(stu_node *h);//销毁链表
int confirm(); //确认
void set_admin_psw(); //设置密码
void quit(stu_node *head);//退出
extern int count;  // 全局变量用来计学生学号
extern int save;   //全局变变量 作保存标志
#endif

