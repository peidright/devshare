#include "config.h"

using namespace std;
TThostFtdcBrokerIDType appId;		// Ӧ�õ�Ԫ
TThostFtdcUserIDType userId;		// Ͷ���ߴ���

extern int requestId; 
extern CSem sem;

// �Ự����
int	 frontId;	//ǰ�ñ��
int	 sessionId;	//�Ự���
char orderRef[13];


//Trader *trader= Trader(string username,string password,string brokerid,string trade_addr);
	
string g_username="00000071";
string g_password="123456";
string g_brokerid="1017";
string g_trade_addr="tcp://ctpmn1-front1.citicsf.com:51205";
string g_quote_addr="tcp://ctpmn1-front1.citicsf.com:51213";
