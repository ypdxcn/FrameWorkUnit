//Э������ ���������½ӿڵķ��������:
//��ط��������ؿͻ���֮���F1�ӿ�
#ifndef _PROCESS_INTERFACE_F1S_H
#define _PROCESS_INTERFACE_F1S_H

#include "CommApRisk.h"
// #include "ProtocolProcess.h"
#include "TradePacket.h"
#include "ProcessInterfaceNm.h"
using namespace std;

class COMMAPRISK_CLASS CProcessInterfaceF1S : public CProcessInterfaceSvrNm
{
public:
	CProcessInterfaceF1S(void);
	~CProcessInterfaceF1S(void);

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

	virtual int OnAccept();					// ������˽��յ����Ӻ�ص�
	virtual void OnClose();					// �Ͽ�����ʱ����
	int GetNmKey(string& sKey);
protected:
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	virtual int HandleTimeout(unsigned long& ulTmSpan);

	//virtual bool IsLogin() {return m_blIsLogin;} //��¼״̬

	//Э�鶨��Ľ�������
    //virtual int OnLogin(CTradePacket & GessPacket);
private:
	int SendHello();
	int OnHello(CTradePacket & GessPacket);

	static GessPktInfo m_GessPktInfo;
	static bool	m_blGessPktInfoInited;
	//bool		m_blIsLogin;			//��¼״̬
	
	CConfig *	m_pCfg;
	//std::deque<CTradePacket> m_qSend;
	CGessMutex m_csF1S;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};
#endif
