//Э������ ���������½ӿڵĿͻ�������:
//��ط��������ط�����֮���H2�ӿ�
//���̻����ط�����֮���H2�ӿ�
//������Դ���������ط�����֮���H2�ӿ�
#ifndef _PROCESS_INTERFACE_H2C_H
#define _PROCESS_INTERFACE_H2C_H

#include "CommAp.h"
#include "ProcessInterfaceNm.h"
#include "BroadcastPacket.h"

using namespace std;

class COMMAP_CLASS CProcessInterfaceH2C : public CProcessInterfaceClnNm
{
public:
	CProcessInterfaceH2C(void);
	~CProcessInterfaceH2C(void);

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

		std::string	term_type;	//
		std::string	user_key;
		std::string	user_type;
		std::string	user_id;
		std::string	user_pwd;
		std::string	branch_id;
		std::string	again_flag;
	} GessPktInfo,*PGessPktInfo;

	int Init(CConfig * pCfg);

	virtual int OnConnect();		// ���ͻ������ӳɹ���ص�
	virtual void OnClose();	        // �Ͽ�����ʱ����
	int GetNmKey(string& sKey);
protected:
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	int HandleTimeout(unsigned long& ulTmSpan);


	//Э�鶨��Ľ�������
	virtual int SendHello();
	virtual int OnHello(CBroadcastPacket& pkt);
private:
	static GessPktInfo m_GessPktInfo;
	static int	m_blGessPktInfoInited;
	
	CConfig *	m_pCfg;
	//std::deque<CBroadcastPacket> m_qSend;
	CGessMutex m_csH2C;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};
#endif