#ifndef _NETMAGMODULE_H
#define _NETMAGMODULE_H

#include <deque>
#include <vector>
#include <map>
#include "Gess.h"
#include "CommAp.h"
#include "WorkThreadNm.h"
#include "Singleton.h"
#include "Logger.h"
#include "BroadcastPacket.h"
#include "PacketBodyStructBroadcastNm.h"
#include "PacketBodyStructTradeNm.h"
#include "PacketStructTransferBroadcastNm.h"
#include "PacketStructTransferTradeNm.h"
#include "NetMgr.h"
#include "NetMgrAgent.h"

using namespace std;
using namespace nmagent;

class AGENT_CLASS CNetMgrModule:public CConnectPointAsyn, public CWorkThreadNm,public CNmConfigIf,public CNmNotifyIf
{
private:
	//�澯֪ͨ�߳�
	class CAlmNtfThread :public CWorkThreadNm
	{
	public:
		CAlmNtfThread():m_pParent(0){}
		virtual ~CAlmNtfThread(){}
		void Bind(CNetMgrModule* p){m_pParent = p;}
		int Enque(const CAlarm& oAlm)
		{
			m_deqCondMutex.Lock();
			m_deqAlm.push_back(oAlm);
			m_deqCondMutex.Unlock();
			m_deqCondMutex.Signal();
			return 0;
		}
	private:
		int ThreadEntry()
		{
			try
			{
				while(!m_bEndThread)
				{
					m_deqCondMutex.Lock();
					while(m_deqAlm.empty() && !m_bEndThread)
						m_deqCondMutex.Wait();
					
					if (m_bEndThread)
					{
						m_deqAlm.clear();
						m_deqCondMutex.Unlock();
						break;
					}

					if ( !m_deqAlm.empty())
					{
						CAlarm oAlm = m_deqAlm.front();
						m_deqAlm.pop_front();
						m_deqCondMutex.Unlock();
						
						if (0 == m_pParent)
							continue;

						try
						{
							m_pParent->NotifyAlarm(oAlm);
						}
						catch(std::exception e)
						{
							CRLog(E_ERROR,"exception:%s!",e.what());
						}
						catch(...)
						{
							CRLog(E_ERROR,"%s","Unknown exception!");
						}
					}
				}

				CRLog(E_SYSINFO,"%s","Alarm Notify Thread exit!");
				return 0;
			}
			catch(std::exception e)
			{
				CRLog(E_ERROR,"exception:%s!",e.what());
				return -1;
			}
			catch(...)
			{
				CRLog(E_ERROR,"%s","Unknown exception!");
				return -1;
			}
		}
		int End()
		{
			m_deqCondMutex.Lock();
			m_deqCondMutex.Signal();
			m_deqCondMutex.Unlock();
			Wait();
			return 0;
		}
		//�������߳�״̬�Ƿ���Ҫ������
		bool IsNetManaged(string& sKeyName)
		{
			sKeyName = "�澯֪ͨ�߳�";
			return true;
		}
	private:
		CNetMgrModule* m_pParent;
		//��־��Ϣ����
		std::deque<CAlarm> m_deqAlm;
		CCondMutex	m_deqCondMutex;
	};

	//�澯�����߳�
	class CEvtNtfThread :public CWorkThreadNm
	{
	public:
		CEvtNtfThread():m_pParent(0){}
		virtual ~CEvtNtfThread(){}
		void Bind(CNetMgrModule* p){m_pParent = p;}
		int Enque(const CEventSimple& oEvt)
		{
			m_deqCondMutex.Lock();
			m_deqEvt.push_back(oEvt);
			m_deqCondMutex.Unlock();
			m_deqCondMutex.Signal();
			return 0;
		}
	private:
		int ThreadEntry()
		{
			try
			{
				while(!m_bEndThread)
				{
					m_deqCondMutex.Lock();
					while(m_deqEvt.empty() && !m_bEndThread)
						m_deqCondMutex.Wait();
					
					if (m_bEndThread)
					{
						m_deqEvt.clear();
						m_deqCondMutex.Unlock();
						break;
					}

					if ( !m_deqEvt.empty())
					{
						CEventSimple oEvt = m_deqEvt.front();
						m_deqEvt.pop_front();
						m_deqCondMutex.Unlock();
						
						if (0 == m_pParent)
							continue;

						try
						{
							m_pParent->NotifyEvent(oEvt);
						}
						catch(std::exception e)
						{
							CRLog(E_ERROR,"exception:%s!",e.what());
						}
						catch(...)
						{
							CRLog(E_ERROR,"%s","Unknown exception!");
						}
					}
				}

				CRLog(E_SYSINFO,"%s","Event Notify Thread exit!");
				return 0;
			}
			catch(std::exception e)
			{
				CRLog(E_ERROR,"exception:%s!",e.what());
				return -1;
			}
			catch(...)
			{
				CRLog(E_ERROR,"%s","Unknown exception!");
				return -1;
			}
		}
		int End()
		{
			m_deqCondMutex.Lock();
			m_deqCondMutex.Signal();
			m_deqCondMutex.Unlock();
			Wait();
			return 0;
		}
		//�������߳�״̬�Ƿ���Ҫ������
		bool IsNetManaged(string& sKeyName)
		{
			sKeyName = "�¼�֪ͨ�߳�";
			return true;
		}
	private:
		CNetMgrModule* m_pParent;
		//��־��Ϣ����
		std::deque<CEventSimple> m_deqEvt;
		CCondMutex	m_deqCondMutex;
	};
public:
	CNetMgrModule();
	~CNetMgrModule();
public:
	int Init(CConfig* pConfig);
	int Start();
	void Stop();
	void Finish();
	int OnRecvPacket(CPacket &GessPacket){return 0;}
	int SendPacket(CPacket &GessPacket){return Enque(GessPacket);}
	void Bind(CConnectPointManager* pCpMgr,const unsigned long& ulKey);

