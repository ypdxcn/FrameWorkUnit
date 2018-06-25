#include "ProcessInterfaceYC.h"
#include "Logger.h"
#include "strutils.h"
using namespace strutils;

CProcessInterfaceYC::GessPktInfo CProcessInterfaceYC::m_GessPktInfo = 
{
	120,//DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
bool CProcessInterfaceYC::m_blGessPktInfoInited = false;

CProcessInterfaceYC::CProcessInterfaceYC()
:m_pCfg(0)
,m_blIsLogin(false)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceYC::~CProcessInterfaceYC(void)
{
}

int CProcessInterfaceYC::Init(CConfig * pCfg)
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

			pCfg->GetProperty("user_type",m_GessPktInfo.user_type);
			pCfg->GetProperty("user_id",m_GessPktInfo.user_id);
			pCfg->GetProperty("branch_id",m_GessPktInfo.branch_id);
			pCfg->GetProperty("user_pwd",m_GessPktInfo.user_pwd);
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
void CProcessInterfaceYC::GetPacketInfo(PacketInfo & stInfo)
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
int CProcessInterfaceYC::OnPacket(char * pData, size_t nSize)
{
	CBroadcastPacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csYC.Lock();
	m_uiCountNoAlive = 0;
	m_csYC.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();

	if ( sCmdID == "RspLogin" )
	{
		OnRspLogin(GessPacket);
	}
	else if (sCmdID == "ConnectTest")
	{
		return OnHello(GessPacket);
	}
	else if (sCmdID == "ConnectTestRsp")
	{
		return 0;
	}
	else
	{
		CRLog(E_PROINFO,"YC %s",GessPacket.Print().c_str());

		OnRecvPacket(GessPacket);
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
int CProcessInterfaceYC::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"YC OnConnect socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	SendLogin();
	CreateTimer(m_GessPktInfo.ulIdleInterval);
	return 0;
}


int CProcessInterfaceYC::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csYC.Lock();
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
	m_csYC.Unlock();
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
void CProcessInterfaceYC::OnClose()
{
	m_blIsLogin = false;
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"YC OnClose socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	DestroyTimer();
	return;
}

//�����ṩ����Ҫ�ӿں���,��ͨѶ���������ͱ���ʱ����
int CProcessInterfaceYC::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		if (!IsLogin())
			return -1;

		CBroadcastPacket & pkt = dynamic_cast<CBroadcastPacket&>(SendGessPacket);
		
		unsigned int  nLen = 0;
		const char* pcBuf = pkt.Encode(nLen);
				
		int nRtn = 0;
		m_csYC.Lock();
		int nSend = SendData(pcBuf,nLen);
		m_csYC.Unlock();
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

int CProcessInterfaceYC::OnSend(int nSize)
{
	return 0;
}

//�ӿڼ���������
int CProcessInterfaceYC::SendHello()
{
	CBroadcastPacket pkt("ConnectTest");

	unsigned int nLen = 0;
	const char* pcBuf = pkt.Encode(nLen);

	m_csYC.Lock();
	int nSend = SendData( pcBuf, nLen);
	m_csYC.Unlock();

	if (nSend < 0)
		return -1;

	return 0;
}

int CProcessInterfaceYC::OnHello(CBroadcastPacket & GessPacket)
{
	CBroadcastPacket pkt("ConnectTestRsp");

	unsigned int nLen = 0;
	const char* pcBuf = pkt.Encode(nLen);

	m_csYC.Lock();
	int nSend = SendData( pcBuf, nLen);
	m_csYC.Unlock();

	if (nSend < 0)
		return -1;

	return 0;
}

//���ӳɹ����͵ĵ�һ����½����
int CProcessInterfaceYC::SendLogin()
{
	CBroadcastPacket pkt;//("Subscriber");

	srand(static_cast<unsigned int>(time(0)));
	int RANGE_MIN = 0;
    int RANGE_MAX = 10000;
    int nKey = rand() % RANGE_MAX;

	//pkt.AddParameter("term_type","12");
	pkt.AddParameter("user_key",ToString(nKey));
	pkt.AddParameter("user_type",m_GessPktInfo.user_type.c_str());
	pkt.AddParameter("user_id",m_GessPktInfo.user_id.c_str());
	//pkt.AddParameter("user_pwd",m_GessPktInfo.user_pwd.c_str());
	//pkt.AddParameter("branch_id",m_GessPktInfo.branch_id.c_str());
	pkt.AddParameter("again_flag","0");

	unsigned int nLen = 0;	
	const char* pcBuf = pkt.Encode(nLen);

	m_csYC.Lock();
	int nSend = SendData( pcBuf, nLen);
	m_csYC.Unlock();

	CRLog(E_PROINFO,"����������ӳɹ�,������֤����,%s",pkt.Print().c_str());

	//IncreaseStatics(OfferDownOutSystem);
	if (nSend < 0)
		return -1;

	return 0;
}

int CProcessInterfaceYC::OnRspLogin(CBroadcastPacket & GessPacket)
{
	//���Ӧ���Ĳ���״̬
	char szRsp[128],szRspMsg[128];
	memset(szRsp,0x00,128);
	memset(szRspMsg,0x00,128);
	GessPacket.GetParameterVal("RspCode",szRsp);
	GessPacket.GetParameterVal("RspMsg",szRspMsg);
	if (strcmp(szRsp,"0000") == 0)
	{
		m_blIsLogin = true;
	}
	else
	{
		m_blIsLogin = false;
		//RequestDisconnect();
	}

	CRLog(E_PROINFO,"TS��֤Ӧ��:%s,%s",szRsp,szRspMsg);
	return 0;
}

int CProcessInterfaceYC::GetNmKey(string& sKey)
{
	sKey = "A1�ӿڿͻ�������";
	return 0;
}