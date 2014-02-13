
#include "mdseries.h"
#include "boost/date_time.hpp"
using namespace boost::posix_time;
using namespace boost::gregorian;

enum update_status {
	CURRENT_BAR,
	NEXT_BAR,
	NNEXT_BAR,
	NNNEXT_BAR,
	PREV_BAR,
};


class mdseries {
public:
	int period;/*����*/    
	period_type ptype;/*��������*/
	dseries  high;
	dseries  low;
	dseries open;
	dseries close;
	dseries volume;
	update_status get_update_status(int b1,int b2,int e1,int e2,int n1,int n2,period_type ptype) {
		/*
		b1 ��ǰbar�Ŀ�ʼ.
		e1 ��ǰbar�Ľ���.
		n1 ��ǰ�����ʱ�䡣
		��Ҫ�жϵ�ǰ�����飬�Ƿ��ǵ�ǰ��bar������.
		*/
		if(n1+n2<=e1+e2)
			return PREV_BAR;
		switch(ptype){
		case MIRCO:
			if(this->is_continue(e1,e2,n1,n2)) {
				/*���������*/
				if(e1==n1 && e2==0 && n2==500) {
					return NEXT_BAR;
				}else {
					return NNEXT_BAR;
				}
			}else {
				return NNNEXT_BAR;
			}
			break;		
		case MINUTE:
			if(this->is_continue(e1,e2,n1,n2)) {
				/*
				  case 1:��ǰbar.
				  case 2:�¸�bar.
				  case 3:���¸�BAR
				*/
			}else {
				/*
				  case 1:
				  case 2:
				  case 3:
				*/
			}
			break;
		case HOUR:
			break;
		case DAY:
			assert(0);
			break;
		case WEEK:
			assert(0);
			break;
		case YEAR:
			assert(0);
			break;
		default:
			assert(0);
			cout<<"err"<<endl;
			break;
		}

	};
	int updatems(float v, int b1, int b2) {
			/*todo lock 
			  1.����...
			  ����ǵ�ǰ���K���ϵġ��͸��µ�ǰ���k�ߡ�������ǡ�
			  ���ڷ����ߣ��߼����£�
			  ����ǵ�ǰ���ӵģ����±�K�ߡ�
			  �������һ���ӵģ������¸�k�ߡ�
			  ����������������ǲ�����һ���ӵġ�������϶�����Ǹ�����һ���ӡ�
			  ������������ġ������Ÿ��¡�
			  �����֮ǰ�����ݡ����Դ����ݡ�
			*/	    
	};

	int updateme(float v, int b1, int b2) {
			/*todo lock 
			  1.����...
			  ����ǵ�ǰ���K���ϵġ��͸��µ�ǰ���k�ߡ�������ǡ�
			  ���ڷ����ߣ��߼����£�
			  ����ǵ�ǰ���ӵģ����±�K�ߡ�
			  �������һ���ӵģ������¸�k�ߡ�
			  ����������������ǲ�����һ���ӵġ�������϶�����Ǹ�����һ���ӡ�
			  ������������ġ������Ÿ��¡�
			  �����֮ǰ�����ݡ����Դ����ݡ�
			*/
		    
	};
		
	int between(int start, int end,int t)
	{
		if((t>start-300) && (t<end+300))
			return 1;
		else
			return 0;
	}
	int between(int start, int end,int t1,int t2)
	{
		if((t1>start-300) && (t1<end+300) &&
		   (t2>start-300) && (t2<end+300)
			)
			return 1;
		else
			return 0;
	}
	time_t tm_fix(tm *t,int hour,int minutes){
		t->tm_hour=hour;
		t->tm_sec=minutes;
		return mktime(t);
	}
	int tm_continue(tm *t1, tm *t2) {
			int ret=0;
		    tm begin;
			tm end;
			time_t tt1,tt2,tbegin,tend;
			tm *pbegin,*pend;
			//tm *pend=gmtime((time_t*)&e1);
		    //tm *pbegin=gmtime((time_t*)&b1);
			pbegin=&begin;
			pend=&end;
			tt1=mktime(t1);
			tt2=mktime(t2);
			if(tt1<=tt2) {
				memcpy(&begin,t1,sizeof(tm));
				memcpy(&end, t2,sizeof(tm));
			}else {
				memcpy(&begin,t2,sizeof(tm));
				memcpy(&end, t1,sizeof(tm));
			}
			if(t1->tm_mday==t2->tm_mday) {
				/*�����ͬһ��
				*/
				tbegin=this->tm_fix(&begin,9,0);
				tend=this->tm_fix(&end,10,15);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}
				tbegin=this->tm_fix(&begin,10,15);
				tend=this->tm_fix(&end,11,30);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}

