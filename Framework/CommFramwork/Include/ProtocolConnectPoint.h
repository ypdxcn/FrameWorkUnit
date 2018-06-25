#ifndef _PROTOCOL_CONNECT_POINT_H
#define _PROTOCOL_CONNECT_POINT_H

#ifdef AIO_IOCP
#include "ProtocolCommWin.h"
#else
#include "ProtocolCommSelector.h"
#endif
#include "Comm.h"
#include "Logger.h"
#include <cassert>

using namespace std;

class CProtocolConnectPoint: public CConnectPointAsyn
{
public:
	CProtocolConnectPoint(void)
	:m_pCpMgr(0)
	,m_pProtocolComm(0)
	,m_ulKey(0xFFFFFFFF)
	,m_pCfg(0)
	{
		for(int i=0;i<ServiceMaxStatic;i++)
			m_uiStatics[i] = 0;
	}

	virtual ~CProtocolConnectPoint(void)
	{
	}

public:
	//���ӵ��ʼ��
	int Init(CConfig* pConfig)
	{
		assert(pConfig != 0);
		if (pConfig == 0)
			return -1;

		m_pCfg = pConfig;

		m_pProtocolComm = CreateCommInst();	
		if (m_pProtocolComm == 0)
			return -1;

		m_pProtocolComm->Bind(this);
		m_pProtocolComm->Init(m_pCfg);
		return 0;
	}

	//���ӵ��������
	void Finish(void)
	{
		m_pProtocolComm->Finish();

		DestroyCommInst(m_pProtocolComm);
		m_pProtocolComm = 0;
	}

	//���ӵ㿪ʼ����
	int Start()
	{
		return m_pProtocolComm->Start();
	}

	//���ӵ�ֹͣ����
	void Stop()
	{
		m_pProtocolComm->Stop();
	}

	//
	void Bind(CConnectPointManager* pCpMgr,const unsigned long& ulKey)
	{
		m_pCpMgr = dynamic_cast<CProtocolCpMgr*>(pCpMgr);
		m_ulKey = ulKey;

		if (0 == m_pCpMgr)
			CRLog(E_ERROR,"%s","cast null");
	}

	//�����ṩ�����б�����Ҫ�ӿں���
	int SendPacket(CPacket &GessPacket)
	{
		assert(m_pProtocolComm != 0);
		if (0 == m_pProtocolComm)
			return -1;

		//ͳ�����б��� Ŀǰδ�ӱ���
		m_uiStatics[ServiceDown]++;
		
		assert(0 != m_pProtocolComm);
		if (0 == m_pProtocolComm)
		{
			CRLog(E_ERROR,"%s","0 ProtocolCom");
			return -1;
		}

		return m_pProtocolComm->SendPacket(GessPacket);
	}

	//�ص���,���ӵ��ͨѶ�������ṩ�ı����ϴ��ص����� ���ڱ����ϴ�
	int OnRecvPacket(CPacket &GessPacket)
	{
		assert(m_pCpMgr != 0);
		if (0 == m_pCpMgr)
			return -1;

		//ͳ�����б��� Ŀǰδ�ӱ���
		m_uiStatics[ServiceUp]++;
		return m_pCpMgr->Forward(GessPacket, m_ulKey);
	}

	int OnLogin(const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort,int nFlag)
	{
		if (0 == m_pCpMgr)
			return -1;

		return m_pCpMgr->OnLogin(m_ulKey,sLocalIp,nLocalPort,sPeerIp,nPeerPort,nFlag);
	}

	int OnClose(const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort)
	{
		if (0 == m_pCpMgr)
			return -1;

		return m_pCpMgr->OnClose(m_ulKey,sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	}

	//����ͳ��
	enum eServiceStaticType
	{
		ServiceUp,		//���б��� ��ģ��ת��������		
		ServiceDown,			//���б��� ��ģ���յ��ı�������
		ServiceMaxStatic
	};

protected:
	virtual CProtocolComm* CreateCommInst() = 0;
	virtual void DestroyCommInst(CProtocolComm* p) = 0;

	CProtocolCpMgr*		m_pCpMgr;				//���ӵ������
	unsigned long		m_ulKey;				//�����ӵ��key��ʶ
private:	
	CProtocolComm*		m_pProtocolComm;		//ͨѶ������
	CConfig *	m_pCfg;							//���ýӿ�

	unsigned int m_uiStatics[ServiceMaxStatic]; //����ͳ��
};

class CProtocolConnectPointClient:  public CProtocolConnectPoint
{
public:
	CProtocolConnectPointClient(){}
	virtual ~CProtocolConnectPointClient(){}

	int OnConnect(const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort, int nFlag){return m_pCpMgr->OnConnect(m_ulKey,sLocalIp,nLocalPort,sPeerIp,nPeerPort,nFlag);}
};

template<typename PROCESS>
class CProtocolCpCli:  public CProtocolConnectPointClient
{
public:
	CProtocolCpCli(){}
	~CProtocolCpCli(){}
private:
	CProtocolComm* CreateCommInst()
	{
		CProtocolComm* pProtocolComm = new CProtocolCommClientImp<PROCESS>();
		return pProtocolComm;
	}
	void DestroyCommInst(CProtocolComm* p){delete p;}
};

class CProtocolConnectPointServer:  public CProtocolConnectPoint
{
public:
	CProtocolConnectPointServer(){}
	virtual ~CProtocolConnectPointServer(){}

	int OnAccept(const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort){return m_pCpMgr->OnAccept(m_ulKey,sLocalIp,nLocalPort,sPeerIp,nPeerPort);}
};

template<typename PROCESS>
class CProtocolCpSvr:  public CProtocolConnectPointServer
{
public:
	CProtocolCpSvr(){}
	~CProtocolCpSvr(){}
private:
	CProtocolComm* CreateCommInst()
	{
		CProtocolComm* pProtocolComm = new CProtocolCommServerImp<PROCESS>();
		return pProtocolComm;
	}
	void DestroyCommInst(CProtocolComm* p){delete p;}
};
#endif