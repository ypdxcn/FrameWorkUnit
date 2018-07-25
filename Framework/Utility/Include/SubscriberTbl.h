#ifndef _SUBSCRIPB_INC_H
#define _SUBSCRIPB_INC_H
#include "Gess.h"



typedef struct SubscriberContext
{
	unsigned int nodeId;
	char subType;		/*0--ֻ�����оٲ���,1-��ָ���б���,*--����������Ϣ */
	vector<unsigned int> vecInstId;  //��ԼID�б�s
}SUB_CONTEXT, *PSUB_CONTEXT;

using namespace std;

///��㶩�Ĺ���
class CSubscriberTbl
{

public:

	CSubscriberTbl(void);
	~CSubscriberTbl(void);
public:
	

	///ע�������û��Ķ������� 0-�ɹ���1-ʧ��
	int AddSubscripItem(const unsigned int & subscriberID,char & subType,vector<unsigned int>& vecInstId );

	///�����û�ȡ����¼���� 0-�ɹ���1-ʧ��
	int CancelSubscriber(const unsigned int & subscriberID);

	///��ȡ��ǰ���е�¼�û��ļ���
	map<unsigned int,SUB_CONTEXT> GetSubscriberMap();

	///�ͷų�ԱԪ��
	void Finish();
private:
	map<unsigned int,SUB_CONTEXT> m_mapSubscriber;
	CGessMutex m_mutexTbl;
};
#endif
