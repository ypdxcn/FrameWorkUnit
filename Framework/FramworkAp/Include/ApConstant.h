#ifndef _AP_CONSTANT_H_
#define _AP_CONSTANT_H_

#include <string>
using namespace std;

#define GESS_FLD_SEPERATOR  "#"  //�ֶηָ�
#define GESS_VAL_SEPERATOR  "="  //��ֵ�ָ�
#define GESS_NODE_TYPE  "NodeType"     //�������KeyΨһ��ʶ
#define GESS_NODE_ID  "NodeID"     //�������KeyΨһ��ʶ
#define GESS_API_NAME  "ApiName"   //�����������
#define GESS_DATA_TYPE "DataType"  //�������һ���ṹ����
#define GESS_ROOT_ID  "RootID"     //�������KeyΨһ��ʶ

#define DEFAULT_IDLE_TIMEOUT						16
#define DEFAULT_HELLO_RESEND_INTERVAL				6
#define DEFAULT_HELLO_RESEND_COUNT					8


namespace ApConst 
{

	//ArrayListMsg/HashtableMsg	
	//֧�ֵ������
	const int SEPARATOR_MAX_LEVEL = 4;							
	//�༶�ָ���
	const string SEPARATOR_RECORD[SEPARATOR_MAX_LEVEL] = { "��", "��", "��","��"};
    

}
#endif