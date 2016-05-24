#include "MysqlTool.h"
#include <stdio.h>
#include "MysqlHandler.h"
//g++ main.cpp  MysqlTool.cpp  -lmysqlclient -L /usr/lib64/mysql/
#include <logger.h>
#include <Asynclog.h>
#include <unistd.h>

using namespace daocode;
int main()
{
#ifdef DEBUG
	CSingletonLogger::GetInstance()->set_logger(new BaseLogger);
#else
	CSingletonLogger::GetInstance()->set_logger(new AsyncLog("test.log",100000));
#endif
	CSingletonLogger::GetInstance()->get_logger()->set_level(LEVEL_TRACE);
	CSingletonLogger::GetInstance()->get_logger()->start();

	MysqlTool mysql("10.24.221.144","root","root","test");
	mysql.Init();
	mysql.Connect();
	//int ret =mysql.exec("INSERT INTO t_0 VALUES(111111,2222)",row);
	Result retsql;
	//int ret =mysql.exec("select * from t_0",retsql);
	
	int ret =mysql.exec("INSERT INTO t_0 VALUES(111111,2222)",retsql);
	
	for (size_t i=0;i<retsql.rows.size();i++){
		for (size_t j=0;j<retsql.rows[i].row.size();j++){
			//printf("%s\t",retsql.rows[i].row[j].c_str());
			LOG_DEBUG("%s\n",retsql.rows[i].row[j].c_str());
		}
		//LOG_DEBUG("\n",1);
	}
		
	sleep(1);
//	std::vector<int> a;
//	a[0]=1;
}
