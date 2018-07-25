#include "ServiceHandle.h"
#include "MainCPMgr.h"

//报文对应的处理成员函数配置表
CServiceHandle::PktCmd2Api CServiceHandle::m_PktCmd2Api[] =
{
	//请求cmd					请求处理函数指针
	{ "80000001",							&CServiceHandle::OnRecvLoginRsp },
	{ "80000002",							&CServiceHandle::OnRecvLogoutRsp },
	{ "80000003",							&CServiceHandle::OnRecvSubscripRsp },
	{ "80000004",							&CServiceHandle::OnRecvUnSubscripRsp },
	{ "80000005",							0 },//&CServiceHandler::OnRecvHelloRsp}

	{ "00000001",							&CServiceHandle::OnRecvLogin },
	{ "00000002",							&CServiceHandle::OnRecvLogout },
	{ "00000003",							&CServiceHandle::OnRecvSubscrip },
	{ "00000004",							&CServiceHandle::OnRecvUnSubscrip },
	{ "00000005",							&CServiceHandle::OnRecvHello }
};


CServiceHandle::CServiceHandle():m_pCvgCpMgr(nullptr),m_pCfg(nullptr)
{
}


CServiceHandle::~CServiceHandle()
{
}

int CServiceHandle::Init(CConfig* pConfig)
{
	if (0 == pConfig)
		return -1;

	m_pCfg = pConfig;

	return 0;
}
int CServiceHandle::Start()
{
	BeginThread();

	return 0;
}
void CServiceHandle::Stop()
{
	EndThread();

}
void CServiceHandle::Finish()
{
	m_deqService.clear();
}

//连接点下层实体收到报文向上(向内)转发的接口
int CServiceHandle::OnRecvPacket(CPacket &GessPacket)
{
	return 0;
}

//连接点上层实体如连接点管理器向下(向外)转发报文的接口
int CServiceHandle::SendPacket(CPacket &GessPacket)
{
	try
	{
		CSamplerPacket & pktService = dynamic_cast<CSamplerPacket&>(GessPacket);

		m_deqCondMutex.Lock();
		m_deqService.push_back(pktService);
		m_deqCondMutex.Signal();
		m_deqCondMutex.Unlock();
		return 0;
	}
	catch (std::bad_cast)
	{
		CRLog(E_ERROR, "%s", "packet error!");
		return -1;
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
//绑定连接点管理器接口
void CServiceHandle::Bind(CConnectPointManager* pCpMgr, const unsigned long& ulKey)
{
	m_ulKey     = ulKey;
	m_pCvgCpMgr = dynamic_cast<MainCPMgr *>(pCpMgr);
}




int CServiceHandle::RunPacketHandleApi(CSamplerPacket& pkt)
{
	std::string sCmdID;
	try
	{
		sCmdID = pkt.GetCmdID();

		int nSize = sizeof(m_PktCmd2Api) / sizeof(PktCmd2Api);
		for (int i = 0; i < nSize; i++)
		{
			if (m_PktCmd2Api[i].sApiName == sCmdID)
			{
				if (m_PktCmd2Api[i].pMemberFunc == 0)
					break;

				return (this->*(m_PktCmd2Api[i].pMemberFunc))(pkt);
			}
		}

		CRLog(E_ERROR, "Unknown packet! sCmdID= %s", sCmdID.c_str());
		return -1;
	}
	catch (std::exception e)
	{
		CRLog(E_CRITICAL, "exception:%s,Handle Packet:%s", e.what(), sCmdID.c_str());
		return -1;
	}
	catch (...)
	{
		CRLog(E_CRITICAL, "Unknown exception,Handle Packet:%s", sCmdID.c_str());
		return -1;
	}

	return 0;
}

int CServiceHandle::OnRecvLoginRsp(CSamplerPacket& pkt)
{
	return 0;
}
int CServiceHandle::OnRecvSubscripRsp(CSamplerPacket& pkt)
{
	return 0;
}
int CServiceHandle::OnRecvLogoutRsp(CSamplerPacket& pkt)
{
	return 0;
}
int CServiceHandle::OnRecvUnSubscripRsp(CSamplerPacket& pkt)
{
	return 0;
}

//int OnRecvHelloRsp(CSamplerPacket& pkt)

int CServiceHandle::OnRecvLogin(CSamplerPacket& pkt)
{
	return 0;
}
int CServiceHandle::OnRecvSubscrip(CSamplerPacket& pkt)
{
	return 0;
}
int CServiceHandle::OnRecvLogout(CSamplerPacket& pkt)
{
	return 0;
}
int CServiceHandle::OnRecvUnSubscrip(CSamplerPacket& pkt)
{
	return 0;
}
int CServiceHandle::OnRecvHello(CSamplerPacket& pkt)
{
	return 0;
}



int CServiceHandle::ThreadEntry()
{
	try
	{
		while (!m_bEndThread)
		{
			m_deqCondMutex.Lock();
			while (m_deqService.empty() && !m_bEndThread)
				m_deqCondMutex.Wait();
		

			if (m_bEndThread)
			{
				m_deqCondMutex.Unlock();
				break;
			}

			CSamplerPacket pkt = m_deqService.front();
			m_deqService.pop_front();
			m_deqCondMutex.Unlock();

			try
			{
				RunPacketHandleApi(pkt);
			}
			catch (...)
			{
				CRLog(E_CRITICAL, "%s", "Unknown exception");
			}
		}
		CRLog(E_APPINFO, "%s", "RiskHandler Thread exit!");
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

	return  0;
}

int CServiceHandle::End()
{
	m_deqCondMutex.Lock();
	m_deqCondMutex.Signal();
	m_deqCondMutex.Unlock();

	CRLog(E_APPINFO, "%s", "ServiceHanlder thread wait end");
	Wait();
	return 0;


}