#include "ProcessInterfaceKS.h"
#include "IpcPacket.h"
#include "Logger.h"
#include "ApConstant.h"
using namespace ApConst;

CProcessInterfaceKS::GessPktInfo CProcessInterfaceKS::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
int CProcessInterfaceKS::m_blGessPktInfoInited = false;

CProcessInterfaceKS::CProcessInterfaceKS()
:m_pCfg(0)
,m_uiPacketRev(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceKS::~CProcessInterfaceKS(void)
{
}

int CProcessInterfaceKS::Init(CConfig * pCfg)
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
void CProcessInterfaceKS::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltCharactersDec;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = IPC_LENGTH_BYTES;
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
int CProcessInterfaceKS::OnPacket(char * pData, size_t nSize)
{
	CIpcPacket GessPacket;
	GessPacket.Decode(pData, nSize);

	bool blLog = false;
	m_csKS.Lock();
	m_uiCountNoAlive = 0;
	m_uiPacketRev++;
	if (m_uiPacketRev % 200 == 0)
	{
		blLog = true;
		m_uiPacketRev = 0;
	}
	m_csKS.Unlock();

	if (blLog)
	{
		CRLog(E_PROINFO,"Recv:%s",GessPacket.Print().c_str());
	}

	std::string sCmdID = GessPacket.GetCmdID();
	if (sCmdID == "Hello")
	{
		//CRLog(E_PROINFO,"P3S�յ�����:%s",GessPacket.Print().c_str());
		return OnHello(GessPacket);
	}
	else if (sCmdID == "HelloRsp")
	{
		//CRLog(E_PROINFO,"P3S�յ�����Ӧ��:%s",GessPacket.Print().c_str());
		return 0;
	}


	std::string sKey = GessPacket.RouteKey();
	OnRecvPacket(sKey,GessPacket);
	return 0;
}

// ������˽��յ����Ӻ�ص�
int CProcessInterfaceKS::OnAccept()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"KS OnAccept socket(%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
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
void CProcessInterfaceKS::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"KS Long Connection Close socket(%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	return;
}


//����ʱ����ʱ
int CProcessInterfaceKS::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csKS.Lock();
	if (m_uiCountNoAlive >= 1)
	{//������·������ʱ��δ�յ����ģ���������
		if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		{//�ط��������������涨������׼���ر�
			nRtn = -1;
			CRLog(E_ERROR,"%s","������ʱ!");
			ReqClose();
		}
		else
		{//���ö�ʱ�����
			ulTmSpan = m_GessPktInfo.ulHelloReSend;
			m_uiCountSended++;

			if (m_uiCountSended > 1)
				CRLog(E_PROINFO,"P3S��������,��%d��!",m_uiCountSended);

			if (0 > SendHello())
				nRtn = -1;
		}
	}
	else
	{
		m_uiCountSended = 0;
		ulTmSpan = m_GessPktInfo.ulIdleInterval;
	}
	m_uiCountNoAlive++;
	m_csKS.Unlock();
	return nRtn;
}

//��������
int CProcessInterfaceKS::SendHello()
{
	CIpcPacket pkt("Hello");
	CAppProcess::SendPacket(pkt);
	return 0;
}

//��������Ӧ��
int CProcessInterfaceKS::OnHello(CIpcPacket& pktHello)
{
	CIpcPacket pkt("HelloRsp");
	CAppProcess::SendPacket(pkt);
	return 0;
}

int CProcessInterfaceKS::GetNmKey(string& sKey)
{
	sKey = "K�ӿڷ��������.";
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
		int nRandom = rand() * (RANGE_MAX - RANGE_MIN) / RAND_MAX + RANGE_MIN;
		sKey += ToString<int>(nRandom);
	}

	return 0;
}
