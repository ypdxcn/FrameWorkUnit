//Э������ ���������½ӿڵķ��������:
//
#ifndef _PROCESS_INTERFACE_ZS_H
#define _PROCESS_INTERFACE_ZS_H

#include "CommApSampler.h"
#include "ProtocolProcess.h"
#include "SamplerPacket.h"
#include "ApConstant.h"

using namespace std;

class COMMAPSAMPLER_CLASS CProcessInterfaceZS : public CTcpAppProcessServer
{
public:
	CProcessInterfaceZS(void);
	~CProcessInterfaceZS(void);

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
	int OnSend(int nSize);

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
	int OnHello(CSamplerPacket & GessPacket);

	static GessPktInfo m_GessPktInfo;
	static bool	m_blGessPktInfoInited;
	//bool		m_blIsLogin;			//��¼״̬
	
	CConfig *	m_pCfg;
	CGessMutex m_csZS;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};
#endif
