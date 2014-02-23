#include <iostream>
#include "CtpTraderSpi.h"
#include "CSem.h"
#include <algorithm>
#include <vector>
#include "sqlite3.h"
#include "../CtpTrader.h"
#include "../CtpQuoter.h"
#include "../config.h"
#include "../trader.h"
#include "../datalocal.h"
#include "../ntp.h"
#include "../luajit_support.h"
#include <boost/regex.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "../boosthelp.h"
using namespace std;

//请求编号
int requestId=0;

// 前置地址
char tradeFront[]="tcp://asp-sim2-front1.financial-trading-platform.com:26205";

CSem sem(0);

//vector<struct CThostFtdcOrderField *> orderList;
//vector<struct CThostFtdcTradeField *> tradeList;
extern void test1();
int main(int argc, char * argv[]){
	test1();
	getchar();
	std::string line;
    /*
	boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

    while (std::cin)
    {
		break;
        std::getline(std::cin, line);
        boost::smatch matches;
        if (boost::regex_match(line, matches, pat))
            std::cout << matches[2] << std::endl;
    }*/

//int main(){
	//ntpdate();
	//exit(0);
	//CThostFtdcTraderApi* pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./tlog");
	//getchar();
	//return 0;
	//datalocal *dl=new datalocal();
	//luajit_demo();
	getchar();
	//return 0;
	cout<<"ddd1"<<endl;
	datalocal *dl=new datalocal();
	vector<map<string,string>> rows;
	cout<<"ddd2"<<endl;
	dl->exe_cmd("select name from sqlite_master where type='table'",rows);
	getchar();
	
	dl->get_product_list(g_product_list);
		for(int i=0;i<g_product_list.size();i++) {
		printf("%s\n",g_product_list[i].c_str());
	}
	
	//getchar();

	//Trader *trader=new Trader(g_username,g_password,g_brokerid,g_trade_addr);
	//CtpTrader *ctp_trader=new CtpTrader(trader);

	Quoter *quoter=new Quoter(g_username,g_password,g_brokerid,g_quote_addr);
	CtpQuoter *ctp_quoter=new CtpQuoter(quoter);

	getchar();
	/*
	api = CThostFtdcTraderApi::CreateFtdcTraderApi("./tlog");
	api->RegisterSpi((CThostFtdcTraderSpi*)t);
	api->RegisterFront("tcp://ctpmn1-front1.citicsf.com:51205");
	api->Init();
    getchar();
	*/

	//CtpTraderSpi* pUserSpi = new CtpTraderSpi(pUserApi);
	//pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	//pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// 注册公有流
	//pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);			  // 注册私有流
	//pUserApi->RegisterFront(tradeFront);							// 注册交易前置地址
	//pUserApi->Init();
	//todo
	
	/*
	  CThostFtdcTraderApi* pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./tlog");
	  pUserApi->Join();
	*/
    //pUserapi->
	//pUserApi->Release();
	return 0;
}
