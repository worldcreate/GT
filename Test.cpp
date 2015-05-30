#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "Test.h"

#define INPUTFILE "sample3.txt"


using namespace std;

Test::Test(){
	ifstream ifs(INPUTFILE);
	string str;

	while(getline(ifs,str)){
		vector<Gt::JobPair> row;
		vector<string> array=split(str,':');

		for(int i=0;i<array.size();i++){
			vector<string> pair=split(array[i],',');
			const char *machine=pair[0].c_str();
			const char *time=pair[1].c_str();
			Gt::JobPair jp;
			jp.machine=atoi(machine);
			jp.time=atoi(time);
			row.push_back(jp);
		}
		mTable.push_back(row);
	}
}

Gt::Table Test::getTable(){
	return mTable;
}

vector<string> Test::split(const string &str, char delim){
	istringstream iss(str); string tmp; vector<string> res;
	while(getline(iss, tmp, delim)) res.push_back(tmp);
	return res;
}