//Э������ �����ڷ�ط������뽻�׷�������A1�ӿ�
#ifndef _PROCESS_INTERFACE_A1C_H
#define _PROCESS_INTERFACE_A1C_H

#include "CommApRisk.h"
// #include "ProtocolProcess.h"
#include "BroadcastPacket.h"
#include "ProcessInterfaceNm.h"
using namespace std;

class COMMAPRISK_CLASS CProcessInterfaceA1C : public CProcessInterfaceClnNm
{
public:
	CProcessInterfaceA1C(void);
	~CProcessInterfaceA1C(void);

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

		std::string	term_type;	//
		std::string	user_key;
		std::string	user_type;
		std::string	user_id;
		std::string	user_pwd;
		std::string	branch_id;
		std::string	again_flag;
	} GessPktInfo,*PGessPktInfo;

	int Init(CConfig * pCfg);
	int SendPacket(CPacket & packet);
//	int OnSend(int nSize);

	virtual int OnConnect();		// ���ͻ������ӳɹ���ص�
	virtual void OnClose();	        // �Ͽ�����ʱ����
	int GetNmKey(string& sKey);
protected:
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	int HandleTimeout(unsigned long& ulTmSpan);

	virtual bool IsLogin() {return m_blIsLogin;} //��¼״̬

	//Э�鶨��Ľ�������
	virtual int SendHello();
	virtual int OnHello(CBroadcastPacket & GessPacket);
	virtual int SendLogin();
    virtual int OnRspLogin(CBroadcastPacket & GessPacket);
private:
	static GessPktInfo m_GessPktInfo;
	static bool	m_blGessPktInfoInited;
	bool		m_blIsLogin;	//��¼״̬
	
	CConfig *	m_pCfg;
	//std::deque<CBroadcastPacket> m_qSend;
	CGessMutex m_csA1C;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};
#endif