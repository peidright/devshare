#ifndef CONFIG_H_
#define CONFIG_H_


#include <iostream>
#include <vector>
//#include <sys/sem.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CtpTrade.h"
#include "ThostFtdcTraderApi.h"
#include "CtpTraderSpi.h"
#include "CSem.h"


using namespace std;
extern TThostFtdcBrokerIDType appId;		// Ӧ�õ�Ԫ
extern TThostFtdcUserIDType userId;		// Ͷ���ߴ���

extern int requestId; 
extern CSem sem;
#define PROD_INFO "Q7 7994"

// �Ự����
extern int	 frontId;	//ǰ�ñ��
extern int	 sessionId;	//�Ự���
extern char orderRef[13];

#define TRADE_DIR "./tlog"
#define QUOTE_DIR "./qlog"

typedef enum LoginStatus {
	SUCESS=0,
	LOGIN=1,
	FAIL=2
}LoginStatus;




extern string g_username;
extern string g_password;
extern string g_brokerid;
extern string g_trade_addr;
extern string g_quote_addr;

#endif