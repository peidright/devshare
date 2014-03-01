#ifndef QUOTE_IO_H_
#define QUOTE_IO_H_
#include <map>
#include <deque>
#include <string>

using namespace std;
typedef struct tdata_s {
	/*Ϊ�������ϣ���ʱֱ��д���ֶΡ��Ժ�Ϊ��Ч�ʣ��ٿ������
	this->exe_cmd("create table instrument(day integer, seconds integer, \
				  closeprice integer,openprice  interger,uprice integer,lprice integer,\
				  highprice integer,lowprice integer,lastprice integer,\
				  avgprice integer,vol integer,bid1 integer,ask1 integer",rows);
    */
	int sec;
	int msec;
	int close;
	int open;
	int uprice;
	int lprice;
	int highprice;
	int lowprice;
	int lastprice;
	int avgprice;
	int vol;
	int bid1;
	int ask1;
	int bid2;
	int ask2;
	int bid3;
	int ask3;
	int bid4;
	int ask4;
	int bid5;
	int ask5;
}tdata_t;

typedef struct tdata_io_s {
	int lsec;
	int lmsec;
	deque<tdata_t*> tdataq;
}tdata_io_t;

typedef struct kdata_s {
	/*Ϊ�������ϣ���ʱֱ��д���ֶΡ��Ժ�Ϊ��Ч�ʣ��ٿ������*/
	int sec;
	int msec;
	int close;
	int open;
	int uprice;
	int lprice;
	int highprice;
	int lowprice;
	int lastprice;
	int avgprice;
	int vol;
}kdata_t;
typedef struct kdata_io_s {
	int lsec;
	int lmsec;
	deque<kdata_t*> kdataq;
}kdata_io_t;



typedef struct quote_io_s {
	/*string ��������
	  cu401    ��ͭ��1401��Լ
	  cu4015.  ��ʾͭ��1401 ��5���Ӻ�Լ.
	*/
	map<string, kdata_io_t> kdata_io;
	map<string, tdata_io_t> tdata_io;
}quote_io_t;

#endif