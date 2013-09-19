#include <iostream>
#include "CtpTraderSpi.h"
#include "CSem.h"
#include <algorithm>
#include <vector>
using namespace std;

//请求编号
int requestId=0;

// 前置地址
char tradeFront[]="tcp://asp-sim2-front1.financial-trading-platform.com:26205";

CSem sem(0);

//vector<struct CThostFtdcOrderField *> orderList;
//vector<struct CThostFtdcTradeField *> tradeList;
int main(int argc, char * argv[]){
//int main(){
	
	CThostFtdcTraderApi* pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./tlog");
	

	//CtpTraderSpi* pUserSpi = new CtpTraderSpi(pUserApi);
	//pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	//pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// 注册公有流
	//pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);			  // 注册私有流
	//pUserApi->RegisterFront(tradeFront);							// 注册交易前置地址
	//pUserApi->Init();
	//todo
	
	pUserApi->Join();
    //pUserapi->
	//pUserApi->Release();
	return 0;
}
