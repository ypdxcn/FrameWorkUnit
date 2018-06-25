#ifndef _PROTOCOLCOMM_SELECTOR_H
#define _PROTOCOLCOMM_SELECTOR_H

#include "ProtocolComm.h"
#include "ListenerSelector.h"
#include "Selector.h"
#include "Comm.h"
#include "Logger.h"
#include "strutils.h"
#include "osdepend.h"
#include <cassert>

using namespace strutils;
using namespace std;

template<typename PROCESS>
class CProtocolCommClientImp:public CProtocolCommClient
{
public:
	CProtocolCommClientImp():m_pProcessHandler(0){}
	virtual ~CProtocolCommClientImp(){}

	CAio* CreateAioInstance()
	{
		return CSingleton<CSelectorIo>::Instance();
	}

	void Finish()
	{
		m_csProcessHandler.Lock();
		if (0 != m_pProcessHandler)
			delete m_pProcessHandler;
		m_pProcessHandler = 0;
		m_csProcessHandler.Unlock();

		CProtocolCommClient::Finish();
	}
	
	void Stop()
	{
		CProtocolCommClient::Stop();
		
		m_csProcessHandler.Lock();
		if (0 != m_pProcessHandler)
		{
			CRLog(E_SYSINFO,"ProtocolCommCli closed scoekt:%d",m_pProcessHandler->SocketID());
			int nResult = closesocket(m_pProcessHandler->SocketID());
			if (SOCKET_ERROR == nResult)
			{
				CRLog(E_ERROR,"%s","closesocket err");
			}
		}
		m_csProcessHandler.Unlock();
	}

	//CConnector ���ӷ���˳ɹ��� ����
	int OnConnect(tsocket_t sSocket,string sLocalIp,int nLocalPort,string sPeerIp,int nPeerPort,int nFlage)
	{
		bool blRegiste = false;

		if (esStop == GetStage())
		{
			CRLog(E_SYSINFO,"%s","OnConnect but stopped!");
			return 0;
		}

		if (0 == nFlage)
		{//�ɹ�����
			//Э�����̴�����
			m_csProcessHandler.Lock();
			if (0 == m_pProcessHandler)
			{
				blRegiste = true;
				PROCESS* p = new PROCESS();
				if (0 == p)
				{
					CRLog(E_CRITICAL,"%s", "No mem");
					m_csProcessHandler.Unlock();
					return 0;
				}
				m_pProcessHandler = p;
			}			
			m_csProcessHandler.Unlock();

			//���û�������
			m_pProcessHandler->SocketID(sSocket);
			m_pProcessHandler->SetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
			m_pProcessHandler->Bind(this);
			m_pProcessHandler->Init(m_pCfg);

			//ע��AIO
			if (0 != RegisterAio(m_pProcessHandler))
			{
				closesocket(sSocket);
				//delete p;
				return -1;
			}

			//����Э�����̴�������OnConnect,���ڵ�¼�ȴ���
			m_pProcessHandler->OnConnect();

			//ע��/�ϱ�������Ϣ
			{
				string sNmKey("");
				m_pProcessHandler->GetNmKey(sNmKey);
				if (sNmKey == "")
				{
					sNmKey = sLocalIp + "." + ToString<int>(nLocalPort) + "." + sPeerIp + "." + ToString<int>(nPeerPort);
				}
				RegisterTcpConn(sLocalIp,nLocalPort,sPeerIp,nPeerPort,sNmKey,blRegiste);
			}
		}

		//���ദ��
		CProtocolCommClient::OnConnect(sSocket,sLocalIp,nLocalPort,sPeerIp,nPeerPort,nFlage);		
		return 0;
	}
	
