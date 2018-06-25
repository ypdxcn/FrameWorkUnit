#include "ProcessInterfaceH1C.h"
#include "Logger.h"
#include "ApConstant.h"
using namespace ApConst;

CProcessInterfaceH1C::GessPktInfo CProcessInterfaceH1C::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
int CProcessInterfaceH1C::m_blGessPktInfoInited = false;

CProcessInterfaceH1C::CProcessInterfaceH1C()
:m_pCfg(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceH1C::~CProcessInterfaceH1C(void)
{
}

int CProcessInterfaceH1C::Init(CConfig * pCfg)
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


			CConfig* pCfgGlobal = pCfg->GetCfgGlobal();
			pCfgGlobal->GetProperty("node_type",m_GessPktInfo.node_type);
			pCfgGlobal->GetProperty("node_id",m_GessPktInfo.node_id);
			pCfgGlobal->GetProperty("node_name",m_GessPktInfo.node_name);
			pCfgGlobal->GetProperty("host_id",m_GessPktInfo.host_id);			
		}
	}

	m_pCfg = pCfg;
	m_uiCountNoAlive = 0;
	m_uiCountSended = 0;
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
void CProcessInterfaceH1C::GetPacketInfo(PacketInfo & stInfo)
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
int CProcessInterfaceH1C::OnPacket(char * pData, size_t nSize)
{
	CTradePacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csH1C.Lock();
	m_uiCountNoAlive = 0;
	m_csH1C.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();
	if (sCmdID == "1902")
	{
		return OnHello(GessPacket);
	}
	else if (sCmdID == "1926")
	{
		//
		return 0;
	}

	CRLog(E_PROINFO,"H1C %s",GessPacket.Print().c_str());
	OnRecvPacket(GessPacket);

	return 0;
}

int CProcessInterfaceH1C::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"H1C OnConnect socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);

	CreateTimer(m_GessPktInfo.ulIdleInterval);
	SendNodeInfo();
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
void CProcessInterfaceH1C::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"H1C OnClose socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	DestroyTimer();
}

//����ʱ����ʱ
int CProcessInterfaceH1C::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csH1C.Lock();
	if (m_uiCountNoAlive >= 1)
	{//������·������ʱ��δ�յ����ģ���������
		//if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		//{//�ط��������������涨������׼���ر�
		//	nRtn = -1;
		//	CRLog(E_PROINFO,"H1%s(%u-%u)","������ʱ!",m_uiCountNoAlive,m_uiCountSended);
		//	ReqClose();
		//}
		//else
		//{//���ö�ʱ�����
			ulTmSpan = m_GessPktInfo.ulIntervalReSend;
			m_uiCountSended++;

			//if (m_uiCountSended > 1)
			//	CRLog(E_PROINFO,"H1��������,��%d��!",m_uiCountSended);
			
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
	m_csH1C.Unlock();
	return nRtn;
}

//��������
int CProcessInterfaceH1C::SendHello()
{
	HEADER_REQ stHeaderReq;

	CTradePacket pktHello;
	memset(&stHeaderReq,0x00,sizeof(HEADER_REQ));
	sprintf(stHeaderReq.seq_no,"%s","000000000");
	sprintf(stHeaderReq.msg_type,"%s","1");
	sprintf(stHeaderReq.exch_code,"%s","1902");
	sprintf(stHeaderReq.msg_flag,"%s","1");
	sprintf(stHeaderReq.term_type,"%s","11");
	sprintf(stHeaderReq.user_type,"%s","1");
	sprintf(stHeaderReq.user_id,"%s",m_GessPktInfo.node_id.c_str());
	pktHello.AddParameter("rsp_msg","ok");
	pktHello.AddParameter("oper_flag","1");
	pktHello.SetHeader(stHeaderReq);
	
	CAppProcess::SendPacket(pktHello);
	return 0;
}

//�յ�Hello����
int CProcessInterfaceH1C::OnHello(CTradePacket& GessPacket)
{
	if (HEAD_RSP == GessPacket.PktType())
		return 0;

	//���������Ӧ��
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

	CAppProcess::SendPacket(pktRsp);
	return 0;
}

int CProcessInterfaceH1C::SendNodeInfo()
{
	HEADER_REQ stHeaderReq;

	CTradePacket pktNodeInfo;
	memset(&stHeaderReq,0x00,sizeof(stHeaderReq));
	sprintf(stHeaderReq.seq_no,"%s","000000000");
	sprintf(stHeaderReq.msg_type,"%s","2");
	sprintf(stHeaderReq.exch_code,"%s","1926");
	sprintf(stHeaderReq.msg_flag,"%s","1");
	sprintf(stHeaderReq.term_type,"%s","12");
	sprintf(stHeaderReq.user_type,"%s","1");
	sprintf(stHeaderReq.user_id,"%s",m_GessPktInfo.node_id.c_str());
	//sprintf(stHeaderReq.c_teller_id1,"%s","");
	//sprintf(stHeaderReq.c_teller_id2,"%s","");
	
	pktNodeInfo.SetHeader(stHeaderReq);
	pktNodeInfo.AddParameter("node_id",m_GessPktInfo.node_id);
	pktNodeInfo.AddParameter("host_id",m_GessPktInfo.host_id);
	pktNodeInfo.AddParameter("node_name",m_GessPktInfo.node_name);
	
	CRLog(E_PROINFO,"���Ӽ�ط������ɹ�,���ͽڵ���Ϣ����,%s",pktNodeInfo.Print().c_str());
	CAppProcess::SendPacket(pktNodeInfo);
	return 0;
}

int CProcessInterfaceH1C::GetNmKey(string& sKey)
{
	sKey = "H1�ӿڿͻ�������";
	return 0;
}
