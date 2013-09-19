#include "CtpQuote.h"
#include <string>
using namespace std;
 CtpQuote::CtpQuote(string username,string password, string quote_addr)
{
	/*
	this->api = CThostFtdcMdApi::CreateFtdcMdApi("./qlog");
	md->RegisterSpi((CThostFtdcMdSpi*)q);
	md->RegisterFront("tcp://ctpmn1-front1.citicsf.com:51213");
	md->Init();
	*/
}
/*
void CtpQuoteApi::Init()
{
}
int CtpQuoteApi::Join()
{
	 return 0;
}

void CtpQuoteApi::RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo)
{
}
void CtpQuoteApi::RegisterFront(char *pszFrontAddress)
{
}
void CtpQuoteApi::RegisterNameServer(char *pszNsAddress)
{
}
void CtpQuoteApi::RegisterSpi(CThostFtdcMdSpi *pSpi)
{
}


void CtpQuoteApi::Release()
{
}
int CtpQuoteApi::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID)
{
	return 0;
}
int CtpQuoteApi::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	return 0;
}
int CtpQuoteApi::SubscribeMarketData(char *ppInstrumentID[], int nCount)
{
	return 0;
}

int CtpQuoteApi::UnSubscribeMarketData(char *ppInstrumentID[], int nCount)
{
	return 0;
}
 CtpQuoteApi::~CtpQuoteApi()
{
}
 */

void CtpQuoteSpi::OnFrontConnected()
{
}
void CtpQuoteSpi::OnFrontDisconnected(int nReason)
{
}
void CtpQuoteSpi::OnHeartBeatWarning(int nTimeLapse)
{
}
void CtpQuoteSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
void CtpQuoteSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
void CtpQuoteSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
void CtpQuoteSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
void CtpQuoteSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
void CtpQuoteSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{

}