	void RegisterTcpConn(const string& sLocalIp, int nLocalPort,const string& sPeerIp,int nPeerPort,const string& sNmKey,bool blRegister = false)
	{
		vector<CNMO> vNmo;
		vector< pair<string,string> > vpaOid;
		pair<string,string> pa;
		CNMO oNmo;
		oNmo.m_sOid = gc_sTcpLocalIp;
		oNmo.m_sOidIns = gc_sTcpLocalIp + "." + sNmKey;
		oNmo.m_sValue = sLocalIp;
		oNmo.m_nQuality = gc_nQuolityGood;
		oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
		vNmo.push_back(oNmo);
		pa.first = oNmo.m_sOid;
		pa.second = oNmo.m_sOidIns;
		vpaOid.push_back(pa);

		oNmo.m_sOid = gc_sTcpLocalPort;
		oNmo.m_sOidIns = gc_sTcpLocalPort + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(nLocalPort);
		vNmo.push_back(oNmo);
		pa.first = oNmo.m_sOid;
		pa.second = oNmo.m_sOidIns;
		vpaOid.push_back(pa);

		oNmo.m_sOid = gc_sTcpRemoteIp;
		oNmo.m_sOidIns = gc_sTcpRemoteIp + "." + sNmKey;
		oNmo.m_sValue = sPeerIp;
		vNmo.push_back(oNmo);
		pa.first = oNmo.m_sOid;
		pa.second = oNmo.m_sOidIns;
		vpaOid.push_back(pa);

		oNmo.m_sOid = gc_sTcpRemotePort;
		oNmo.m_sOidIns = gc_sTcpRemotePort + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(nPeerPort);
		vNmo.push_back(oNmo);
		pa.first = oNmo.m_sOid;
		pa.second = oNmo.m_sOidIns;
		vpaOid.push_back(pa);

		oNmo.m_sOid = gc_sTcpState;
		oNmo.m_sOidIns = gc_sTcpState + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(gc_nTcpConneted);
		vNmo.push_back(oNmo);
		pa.first = oNmo.m_sOid;
		pa.second = oNmo.m_sOidIns;
		vpaOid.push_back(pa);

		oNmo.m_sOid = gc_sTcpInBytesAve;
		oNmo.m_sOidIns = gc_sTcpInBytesAve + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(0);
		vNmo.push_back(oNmo);
		pa.first = oNmo.m_sOid;
		pa.second = oNmo.m_sOidIns;
		vpaOid.push_back(pa);

		oNmo.m_sOid = gc_sTcpOutBytesAve;
		oNmo.m_sOidIns = gc_sTcpOutBytesAve + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(0);
		vNmo.push_back(oNmo);
		pa.first = oNmo.m_sOid;
		pa.second = oNmo.m_sOidIns;
		vpaOid.push_back(pa);

		if (blRegister)
			CNetMgr::Instance()->Register(&m_oNmoModule,vpaOid);
		CNetMgr::Instance()->Report(vNmo);
	}

	void UnRegisterTcpConn(const string& sLocalIp, int nLocalPort,const string& sPeerIp,int nPeerPort,const string& sNmKey)
	{
		CNMO oNmo;
		oNmo.m_sOid = gc_sTcpState;
		oNmo.m_sOidIns = gc_sTcpState + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(gc_nTcpDisConneted);
		oNmo.m_nQuality = gc_nQuolityGood;
		oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
		CNetMgr::Instance()->Report(oNmo);
		//CNetMgr::Instance()->UnRegisterModule(&m_oNmoModule);
	}

	//�ͻ��� Ŀǰֻ֧�ֵ���socket���� ����·��
	int SendPacket(CPacket & pkt)
	{
		if (gc_nTcpDisConneted == GetConnState())
		{
			CRLog(E_SYSINFO,"%s","Connetion has not been established!");
			return -1;
		}

		m_csProcessHandler.Lock();
		//assert(0 != m_pProcessHandler);
		if (0 == m_pProcessHandler)
		{
			m_csProcessHandler.Unlock();

			CRLog(E_SYSINFO,"%s","Connetion has not been established!");
			return -1;
		}

		int nRtn = m_pProcessHandler->SendPacket(pkt);
		m_csProcessHandler.Unlock();
		return nRtn;
	}

