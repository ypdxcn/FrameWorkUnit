#include "ProcessInterfaceF2S.h"
#include "BroadcastPacket.h"
#include "Logger.h"
#include "ApConstant.h"
using namespace ApConst;

CProcessInterfaceF2S::GessPktInfo CProcessInterfaceF2S::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
bool CProcessInterfaceF2S::m_blGessPktInfoInited = false;

CProcessInterfaceF2S::CProcessInterfaceF2S()
:m_pCfg(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceF2S::~CProcessInterfaceF2S(void)
{
}

int CProcessInterfaceF2S::Init(CConfig * pCfg)
{
	CTcpAppProcessServer::Init(pCfg);
	if (!m_blGessPktInfoInited)
	{
		m_blGessPktInfoInited = true;
		

		string sLoginFlag;
		if (0 == pCfg->GetProperty("login",sLoginFlag))
		{
			if (1 == FromString<int>(sLoginFlag))
				m_GessPktInfo.blNeedLogin = true;
		}

		CConfig* pCfgGlobal = pCfg->GetCfgGlobal();
		pCfgGlobal->GetProperty("node_type",m_GessPktInfo.node_type);
		pCfgGlobal->GetProperty("node_id",m_GessPktInfo.node_id);
		pCfgGlobal->GetProperty("host_id",m_GessPktInfo.node_name);
		pCfgGlobal->GetProperty("host_id",m_GessPktInfo.host_id);	
	}
	m_pCfg = pCfg;
	return 0;
}

/******************************************************************************
��������:��ȡЭ�鶨��ı��ĸ�ʽ��Ϣ
���ú���:�������ص�
�������:PacketInfo & stInfo ���ĸ�ʽ��Ϣ
        eLengthType �����ֶ����� ����/10�����ַ���/16�����ַ���
		nLengthBytes ��Ϣ�������ֶεĳ���,Ϊ����ʱֻ֧�� 1 2 4�ֽ�
		nLengthPos �����ֶ���ʼλ��
		blLenIncludeHeader �����Ƿ񺬱���ͷ
		nFixHeadLen  �������ֶ�ָʾ�ĳ�����,���Ĺ̶����ֳ���
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CProcessInterfaceF2S::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltCharactersDec;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = BROADCAST_LENGTH_BYTES;
	stInfo.blLenIncludeHeader = false;
	stInfo.nFixHeadLen = stInfo.nLengthPos + stInfo.nLengthBytes;
}

/******************************************************************************
��������:Э�鱨�Ĵ�������Ҫ����,���ݱ��������ֽ���ֱ�Ӵ����ת��
���ú���:�������ص�
��������:OnRecvPacket,�ϴ�����
�������:char * pData���ջ���, size_t nSize�����С
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
int CProcessInterfaceF2S::OnPacket(char * pData, size_t nSize)
{
	CBroadcastPacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csF2S.Lock();
	m_uiCountNoAlive = 0;
	m_csF2S.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();
	if (sCmdID == "Hello")
	{
		//CRLog(E_PROINFO,"%s",GessPacket.Print().c_str());
		return OnHello(GessPacket);
	}
	else if(sCmdID=="RiskBroadCastConnectTest")
	{
		//CRLog(E_PROINFO,"%s",GessPacket.Print().c_str());
		return OnHello(GessPacket);
	}
	else if(sCmdID=="ConnectTest")
	{
		return OnHello(GessPacket);
	}
	//if (!IsLogin())
	//	return -1;

	return 0;
	//CRLog(E_PROINFO,GessPacket.Print().c_str());

	std::string sKey = GessPacket.RouteKey();
	OnRecvPacket(sKey,GessPacket);
	return 0;
}

// ������˽��յ����Ӻ�ص�
int CProcessInterfaceF2S::OnAccept()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"F2S OnAccept socket (%d) %s:%d",SocketID(),sPeerIp.c_str(),nPeerPort);
	//CreateTimer(m_GessPktInfo.ulIdleInterval);
	return 0;
}		

/******************************************************************************
��������:socket�����жϺ���֪ͨ,�ɸ���Э��Ҫ����д���
���ú���:ͨѶ����������ص�
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CProcessInterfaceF2S::OnClose()
{
	//m_blIsLogin = false;
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"F2S Long Connection Close socket (%d) %s:%d",SocketID(),sPeerIp.c_str(),nPeerPort);

	//DestroyTimer();
	return;
}

//�����ṩ����Ҫ�ӿں���,��ͨѶ���������ͱ���ʱ����
int CProcessInterfaceF2S::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		//if (!IsLogin())
		//	return -1;

		CBroadcastPacket & pkt = dynamic_cast<CBroadcastPacket&>(SendGessPacket);

		unsigned int  nLen = 0;
		const char* pcBuf = pkt.Encode(nLen);
		
		string sLocalIp,sPeerIp;
		int nLocalPort,nPeerPort;
		GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
		CRLog(E_PROINFO,"F2S(%s:%d) %s",sPeerIp.c_str(),nPeerPort,pcBuf);
		
		//m_csF2S.Lock();
		//int nSend = SendData(pcBuf,nLen);
		int nSend = CAppProcess::SendPacket(SendGessPacket);
		//m_csF2S.Unlock();

		if (nSend < 0)
		{
			//CRLog(E_ERROR,"%s","SendData err");
			return -1;
		}
		return 0;
	}
	catch(std::bad_cast)
	{
		CRLog(E_ERROR,"%s","packet error!");
		return -1;
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
/*
int CProcessInterfaceF2S::OnSend(int nSize)
{
	return 0;
}
*/
//�����¼����
//int CProcessInterfaceF2S::OnLogin(CBroadcastPacket & GessPacket)
//{
//	//���Ӧ���Ĳ���״̬
//	string sNodeID,sPassword;
//	GessPacket.GetParameterVal(GESS_NODE_ID,sNodeID);
//	GessPacket.GetParameterVal("password",sPassword);
//
//	string sCfgPwd("");
//	CConfig* pNode = m_pCfg->GetProperties(GESS_NODE_ID);
//	if (pNode != 0)
//	{
//		pNode->GetProperty("password",sCfgPwd);
//		if (sCfgPwd == sCfgPwd)
//			m_blIsLogin = true;
//		else
//			m_blIsLogin = false;
//	}
//	else
//	{
//		m_blIsLogin = true;
//	}
//
//	if (m_blIsLogin)
//		CRLog(E_PROINFO,"%s","TS��֤�ɹ�");
//	else
//		CRLog(E_PROINFO,"TS��֤ʧ��:%s,%s",sNodeID,sPassword);
//
//	return 0;
//}

//������̬��ⱨ��
int CProcessInterfaceF2S::OnHello(CBroadcastPacket & GessPacket)
{
	//���Ӧ���Ĳ���״̬
	CBroadcastPacket RspPacket("ConnectTestRsp");
	
	//unsigned int  nLen = 0;
	//const char* pcBuf = RspPacket.Encode(nLen);	
	//m_csF2S.Lock();
	//int nSend = SendData(pcBuf,nLen);
	int nSend = CAppProcess::SendPacket(RspPacket);
	//m_csF2S.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0;
 
}

//����ʱ����ʱ
int CProcessInterfaceF2S::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csF2S.Lock();
	if (m_uiCountNoAlive >= 1)
	{//������·������ʱ��δ�յ����ģ���������
		//if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		//{//�ط��������������涨������׼���ر�
		//	nRtn = -1;
		//	ReqClose();
		//}
		//else
		//{//���ö�ʱ�����
		//	ulTmSpan = m_GessPktInfo.ulHelloReSend;
		//	m_uiCountSended++;
			if (0 > SendHello())
				nRtn = -1;
		//}
	}
	else
	{
		m_uiCountSended = 0;
		ulTmSpan = m_GessPktInfo.ulIdleInterval;
	}
	m_uiCountNoAlive++;
	m_csF2S.Unlock();
	return nRtn;
}

//��������
int CProcessInterfaceF2S::SendHello()
{
	CBroadcastPacket pkt("ConnectTest");

	//unsigned int nLen = 0;
	//const char* pcBuf = pkt.Encode(nLen);

	//m_csF2S.Lock();
	//int nSend = SendData( pcBuf, nLen);
	int nSend =CAppProcess::SendPacket(pkt);
	//m_csF2S.Unlock();

	if (nSend < 0)
		return -1;

	return 0;
}



int CProcessInterfaceF2S::GetNmKey(string& sKey)
{
	sKey = "F2�ӿڷ��������.";
	int nSockeID = static_cast<int>( SocketID());
	if (INVALID_SOCKET != nSockeID)
	{
		sKey += ToString<int>(nSockeID);
	}
	else
	{
		srand(static_cast<unsigned int>(time(0)));
		int RANGE_MIN = 1;
		int RANGE_MAX = 99;
		int nRandom = rand() % (RANGE_MAX - RANGE_MIN) + RANGE_MIN;
		sKey += ToString<int>(nRandom);
	}

	return 0;
}