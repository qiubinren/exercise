#include "Query.h"

Query::Query()
{
	isConnect = false;	
	mysql_init(&mysql);
	res = NULL;
	rowcount = 0;
	colcount = 0;
	nreadrow = 0;
	nreadcol = 0;
}
Query::~Query()
{
	if(IsConnect())
		disConnect();
	mysql_free_result(res);
}
int Query::Connect(string host,string user,string passwd,string db,unsigned int port)
{
	if(!mysql_real_connect(&mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0))
		return -1;
	isConnect = true;
	return 0;
}	
int Query::disConnect()
{
	if(!IsConnect())
	{
		isConnect=false;
		mysql_close(&mysql);
		return 0;
	}
	return -1;
}
bool Query::IsConnect()
{
	return isConnect;
}
int Query::ExecSql(string sql)
{
	int ret =  mysql_query(&mysql, sql.c_str());	
	if(ret)
		return -1;	
	res = mysql_use_result(&mysql);
	if(!res)
		return -1;
	rowcount = mysql_field_count(&mysql);
}
Query& Query::operator >> (string &vec)
{
	if(nreadrow < rowcount)	
	{
		if(nreadcol < colcount)	
		{
			vec = row[nreadcol];
			nreadcol ++;
			if(nreadcol == colcount)
				nreadrow++;
		}
		else 
		{
			row=mysql_fetch_row(res);
			colcount = mysql_num_fields(res);
			nreadcol = 0;
			vec = row[nreadcol];
			nreadcol++;
			if(nreadcol == colcount)
				nreadrow++;
		}
	}
	return *this;
}
bool Query::eof()
{
	if(nreadrow < rowcount || nreadcol < colcount)
		return false;
	return true;
}	


