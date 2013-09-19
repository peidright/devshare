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
