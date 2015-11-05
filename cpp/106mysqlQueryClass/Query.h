#ifndef _QUERY_H_
#define _QUERY_H_

#include "mysql/mysql.h"
#include <iostream>
#include <string>
using namespace std;

class Query
{
public:
	Query();
	~Query();
	int Connect(string host,string user,string passwd,string db,unsigned int port);	
	int disConnect();
	bool IsConnect();
	int ExecSql(string sql);	
	Query& operator >> (string &vec);
	bool eof();
private:
	bool isConnect;	
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int rowcount;
	int colcount;
	int nreadrow;
	int nreadcol;
};

#endif
