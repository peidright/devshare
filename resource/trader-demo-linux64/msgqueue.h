#ifndef MSGQUEUE1_H_
#define MSGQUEUE1_H_
#include <iostream>
#include <vector>
//#include <sys/sem.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include "CtpTrade.h"
#include "ThostFtdcTraderApi.h"

//#include "CtpQuote.h"
#include "../boosthelp.h"


enum msgtype {
	TSTOP,
	TSTART,
	TOnFrontConnected=1,
	TReqUserLogin,
	TOnRspUserLogin,

	TReqSettlementInfoConfirm,
	TOnRspSettlementInfoConfirm,
	
	TReqQryInstrument,
	TOnRspQryInstrument,
	
	TReqQryTradingAccount,
	TOnRspQryTradingAccount,

	TReqQryInvestorPosition,
	TOnRspQryInvestorPosition,

	TReqOrderInsert,
	TOnRspOrderInsert,

	TReqOrderAction,
	TOnRspOrderAction,


	TOnRtnOrder,
	TOnFrontDisconnected,
	TOnHeartBeatWarning,
	TOnRspError,

	TRADE_QUOTE=64,
	QSTOP,
	QSTART,
	QOnFrontConnected,
	QOnFrontDisconnected,
	QOnHeartBeatWarning,
	QOnRspError,
	QReqSubscribeMarketData,
    QOnRspSubMarketData,
	QOnRspUnSubMarketData,
	
	QReqUserLogin,
	QOnRspUserLogin,
	QOnRspUserLogout,
	QOnRtnDepthMarketData,
};


typedef struct  msg_s{
	msgtype type;
	int     len;
	void    *data;
}msg_t;

/*
class msg_t {
public:
	msgtype type;
	int     len;
	void    *data;
};*/

typedef struct  {
}TOnFrontConnected_t;

typedef struct {
	struct CThostFtdcRspUserLoginField pRspUserLogin;
	struct CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}TOnRspUserLogin_t;

typedef struct {
	CThostFtdcSettlementInfoConfirmField  pSettlementInfoConfirm;
	struct CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}TOnRspSettlementInfoConfirm_t;

typedef struct {
	CThostFtdcInstrumentField pInstrument;
    CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}TOnRspQryInstrument_t;

typedef struct {
	CThostFtdcTradingAccountField pTradingAccount;
	CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}TOnRspQryTradingAccount_t;

typedef struct {
	CThostFtdcInvestorPositionField pInvestorPosition;
	CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}TOnRspQryInvestorPosition_t;

typedef struct {
    CThostFtdcInputOrderField pInputOrder;
	CThostFtdcRspInfoField *pRspInfo;
	int nRequestID;
	bool bIsLast;
}TOnRspOrderInsert_t;

typedef struct {
	  CThostFtdcInputOrderActionField pInputOrderAction;
      CThostFtdcRspInfoField pRspInfo;
	  int nRequestID;
	  bool bIsLast;
}TOnRspOrderAction_t;

typedef struct {
	  CThostFtdcOrderField  pOrder;
}TOnRtnOrder_t;

typedef struct {
	CThostFtdcTradeField pTrade;
}TOnRtnTrade_t;

typedef struct {
	int nReason;
}TOnFrontDisconnected_t;
	

typedef struct {
	int nTimeLapse;
}TOnHeartBeatWarning_t;

typedef struct {
	CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}TOnRspError_t;

typedef struct {
}QOnFrontConnected_t;

typedef struct {
	int nReason;
}QOnFrontDisconnected_t;
typedef struct {
	int nTimeLapse;
}QOnHeartBeatWarning_t;

typedef struct {
	CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}QOnRspError_t;

typedef struct {
	CThostFtdcSpecificInstrumentField pSpecificInstrument;
	CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}QOnRspSubMarketData_t;

typedef struct {
	CThostFtdcSpecificInstrumentField pSpecificInstrument;
	CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}QOnRspUnSubMarketData_t;

typedef struct {
	CThostFtdcRspUserLoginField  pRspUserLogin;
	CThostFtdcRspInfoField       pRspInfo;
	int nRequestID;
	bool bIsLast;
}QOnRspUserLogin_t;

typedef struct {
	CThostFtdcUserLogoutField pUserLogout;
	CThostFtdcRspInfoField pRspInfo;
	int nRequestID;
	bool bIsLast;
}QOnRspUserLogout_t;

typedef struct {
	CThostFtdcDepthMarketDataField pDepthMarketData;
}QOnRtnDepthMarketData_t;


#endif