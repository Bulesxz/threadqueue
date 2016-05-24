#include "MysqlTool.h"
#include <stdio.h>
#include <mysql/errmsg.h>
MysqlTool::MysqlTool(std::string host,std::string user,std::string passwd,std::string database):m_host(host),m_user(user),
		m_passwd(passwd),m_database(database),mysql(NULL)
{
}

int MysqlTool::Init()
{
	mysql= mysql_init(NULL);
	if (mysql==NULL){
		fprintf(stderr, "Failed to mysql_init\n");
		return -1;
	}
	return 0;
}

int MysqlTool::Connect()
{
	mysql_options(mysql,MYSQL_INIT_COMMAND,"set names utf8");

	if (!mysql_real_connect(mysql,m_host.c_str(),m_user.c_str(),m_passwd.c_str(),m_database.c_str(),0,NULL,0))
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(mysql));
		return -1;
	}
	return 0;
}

int MysqlTool::exec(const std::string sql,Result &retsql)
{
	int err = mysql_real_query(mysql,sql.c_str(),sql.size());
	if (err!=0){
			fprintf(stderr, "Failed to mysql_real_query database: Error: %s\n", mysql_error(mysql));
			retsql.ret = err;
			return err;
	}

	MYSQL_RES *result = mysql_store_result(mysql);
	if (result==NULL){
		err = mysql_errno(mysql);
		if (err!=0){
			fprintf(stderr, "Failed to mysql_store_result database: Error: %s\n", mysql_error(mysql));
			if (CR_SERVER_LOST==err){
				this->Connect();//重连
			}
			retsql.ret = err;
			return err;
		}
	}else{ //有结果集
			unsigned int num_fields = mysql_num_fields(result);
			MYSQL_ROW row;
			int rc=0;//行
			while ((row = mysql_fetch_row(result)))
			{
					retsql.rows.push_back(ROW(num_fields));
					unsigned long *lengths;
					lengths = mysql_fetch_lengths(result);
					for(unsigned int i = 0; i < num_fields; i++)
					{
							//retsql.rows[rc].row[i]= lengths[i];
					//		printf("[%.*s]", (int) lengths[i],row[i] ? row[i] : "NULL");
							retsql.rows[rc].row[i] = std::string(row[i],lengths[i]);
					}
					//printf("\n");
					rc++;
			}
	}
	// query does not return data
	// (it was not a SELECT)
	retsql.affectrow = mysql_affected_rows(mysql);
	if (result!=NULL){
		mysql_free_result(result);
	}

	err= mysql_errno(mysql);
	retsql.ret = err;

	return err;

}
MysqlTool::~MysqlTool()
{
	if (mysql!=NULL)
		mysql_close(mysql);
}
