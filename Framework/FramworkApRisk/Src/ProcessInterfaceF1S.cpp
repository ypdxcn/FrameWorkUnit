#include "ProcessInterfaceF1S.h"
#include "Logger.h"

CProcessInterfaceF1S::GessPktInfo CProcessInterfaceF1S::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
bool CProcessInterfaceF1S::m_blGessPktInfoInited = false;

CProcessInterfaceF1S::CProcessInterfaceF1S()
:m_pCfg(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceF1S::~CProcessInterfaceF1S(void)
{
}

int CProcessInterfaceF1S::Init(CConfig * pCfg)
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
void CProcessInterfaceF1S::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltCharactersDec;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = LENGTH_BYTES;
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
int CProcessInterfaceF1S::OnPacket(char * pData, size_t nSize)
{
	CTradePacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csF1S.Lock();
	m_uiCountNoAlive = 0;
	m_csF1S.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();
	if(sCmdID=="1902")
	{
		//CRLog(E_PROINFO,"F1S %u %s",SocketID(), GessPacket.Print().c_str());
		return OnHello(GessPacket);
	}
	else
	{
		//if (!IsLogin())
		//	return -1;

		CRLog(E_PROINFO,"F1S %s",GessPacket.Print().c_str());

		//���أ�
		std::string sKey = GessPacket.RouteKey();
		OnRecvPacket(sKey,GessPacket);
	}

	return 0;
}


// ������˽��յ����Ӻ�ص�
int CProcessInterfaceF1S::OnAccept()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"F1S OnAccept socket (%d) %s:%d",SocketID(),sPeerIp.c_str(),nPeerPort);
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
void CProcessInterfaceF1S::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"F1S Long Connection Close socket (%d) %s:%d",SocketID(),sPeerIp.c_str(),nPeerPort);

	//DestroyTimer();
	return;
}

//�����ṩ����Ҫ�ӿں���,��ͨѶ���������ͱ���ʱ����
int CProcessInterfaceF1S::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		//if (!IsLogin())
		//	return -1;

		CTradePacket & pkt = dynamic_cast<CTradePacket&>(SendGessPacket);

		unsigned int  nLen = 0;
		const char* pcBuf = pkt.Encode(nLen);
		//
		CRLog(E_PROINFO,"F1S %s",pcBuf);
		//
		//int nRtn = 0;
		//m_csF1S.Lock();
		//int nSend = SendData(pcBuf,nLen);
		//m_csF1S.Unlock();
		//if (nSend < 0)
		//{
		//	//CRLog(E_ERROR,"F1S %s","SendData err");
		//	nRtn = -1;
		//}
		return CAppProcess::SendPacket(SendGessPacket);
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
int CProcessInterfaceF1S::OnSend(int nSize)
{

	return 0;
}
*/
//����ʱ����ʱ
int CProcessInterfaceF1S::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csF1S.Lock();
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
	m_csF1S.Unlock();
	return nRtn;
}

//��������
int CProcessInterfaceF1S::SendHello()
{
	HEADER_REQ stHeaderReq;

	CTradePacket pktHello;
	memset(&stHeaderReq,0x00,sizeof(HEADER_REQ));
	sprintf(stHeaderReq.seq_no,"%s","000000000");
	sprintf(stHeaderReq.msg_type,"%s","1");
	sprintf(stHeaderReq.exch_code,"%s","1902");
	sprintf(stHeaderReq.msg_flag,"%s","1");
	sprintf(stHeaderReq.term_type,"%s","12");
	sprintf(stHeaderReq.user_type,"%s","1");
	sprintf(stHeaderReq.user_id,"%s",m_GessPktInfo.node_id.c_str());
	pktHello.AddParameter("rsp_msg","ok");
	pktHello.AddParameter("oper_flag","1");
	pktHello.SetHeader(stHeaderReq);
	
	//unsigned int  nLen = 0;
	//const char* pcBuf = pktHello.Encode(nLen);	
	//m_csF1S.Lock();
	//int nSend = SendData(pcBuf,nLen);
	int nSend=CAppProcess::SendPacket(pktHello);
	//m_csF1S.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0;

}

//������̬��ⱨ��
int CProcessInterfaceF1S::OnHello(CTradePacket & GessPacket)
{
	if (HEAD_RSP == GessPacket.PktType())
		return 0;

	HEADER_REQ stHeaderReq;	
	HEADER_RSP stHeaderRsp;
	
	GessPacket.GetHeader(stHeaderReq);
	CTradePacket pktRsp;
	memset(&stHeaderRsp,0x00,sizeof(stHeaderRsp));
	sprintf(stHeaderRsp.seq_no,"%s",stHeaderReq.seq_no);
	sprintf(stHeaderRsp.msg_type,"%s",stHeaderReq.msg_type);
	sprintf(stHeaderRsp.exch_code,"%s",stHeaderReq.exch_code);
	sprintf(stHeaderRsp.msg_flag,"%s","2");
	sprintf(stHeaderRsp.term_type,"%s",stHeaderReq.term_type);
	sprintf(stHeaderRsp.user_type,"%s",stHeaderReq.user_type);
	sprintf(stHeaderRsp.user_id,"%s",stHeaderReq.user_id);
	sprintf(stHeaderRsp.area_code,"%s",stHeaderReq.area_code);
	sprintf(stHeaderRsp.branch_id,"%s",stHeaderReq.branch_id);
	sprintf(stHeaderRsp.rsp_code,"%s","00000000");
	
	pktRsp.AddParameter("rsp_msg","ok");
	pktRsp.AddParameter("oper_flag","1");
	pktRsp.SetHeader(stHeaderRsp);

	//unsigned int  nLen = 0;
	//const char* pcBuf = pktRsp.Encode(nLen);	
	//m_csF1S.Lock();
	//int nSend = SendData(pcBuf,nLen);
	int nSend =CAppProcess::SendPacket(pktRsp);
	//m_csF1S.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0; 
}


int CProcessInterfaceF1S::GetNmKey(string& sKey)
{
	sKey = "F1�ӿڷ��������.";
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