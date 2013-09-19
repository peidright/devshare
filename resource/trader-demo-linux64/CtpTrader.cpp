#include "CtpTrader.h"
#include "Trader.h"

CtpTrader::CtpTrader(Trader *trader)
{
	CThostFtdcTraderApi* trade_api = CThostFtdcTraderApi::CreateFtdcTraderApi(TRADE_DIR);
	this->trade_api=trade_api;
	CtpTradeSpi* trade_spi = new CtpTradeSpi(trade_api,trader);
	this->trade_spi = trade_spi;

	trade_api->RegisterSpi((CThostFtdcTraderSpi*)trade_spi);			// ע���¼���
	trade_api->SubscribePublicTopic(THOST_TERT_RESTART);					// ע�ṫ����
	trade_api->SubscribePrivateTopic(THOST_TERT_RESTART);			  // ע��˽����
	trade_api->RegisterFront((char*)trader->trade_addr.c_str());	// ע�ύ��ǰ�õ�ַ
	

	
	CThostFtdcMdApi *quote_api = CThostFtdcMdApi::CreateFtdcMdApi(QUOTE_DIR);
	CtpQuoteSpi *quote_spi = new CtpQuoteSpi(quote_api,trader);
	quote_api->RegisterSpi((CThostFtdcMdSpi*)quote_spi);
	quote_api->RegisterFront((char*)trader->trade_addr.c_str());
	
	/*
	md->Init();
	cout<<"market init"<<endl;
	pUserApi->Init();
	//todo
	pUserApi->Join();
	*/
}