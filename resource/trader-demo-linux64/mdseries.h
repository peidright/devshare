#ifndef MDSERIES_H_
#define MDSERIES_H_
#include "dseries.h"
#include "mdseries.h"
#include <map>
using namespace std;

/*500�����ߣ�ʵʱ���������ߡ������߻��ߣ��������߼�����*/
class mdseries {
public:
	int period;/*����*/    
	period_type ptype;/*��������*/
	dseries  high;
	dseries  low;
	dseries open;
	dseries close;
	int update(float v, int t1, int t2) {};
};

class md {
public:
	int regmd(int period) {
		/*ע��һ������*/
	};
	int drivemd() {
		/*��������,���¸�������*/
	};
	
	map<int, mdseries> mds;
	dseries            ds;  /*base misc service*/
};

class mdservice {
	/*ÿ��mdһ���߳�*/
	map<string, md> mds;
	/*todo ��д��*/
	int md(string contract,int period, int bar){};
	int update(string contract, float v, int t1, int t2);
};





#endif