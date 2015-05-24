#ifndef _TEST_H_
#define _TEST_H_

#include "Gt.h"

class Test{
public:
	Test();
	Gt::Table getTable();
private:
	Gt::Table mTable;
	vector<string> split(const string &str, char delim);
};

#endif