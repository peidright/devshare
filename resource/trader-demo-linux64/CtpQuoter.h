#ifndef CTPQUOTER_H_
#define CTPQUOTER_H_

#include "CtpQuote.h"
#include "CtpTrade.h"
#include "msgqueue.h"
class CtpTradeSpi;
class CtpQuoter{
public:
	//CtpTradeSpi * trade_spi;
	//CThostFtdcTraderApi* trade_api;
	CtpQuoteApi *quote_spi;
    CThostFtdcMdApi *quote_api;
	Quoter *quoter;
	deque<msg_t> mqueue;
	boost::interprocess::interprocess_semaphore qsem;
    boost::timed_mutex qmutex;
	
	CtpQuoter(Quoter *quoter);
	void start();
	void post_msg(msg_t *msg);
	void quote_stm(msg_t &msg);
};



#endif