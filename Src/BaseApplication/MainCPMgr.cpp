#include "MainCPMgr.h"
#include "GessTimerMgrPosix.h"
#include "ServiceHandle.h"






MainCPMgr::MainCPMgr()
{
	m_pConfig   = new CConfigImpl();
	
}


MainCPMgr::~MainCPMgr()
{
	if (m_pConfig != nullptr)
	{
		delete m_pConfig;
	}

	if (m_nanoserver != nullptr)
	{
		delete m_nanoserver;
	}

	if (m_WebServer != nullptr)
	{
		delete m_WebServer;
	}
}

int MainCPMgr::OnIfkTimeout(const string& ulKey)
{
	if (ulKey == "quotation")
	{
		CRLog(E_APPINFO, "%s", "[行情定时器]-响应逻辑");
	}
	else if (ulKey == "tradeRecord")
	{
		CRLog(E_APPINFO, "%s", "[交易定时器]-响应逻辑");
	}
	else if (ulKey == "Strategy")
	{
		CRLog(E_APPINFO, "%s", "[策略定时器]-响应逻辑");
	}

	return 0;//返回-1，定时器执行一次就删除，返回0，多次运行
}
//管理器初始化
int MainCPMgr::Init()
{
	std::string sCfgFilename;
	sCfgFilename = DEFUALT_CONF_PATH PATH_SLASH;
	sCfgFilename = sCfgFilename + "app.cfg";
	if (m_pConfig->Load(sCfgFilename) != 0)
	{
		//cout << "Log Config File failure!" << endl;
		Sleep(3);
		return -1;
	}
	//cout << "初始化日志..." << endl;
	// 初始化日志
	if (CLogger::Instance()->Initial(m_pConfig->GetProperties("logger")) != 0)
	{
		//cout << "Log Init failure!" << endl;
		Sleep(3);
		return -1;
	}
	//cout << "启动日志..." << endl;
	// 启动日志
	if (CLogger::Instance()->Start() != 0)
	{
		//cout << "Log start failure!" << endl;
		Sleep(3);
		return -1;
	}

	CRLog(E_APPINFO, "%s", "服务器开始运行v20180718!");

	m_oIfQTTimer.Bind(this);
	m_oIfTDTimer.Bind(this);
	m_oIfSTTimer.Bind(this);
	//初始化定时器管理器/启动定时器
	m_pGessTimerMgr = CGessTimerMgrImp::Instance();
	m_pGessTimerMgr->Init(2);
	
	//业务逻辑，架设了nanomsg服务组件
	m_nanoserver = new  CNanoServerThread;
	m_nanoserver->Bind(this);
	m_nanoserver->Init();

	//
	m_mainService = new CServiceHandle();
	if (m_mainService->Init(m_pConfig) != 0)
	{
		return  -1;
	}
	m_mainService->Bind(this, EnumKeyMainService);
	
	//web server
	m_WebServer = new CWebServerThread();
	m_WebServer->Bind(this);

	return 0;
}
void MainCPMgr::Finish()
{
	
	m_pGessTimerMgr->Finish();

}
//启动各主动类线程
int MainCPMgr::Start()
{
	return 0;
}

//启动被动类线程
int MainCPMgr::StartMe()
{
	m_pGessTimerMgr->CreateTimer(&m_oIfTDTimer, 8, "tradeRecord");
	m_pGessTimerMgr->CreateTimer(&m_oIfQTTimer, 5, "quotation");
	m_pGessTimerMgr->CreateTimer(&m_oIfSTTimer, 2, "Strategy");

	m_mainService->Start();
	m_pGessTimerMgr->Start();
	m_nanoserver->BeginThread();
	CRLog(E_APPINFO, "%s", "NanoMsg消息队列中间件开始运行!");
	m_WebServer->BeginThread();
	CRLog(E_APPINFO, "%s", "Web服务器开始运行!");

	return 0;
}
void MainCPMgr::Stop()
{
	m_pGessTimerMgr->DestroyTimer(&m_oIfTDTimer, "tradeRecord");
	m_pGessTimerMgr->DestroyTimer(&m_oIfQTTimer, "quotation");
	m_pGessTimerMgr->DestroyTimer(&m_oIfSTTimer, "Strategy");

	m_pGessTimerMgr->Stop();
	m_nanoserver->EndThread();
	m_WebServer->EndThread();
}

void MainCPMgr::StopMe()
{

}

int MainCPMgr::Run()
{
	try
	{
		while (!m_bStop)
		{
			m_deqCondMutex.Lock();
		/*	while (m_deqIpcPacket.empty() && !m_bStop)
				m_deqCondMutex.Wait();*/

			if (m_bStop)
			{
				//m_deqIpcPacket.clear();
				//m_deqCondMutex.Unlock();
				break;
			}

			//if (!m_deqIpcPacket.empty())
			{
				//CIpcPacket pkt = m_deqIpcPacket.front();
				//m_deqIpcPacket.pop_front();
				//m_deqCondMutex.Unlock();
				//RunIpcPacketHandleApi(pkt);
			}
		}

		//异步清理退出
		AsynQuit();

		//最多等待10秒,否则主线程直接退出
		int nCount = 0;
		do
		{
			if (IsReadyToQuit())
			{
				break;
			}

			Sleep(1);
			nCount++;
		} while (nCount < 10);

		return 0;
	}
	catch (std::exception e)
	{
		CRLog(E_CRITICAL, "exception:%s", e.what());
		return -1;
	}
	catch (...)
	{
		CRLog(E_CRITICAL, "%s", "Unknown exception");
		return -1;
	}

	return -1;
}



int MainCPMgr::AnalyData(const char *data, int  len)
{
	//
	string  tmp;
	tmp.append(data, 6);
	if (tmp == "login")
	{
		tmp.clear();
		tmp.append(data, len);
		Slogin login;
		login.Decode(data, len);
		if (tmp.find(login.m_content.user) == 0 && tmp.find(login.m_content.pswd) == 0)
			return  1;
	}

	return -1;
}




int MainCPMgr::OnAccept(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort)
{
	return 0;
}
int MainCPMgr::OnConnect(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort, int nFlag)
{
	return 0;
}
int MainCPMgr::OnLogin(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort, int nFlag)
{
	return 0;
}
int MainCPMgr::OnClose(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort)
{
	return 0;
}

int MainCPMgr::Forward(CPacket &GessPacket, const unsigned long& ulKey)
{

	return 0;
}