	void CloseProcess(CProtocolProcess* pProcess)
	{
		assert(0 !=  pProcess);
		PROCESS* p = dynamic_cast<PROCESS*>(pProcess);
		if (0 == p)
		{
			CRLog(E_ERROR,"%s","ProtocolProcess is 0");
			return;
		}

		string sLocalIp,sPeerIp;
		int nLocalPort,nPeerPort;
		p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
		string sNmKey("");
		p->GetNmKey(sNmKey);
		if (sNmKey == "")
		{
			sNmKey = sLocalIp + "." + ToString<int>(nLocalPort) + "." + sPeerIp + "." + ToString<int>(nPeerPort);
		}
		UnRegisterTcpConn(sLocalIp,nLocalPort,sPeerIp,nPeerPort,sNmKey);

		p->OnClose();
		
		//m_csProcessHandler.Lock();
		//if (p == m_pProcessHandler)
		//	m_pProcessHandler = 0;
		//m_csProcessHandler.Unlock();
		//delete p;

		//֪ͨ����
		if (esStart == GetStage())
			NotifyConnect();
	}

	//������ѯ�ӿ�
	int Query(CNMO& oNmo) const
	{
		string sOidIns = oNmo.m_sOidIns;
		string sPrefix = oNmo.m_sOid + ".";	
		if (oNmo.m_sOid == gc_sTcpInBytesAve || oNmo.m_sOid == gc_sTcpOutBytesAve)
		{
			string sKey;
			string::size_type nPos = sOidIns.find(sPrefix);
			if (string::npos != nPos)
			{
				if (nPos < sOidIns.length() - 1)
				{
					m_csProcessHandler.Lock();
					if (0 != m_pProcessHandler)
					{
						unsigned int uiInNowStat = 0, uiInAveBytes = 0,uiOutNowStat = 0,uiOutAveBytes = 0;
						m_pProcessHandler->GetFlowStatics(uiInNowStat,uiInAveBytes,uiOutNowStat,uiOutAveBytes);
						oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
						if (oNmo.m_sOid == gc_sTcpInBytesAve)
						{
							oNmo.m_sValue = ToString<unsigned int>(uiInAveBytes);
						}
						else
						{
							oNmo.m_sValue = ToString<unsigned int>(uiOutAveBytes);
						}
					}
					m_csProcessHandler.Unlock();
				}
			}
		}
		else if (oNmo.m_sOid == gc_sTcpState)
		{
			oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
			oNmo.m_sValue = ToString<int>(GetConnState());
		}
		return 0;
	}
	//���ƽӿ�
	int Operate(const string &sOid, int nflag, const string &sDstValue, const string &sParamer){return 0;}
private:
	//Э�����̴���������
	PROCESS* m_pProcessHandler;
	mutable CGessMutex  m_csProcessHandler;
};

///////////////////////////////////////////////////////////////////////////////
//�����Э��ͨѶģ����
template<typename PROCESS>
class CProtocolCommServerImp:public CProtocolCommServer
{
public:
	CProtocolCommServerImp();
	virtual ~CProtocolCommServerImp();
	
	int Init(CConfig* pConfig);
	void Finish();
	void Stop();

	//���ϲ�Ӧ�ò��ṩ�����б�����Ҫ�ӿں��� ��Ҫ�߱�����·��
	int SendPacket(CPacket & packet);
protected:
	CListener* CreateListener(CProtocolCommServer* p);
	void DestroyListener(CListener* p);
	CAio* CreateAioInstance();
private:
	void UnRegisterTcpConn(const string& sLocalIp, int nLocalPort,const string& sPeerIp,int nPeerPort,const string& sNmKey);
	void RegisterTcpConn(const string& sLocalIp, int nLocalPort,const string& sPeerIp,int nPeerPort,const string& sNmKey);

	void CloseProcess(CProtocolProcess* p);
	int OnAccept(tsocket_t sSocket,string sLocalIp,int nLocalPort,string sPeerIp,int nPeerPort);	
	//������ѯ�ӿ�
	int Query(CNMO& oNmo) const;
	//���ƽӿ�
	int Operate(const string &sOid, int nflag, const string &sDstValue, const string &sParamer);

