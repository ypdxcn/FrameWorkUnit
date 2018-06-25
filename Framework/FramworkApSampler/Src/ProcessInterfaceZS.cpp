#include "ProcessInterfaceZS.h"
#include "Logger.h"
#include "strutils.h"

CProcessInterfaceZS::GessPktInfo CProcessInterfaceZS::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
bool CProcessInterfaceZS::m_blGessPktInfoInited = false;

CProcessInterfaceZS::CProcessInterfaceZS()
:m_pCfg(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceZS::~CProcessInterfaceZS(void)
{
}

int CProcessInterfaceZS::Init(CConfig * pCfg)
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
void CProcessInterfaceZS::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltInterger;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = 4;
	stInfo.blLenIncludeHeader = true;
	stInfo.nFixHeadLen = 16;
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
int CProcessInterfaceZS::OnPacket(char * pData, size_t nSize)
{	
	CSamplerPacket oPacket;
	oPacket.Decode(pData, nSize);

	m_csZS.Lock();
	m_uiCountNoAlive = 0;
	m_csZS.Unlock();

	std::string sCmdID = oPacket.GetCmdID();
	if (YL_HELLO_RSP == strutils::FromString<unsigned long>(sCmdID))
	{
		
	}
	else if (YL_HELLO == strutils::FromString<unsigned long>(sCmdID))
	{
		return OnHello(oPacket);
	}
	else
	{
		//if (!IsLogin())
		//	return -1;

		// 
		std::string sKey = oPacket.RouteKey();
		OnRecvPacket(sKey,oPacket);
	}

	return 0;
}


// ������˽��յ����Ӻ�ص�
int CProcessInterfaceZS::OnAccept()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"ZS OnAccept socket (%d) %s:%d",SocketID(),sPeerIp.c_str(),nPeerPort);
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
void CProcessInterfaceZS::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"ZS Long Connection Close socket (%d) %s:%d",SocketID(),sPeerIp.c_str(),nPeerPort);

	//DestroyTimer();
	return;
}

//�����ṩ����Ҫ�ӿں���,��ͨѶ���������ͱ���ʱ����
int CProcessInterfaceZS::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		//if (!IsLogin())
		//	return -1;

		CSamplerPacket & pkt = dynamic_cast<CSamplerPacket&>(SendGessPacket);

		unsigned int  nLen = 0;
		const char* pcBuf = pkt.Encode(nLen);
		
		//CRLog(E_PROINFO,"F1S %s",pcBuf);
		
		int nRtn = 0;
		m_csZS.Lock();
		int nSend = SendData(pcBuf,nLen);
		m_csZS.Unlock();
		if (nSend < 0)
		{
			//CRLog(E_ERROR,"F1S %s","SendData err");
			nRtn = -1;
		}
		return nRtn;
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

int CProcessInterfaceZS::OnSend(int nSize)
{

	return 0;
}

//����ʱ����ʱ
int CProcessInterfaceZS::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csZS.Lock();
	if (m_uiCountNoAlive >= 1)
	{//������·������ʱ��δ�յ����ģ���������
		if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		{//�ط��������������涨������׼���ر�
			nRtn = -1;
			ReqClose();
		}
		else
		{//���ö�ʱ�����
			ulTmSpan = m_GessPktInfo.ulHelloReSend;
			m_uiCountSended++;
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
	m_csZS.Unlock();
	return nRtn;
}

//��������
int CProcessInterfaceZS::SendHello()
{
	CSamplerPacket oPacketHello(YL_HELLO);
	CMessage &  msg = oPacketHello.GetMsg();

	//msg.SetField(MSG_CMD_ID,static_cast<unsigned long>(YL_HELLO_RSP));
	msg.SetField(MSG_SEQ_ID,static_cast<unsigned long>(0));
	msg.SetField(MSG_NODE_ID,static_cast<unsigned long>(0));
	
	unsigned int  nLen = 0;
	const char* pcBuf = oPacketHello.Encode(nLen);	
	m_csZS.Lock();
	int nSend = SendData(pcBuf,nLen);
	m_csZS.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0;

}

//������̬��ⱨ��
int CProcessInterfaceZS::OnHello(CSamplerPacket & oPacket)
{
    CMessage &  msgReq = oPacket.GetMsg();
	unsigned long uiSeqID = 0;
	msgReq.GetField(MSG_SEQ_ID,uiSeqID);
	unsigned long uiNodeID = 0;
	msgReq.GetField(MSG_NODE_ID,uiNodeID);

	CSamplerPacket oPacketRsp(YL_HELLO_RSP);
	CMessage &  msgRsp = oPacket.GetMsg();

	//msgRsp.SetField(MSG_CMD_ID,static_cast<unsigned long>(YL_HELLO_RSP));
	msgRsp.SetField(MSG_SEQ_ID,uiSeqID);
	msgRsp.SetField(MSG_NODE_ID,uiNodeID);

	unsigned int  nLen = 0;
	const char* pcBuf = oPacketRsp.Encode(nLen);	
	m_csZS.Lock();
	int nSend = SendData(pcBuf,nLen);
	m_csZS.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0; 
}


int CProcessInterfaceZS::GetNmKey(string& sKey)
{
	sKey = "ZS�ӿڷ��������.";
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