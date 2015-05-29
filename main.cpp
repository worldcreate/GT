#include <iostream>
#include "Gt.h"
#include "Test.h"

#define TRIAL 50

using namespace std;

int main(void){
	Test t;
	Gt::Table table=t.getTable();

	double makespanAve=0;
	for(int i=0;i<TRIAL;i++){
		Gt gt;
		gt.setTable(table);
		gt.execute();
		vector<vector<int> > result=gt.getASTable();
		
		cout<<"  ";
		for(int i=0;i<result[0].size();i++)
			cout<<i<<"\t";
		cout<<endl;
		for(int i=0;i<result.size();i++){
			cout<<i<<":";
			for(int j=0;j<result[0].size();j++){
				cout<<result[i][j]<<"\t";
			}
			cout<<endl;
		}
		cout<<"makespan="<<gt.getMakespan()<<endl;
		makespanAve+=gt.getMakespan();
	}
	cout<<"makespanAverage="<<makespanAve/TRIAL<<endl;
}