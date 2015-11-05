#include <stdio.h>
#include <mysql/mysql.h>
int main()
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* query="select * from test;";
	int t,r;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root","","test2",0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(&mysql));
	}
	else
		printf("Connected...");
	t=mysql_query(&mysql,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(&mysql));
	}
	else
	{
		printf("Query made...\n");
		res = mysql_use_result(&mysql);
		if(res)
		{
			for(r=0;r<mysql_field_count(&mysql);r++)
			{
				row=mysql_fetch_row(res);
				if(row<0)
					break;
				for(t=0;t<mysql_num_fields(res);t++)
					printf("%s ",row[t]);
				printf("\n");
			}
		}
		mysql_free_result(res);
	}
	mysql_close(&mysql);
	return 0;
}