				tbegin=this->tm_fix(&begin,13,30);
				tend=this->tm_fix(&end,15,0);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}

				tbegin=this->tm_fix(&begin,21,0);
				tend=this->tm_fix(&end,2,30);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}
			}else {
				/*�������ͬһ��
				*/	
				tbegin=this->tm_fix(&begin,9,0);
				tend=this->tm_fix(&end,10,15);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}

				tbegin=this->tm_fix(&begin,10,15);
				tend=this->tm_fix(&end,11,30);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}

				tbegin=this->tm_fix(&begin,13,30);
				tend=this->tm_fix(&end,15,0);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}

				tbegin=this->tm_fix(&begin,21,0);
				tend=this->tm_fix(&end,2,30);
				if(this->between(tbegin,tend,tt1,tt2)) {
					ret=1;
					goto out;
				}
			}
			return ret;
out:
			return ret;
	}
	int is_continue(int e1,int e2, int b1, int b2){
	    /*9�㵽-10:15,10:30-11:30,1:30-3:00,21:00-2:30
		  0 =is_continue;
		  1 =biger than xxx
		  -1=smaller than xxx
		*/

		/*
		tm *t;
		ptime d(ptime_from_tm(*t));
		time_t td=time(NULL);
		t=gmtime(&td);
		*/
		
		tm *end=gmtime((time_t*)&e1);
		tm *begin=gmtime((time_t*)&b1);
		if(e1+ 28800<b1) {
			/*ʱ���8Сʱ
			*/
			return 0;
		}else if(e1 > b1+28800){
			/*ʱ���8Сʱ
			*/
			return 0;
		}else {


		}
	};
	
	int fix(){
		/*���������ʱ������������ͼۡ���������*/
	};
};

int mdseries::update(float v, int t1, int t2) 
{
    /**/
}

#define OPEN_FLAG 0x01
#define CLOSE_FLAG 0x02
#define HIGH_FLAG  0x04
#define LOW_FLAG   0x08
#define VOLUME_FLAG 0x10

class md {
public:
	int regmd(int period) {
		/*ע��һ������*/
	};
	int drivemd() {
		/*��������,���¸�������*/
	};
	
	map<int, mdseries> mds;
	vector<int>         perids;
	dseries             ds;  /*base misc service*/
	int update(string contract, float v, int t1, int t2) {
		/*1.���� ds
		  2.���� �����ߡ�
		  3.���� x�����ߡ�
		  ÿ�θ��£��������Ƿ�Ҫ�����´��ߵ��ĸ�ֵ��
		*/
		int status=this->ds.update(v,t1,t2);
		if(status <0) {
			/**/
		}else {
			/*
			*/
			float o,c,h,l;int e1,e2;
			/*���·�����*/
			c=ds[0];
			e1=ds.csec;
			e2=ds.cmsec;
			status=mds[1].update500ms(c,e1,e2);


			/*������������*/
			o=mds[1].open[0];
			c=mds[1].close[0];
			h=mds[1].high[0];
			l=mds[1].low[0];
			e1=mds[1].close.csec;
			e2=mds[1].close.cmsec;

			for(vector<int>::iterator it=perids.begin();it!=perids.end();it++) {
				int temp=0;
				if(status & OPEN_FLAG) {
					temp=temp | mds[*it].open.update(o,e1,e2);
				}
				if(status & CLOSE_FLAG) {
					temp=temp | mds[*it].close.update(c,e1,e2);
				}
				if(status & HIGH_FLAG) {
					temp=temp | mds[*it].high.update(h,e1,e2);
				}
				if(status & LOW_FLAG) {
					temp=temp | mds[*it].low.update(l,e1,e2);
				}
				if(status & VOLUME_FLAG) {
					//vol how to process
					//temp=temp | mds[*it].open.update(v,e1,e2);
				}
				status=temp;
			}
		}
	}

	int update_timer()
	{
		/*
			ÿ1������һ�Ρ�
			�����ǰ��xx���ڵĿ�ʼ�����ҵ�ǰ����û�����飬��Ĭ��������顣
			ֻ���Ƿ��Ӽ��������ϼ�������.
		*/
	};

};

class mdservice {
	/*ÿ��mdһ���߳�*/
	map<string, md> mds;
	/*todo ��д��*/
	int md(string contract,int period, int bar){};
	int update(string contract, float v, int t1, int t2);
	int update_timer() {
		/*
			ÿ1������һ�Ρ�
			�����ǰ��xx���ڵĿ�ʼ���Ĭ�����顣
		*/
	}
	/*��ʱ��������ʱ���¸�����Լ�ĸ���������
	  �ر���ֻ��������������Ӧ���Ǹ������ߡ������߶�ʱ��������������ڵ��ߡ�
	*/
};
