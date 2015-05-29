#ifndef _GT_H_
#define _GT_H_

#include <vector>
#include <map>

using namespace std;

class Gt{
public:
	class JobPair{
	public:
		JobPair(){
			machine=-1;
			time=-1;
			checked=false;
		}
		int machine;
		int time;
		bool isCheck(){return checked;}
		void check(){checked=true;}
	private:
		bool checked;
	};
	typedef vector<vector<JobPair> > Table;
	
	Gt();
	void setTable(Table&);
	void execute();
	vector<vector<int> > getASTable();
	vector<vector<int> > convertAStoMatrix(const vector<vector<int> >&);
	int getMakespan();
private:
	
	Table mTable;
	vector<vector<vector<int> > > mCreateTable;
	int mJobNum;
	int mMachineNum;

	int getMinTimeOverT(const vector<vector<int> > &,pair<int,int>&);
	bool checkConflict(int,int,pair<int,int>&);
	void fixConflict(int,int,pair<int,int>&);
	void setNextJobpair(int,int,pair<int,int>);
	void addNextIndexTable(int);
	Gt::JobPair* findJobpairByMachineAndJob(int,int,int);
	enum {PREVJOBPAIR=-1,NOWJOBPAIR,NEXTJOBPAIR};
};

#endif