	void RemoveEndPoint(PROCESS*);
	void On1stPacket(CProtocolProcess* p,const string& sRouteKey);

	//������Э�����̴�������
	std::map<std::string, PROCESS*> m_mapNm;
	mutable CGessMutex	m_csNm;

	//�����ӵ�û�������շ�
	std::list<PROCESS*>	m_lstEpAccepted;
	CGessMutex	m_csEpAccepted;
	
	//���յ���������
	std::map<std::string, PROCESS*> m_mapEpNormal;
	CGessMutex	m_csEpNormal;

	//�Ƿ�㲥��־ 0�ǹ㲥 1�㲥
	int m_nBroadcast;
};

template<typename PROCESS>
CProtocolCommServerImp<PROCESS>::CProtocolCommServerImp()
:CProtocolCommServer()
,m_nBroadcast(0)
{}

template<typename PROCESS>
CProtocolCommServerImp<PROCESS>::~CProtocolCommServerImp()
{}

template<typename PROCESS>
CAio* CProtocolCommServerImp<PROCESS>::CreateAioInstance()
{
	return CSingleton<CSelectorIo>::Instance();
}

//��ʼ��
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::Init(CConfig* pConfig)
{
	//�����ʼ��
	if (0 != CProtocolCommServer::Init(pConfig))
		return -1;

	//�㲥��־
	std::string sBroadcast("");
	int nOk = pConfig->GetProperty("broadcast",sBroadcast);
	if (nOk == 0)
		m_nBroadcast = FromString<int>(sBroadcast);
	if (m_nBroadcast != 0 && m_nBroadcast != 1 && m_nBroadcast != 2)
		m_nBroadcast = 0;

	return 0;
}

//��������
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::Finish()
{
	////���������õ�Э�����̴�������
	//m_csNm.Lock();
	//m_mapNm.clear();
	//m_csNm.Unlock();

	////����û���������ݵ�����list 
	//PROCESS* p = 0;
	//typename std::list<PROCESS*>::iterator itList;
	//m_csEpAccepted.Lock();
	//for (itList = m_lstEpAccepted.begin(); itList != m_lstEpAccepted.end(); ++itList)
	//{
	//	p = (*itList);
	//	delete p;
	//}
	//m_lstEpAccepted.clear();
	//m_csEpAccepted.Unlock();

	////���������������ݵ�����map
	//typename std::map<std::string, PROCESS*>::iterator itMap;
	//m_csEpNormal.Lock();
	//for (itMap = m_mapEpNormal.begin(); itMap != m_mapEpNormal.end(); ++itMap)
	//{
	//	p = (*itMap).second;
	//	delete p;
	//}
	//m_mapEpNormal.clear();
	//m_csEpNormal.Unlock();

	//�����������
	CProtocolCommServer::Finish();
}

template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::Stop()
{
	//����ӿ�
	CProtocolCommServer::Stop();


	////���������õ�Э�����̴�������
	//m_csNm.Lock();
	//m_mapNm.clear();
	//m_csNm.Unlock();

	////�ر�Э��socket��ɾ��Э�����̶���
	//PROCESS* p = 0;
	//typename std::list<PROCESS*>::iterator itList;
	//m_csEpAccepted.Lock();
	//for (itList = m_lstEpAccepted.begin(); itList != m_lstEpAccepted.end(); ++itList)
	//{
	//	p = (*itList);
	//	if (0 != p)
	//	{
	//		closesocket(p->SocketID());
	//		delete p;			
	//	}
	//}
	//m_lstEpAccepted.clear();
	//m_csEpAccepted.Unlock();

	////�ر�Э��socket��ɾ��Э�����̶���
	//typename std::map<std::string, PROCESS*>::iterator itMap;
	//m_csEpNormal.Lock();
	//for (itMap = m_mapEpNormal.begin(); itMap != m_mapEpNormal.end(); ++itMap)
	//{
	//	p = (*itMap).second;
	//	closesocket(p->SocketID());
	//	delete p;
	//}
	//m_mapEpNormal.clear();
	//m_csEpNormal.Unlock();
}

