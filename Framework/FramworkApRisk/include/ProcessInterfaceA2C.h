
//Э������ ���������½ӿڿͻ�������:
//��ط������뽻�׷�����֮���A2�ӿ�
#ifndef _PROCESS_INTERFACE_A2C_H
#define _PROCESS_INTERFACE_A2C_H

#include "CommApRisk.h"
// #include "ProtocolProcess.h"
#include "TradePacket.h"
#include "ProcessInterfaceNm.h"
using namespace std;

class COMMAPRISK_CLASS CProcessInterfaceA2C :  public CProcessInterfaceClnNm
{
public:
	CProcessInterfaceA2C(void);
	~CProcessInterfaceA2C(void);

		typedef struct tagGessPktInfo
	{
		unsigned long ulIdleInterval;		//����ʱ��������Hello���ʱ�䣬Ҳ����·�ϵ������ʱ��
		unsigned long ulIntervalReSend;		//��Ӧ����ؼ����
		unsigned long ulHelloReSend;		//��Ӧ����ط������Ĵ���
		bool blNeedLogin;					//�Ƿ���Ҫ��¼

		std::string	node_type;
		std::string	node_id;
		std::string	node_name;
		std::string	host_id;
		std::string	sUserName;				//���ͻ�ʱ�����˵�¼�û���
		std::string	sPassword;				//���ͻ�ʱ�����˵�¼����
	} GessPktInfo,*PGessPktInfo;

	int Init(CConfig * pCfg);
	int SendPacket(CPacket & packet);
// 	int OnSend(int nSize);

	virtual int OnConnect();		// ���ͻ������ӳɹ���ص�
	virtual void OnClose();	        // �Ͽ�����ʱ����
	int GetNmKey(string& sKey);
protected:
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	virtual int HandleTimeout(unsigned long& ulTmSpan);
private:
	//Э�鶨��Ľ�������
	int SendHello();
	int OnHello(CTradePacket& GessPacket);
private:
	static GessPktInfo m_GessPktInfo;
	static bool	m_blGessPktInfoInited;
	
	CConfig *	m_pCfg;
	//std::deque<CTradePacket> m_qSend;
	CGessMutex m_csA2C;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};
#endif
