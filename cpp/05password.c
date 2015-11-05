#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#define MAXLEN 10
int main()
{
	char c;
	char password[MAXLEN];
	int i=0;
	initscr();
	while((c=getch())!='\r'&&i<MAXLEN-1)
	{
		if(c==8)
		{
			if(i>0)
			{
				password[--i]=0;
				printf("%c%c%c",8,' ',8);
			}
			else
				putchar(7);
		}
		else
		{
			password[i++]=c;
			putchar('*');
		}
	}
	password[i]=0;
	printf("\n%s\n",password);
	endwin();
	return 0;
}
