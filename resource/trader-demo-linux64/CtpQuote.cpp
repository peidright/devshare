#include "CtpQuote.h"
#include "msgqueue.h"
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
	msg_t *msg=new(msg_t);
	msg->len=0;
	msg->data=new(QOnFrontConnected_t);
	msg->type=QOnFrontConnected;

	/**/
	printf("OnFront Connect DEBUG\n");
    this->ctpquoter->post_msg(msg);

}
int CtpQuoteSpi::ReqUserLogin(TThostFtdcBrokerIDType	vAppId,
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
	cerr<<" md 请求 | 发送登录..."<<((ret == 0) ? "成功" :"失败") << endl;
	return ret;
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
	cout<<pSpecificInstrument->InstrumentID<<std::endl;
	cout<<pRspInfo->ErrorID<<pRspInfo->ErrorMsg<<std::endl;
	msg_t *msg=new(msg_t);
	QOnRspSubMarketData_t *data=new(QOnRspSubMarketData_t);
	msg->len=sizeof(QOnRspSubMarketData_t);
	msg->data=(void*)data;
	msg->type=QOnRspSubMarketData;
    this->ctpquoter->post_msg(msg);
}
void CtpQuoteSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout<<pSpecificInstrument->InstrumentID<<std::endl;
	cout<<pRspInfo->ErrorID<<pRspInfo->ErrorMsg<<std::endl;
	msg_t *msg=new(msg_t);
	QOnRspUnSubMarketData_t *data=new(QOnRspUnSubMarketData_t);
	msg->len=sizeof(QOnRspUnSubMarketData_t);
	msg->data=(void*)data;
	msg->type=QOnRspUnSubMarketData;
    this->ctpquoter->post_msg(msg);
}

void CtpQuoteSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	/**/
	cout<<pRspInfo->ErrorID<<pRspInfo->ErrorMsg<<std::endl;
	msg_t *msg=new(msg_t);
	QOnRspUserLogin_t *data=new(QOnRspUserLogin_t);
	data->bIsLast=bIsLast;
	data->nRequestID=nRequestID;
	memcpy(&data->pRspInfo,pRspInfo,sizeof(pRspInfo));
	memcpy(&data->pRspUserLogin,pRspUserLogin,sizeof(pRspUserLogin));
	msg->len=sizeof(QOnRspUserLogin_t);
	msg->data=(void*)data;
	msg->type=QOnRspUserLogin;
	this->ctpquoter->post_msg(msg);

}

void CtpQuoteSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void dump_depthmarketdata(CThostFtdcDepthMarketDataField *dmd)
{
	//
	cout<<"业务日期         ActionDay :     "<<dmd->ActionDay<<endl;
	cout<<"交易所代码       ExchangeID:     "<<dmd->ExchangeID<<endl;
	cout<<"更新时间         UpdateTime:     "<<dmd->UpdateTime<<endl;
	cout<<"最后修改毫秒 UpdateMillisec:     "<<dmd->UpdateMillisec<<endl;
	cout<<"合约ID         InstrumentID:     "<<dmd->InstrumentID<<endl;
	cout<<"交易日           TradingDay:     "<<dmd->TradingDay<<endl;
	cout<<"今收盘           ClosePrice:     "<<dmd->ClosePrice<<endl;
	cout<<"昨收盘        PreClosePrice:     "<<dmd->PreClosePrice<<endl;
	cout<<"今开盘            OpenPrice:     "<<dmd->OpenPrice<<endl;
	cout<<"最高价         HighestPrice:     "<<dmd->HighestPrice<<endl;
	cout<<"最低价          LowestPrice:     "<<dmd->LowestPrice<<endl;
	cout<<"本次结算价  SettlementPrice:     "<<dmd->SettlementPrice<<endl;
	cout<<"上次结算价  PreSettlementPrice:  "<<dmd->PreSettlementPrice<<endl;
	cout<<"涨停板价    UpperLimitPrice:     "<<dmd->UpperLimitPrice<<endl;
	cout<<"跌停板价    LowerLimitPrice:     "<<dmd->LowerLimitPrice<<endl;
	cout<<"昨虚实度           PreDelta:     "<<dmd->PreDelta<<endl;
	cout<<"今虚实度          CurrDelta:     "<<dmd->CurrDelta<<endl;
	cout<<"数量                 Volume:     "<<dmd->Volume<<endl;
	cout<<"成交金额           Turnover:     "<<dmd->Turnover<<endl;
	cout<<"持仓量         OpenInterest:     "<<dmd->OpenInterest<<endl;
	cout<<"买1               BidPrice1:     "<<dmd->BidPrice1<<endl;
	cout<<"最新价            LastPrice:     "<<dmd->LastPrice<<endl;
	/*
	cout<<"买2               BidPrice2:     "<<dmd->BidPrice2<<endl;
	cout<<"买3               BidPrice3:     "<<dmd->BidPrice3<<endl;
	cout<<"买4               BidPrice4:     "<<dmd->BidPrice4<<endl;
	cout<<"买5               BidPrice5:     "<<dmd->BidPrice5<<endl;
	*/
	cout<<"卖1               AskPrice1:     "<<dmd->AskPrice1<<endl;
	/*
	cout<<"卖2               AskPrice1:     "<<dmd->AskPrice2<<endl;
	cout<<"卖3               AskPrice1:     "<<dmd->AskPrice3<<endl;
	cout<<"卖4               AskPrice1:     "<<dmd->AskPrice4<<endl;
	cout<<"卖5               AskPrice1:     "<<dmd->AskPrice5<<endl;
	*/
	cout<<"均价           AveragePrice:     "<<dmd->AveragePrice<<endl;
}

void CtpQuoteSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	cout<<"md subscribe market cu1401 successed"<<endl;
	dump_depthmarketdata(pDepthMarketData);
}
