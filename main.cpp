#include <iostream>
#include "Gt.h"

using namespace std;

int main(void){
	Test t;
	Gt gt;
	gt.setTable(t.getTable());
	gt.execute();
	vector<vector<int> > result=gt.convertAStoMatrix(gt.getASTable());
	for(int i=0;i<result.size();i++){
		for(int j=0;j<result[0].size();j++){
			cout<<result[i][j]<<"\t";
		}
		cout<<endl;
	}
}