#include <stdio.h>
int theyearday(int y,int m,int d)
{
	int day[12]={31,59,90,120,151,181,212,243,273,304,334,365};
	int sum=0;
	if((y%4==0&&y%100!=0)||y%400==0)
		sum+=1;
	sum+=day[m-1]+d;
	return sum;
}
int sumday(int y,int m,int d)
{
	int sum=(y-1)/4-(y-1)/100+(y-1)/400;
	int sum1=y-sum;
	int sum2=sum*366+sum1*365;
	sum2+=theyearday(y,m,d);
	return sum2;
}
int main()
{
	int y1,m1,d1;
	int y2,m2,d2;
	scanf("%d-%d-%d",&y1,&m1,&d1);
	scanf("%d-%d-%d",&y2,&m2,&d2);
	int sum1=0,sum2=0;
	sum1=theyearday(y1,m1,d1);
	printf("%d\n",sum1);
	sum1=sumday(y1,m1,d1);
	sum2=sumday(y2,m2,d2);
	printf("%d\n",sum1-sum2);
	
	return 0;
}
