#ifndef _GT_H_
#define _GT_H_

#include <vector>
#include <map>

using namespace std;

class Gt{
public:
	typedef pair<int,int> JobPair;
	typedef vector<vector<JobPair> > Table;
	typedef pair<int,bool> Time;
	
	Gt();
	void setTable(Table&);
	void execute();
	vector<vector<Gt::Time> > getASTable();
private:
	
	Table mTable;
	vector<vector<vector<Time> > > mCreateTable;
	int mJobNum;
	int mMachineNum;

	int getMinTimeOverT(const vector<vector<Time> > &,int*);
	bool checkConflict(int,int,int);
	void fixConflict(int,int,int );
	void setNextJobpair(int,int,int);
	void addNextIndexTable(int);
	vector<Gt::JobPair> getFirstOrder();
	Gt::JobPair findJobpairByMachineAndJob(int,int,int);
	enum {PREVJOBPAIR=-1,NOWJOBPAIR,NEXTJOBPAIR};
};

#endif