template<typename PROCESS>
CListener* CProtocolCommServerImp<PROCESS>::CreateListener(CProtocolCommServer* p)
{
	CListener* pListener = new CListenerSelector(p);
	return pListener;
}

template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::DestroyListener(CListener* p)
{
	delete p;
}

//�����Ӵ���ӿ�
//tsocket_t sSocket,�ѽ��յ�����
//std::string sPeerIp,int nPeerPort,�Զ˵�ip�Ͷ˿�
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::OnAccept(tsocket_t sSocket,string sLocalIp,int nLocalPort,string sPeerIp,int nPeerPort)
{
	PROCESS* p = new PROCESS();
	if (0 == p)
	{
		CRLog(E_CRITICAL,"%s", "No mem");
		return -1;
	}
	p->SocketID(sSocket);
	p->SetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	p->Bind(this);
	p->Init(m_pCfg);

	if (0 != RegisterAio(p))
	{
		closesocket(sSocket);
		delete p;
		return -1;
	}

	m_csEpAccepted.Lock();
	//���Լ�¼ʱ����Ϣ,���ж��Ƿ�ʱ�����Ӷ���������
	m_lstEpAccepted.push_back(p);
	m_csEpAccepted.Unlock();

	p->OnAccept();

	string sNmKey("");
	p->GetNmKey(sNmKey);
	if (sNmKey == "")
	{
		sNmKey = sLocalIp + "." + ToString<int>(nLocalPort) + "." + sPeerIp + "." + ToString<int>(nPeerPort);
	}
	m_csNm.Lock();
	m_mapNm[sNmKey] = p;
	m_csNm.Unlock();
	RegisterTcpConn(sLocalIp,nLocalPort,sPeerIp,nPeerPort,sNmKey);
	CProtocolCommServer::OnAccept(sSocket,sLocalIp,nLocalPort,sPeerIp,nPeerPort);	
	return 0;
}

//��Ӧsocket�ر�
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::CloseProcess(CProtocolProcess* pProcess)
{
	assert(pProcess != 0);
	PROCESS* p = dynamic_cast<PROCESS*>(pProcess);
	if (!p)
		return;
		
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	string sNmKey("");
	p->GetNmKey(sNmKey);
	if (sNmKey == "")
	{
		sNmKey = sLocalIp + "." + ToString<int>(nLocalPort) + "." + sPeerIp + "." + ToString<int>(nPeerPort);
	}	
	UnRegisterTcpConn(sLocalIp,nLocalPort,sPeerIp,nPeerPort,sNmKey);

	p->OnClose();
	RemoveEndPoint(p);
	delete p;
}

template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::UnRegisterTcpConn(const string& sLocalIp, int nLocalPort,const string& sPeerIp,int nPeerPort,const string& sNmKey)
{
	//CNMO oNmo;
	//oNmo.m_sOid = gc_sTcpState;
	//oNmo.m_sOidIns = gc_sTcpState + "." + sNmKey;
	//oNmo.m_sValue = ToString<int>(gc_nTcpDisConneted);
	//oNmo.m_nQuality = gc_nQuolityGood;
	//oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
		
	//����˵�TCP�����ж�ʱ���ϱ�,�������澯
	//CNetMgr::Instance()->Report(oNmo);

	vector< string > vpaOid;
	vpaOid.push_back( gc_sTcpLocalIp + "." + sNmKey );

	vpaOid.push_back( gc_sTcpLocalPort + "." + sNmKey);
	
	vpaOid.push_back(gc_sTcpRemoteIp + "." + sNmKey);
	
	vpaOid.push_back(gc_sTcpRemotePort + "." + sNmKey);
	
	vpaOid.push_back(gc_sTcpState + "." + sNmKey);
	
	vpaOid.push_back(gc_sTcpInBytesAve + "." + sNmKey);
	
	vpaOid.push_back(gc_sTcpOutBytesAve + "." + sNmKey);

	CNetMgr::Instance()->UnRegisterNmo(&m_oNmoModule,vpaOid);
}

