#ifndef DSERIES_H_
#define DSERIES_H_
#include "boosthelp.h"

enum period_type {
	MIRCO,
	MINUTE,
	HOUR,
	DAY,
	WEEK,
	YEAR,
};

enum kdata_type {
	HIGH,
	LOW,
	OPEN,
	CLOSE,
};

class dseries {
public:
	static const int MAX_DSERIES_SIZE=10000;
	float data[MAX_DSERIES_SIZE];
	int   tsec[MAX_DSERIES_SIZE];
	int   tmsec[MAX_DSERIES_SIZE];
	float operator[](int i){
		/*fault tolerent*/
		return this->data[cidx-i];
	}
	typedef int (*updatecb)(float ,int,int);
	updatecb cb;
	int eidx;
	int bidx;
	int cidx;
	int esec,emsec;
    int csec,cmsec;
	int bsec,bmsec;
	period_type ptype;
	dseries(){cidx=0;};
	dseries(updatecb cb) {this->cb = cb;};
	boost::timed_mutex mutex;

	int update_ms(float v, int sec, int msec){
		/*
		  1.
		  2.
		*/
	again:
		boost::unique_lock<boost::timed_mutex> lk(this->mutex,boost::chrono::milliseconds(1));
		if(lk) {
			if( (sec > this->csec) || 
				(sec== this->csec && (msec >this->cmsec))
				) {
			        /*需要更新,这里不确认是否保证先后顺序.暂时按顺序的处理。忽略不按顺序的包丢弃.
				   */
					this->tmsec[this->cidx]=msec;
					this->tsec[this->cidx]=sec;
					this->data[this->cidx]=v;
					this->cidx++;
					this->csec=sec;
					this->cmsec=msec;
			}else {
				/*todo warning, drop old message*/
			}
		}else {
			/*warnring*/
			goto again;
		}
		return 0;
	}
	int update_meh(float v, int sec, int msec){
			/*判断是否是当前这根k线
			  如果是当前分钟的，更新本k线。
		      如果是下一分钟线，更新下根k线，如果本根k线为空，是否考虑修复本根？
			  如果是是连续的，但不是下一分钟，流出空隙。但更新下一分钟。
			  如果不是连续的，紧接着更新。
			  如果是之前的数据，忽略此数据..
			*/	
		    int start,cidx,now;
			start=this->tsec[this->cidx];
			cidx=this->cidx;
			now=60*(sec/60);
			if(start==0 && cidx==0) {
				/*如果当前是刚开始。	  
				*/
				this->data[cidx]=v;
				this->tsec[cidx]=60*(sec /60);

			}else if(cidx==0 && start!=0){
	           /*如果是第一根k线，
			      1.是否是最新的数据
				  2.取max值。
			   */
				if(start==(sec/60)*60) {
					/*如果是同一分钟*/
				    this->data[cidx]=std::max<float>(this->data[cidx],v);
				}else if((start+1)==now){
					/*如果是新的一分钟*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}else if(1/*是同一时间段*/) {
					/*有可能要考虑补全间隙*/

				}else {
					/*不再考虑补全间隙*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}

			} else if(cidx!=0 && start!=0) {
			   /*当cidx为非零值得时候，这个cidx必然是已经有有实际报价，
			     或者timer定时器已经发生过!
			   */
				if(start==(sec/60)*60) {
					/*如果是同一分钟*/
				    this->data[cidx]=std::max<float>(this->data[cidx],v);
				}else if((start+1)==now){
					/*如果是新的一分钟*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}else if(1/*是同一时间段*/) {
					/*有可能要考虑补全间隙*/

				}else {
					/*不再考虑补全间隙*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}
			} else if(cidx!=0 && start==0) {
					assert(0);
			}
			this->csec=sec;
			this->cmsec=msec;
			return 0;
	};
	int update_mel(float v, int sec, int msec){
				/*判断是否是当前这根k线
			  如果是当前分钟的，更新本k线。
		      如果是下一分钟线，更新下根k线，如果本根k线为空，是否考虑修复本根？
			  如果是是连续的，但不是下一分钟，流出空隙。但更新下一分钟。
			  如果不是连续的，紧接着更新。
			  如果是之前的数据，忽略此数据..
			*/	
		    int start,cidx,now;
			start=this->tsec[this->cidx];
			cidx=this->cidx;
			now=60*(sec/60);
			if(start==0 && cidx==0) {
				/*如果当前是刚开始。	  
				*/
				this->data[cidx]=v;
				this->tsec[cidx]=60*(sec /60);

			}else if(cidx==0 && start!=0){
	           /*如果是第一根k线，
			      1.是否是最新的数据
				  2.取max值。
			   */
				if(start==(sec/60)*60) {
					/*如果是同一分钟*/
				    this->data[cidx]=std::min<float>(this->data[cidx],v);
				}else if((start+1)==now){
					/*如果是新的一分钟*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}else if(1/*是同一时间段*/) {
					/*有可能要考虑补全间隙*/

				}else {
					/*不再考虑补全间隙*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}

			} else if(cidx!=0 ) {
			   /*当cidx为非零值得时候，这个cidx必然是已经有有实际报价，
			     或者timer定时器已经发生过!
			   */
				if(start==(sec/60)*60) {
					/*如果是同一分钟*/
				    this->data[cidx]=std::min<float>(this->data[cidx],v);
				}else if((start+1)==now){
					/*如果是新的一分钟*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}else if(1/*是同一时间段*/) {
					/*有可能要考虑补全间隙*/

				}else {
					/*不再考虑补全间隙*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}
			}
			this->csec=sec;
			this->cmsec=msec;
			return 0;
	};
	int update_meo(float v, int sec, int msec){
				/*判断是否是当前这根k线
			  如果是当前分钟的，更新本k线。
		      如果是下一分钟线，更新下根k线，如果本根k线为空，是否考虑修复本根？
			  如果是是连续的，但不是下一分钟，流出空隙。但更新下一分钟。
			  如果不是连续的，紧接着更新。
			  如果是之前的数据，忽略此数据..
			*/	
		    int start,cidx,now;
			start=this->tsec[this->cidx];
			cidx=this->cidx;
			now=60*(sec/60);
			if(start==0 && cidx==0) {
				/*如果当前是刚开始。	  
				*/
				this->data[cidx]=v;
				this->tsec[cidx]=60*(sec /60);

			}else if(cidx==0 && start!=0){
	           /*如果是第一根k线，
			      1.是否是最新的数据
				  2.取max值。
			   */

			} else if(cidx!=0 && start==0) {
			   /*当cidx为非零值得时候，这个cidx必然是已经有有实际报价，
			     或者timer定时器已经发生过!
			   */
				if(start==(sec/60)*60) {
					/*如果是同一分钟,不是open*/
				    //this->data[cidx]=std::max<float>(this->data[cidx],v);
				}else if((start+1)==now){
					/*如果是新的一分钟*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}else if(1/*是同一时间段*/) {
					/*有可能要考虑补全间隙*/

				}else {
					/*不再考虑补全间隙*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}
			}else if (cidx!=0 && start!=0) {
				//ignore
			}
			this->csec=sec;
			this->cmsec=msec;
			return 0;
	};
	int update_mec(float v, int sec, int msec){
				/*判断是否是当前这根k线
			  如果是当前分钟的，更新本k线。
		      如果是下一分钟线，更新下根k线，如果本根k线为空，是否考虑修复本根？
			  如果是是连续的，但不是下一分钟，流出空隙。但更新下一分钟。
			  如果不是连续的，紧接着更新。
			  如果是之前的数据，忽略此数据..
			*/	
		    int start,cidx,now;
			start=this->tsec[this->cidx];
			cidx=this->cidx;
			now=60*(sec/60);
			if(start==0 && cidx==0) {
				/*如果当前是刚开始。	  
				*/
				this->data[cidx]=v;
				this->tsec[cidx]=60*(sec /60);

			}else if(cidx==0 && start!=0){
	           /*如果是第一根k线，
			      1.是否是最新的数据
				  2.取max值。
			   */
				if(start==(sec/60)*60) {
					/*如果是同一分钟*/
				    this->data[cidx]=v;
				}else if((start+1)==now){
					/*如果是新的一分钟*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}else if(1/*是同一时间段*/) {
					/*有可能要考虑补全间隙*/

				}else {
					/*不再考虑补全间隙*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}

			} else if(cidx!=0) {
			   /*当cidx为非零值得时候，这个cidx必然是已经有有实际报价，
			     或者timer定时器已经发生过!
			   */
				if(start==(sec/60)*60) {
					/*如果是同一分钟*/
				    this->data[cidx]=v;
				}else if((start+1)==now){
					/*如果是新的一分钟*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}else if(1/*是同一时间段*/) {
					/*有可能要考虑补全间隙*/

				}else {
					/*不再考虑补全间隙*/
					this->cidx++;
					cidx=this->cidx;
					this->tsec[cidx]=now;
					this->data[cidx]=v;
				}
			}
			this->csec=sec;
			this->cmsec=msec;
			return 0;
	};
	int update_me(float v, int sec, int msec,kdata_type type){
	again:
		boost::unique_lock<boost::timed_mutex> lk(this->mutex,boost::chrono::milliseconds(1));
		if(lk) {
			switch(type) {
			case HIGH:
				this->update_meh(v,sec,msec);
				break;
			case LOW:
				this->update_mel(v,sec,msec);
				break;
			case OPEN:
				this->update_meo(v,sec,msec);
				break;
			case CLOSE:
				this->update_mec(v,sec,msec);
				break;
			default:
				break;
			}
		}else {
			/*warnring*/
			goto again;
		}
		return 0;
	}

	int callback(float v,int sec, int msec){
		int ret;
		again:
		boost::unique_lock<boost::timed_mutex> lk(this->mutex,boost::chrono::milliseconds(1));
		if(lk) {
		}else {
			/*warnring*/
			ret=this->cb(v,sec,msec);
			goto again;
		}
	}
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
				/*如果是同一天
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
				/*如果不是同一天
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
	    /*9点到-10:15,10:30-11:30,1:30-3:00,21:00-2:30
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
			/*时间差8小时
			*/
			return 0;
		}else if(e1 > b1+28800){
			/*时间差8小时
			*/
			return 0;
		}else {


		}
	};
	
	int fix(){
		/*如果报单延时，则更新最高最低价。量不动。*/
	};
	/*need a mutex*/
};
#endif