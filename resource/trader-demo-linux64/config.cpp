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