template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::RegisterTcpConn(const string& sLocalIp, int nLocalPort,const string& sPeerIp,int nPeerPort,const string& sNmKey)	
{
	vector<CNMO> vNmo;
	vector< pair<string,string> > vpaOid;
	pair<string,string> pa;
	CNMO oNmo;
	oNmo.m_sOid = gc_sTcpLocalIp;
	oNmo.m_sOidIns = gc_sTcpLocalIp + "." + sNmKey;
	oNmo.m_sValue = sLocalIp;
	oNmo.m_nQuality = gc_nQuolityGood;
	oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
	vNmo.push_back(oNmo);
	pa.first = oNmo.m_sOid;
	pa.second = oNmo.m_sOidIns;
	vpaOid.push_back(pa);

	oNmo.m_sOid = gc_sTcpLocalPort;
	oNmo.m_sOidIns = gc_sTcpLocalPort + "." + sNmKey;
	oNmo.m_sValue = ToString<int>(nLocalPort);
	vNmo.push_back(oNmo);
	pa.first = oNmo.m_sOid;
	pa.second = oNmo.m_sOidIns;
	vpaOid.push_back(pa);

	oNmo.m_sOid = gc_sTcpRemoteIp;
	oNmo.m_sOidIns = gc_sTcpRemoteIp + "." + sNmKey;
	oNmo.m_sValue = sPeerIp;
	vNmo.push_back(oNmo);
	pa.first = oNmo.m_sOid;
	pa.second = oNmo.m_sOidIns;
	vpaOid.push_back(pa);

	oNmo.m_sOid = gc_sTcpRemotePort;
	oNmo.m_sOidIns = gc_sTcpRemotePort + "." + sNmKey;
	oNmo.m_sValue = ToString<int>(nPeerPort);
	vNmo.push_back(oNmo);
	pa.first = oNmo.m_sOid;
	pa.second = oNmo.m_sOidIns;
	vpaOid.push_back(pa);

	oNmo.m_sOid = gc_sTcpState;
	oNmo.m_sOidIns = gc_sTcpState + "." + sNmKey;
	oNmo.m_sValue = ToString<int>(gc_nTcpConneted);
	vNmo.push_back(oNmo);
	pa.first = oNmo.m_sOid;
	pa.second = oNmo.m_sOidIns;
	vpaOid.push_back(pa);

	oNmo.m_sOid = gc_sTcpInBytesAve;
	oNmo.m_sOidIns = gc_sTcpInBytesAve + "." + sNmKey;
	oNmo.m_sValue = ToString<int>(0);
	vNmo.push_back(oNmo);
	pa.first = oNmo.m_sOid;
	pa.second = oNmo.m_sOidIns;
	vpaOid.push_back(pa);

	oNmo.m_sOid = gc_sTcpOutBytesAve;
	oNmo.m_sOidIns = gc_sTcpOutBytesAve + "." + sNmKey;
	oNmo.m_sValue = ToString<int>(0);
	vNmo.push_back(oNmo);
	pa.first = oNmo.m_sOid;
	pa.second = oNmo.m_sOidIns;
	vpaOid.push_back(pa);

	CNetMgr::Instance()->Register(&m_oNmoModule,vpaOid);
	CNetMgr::Instance()->Report(vNmo);
}


