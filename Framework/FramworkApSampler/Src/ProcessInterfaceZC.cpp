#include "ProcessInterfaceZC.h"
#include "Logger.h"
#include "strutils.h"

using namespace strutils;

CProcessInterfaceZC::GessPktInfo CProcessInterfaceZC::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false,
	0
};
bool CProcessInterfaceZC::m_blGessPktInfoInited = false;

CProcessInterfaceZC::CProcessInterfaceZC()
:m_pCfg(0)
,m_blIsLogin(false)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceZC::~CProcessInterfaceZC(void)
{
}

int CProcessInterfaceZC::Init(CConfig * pCfg)
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
		
			pCfg->GetProperty("user_id",m_GessPktInfo.sUserName);
			pCfg->GetProperty("user_pwd",m_GessPktInfo.sPassword);
			if (0 != pCfg->GetProperty("node_id",m_GessPktInfo.node_id))
			{
				CConfig* p = pCfg->GetCfgGlobal();
				p->GetProperty("node_id",m_GessPktInfo.node_id);
			}
		}
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
void CProcessInterfaceZC::GetPacketInfo(PacketInfo & stInfo)
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
int CProcessInterfaceZC::OnPacket(char * pData, size_t nSize)
{
	CSamplerPacket oPacket;
	oPacket.Decode(pData, nSize);

	m_csZC.Lock();
	m_uiCountNoAlive = 0;
	m_csZC.Unlock();

	std::string sCmdID = oPacket.GetCmdID();
	if (strutils::ToHexString<unsigned long>(YL_HELLO_RSP) == sCmdID)
	{
		
	}
	else if (strutils::ToHexString<unsigned long>(YL_HELLO) == sCmdID)
	{
		return OnHello(oPacket);
	}
	else if (strutils::ToHexString<unsigned long>(YL_LOGIN_RSP) == sCmdID)
	{
		OnLoginRsp(oPacket);
		OnRecvPacket(oPacket);
	}
	else
	{
		OnRecvPacket(oPacket);
	}
	return 0;
}

