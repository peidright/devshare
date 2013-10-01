#include "CtpQuote.h"
#include "config.h"
#include <string>
#include <assert.h>
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
	/*
	CThostFtdcReqUserLoginField f;
	memset(&f, 0, sizeof(f));
	strcpy(f.BrokerID, "1017");
	strcpy(f.UserID, "00000071");
	strcpy(f.Password, "123456");
	md->ReqUserLogin(&f, ++nReq);
	*/
	cerr <<"md connected"<<endl;
		this->ReqUserLogin((char*)this->trader->brokerid.c_str(),
		(char*)this->trader->username.c_str(),
		(char*)this->trader->password.c_str()
		);
}
void CtpQuoteSpi::ReqUserLogin(TThostFtdcBrokerIDType	vAppId,
	        TThostFtdcUserIDType	vUserId,	TThostFtdcPasswordType	vPasswd)
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, vAppId); strcpy(appId, vAppId); 
	strcpy(req.UserID, vUserId);  strcpy(userId, vUserId); 
	strcpy(req.Password, vPasswd);
	this->login_status=LOGIN;
	int ret = this->api->ReqUserLogin(&req, ++this->requestId);	
	if (ret) {
		this->login_status=FAIL;
	}
	cerr<<" md ���� | ���͵�¼..."<<((ret == 0) ? "�ɹ�" :"ʧ��") << endl;
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
	/**/
	int count;
	
	count=g_product_list.size();
	char ** ppInst = (char**)new char *[MAX_INSTS];
	//char insts[MAX_INSTS][32];
	//ppInst=(char**)insts;
	//memset(insts,0x0, sizeof(insts));
	cerr<<"md login sucess: "<<count<<endl;
	//g_product_list
	assert(count <MAX_INSTS);
	for(int i=0;i<MAX_INSTS;i++) {
		ppInst[i]=(char*)0;
	}
	for(int i=0;i<count;i++) {
		    ppInst[i]=new char[32];
			strcpy(ppInst[i], g_product_list[i].c_str());
			printf("insts is %s\n",ppInst[i]);
	}
	//return;
	//char inst[32];
	//strcpy(inst, "cu1401");
	//char*ppInst[1];

	//ppInst[0] = inst;
	this->api->SubscribeMarketData(ppInst, count);
	cout<<"md subscribeMarketDate cu1401"<<endl;
	delete [] ppInst;
}

void CtpQuoteSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void dump_depthmarketdata(CThostFtdcDepthMarketDataField *dmd)
{
	cout<<"ҵ������         ActionDay :     "<<dmd->ActionDay<<endl;
	cout<<"����������       ExchangeID:     "<<dmd->ExchangeID<<endl;
	cout<<"����ʱ��         UpdateTime:     "<<dmd->UpdateTime<<endl;
	cout<<"����޸ĺ��� UpdateMillisec:     "<<dmd->UpdateMillisec<<endl;
	cout<<"��ԼID         InstrumentID:     "<<dmd->InstrumentID<<endl;
	cout<<"������           TradingDay:     "<<dmd->TradingDay<<endl;
	cout<<"������           ClosePrice:     "<<dmd->ClosePrice<<endl;
	cout<<"������        PreClosePrice:     "<<dmd->PreClosePrice<<endl;
	cout<<"����            OpenPrice:     "<<dmd->OpenPrice<<endl;
	cout<<"��߼�         HighestPrice:     "<<dmd->HighestPrice<<endl;
	cout<<"��ͼ�          LowestPrice:     "<<dmd->LowestPrice<<endl;
	cout<<"���ν����  SettlementPrice:     "<<dmd->SettlementPrice<<endl;
	cout<<"��������  PreSettlementPrice:  "<<dmd->PreSettlementPrice<<endl;
	cout<<"��ͣ���    UpperLimitPrice:     "<<dmd->UpperLimitPrice<<endl;
	cout<<"��ͣ���    LowerLimitPrice:     "<<dmd->LowerLimitPrice<<endl;
	cout<<"����ʵ��           PreDelta:     "<<dmd->PreDelta<<endl;
	cout<<"����ʵ��          CurrDelta:     "<<dmd->CurrDelta<<endl;
	cout<<"����                 Volume:     "<<dmd->Volume<<endl;
	cout<<"�ɽ����           Turnover:     "<<dmd->Turnover<<endl;
	cout<<"�ֲ���         OpenInterest:     "<<dmd->OpenInterest<<endl;
	cout<<"��1               BidPrice1:     "<<dmd->BidPrice1<<endl;
	/*
	cout<<"��2               BidPrice2:     "<<dmd->BidPrice2<<endl;
	cout<<"��3               BidPrice3:     "<<dmd->BidPrice3<<endl;
	cout<<"��4               BidPrice4:     "<<dmd->BidPrice4<<endl;
	cout<<"��5               BidPrice5:     "<<dmd->BidPrice5<<endl;
	*/
	cout<<"��1               AskPrice1:     "<<dmd->AskPrice1<<endl;
	/*
	cout<<"��2               AskPrice1:     "<<dmd->AskPrice2<<endl;
	cout<<"��3               AskPrice1:     "<<dmd->AskPrice3<<endl;
	cout<<"��4               AskPrice1:     "<<dmd->AskPrice4<<endl;
	cout<<"��5               AskPrice1:     "<<dmd->AskPrice5<<endl;
	*/
	cout<<"����           AveragePrice:     "<<dmd->AveragePrice<<endl;
}

void CtpQuoteSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	cout<<"md subscribe market cu1401 successed"<<endl;
	dump_depthmarketdata(pDepthMarketData);
}