//�յ��׸�Э�����ݱ���ʱ���� �û�����·����Ϣ
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::On1stPacket(CProtocolProcess* p,const string& sRouteKey)
{
	PROCESS* pProcess = dynamic_cast<PROCESS*>(p);
	if (!pProcess)
		return;

	//·����ϢΪ�� ��Ϊ�㲥������·�ɱ�
	if (m_nBroadcast != 0 || sRouteKey == "")
		return;

	typename std::list<PROCESS*>::iterator it;
	m_csEpAccepted.Lock();
	for(it = m_lstEpAccepted.begin();it != m_lstEpAccepted.end(); ++it)
	{
		//��ⳬʱ
		//...

		if (*it == pProcess)
		{
			m_lstEpAccepted.erase(it);
			break;
		}
	}
	m_csEpAccepted.Unlock();

	//
	typename std::map<std::string, PROCESS*>::iterator itMap;
	m_csEpNormal.Lock();
	itMap = m_mapEpNormal.find(sRouteKey);
	if (itMap != m_mapEpNormal.end())
	{
		if (0 != itMap->second)
			itMap->second->RemoveKey(sRouteKey);
		//m_mapEpNormal.erase(itMap);
	}
	m_mapEpNormal[sRouteKey] = pProcess;
	m_csEpNormal.Unlock();
}

//�Ƴ�
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::RemoveEndPoint(PROCESS* p)
{
	if (0 == p)
		return;

	//���������õ�Э�����̴�������
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	string sNmKey("");
	if (0 != p)
	{		
		p->GetNmKey(sNmKey);
		if (sNmKey == "")
		{
			p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
			sNmKey = sLocalIp + "." + ToString<int>(nLocalPort) + "." + sPeerIp + "." + ToString<int>(nPeerPort);
		}
	}
	m_csNm.Lock();	
	typename map<string,PROCESS*>::iterator itNm = m_mapNm.find(sNmKey);
	if (itNm != m_mapNm.end())
		m_mapNm.erase(itNm);
	m_csNm.Unlock();

	bool blFind = false;
	std::list<std::string> lst = p->Keys();
	if (lst.size() >0)
	{
		typename std::map<std::string, PROCESS*>::iterator itMap;
		std::list<std::string>::iterator itList;
		m_csEpNormal.Lock();
		for (itList=lst.begin();itList!=lst.end();++itList)
		{
			itMap = m_mapEpNormal.find(*itList);
			if (itMap != m_mapEpNormal.end())
			{
				m_mapEpNormal.erase(itMap);
				blFind = true;

				CRLog(E_SYSINFO,"%s","Remove from normalmap!");
			}
		}
		m_csEpNormal.Unlock();

		if (blFind)
			return;
	}

	typename std::list<PROCESS*>::iterator it;
	m_csEpAccepted.Lock();
	for(it = m_lstEpAccepted.begin();it != m_lstEpAccepted.end(); ++it)
	{
		if (*it == p)
		{
			m_lstEpAccepted.erase(it);
			m_csEpAccepted.Unlock();

			CRLog(E_SYSINFO,"%s","Remove from acceptlist!");
			return;
		}
	}
	m_csEpAccepted.Unlock();
}

