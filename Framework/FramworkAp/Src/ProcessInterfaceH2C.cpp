#include "ProcessInterfaceH2C.h"
#include "Logger.h"
#include "strutils.h"
using namespace strutils;

CProcessInterfaceH2C::GessPktInfo CProcessInterfaceH2C::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
int CProcessInterfaceH2C::m_blGessPktInfoInited = false;

CProcessInterfaceH2C::CProcessInterfaceH2C()
:m_pCfg(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceH2C::~CProcessInterfaceH2C(void)
{
}

int CProcessInterfaceH2C::Init(CConfig * pCfg)
{
	CTcpAppProcessClient::Init(pCfg);
	if (!m_blGessPktInfoInited)
	{
		m_blGessPktInfoInited = true;
		

		if (0 != pCfg)
		{
			string sLoginFlag;
			if (0 == pCfg->GetProperty("login",sLoginFlag))
			{
				if (1 == FromString<int>(sLoginFlag))
					m_GessPktInfo.blNeedLogin = true;
			}

			string sVal;
			if (0 == pCfg->GetProperty("max_idle",sVal))
			{
				m_GessPktInfo.ulIdleInterval = strutils::FromString<unsigned long>(sVal);
				if (m_GessPktInfo.ulIdleInterval > 300 || m_GessPktInfo.ulIdleInterval < 2)
					m_GessPktInfo.ulIdleInterval = DEFAULT_IDLE_TIMEOUT;
			}

			if (0 == pCfg->GetProperty("resend_interval",sVal))
			{
				m_GessPktInfo.ulIntervalReSend = strutils::FromString<unsigned long>(sVal);
				if (m_GessPktInfo.ulIntervalReSend > 60 || m_GessPktInfo.ulIntervalReSend < 2)
					m_GessPktInfo.ulIntervalReSend = DEFAULT_HELLO_RESEND_INTERVAL;
			}

			if (0 == pCfg->GetProperty("resend_count",sVal))
			{
				m_GessPktInfo.ulHelloReSend = strutils::FromString<unsigned long>(sVal);
				if (m_GessPktInfo.ulHelloReSend > 30 || m_GessPktInfo.ulHelloReSend < 1)
					m_GessPktInfo.ulHelloReSend = DEFAULT_HELLO_RESEND_COUNT;
			}
			CRLog(E_DEBUG, "MC:max_idle:%u, resend_interval:%u, resend_count:%u",m_GessPktInfo.ulIdleInterval, m_GessPktInfo.ulIntervalReSend, m_GessPktInfo.ulHelloReSend);


			pCfg->GetProperty("user_type",m_GessPktInfo.user_type);
			pCfg->GetProperty("user_id",m_GessPktInfo.user_id);
			pCfg->GetProperty("branch_id",m_GessPktInfo.branch_id);
			pCfg->GetProperty("user_pwd",m_GessPktInfo.user_pwd);
		}
	}

	m_pCfg = pCfg;
	m_uiCountNoAlive = 0;
	m_uiCountSended = 0;
	return 0;
}

/******************************************************************************
��������:Э�鱨�Ĵ���ص�����,��ȡЭ�鶨��ı��ĸ�ʽ��Ϣ
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
void CProcessInterfaceH2C::GetPacketInfo(PacketInfo & stInfo)
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
��������:��װ��ӿں���,�ϴ�����
�������:char * pData���ջ���, size_t nSize�����С
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
int CProcessInterfaceH2C::OnPacket(char * pData, size_t nSize)
{
	CBroadcastPacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csH2C.Lock();
	m_uiCountNoAlive = 0;
	m_csH2C.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();
	if (sCmdID == "ConnectTest")
	{
		return OnHello(GessPacket);
	}
	else if (sCmdID == "ConnectTestRsp")
	{
		return 0;
	}
	else
	{
		//CRLog(E_PROINFO,GessPacket.Print().c_str());
		OnRecvPacket(GessPacket);
	}
	return 0;
}


int CProcessInterfaceH2C::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"H2C OnConnect socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	CreateTimer(m_GessPktInfo.ulIdleInterval);
	return 0;
}

//����ʱ����ʱ
int CProcessInterfaceH2C::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csH2C.Lock();
	if (m_uiCountNoAlive >= 1)
	{//������·������ʱ��δ�յ����ģ���������
		//if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		//{//�ط��������������涨������׼���ر�
		//	nRtn = -1;
		//	CRLog(E_PROINFO,"H2%s(%u-%u)","������ʱ!",m_uiCountNoAlive,m_uiCountSended);
		//	ReqClose();
		//}
		//else
		//{//���ö�ʱ�����
			ulTmSpan = m_GessPktInfo.ulIntervalReSend;
			m_uiCountSended++;

			//if (m_uiCountSended > 1)
			//	CRLog(E_PROINFO,"H2��������,��%d��!",m_uiCountSended);
			
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
	m_csH2C.Unlock();
	return nRtn;
}

/******************************************************************************
��������:socket�����жϺ���֪ͨ,�ɸ���Э��Ҫ����д���
���ú���:ͨѶ����������ص�
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CProcessInterfaceH2C::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"H2C OnClose socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	DestroyTimer();
	return;
}

//�ӿڼ���������
int CProcessInterfaceH2C::SendHello()
{
	CBroadcastPacket pkt("Hello");
	CAppProcess::SendPacket(pkt);
	return 0;
}

int CProcessInterfaceH2C::OnHello(CBroadcastPacket& pktHello)
{
	CBroadcastPacket pkt("ConnectTestRsp");
	CAppProcess::SendPacket(pkt);
	return 0;
}


int CProcessInterfaceH2C::GetNmKey(string& sKey)
{
	sKey = "H2�ӿڿͻ�������";
	return 0;
}
