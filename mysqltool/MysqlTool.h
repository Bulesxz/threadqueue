#ifndef MYSQL_TOOL_H
#define MYSQL_TOOL_H

#include <mysql/mysql.h>
#include <string>
#include "MysqlHandler.h"
class MysqlTool{
	public:
	MysqlTool(std::string host,std::string user,std::string passwd,std::string database);
	~MysqlTool();
	int Connect();
	int Init();
	int exec(const std::string sql,Result &retsql);
	private:
	std::string   m_host;
	std::string   m_user;
	std::string   m_passwd;
	std::string   m_database;
	MYSQL* mysql; 
};
#endif