	int Enque(CPacket& pkt);

private:
	int ThreadEntry();
	int End();

	//�������߳�״̬�Ƿ���Ҫ������
	bool IsNetManaged(string& sKeyName);

	CConnectPointManager* m_pCpMgr;
	unsigned long		m_ulKey;

	CConfig* m_pCfg;
	int m_HostId;
	int m_NodeId;

	std::deque<CTradePacket> m_deqNetMgMod;
	CCondMutex	m_deqCondMutex;
private:
	
	//OIDע��֪ͨ
	void OnItemRegister(const string& sOid,const string& sOidIns);
	//OIDע��֪ͨ
	void OnItemUnRegister(const string& sOid,const string& sOidIns);

public:
	int OnDataChange(const CNMO& oNmo){return 0;}
	int OnAlmNotify(const CAlarm& oAlm);
	int OnEvtNotify(const CEventSimple& evt);
private:
	map<string, vector<string> > m_mapOid2Ins;

	CEvtNtfThread	m_oEvtNtfThread;
	CAlmNtfThread	m_oAlmNtfThread;
private:
	int NotifyEvent(const CEventSimple& oEvt);
	int NotifyAlarm(const CAlarm& oAlm);
private:
	//�����Ա����ָ��
	typedef int (CNetMgrModule::*MFP_PacketHandleApi)(CPacket& pkt);

	//�����������뱨�Ĵ����Ա����ӳ��ṹ
	typedef struct tagCmd2Api
	{
		string sApiName;						//����ApiName���״���
		MFP_PacketHandleApi pMemberFunc;		//���Ĵ�����ָ��
	} Cmd2Api;

	//�����������뱨�Ĵ����Ա����ӳ���
	static Cmd2Api m_Cmd2Api[];

	int RunPacketHandleApi(CTradePacket& pkt);

	// [1921] ҵ�����������
	int OnQueryItemCfgReq(CPacket& pktTrade);
	// [1922] ҵ�����������
	int OnQueryItemReq(CPacket& pktTrade);
	// [1923] ҵ�����������
	int OnAlmQueryReq(CPacket& pktTrade);
	// [1924] ҵ�����������
	int OnEvtQueryReq(CPacket& pktTrade);
	// [1925] ҵ�����������
	int OnItemControlReq(CPacket& pktTrade);

	// [onEventNotify] ҵ����Ӧ�����
	int OnEventNotify(CPacket& pktBroadcast);
	// [onAlarmNotify] ҵ����Ӧ�����
	int OnAlarmNotify(CPacket& pktBroadcast);

	// [1911] ҵ����Ӧ�����
	int OnHostCfgReq(CPacket& pktTrade);
	// [1912] ҵ����Ӧ�����
	int OnNodeCfgReq(CPacket& pktTrade);
	// [1913] ҵ����Ӧ�����
	int OnMibCfgReq(CPacket& pktTrade);

	// [1914] ҵ����Ӧ�����
	int OnItemMibCfgReq(CPacket& pktTrade);
	// [1915] ҵ����Ӧ�����
	int OnItemAnalogCfgReq(CPacket& pktTrade);
	// [1916] ҵ����Ӧ�����
	int OnItemDigitalCfgReq(CPacket& pktTrade);

};



#endif