/******************************************************************************
��������:socket���ӳɹ�����Ϊ�ͻ��˱�֪ͨ,һ�����ڴ�����֤���ķ���
���ú���:ͨѶ����������ص�
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
int CProcessInterfaceZC::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"ZC OnConnect socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	//CreateTimer(m_GessPktInfo.ulIdleInterval);

	CSamplerPacket oPacketLogin(YL_LOGIN);
	CMessage &  msg = oPacketLogin.GetMsg();
	msg.SetField(MSG_SEQ_ID,++m_GessPktInfo.ulSeqNo);
	msg.SetField(MSG_NODE_ID,m_GessPktInfo.node_id);
	msg.SetField(MSG_LOGIN_ID, m_GessPktInfo.sUserName);
	msg.SetField(MSG_LOGIN_PWD, m_GessPktInfo.sPassword);
	unsigned long ulPwdMode = 0;
	msg.SetField(MSG_LOGIN_PWD_ENC,ulPwdMode);

	CRLog(E_PROINFO,"Login:MSG_SEQ_ID=%u,MSG_NODE_ID=%s,MSG_LOGIN_ID=%s,MSG_LOGIN_PWD=%s,MSG_LOGIN_PWD_ENC=%u",m_GessPktInfo.ulSeqNo,m_GessPktInfo.node_id.c_str(),m_GessPktInfo.sUserName.c_str(),m_GessPktInfo.sPassword.c_str(),ulPwdMode);

	unsigned int  nLen = 0;
	const char* pcBuf = oPacketLogin.Encode(nLen);
	m_csZC.Lock();
	int nSend = SendData(pcBuf,nLen);
	m_csZC.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0;
}


int CProcessInterfaceZC::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csZC.Lock();
	if (m_uiCountNoAlive >= 1)
	{//������·������ʱ��δ�յ����ģ���������
		//if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		//{//�ط��������������涨������׼���ر�
		//	nRtn = -1;
		//	ReqClose();
		//}
		//else
		//{//���ö�ʱ�����
		//	ulTmSpan = m_GessPktInfo.ulIntervalReSend;
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
	m_csZC.Unlock();
	return nRtn;
}

/******************************************************************************
��������:socket�����жϺ���֪ͨ,�ɸ���Э��Ҫ����д���
���ú���:�������ص�
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CProcessInterfaceZC::OnClose()
{
	m_blIsLogin = false;
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"ZC OnClose socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	//DestroyTimer();
	return;
}

//�����ṩ����Ҫ�ӿں���,��ͨѶ���������ͱ���ʱ����
int CProcessInterfaceZC::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		//if (!IsLogin())
		//	return -1;

		CSamplerPacket & pkt = dynamic_cast<CSamplerPacket&>(SendGessPacket);
		
		unsigned int  nLen = 0;
		const char* pcBuf = pkt.Encode(nLen);
				
		int nRtn = 0;
		m_csZC.Lock();
		int nSend = SendData(pcBuf,nLen);
		m_csZC.Unlock();
		if (nSend < 0)
		{
			//CRLog(E_ERROR,"%s","SendData err");
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

int CProcessInterfaceZC::OnSend(int nSize)
{
	return 0;
}

//�ӿڼ���������
int CProcessInterfaceZC::SendHello()
{
	CSamplerPacket oPacketHello(YL_HELLO);
	CMessage &  msg = oPacketHello.GetMsg();

	//msg.SetField(MSG_CMD_ID,static_cast<unsigned long>(YL_HELLO_RSP));
	msg.SetField(MSG_SEQ_ID,static_cast<unsigned long>(0));
	//msg.SetField(MSG_SEQ_ID,++m_GessPktInfo.ulSeqNo);
	msg.SetField(MSG_NODE_ID,m_GessPktInfo.node_id);

	unsigned int  nLen = 0;
	const char* pcBuf = oPacketHello.Encode(nLen);	
	m_csZC.Lock();
	int nSend = SendData(pcBuf,nLen);
	m_csZC.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0;
}

int CProcessInterfaceZC::OnHello(CSamplerPacket & oPacket)
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
	m_csZC.Lock();
	int nSend = SendData(pcBuf,nLen);
	m_csZC.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0; 
}

int CProcessInterfaceZC::OnLoginRsp(CSamplerPacket & oPacket)
{
	CMessageImpl& msg = dynamic_cast<CMessageImpl&>(oPacket.GetMsg());

	unsigned long uiSeqNo = 0;
	msg.GetField(MSG_SEQ_ID,uiSeqNo);

	unsigned long uiNodeID = 0;
	msg.GetField(MSG_NODE_ID,uiNodeID);

	unsigned long uiRst = 0;
	msg.GetField(MSG_LOGIN_RESULT,uiRst);
	CRLog(E_PROINFO,"ZC OnRecvLoginRsp SeqNo:%u, NodeID:%u, Result:%u",uiSeqNo, uiNodeID, uiRst);

	if (0 != uiRst)
	{
		ReqClose();
		return -1;
	}

	CMessageImpl oMsgSub;
	oMsgSub.SetField(MSG_SEQ_ID,++m_GessPktInfo.ulSeqNo);
	oMsgSub.SetField(MSG_NODE_ID,m_GessPktInfo.node_id);

	CSamplerPacket oPktSub(oMsgSub,YL_SUBSCRIP);
	CRLog(E_PROINFO,"ZC Subscrib MSG_SEQ_ID=%u,MSG_NODE_ID=%s",m_GessPktInfo.ulSeqNo,m_GessPktInfo.node_id.c_str());

	unsigned int  nLen = 0;
	const char* pcBuf = oPktSub.Encode(nLen);	
	m_csZC.Lock();
	int nSend = SendData(pcBuf,nLen);
	m_csZC.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}
	return 0;
}

int CProcessInterfaceZC::GetNmKey(string& sKey)
{
	sKey = "ZC�ӿڿͻ�������";
	return 0;
}