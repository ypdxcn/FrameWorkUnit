#pragma once


#include "Logger.h"
#include "WorkThread.h"
#include "ConfigImpl.h"
#include "NanoServerImp.h"
#include "Communication.h"
#include "ipcpacket.h"
#include "broadcastpacket.h"


class MainCPMgr : public CProtocolCpMgr
{
private:
	//异步退出线程
	class CAsynQuitThread :public CWorkThread
	{
	public:
		CAsynQuitThread() :m_pParent(0) {}
		virtual ~CAsynQuitThread() {}
		void Bind(MainCPMgr* p) { m_pParent = p; }
	private:
		int ThreadEntry()
		{
			try
			{
				if (0 != m_pParent)
				{
					m_pParent->StopMe();
					m_pParent->Stop();
					m_pParent->Finish();
					m_pParent->ReadyToQuit();
				}
				CRLog(E_SYSINFO, "%s", "CAsynQuitThread exit!");
				return 0;
			}
			catch (std::exception e)
			{
				CRLog(E_ERROR, "exception:%s!", e.what());
				return -1;
			}
			catch (...)
			{
				CRLog(E_ERROR, "%s", "Unknown exception!");
				return -1;
			}
		}
		int End()
		{
			return 0;
		}
	private:
		MainCPMgr* m_pParent;
	};

	class CIfkTimer : public CGessTimer
	{
	public:
		CIfkTimer() {}
		virtual ~CIfkTimer() {}
		void Bind(MainCPMgr* p)
		{
			m_pParent = p;
		}
		int TimeOut(const string& ulKey, unsigned long& ulTmSpan)
		{
			if (0 != m_pParent)
				return m_pParent->OnIfkTimeout(ulKey);
			return -1;
		}
		void TimerCanceled(const string& ulKey)
		{
		}
	private:
		MainCPMgr* m_pParent;
	};

	

	//服务线程
	class CNanoServerThread :public CWorkThread ,public  CNanoServerImp
	{
	public:
		CNanoServerThread() :m_pParent(nullptr) {}
		virtual ~CNanoServerThread() {}
		void  Bind(MainCPMgr* p) { m_pParent = p; }
	private:
		int ThreadEntry()
		{
			try
			{
				char gdata[4096];
				while (nullptr != m_pParent)
				{
					int len = recv_impl(gdata);
					//
					if (m_pParent->AnalyData(gdata, len) < 0)
					{
						close_impl();
						RetSetSvr();
					}
				}
				CRLog(E_SYSINFO, "%s", "CAsynQuitThread exit!");
				return 0;
			}
			catch (std::exception e)
			{
				CRLog(E_ERROR, "exception:%s!", e.what());
				return -1;
			}
			catch (...)
			{
				CRLog(E_ERROR, "%s", "Unknown exception!");
				return -1;
			}
		}
		int End()
		{
			return 0;
		}
	private:
		MainCPMgr* m_pParent;
	};



public:
	virtual int OnAccept(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort) override;
	virtual int OnConnect(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort, int nFlag) override;
	virtual int OnLogin(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort, int nFlag) override;
	virtual int OnClose(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort) override;

	virtual int Forward(CPacket &GessPacket, const unsigned long& ulKey) override;

public:
	MainCPMgr();
	~MainCPMgr();

	int OnIfkTimeout(const string& ulKey);

	int Init();
	void Finish();
	int Start();
	int StartMe();
	void Stop();
	void StopMe();
	int Run();
	int AnalyData(const char *data, int  len);

	CConfigImpl*		m_pConfig;
	//定时器管理类
	CGessTimerMgrIf * m_pGessTimerMgr;
	CIfkTimer      m_oIfQTTimer;
	CIfkTimer      m_oIfTDTimer;
	CIfkTimer      m_oIfSTTimer;


	volatile bool m_bStop;
	int			  m_nReadyQuit;
	CCondMutex	  m_deqCondMutex;

	//异步退出
	CAsynQuitThread m_oAsynQuitThread;
	void AsynQuit() { m_oAsynQuitThread.Bind(this); m_oAsynQuitThread.BeginThread(); }
	void ReadyToQuit() { m_nReadyQuit = 1; }
	bool IsReadyToQuit() { return 1 == m_nReadyQuit; }

	CNanoServerThread  m_nanoserver;


	//数据

};

