#include "MainCPMgr.h"
#include "GessTimerMgrPosix.h"



MainCPMgr::MainCPMgr()
{
	m_pConfig = new CConfigImpl();
}


MainCPMgr::~MainCPMgr()
{
}

int MainCPMgr::OnIfkTimeout(const string& ulKey)
{
	if (ulKey == "quotation")
	{
		CRLog(E_APPINFO, "%s", "[���鶨ʱ��]");
	}
	else if (ulKey == "tradeRecord")
	{
		CRLog(E_APPINFO, "%s", "[���׶�ʱ��]");
	}
	else if (ulKey == "Strategy")
	{
		CRLog(E_APPINFO, "%s", "[���Զ�ʱ��]");
	}

	return 0;//����-1����ʱ��ִ��һ�ξ�ɾ��������0���������
}
//��������ʼ��
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
	//cout << "��ʼ����־..." << endl;
	// ��ʼ����־
	if (CLogger::Instance()->Initial(m_pConfig->GetProperties("logger")) != 0)
	{
		//cout << "Log Init failure!" << endl;
		Sleep(3);
		return -1;
	}
	//cout << "������־..." << endl;
	// ������־
	if (CLogger::Instance()->Start() != 0)
	{
		//cout << "Log start failure!" << endl;
		Sleep(3);
		return -1;
	}

	CRLog(E_APPINFO, "%s", "��������ʼ����v20180718!");

	m_oIfQTTimer.Bind(this);
	m_oIfTDTimer.Bind(this);
	m_oIfSTTimer.Bind(this);
	//��ʼ����ʱ��������/������ʱ��
	m_pGessTimerMgr = CGessTimerMgrImp::Instance();
	m_pGessTimerMgr->Init(2);
	
	m_nanoserver.Bind(this);
	m_nanoserver.InitServerUrl("tcp://127.0.0.1:5560");
	return 0;
}
void MainCPMgr::Finish()
{
	m_pGessTimerMgr->Finish();

}
//�������������߳�
int MainCPMgr::Start()
{
	return 0;
}

//�����������߳�
int MainCPMgr::StartMe()
{
	m_pGessTimerMgr->CreateTimer(&m_oIfTDTimer, 8, "tradeRecord");
	m_pGessTimerMgr->CreateTimer(&m_oIfQTTimer, 5, "quotation");
	m_pGessTimerMgr->CreateTimer(&m_oIfSTTimer, 2, "Strategy");


	m_pGessTimerMgr->Start();

	return 0;
}
void MainCPMgr::Stop()
{
	m_pGessTimerMgr->DestroyTimer(&m_oIfTDTimer, "tradeRecord");
	m_pGessTimerMgr->DestroyTimer(&m_oIfQTTimer, "quotation");
	m_pGessTimerMgr->DestroyTimer(&m_oIfSTTimer, "Strategy");

	m_pGessTimerMgr->Stop();
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

		//�첽�����˳�
		AsynQuit();

		//���ȴ�10��,�������߳�ֱ���˳�
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