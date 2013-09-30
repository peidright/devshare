#include "config.h"

using namespace std;
TThostFtdcBrokerIDType appId;		// 应用单元
TThostFtdcUserIDType userId;		// 投资者代码

extern int requestId; 
extern CSem sem;

// 会话参数
int	 frontId;	//前置编号
int	 sessionId;	//会话编号
char orderRef[13];


//Trader *trader= Trader(string username,string password,string brokerid,string trade_addr);
	
string g_username="00000071";
string g_password="123456";
string g_brokerid="1017";
string g_trade_addr="tcp://ctpmn1-front1.citicsf.com:51205";
string g_quote_addr="tcp://ctpmn1-front1.citicsf.com:51213";
