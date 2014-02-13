#ifndef MDSERIES_H_
#define MDSERIES_H_
#include "dseries.h"
#include "mdseries.h"
#include <map>
using namespace std;

/*500毫秒线，实时启动分钟线。分钟线换线，才驱动高级别线*/
class mdseries {
public:
	int period;/*周期*/    
	period_type ptype;/*周期类型*/
	dseries  high;
	dseries  low;
	dseries open;
	dseries close;
	int update(float v, int t1, int t2) {};
};

class md {
public:
	int regmd(int period) {
		/*注册一个周期*/
	};
	int drivemd() {
		/*行情驱动,更新各个周期*/
	};
	
	map<int, mdseries> mds;
	dseries            ds;  /*base misc service*/
};

class mdservice {
	/*每个md一个线程*/
	map<string, md> mds;
	/*todo 读写锁*/
	int md(string contract,int period, int bar){};
	int update(string contract, float v, int t1, int t2);
};





#endif