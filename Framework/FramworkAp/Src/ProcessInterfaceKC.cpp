#include "ProcessInterfaceKC.h"
#include "IpcPacket.h"
#include "Logger.h"
#include "ApConstant.h"
using namespace ApConst;

CProcessInterfaceKC::GessPktInfo CProcessInterfaceKC::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
int CProcessInterfaceKC::m_blGessPktInfoInited = false;

CProcessInterfaceKC::CProcessInterfaceKC()
:m_pCfg(0)
,m_uiPacketSnd(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceKC::~CProcessInterfaceKC(void)
{
}

int CProcessInterfaceKC::Init(CConfig * pCfg)
{
	CTcpAppProcessClient::Init(pCfg);
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
void CProcessInterfaceKC::GetPacketInfo(PacketInfo & stInfo)
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
int CProcessInterfaceKC::OnPacket(char * pData, size_t nSize)
{
	CIpcPacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csKC.Lock();
	m_uiCountNoAlive = 0;
	m_csKC.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();
	if (sCmdID == "Hello")
	{		
		return OnHello(GessPacket);
	}
	else if (sCmdID == "HelloRsp")
	{
		//CRLog(E_PROINFO,"P3C�յ�����Ӧ��:%s",GessPacket.Print().c_str());
		return 0;
	}

	CRLog(E_PROINFO,"Recv:%s",GessPacket.Print().c_str());

	OnRecvPacket(GessPacket);
	return 0;
}

int CProcessInterfaceKC::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"KC OnConnect socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	//CRLog(E_PROINFO,"P3C OnConnect and CreateTimer");
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
void CProcessInterfaceKC::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"KC OnClose socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	//DestroyTimer();
}

//����ʱ����ʱ
int CProcessInterfaceKC::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csKC.Lock();
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
				CRLog(E_PROINFO,"P3C��������,��%d��!",m_uiCountSended);

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
	m_csKC.Unlock();
	return nRtn;
}

//��������
int CProcessInterfaceKC::SendHello()
{
	CIpcPacket pkt("Hello");
	CAppProcess::SendPacket(pkt);
	return 0;
}

//��������Ӧ��
int CProcessInterfaceKC::OnHello(CIpcPacket& pktHello)
{
	CIpcPacket pkt("HelloRsp");
	CAppProcess::SendPacket(pkt);
	return 0;
}


int CProcessInterfaceKC::GetNmKey(string& sKey)
{
	sKey = "K�ӿڿͻ�������";
	return 0;
}