//���ͱ��Ľӿ�
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::SendPacket(CPacket & pkt)
{
	if (m_nBroadcast == 0)
	{//�ǹ㲥 ����������·��
		std::string sKey;
		try
		{
			CPacketRouteable* pktRoute = dynamic_cast<CPacketRouteable*>(&pkt);
			sKey = pktRoute->RouteKey();
		}
		catch(std::bad_cast)
		{
			CRLog(E_ERROR,"%s","packet err");
			return -1;
		}

		int nRtn = -1;
		m_csEpNormal.Lock();
		typename std::map<std::string, PROCESS*>::iterator it = m_mapEpNormal.find(sKey);
		if (it != m_mapEpNormal.end())
		{
			if (0 != it->second)
			{
				nRtn = it->second->SendPacket(pkt);
			}
			else
			{
				nRtn = -1;
				CRLog(E_ERROR,"%s","err null");
			}
		}
		m_csEpNormal.Unlock();
		return nRtn;
	}
	else if (m_nBroadcast == 1)
	{//�㲥 ��������·�ɣ�ѭ�����ͣ�Ŀǰδ������������				
		typename std::map<std::string, PROCESS*>::iterator it;
		try
		{
			m_csEpNormal.Lock();
			//CRLog(E_SYSINFO,"num %d",m_mapEpNormal.size());
			int nIndex = 1;
			int nSize = m_mapEpNormal.size();
			for (it = m_mapEpNormal.begin();it != m_mapEpNormal.end();++it)
			{
				PROCESS* p = it->second;
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}
				nIndex++;
			}
			m_csEpNormal.Unlock();
		}
		catch(...)
		{
			m_csEpNormal.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}

		typename std::list<PROCESS*>::iterator it2;
		try
		{
			m_csEpAccepted.Lock();
			//CRLog(E_SYSINFO,"num %d",m_lstEpAccepted.size());
			int nIndex = 1;
			int nSize = m_lstEpAccepted.size();
			for(it2 = m_lstEpAccepted.begin();it2 != m_lstEpAccepted.end(); ++it2)
			{
				PROCESS* p = (*it2);
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}
				nIndex++;
			}
			m_csEpAccepted.Unlock();
			return 0;
		}
		catch(...)
		{
			m_csEpAccepted.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}
	}
	else
	{//����ѡһ
		int nNumber = 0;
		typename std::map<std::string, PROCESS*>::iterator it;
		try
		{
			m_csEpNormal.Lock();
			for (it = m_mapEpNormal.begin();it != m_mapEpNormal.end();++it)
			{
				it = m_mapEpNormal.begin();
				PROCESS* p = it->second;
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
					nNumber++;
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}

				if (nNumber > 0)
					break;
			}
			m_csEpNormal.Unlock();
		}
		catch(...)
		{
			m_csEpNormal.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}

		if (nNumber > 0)
			return 0;

		typename std::list<PROCESS*>::iterator it2;
		try
		{
			m_csEpAccepted.Lock();
			for(it2 = m_lstEpAccepted.begin();it2 != m_lstEpAccepted.end(); ++it2)
			{
				PROCESS* p = (*it2);
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
					nNumber++;
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}
				
				if (nNumber > 0)
					break;
			}
			m_csEpAccepted.Unlock();
			return 0;
		}
		catch(...)
		{
			m_csEpAccepted.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}
	}
}

//������ѯ�ӿ�
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::Query(CNMO& oNmo) const
{
	string sOidIns = oNmo.m_sOidIns;
	string sPrefix = oNmo.m_sOid + ".";	
	string sKey;
	string::size_type nPos = sOidIns.find(sPrefix);
	if (string::npos == nPos)
		return -1;

	if (nPos >= sOidIns.length() - 1)
		return -1;
	
	sKey = sOidIns.substr(nPos + sPrefix.length());

	m_csNm.Lock();
	typename map<string,PROCESS*>::const_iterator it = m_mapNm.find(sKey);
	if (it == m_mapNm.end())
	{
		m_csNm.Unlock();
		return -1;
	}

	if (oNmo.m_sOid == gc_sTcpInBytesAve || oNmo.m_sOid == gc_sTcpOutBytesAve)
	{
		unsigned int uiInNowStat = 0, uiInAveBytes = 0,uiOutNowStat = 0,uiOutAveBytes = 0;
		(*it).second->GetFlowStatics(uiInNowStat,uiInAveBytes,uiOutNowStat,uiOutAveBytes);
		oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
		if (oNmo.m_sOid == gc_sTcpInBytesAve)
		{
			oNmo.m_sValue = ToString<unsigned int>(uiInAveBytes);
		}
		else
		{
			oNmo.m_sValue = ToString<unsigned int>(uiOutAveBytes);
		}
	}
	else if (oNmo.m_sOid == gc_sTcpState)
	{
		oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
		oNmo.m_sValue = ToString<int>(gc_nTcpConneted);
	}
	m_csNm.Unlock();
	return 0;
}

//���ƽӿ�
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::Operate(const string &sOid, int nflag, const string &sDstValue, const string &sParamer){return 0;}
#endif