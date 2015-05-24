#include <iostream>
#include "Gt.h"

using namespace std;

int main(void){
	Gt::Table table;
	Gt::JobPair j1,j2,j3,j4,j5,j6,j7,j8,j9;
	j1.first=0;j1.second=2;
	j2.first=1;j2.second=3;
	j3.first=2;j3.second=4;
	j4.first=1;j4.second=4;
	j5.first=0;j5.second=3;
	j6.first=2;j6.second=5;
	j7.first=2;j7.second=6;
	j8.first=1;j8.second=5;
	j9.first=0;j9.second=4;
	vector<Gt::JobPair> firstRow;
	firstRow.push_back(j1);
	firstRow.push_back(j2);
	firstRow.push_back(j3);
	vector<Gt::JobPair> secondRow;
	secondRow.push_back(j4);
	secondRow.push_back(j5);
	secondRow.push_back(j6);
	vector<Gt::JobPair> thirdRow;
	thirdRow.push_back(j7);
	thirdRow.push_back(j8);
	thirdRow.push_back(j9);
	table.push_back(firstRow);
	table.push_back(secondRow);
	table.push_back(thirdRow);
	Gt gt;
	gt.setTable(table);
	gt.execute();
	vector<vector<int> > result=gt.getASTable();
	for(int i=0;i<result.size();i++){
		for(int j=0;j<result[0].size();j++){
			cout<<result[i][j]<<" ";
		}
		cout<<endl;
	}
}