//Э������ ���������½ӿڵĿͻ�������:
//��ط��������ط�����֮���H1�ӿ�
//���̻����ط�������H1�ӿ�
//������Դ���������ط�����֮���H1�ӿ�
#ifndef _PROCESS_INTERFACE_H1C_H
#define _PROCESS_INTERFACE_H1C_H

#include "CommAp.h"
#include "ProcessInterfaceNm.h"
#include "TradePacket.h"

using namespace std;

class COMMAP_CLASS CProcessInterfaceH1C : public CProcessInterfaceClnNm
{
public:
	CProcessInterfaceH1C(void);
	~CProcessInterfaceH1C(void);

	typedef struct tagGessPktInfo
	{
		unsigned long ulIdleInterval;		//����ʱ��������Hello���ʱ�䣬Ҳ����·�ϵ������ʱ��
		unsigned long ulIntervalReSend;		//��Ӧ����ؼ����
		unsigned long ulHelloReSend;		//��Ӧ����ط������Ĵ���
		int blNeedLogin;					//�Ƿ���Ҫ��¼

		std::string	node_type;
		std::string	node_id;
		std::string	node_name;
		std::string	host_id;
		std::string	sUserName;				//���ͻ�ʱ�����˵�¼�û���
		std::string	sPassword;				//���ͻ�ʱ�����˵�¼����
	} GessPktInfo,*PGessPktInfo;

	int Init(CConfig * pCfg);

	virtual int OnConnect();		// ���ͻ������ӳɹ���ص�
	virtual void OnClose();			// �Ͽ�����ʱ����
	int GetNmKey(string& sKey);
protected:
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	int HandleTimeout(unsigned long& ulTmSpan);

	//virtual bool IsLogin() {return m_blIsLogin;} //��¼״̬
private:
	//Э�鶨��Ľ�������
	int SendHello();
	int OnHello(CTradePacket& pkt);
	int SendNodeInfo();

	static GessPktInfo m_GessPktInfo;
	static int	m_blGessPktInfoInited;
	//bool		m_blIsLogin;			//��¼״̬
	
	CConfig *	m_pCfg;
	//std::deque<CTradePacket> m_qSend;
	CGessMutex m_csH1C;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};
#endif