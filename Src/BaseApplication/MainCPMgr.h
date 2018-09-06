#pragma once

#include "Logger.h"
#include "WorkThread.h"
#include "ConfigImpl.h"
#include "NanoServerImp.h"
#include "Communication.h"
#include "ipcpacket.h"
#include "broadcastpacket.h"
#include "BaseDefine.h"

#define MONGOOSE_USE_SSL
#include "webServerHandle.h"




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

	//web服务线程
	class CWebServerThread :public CWorkThread
	{
	public:
		CWebServerThread():m_pParent(nullptr) {}
		virtual ~CWebServerThread() {}
		void  Bind(MainCPMgr* p) { m_pParent = p; }
		
	private:
		int ThreadEntry()
		{
			try
			{
				//signal(SIGTERM, signal_handler);
				//signal(SIGINT, signal_handler);
				//setvbuf(stdout, NULL, _IOLBF, 0);
				//setvbuf(stderr, NULL, _IOLBF, 0);


				mg_mgr_init(&mgr, NULL);

				/*static std::string s_port = "8008r,443s";
				static std::string ssl_cert_path = "/Volumes/SD/key.pem";

				mg_set_option(server[i], "listening_port", s_port.c_str());
				mg_set_option(server[i], "ssl_certificate", ssl_cert_path.c_str());*/

				c = mg_bind(&mgr, s_http_port, ev_handler);
				mg_set_protocol_http_websocket(c);


				s_http_server_opts.document_root = ".";  // Serve current directory
				s_http_server_opts.enable_directory_listing = "yes";


				while (nullptr != m_pParent)
				{
					/*for (;;) 
					{
						mg_mgr_poll(&mgr, 1000);
					}*/

					//while (s_signal_received == 0) 
					{
						mg_mgr_poll(&mgr, 200);
					}

				}

				mg_mgr_free(&mgr);

				CRLog(E_SYSINFO, "%s", "CWebServerThread exit!");
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
		struct mg_mgr mgr;
		struct mg_connection *c;

		MainCPMgr* m_pParent;
	};


	//服务线程
	class CNanoServerThread :public CWorkThread
	{
	public:
		CNanoServerThread() :m_pParent(nullptr), pImp(nullptr){}
		virtual ~CNanoServerThread() {}
		void  Bind(MainCPMgr* p) { m_pParent = p; }
		void  Init( int port = 5560)
		{
			pImp = new CNanoServerImp();
			pImp->InitServerUrl("tcp://127.0.0.1:5560" , 5560,NN_PUB);
			
		}
	private:
		int ThreadEntry()
		{
			try
			{
				char gdata[4096] = {};
				while (nullptr != m_pParent)
				{
					Sleep(5000);
					strcpy(gdata,"NanoMsg server!");
					
					/*
					int len = pImp->recv_impl(gdata);
					//
					if (m_pParent->AnalyData(gdata, len) < 0)
					{
						pImp->close_impl();
						pImp->RetSetSvr();
					}
					*/
					int len = pImp->send_impl(gdata);
					CRLog(E_APPINFO, "发送数据:[%s],发送字节长度:[%d]", gdata , len);
					

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

		CNanoServerImp *pImp;
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

	int  Init();
	void Finish();
	int  Start();
	int  StartMe();
	void Stop();
	void StopMe();
	int  Run();
	int  AnalyData(const char *data, int  len);

	//配置
	CConfigImpl*		m_pConfig;
	

	//主线程变量
	volatile bool m_bStop;
	int			  m_nReadyQuit;
	CCondMutex	  m_deqCondMutex;


	//定时器管理类
	CGessTimerMgrIf * m_pGessTimerMgr;
	CIfkTimer      m_oIfQTTimer;
	CIfkTimer      m_oIfTDTimer;
	CIfkTimer      m_oIfSTTimer;

	//异步退出
	CAsynQuitThread m_oAsynQuitThread;
	void AsynQuit() { m_oAsynQuitThread.Bind(this); m_oAsynQuitThread.BeginThread(); }
	void ReadyToQuit() { m_nReadyQuit = 1; }
	bool IsReadyToQuit() { return 1 == m_nReadyQuit; }

	//
	CNanoServerThread  *m_nanoserver;

	//登录注册服务
	CConnectPointAsyn  *m_mainService;

	//数据
	CWebServerThread   *m_WebServer;

};

