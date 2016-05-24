#ifndef MYSQLHABDLER_H
#define MYSQLHABDLER_H
#include <vector>
typedef struct ROW {
	ROW(int n){
		row = std::vector<std::string>(n);
	}
	std::vector<std::string> row;
}ROW;
typedef struct Result{
	int ret ;
	int affectrow;
	std::vector<ROW> rows;
}Result;
#endif
