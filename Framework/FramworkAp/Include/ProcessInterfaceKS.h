//Э������ ���������½ӿڷ��������:
//���̻���������Դ������֮���K�ӿ�
//��ط�������������Դ������֮���K�ӿ�
#ifndef _PROCESS_INTERFACE_PKS_H
#define _PROCESS_INTERFACE_PKS_H

#include "CommAp.h"
#include "ProcessInterfaceNm.h"
#include "IpcPacket.h"

using namespace std;

class COMMAP_CLASS CIpcPacket;
class COMMAP_CLASS CProcessInterfaceKS : public CProcessInterfaceSvrNm
{
public:
	CProcessInterfaceKS(void);
	~CProcessInterfaceKS(void);

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

	virtual int OnAccept();		// ������˽��յ����Ӻ�ص�
	virtual void OnClose();		// �Ͽ�����ʱ����
	int GetNmKey(string& sKey);
protected:
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	virtual int HandleTimeout(unsigned long& ulTmSpan);

	//virtual bool IsLogin() {return m_blIsLogin;} //��¼״̬

	//Э�鶨��Ľ�������
    //virtual int OnLogin(CIpcPacket & GessPacket);
private:
	int SendHello();
	int OnHello(CIpcPacket& pktHello);

	static GessPktInfo m_GessPktInfo;
	static int	m_blGessPktInfoInited;
	
	CConfig *	m_pCfg;
	//std::deque<CIpcPacket> m_qSend;
	CGessMutex m_csKS;
	
	unsigned long m_uiPacketRev;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};
#endif