#include <limits.h>
#include "Gt.h"

Gt::Gt(){
	
}

/* setTable(Table &)							 */
/* JSPテーブルの設定							 */
/* Pair<int,int>の二次元配列(vector)を引数		 */
/* とする										 */
/* vector[job][order]とし、pair<machine,time>	 */
/* とする										 */
void Gt::setTable(Table &table){
	mTable=table;
	mJobNum=table.size();
	mMachineNum=table[0].size();
}

/* execute()									 */
/* 設定されたテーブルを元にAS(Active 			 */
/* Schedule)を作り出す							 */
void Gt::execute(){
	// step1
	vector<vector<Time> > firstIndex(mMachineNum,vector<Time>(mJobNum,Time(-1,false)));
	vector<JobPair> firstJobPair=getFirstOrder();
	for(int i=0;i<firstJobPair.size();i++){
		JobPair jp=firstJobPair[i];
		int m=jp.first;
		firstIndex[m][i].first=jp.second;
	}
	mCreateTable.push_back(firstIndex);
	int index=0;
	int T=0;
	while(true){
		// step2
		int machine=0;
		machine=getMinTimeOverT(mCreateTable[index],&T);
		if(machine==-1)
			break;
		// step3
		if(checkConflict(index,machine,T)){
			// step4
			fixConflict(index,machine,T);
		}
		// step5
		setNextJobpair(index,machine,T);
		addNextIndexTable(index);
		index++;
	}
}

/* getMinTimeOverT(const vector<vector<int>>&,int*)	 */
/* ASの生成テーブルを引数とし、Tよりは大きく、最小の */
/* T'を取得する										 */
/* 返り値としては、取得したT'のmachineを返す		 */
int Gt::getMinTimeOverT(const vector<vector<Time> > &index,int *T){
	int tempT=INT_MAX;
	int machine=-1;
	for(int m=0;m<mMachineNum;m++){
		for(int j=0;j<mJobNum;j++){
			if(tempT<index[m][j].first)
				continue;
			if(*T>index[m][j].first)
				continue;
			if(index[m][j].second)
				continue;
			tempT=index[m][j].first;
			machine=m;
		}
	}
	*T=tempT;
	return machine;
}

/* checkConflict(int ,int ,const int)				 */
/* index,machineを引数とし、AS生成テーブルの中の同一 */
/* machineの中がコンフリクトを起こしているかを		 */
/* チェックする										 */
bool Gt::checkConflict(int index,int machine,int T){
	vector<Time> jobTable=mCreateTable[index][machine];
	for(int j=0;j<mJobNum;j++){
		if(jobTable[j].first<T)
			continue;
		if(jobTable[j].first-
			findJobpairByMachineAndJob(machine,j,NOWJOBPAIR).second <T){
			return true;
		}
	}
	return false;
}

/* fixConflict(int,int,int)							 */
/* コンフリクトを起こしていた場合、修正する			 */
void Gt::fixConflict(int index,int machine,int T){
	vector<Time> jobTable=mCreateTable[index][machine];
	for(int j=0;j<mJobNum;j++){
		if(jobTable[j].first<T)
			continue;
		if(jobTable[j].first-
			findJobpairByMachineAndJob(machine,j,NOWJOBPAIR).second>T)
			continue;
		if(jobTable[j].first==T)
			continue;
		JobPair prevJobPair;
		int prevT=0;
		int TT=0;
		prevJobPair=findJobpairByMachineAndJob(machine,j,PREVJOBPAIR);

		if(prevJobPair.first!=-1){
			prevT=mCreateTable[index][prevJobPair.first][j].first;
		}
		TT=max(prevT,T);
		mCreateTable[index][machine][j].first=
			findJobpairByMachineAndJob(machine,j,NOWJOBPAIR).second+TT;
	}
}

/* setNextJobpair(int,int,int)							 */
/* 作業iの技術的順序により、次に割り当てられるJobPair	 */
/* をASに記入する										 */
void Gt::setNextJobpair(int index,int machine,int T){
	int jobIndex=-1;
	vector<Time> jobTable=mCreateTable[index][machine];
	for(int j=0;j<mJobNum;j++){
		if(T!=jobTable[j].first)
			continue;
		jobIndex=j;
		break;
	}
	mCreateTable[index][machine][jobIndex].second=true;
	JobPair jp=findJobpairByMachineAndJob(machine,jobIndex,NEXTJOBPAIR);
	if(jp.first==-1)
		return;
	//int emptyTime=0;
	int nextMachine=jp.first;
	vector<Time> nextJobTable=mCreateTable[index][nextMachine];
	/*
	for(int j=0;j<mJobNum;j++){
		if(emptyTime<nextJobTable[j]){
			emptyTime=nextJobTable[j];
		}
	}
	*/
	//int TT=max(emptyTime,T);
	int TT=T;
	nextJobTable[jobIndex].first=TT+jp.second;
	mCreateTable[index][nextMachine]=nextJobTable;
}

/* addNextIndexTable(int)								 */
/* 次の生成テーブルを追加する							 */
void Gt::addNextIndexTable(int index){
	vector<vector<Time> > nextIndex;
	nextIndex=mCreateTable[index];
	mCreateTable.push_back(nextIndex);
}

/* findJobpairByMachineAndJob(int,int,int)				 */
/* machineとjobにより設定テーブルよりJobPairを見つける	 */
/* orderを指定することにより、次の処理(NEXTJOBPAIR)や	 */
/* 前の処理(PREVJOBPAIR)と使い分ける					 */
Gt::JobPair Gt::findJobpairByMachineAndJob(int machine,int jobIndex,int order){
	for(int o=0;o<mMachineNum;o++){
		if(mTable[jobIndex][o].first!=machine)
			continue;
		if(o+order<0 || o+order>mMachineNum-1){
			pair<int,int> p;
			p.first=-1;
			p.second=-1;
			return p;
		}
		return mTable[jobIndex][o+order];
	}
}

vector<Gt::JobPair> Gt::getFirstOrder(){
	vector<JobPair> firstJobPair;
	for(int j=0;j<mJobNum;j++){
		JobPair jp=mTable[j][0];
		firstJobPair.push_back(jp);
	}
	return firstJobPair;
}

/* getASTable()											 */
/* ASが生成完了した際の最終的なテーブルを取得する		 */
vector<vector<Gt::Time> > Gt::getASTable(){
	int index=mCreateTable.size();
	return mCreateTable[index-1];
}