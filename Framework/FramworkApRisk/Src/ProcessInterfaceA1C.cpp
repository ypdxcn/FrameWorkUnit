#include "ProcessInterfaceA1C.h"
#include "Logger.h"
#include "strutils.h"
using namespace strutils;

CProcessInterfaceA1C::GessPktInfo CProcessInterfaceA1C::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
bool CProcessInterfaceA1C::m_blGessPktInfoInited = false;

CProcessInterfaceA1C::CProcessInterfaceA1C()
:m_pCfg(0)
,m_blIsLogin(false)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceA1C::~CProcessInterfaceA1C(void)
{
}

int CProcessInterfaceA1C::Init(CConfig * pCfg)
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
函数描述:获取协议定义的报文格式信息
调用函数:父类对象回调
输出参数:PacketInfo & stInfo 报文格式信息
        eLengthType 长度字段类型 整型/10进制字符串/16进制字符串
		nLengthBytes 消息包长度字段的长度,为整数时只支持 1 2 4字节
		nLengthPos 长度字段起始位置
		blLenIncludeHeader 长度是否含报文头
		nFixHeadLen  除长度字段指示的长度外,报文固定部分长度
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void CProcessInterfaceA1C::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltCharactersDec;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = BROADCAST_LENGTH_BYTES;
	stInfo.blLenIncludeHeader = false;
	stInfo.nFixHeadLen = stInfo.nLengthPos + stInfo.nLengthBytes;
}

/******************************************************************************
函数描述:协议报文处理最主要函数,根据报文命令字进行直接处理或转发
调用函数:父类对象回调
被调函数:OnRecvPacket,上传报文
输入参数:char * pData接收缓存, size_t nSize缓存大小
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CProcessInterfaceA1C::OnPacket(char * pData, size_t nSize)
{
	CBroadcastPacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csA1C.Lock();
	m_uiCountNoAlive = 0;
	m_csA1C.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();

	bool blLog = false;
	string::size_type nPos = sCmdID.find("Quotation");
	if (nPos == string::npos)
	{
		blLog = true;
	}

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
		if (blLog)
		{
			CRLog(E_PROINFO,"A1C %s",GessPacket.Print().c_str());
		}
		OnRecvPacket(GessPacket);
	}
	return 0;
}

/******************************************************************************
函数描述:socket连接成功后，作为客户端被通知,一般用于触发认证报文发送
调用函数:通讯处理器对象回调
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CProcessInterfaceA1C::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"A1C OnConnect socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	SendLogin();
	//CreateTimer(m_GessPktInfo.ulIdleInterval);
	return 0;
}


int CProcessInterfaceA1C::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csA1C.Lock();
	if (m_uiCountNoAlive >= 1)
	{//超过链路最大空闲时间未收到报文，则发送心跳
		//if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		//{//重发心跳次数超过规定次数则准备关闭
		//	nRtn = -1;
		//	ReqClose();
		//}
		//else
		//{//重置定时器间隔
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
	m_csA1C.Unlock();
	return nRtn;
}

/******************************************************************************
函数描述:socket连接中断后则被通知,可根据协议要求进行处理
调用函数:父类对象回调
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void CProcessInterfaceA1C::OnClose()
{
	m_blIsLogin = false;
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"A1C OnClose socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	//DestroyTimer();
	return;
}

//对外提供的主要接口函数,供通讯处理器发送报文时调用
int CProcessInterfaceA1C::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		if (!IsLogin())
			return -1;

		//CBroadcastPacket & pkt = dynamic_cast<CBroadcastPacket&>(SendGessPacket);
		//
		//unsigned int  nLen = 0;
		//const char* pcBuf = pkt.Encode(nLen);
		//		
		int nRtn = 0;
		//m_csA1C.Lock();
		//int nSend =CAppProcess::SendData(pcBuf,nLen);
		int nSend =CAppProcess::SendPacket(SendGessPacket);
		//m_csA1C.Unlock();
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
/*
int CProcessInterfaceA1C::OnSend(int nSize)
{
	return 0;
}
*/
//接口间心跳报文
int CProcessInterfaceA1C::SendHello()
{
	CBroadcastPacket pkt("ConnectTest");

	//unsigned int nLen = 0;
	//const char* pcBuf = pkt.Encode(nLen);

	//m_csA1C.Lock();
	//int nSend = SendData( pcBuf, nLen);
	int nSend = CAppProcess::SendPacket(pkt);
	//m_csA1C.Unlock();

	if (nSend < 0)
		return -1;

	return 0;
}

int CProcessInterfaceA1C::OnHello(CBroadcastPacket & GessPacket)
{
	CBroadcastPacket pkt("ConnectTestRsp");

	//unsigned int nLen = 0;
	//const char* pcBuf = pkt.Encode(nLen);

	//m_csA1C.Lock();
	//int nSend = SendData( pcBuf, nLen);
	int nSend =CAppProcess::SendPacket(pkt);
	//m_csA1C.Unlock();

	if (nSend < 0)
		return -1;

	return 0;
}

//连接成功后发送的第一个登陆报文
int CProcessInterfaceA1C::SendLogin()
{
	CBroadcastPacket pkt;//("Subscriber");

	srand(static_cast<unsigned int>(time(0)));
	int RANGE_MIN = 0;
    int RANGE_MAX = 10000;
    int nKey = rand() % RANGE_MAX;

	pkt.AddParameter("term_type","12");
	pkt.AddParameter("user_key",ToString(nKey));
	pkt.AddParameter("user_type",m_GessPktInfo.user_type.c_str());
	pkt.AddParameter("user_id",m_GessPktInfo.user_id.c_str());
	pkt.AddParameter("user_pwd",m_GessPktInfo.user_pwd.c_str());
	pkt.AddParameter("branch_id",m_GessPktInfo.branch_id.c_str());
	pkt.AddParameter("again_flag","1");

	//unsigned int nLen = 0;	
	//const char* pcBuf = pkt.Encode(nLen);

	//m_csA1C.Lock();
	//int nSend = SendData( pcBuf, nLen);
	int nSend=CAppProcess::SendPacket(pkt);
	//m_csA1C.Unlock();

	CRLog(E_PROINFO,"A1C 与服务器连接成功,发送认证报文,%s",pkt.Print().c_str());

	//IncreaseStatics(OfferDownOutSystem);
	if (nSend < 0)
		return -1;

	return 0;
}

int CProcessInterfaceA1C::OnRspLogin(CBroadcastPacket & GessPacket)
{
	//检查应答报文才置状态
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

	CRLog(E_PROINFO,"TS认证应答:%s,%s",szRsp,szRspMsg);
	return 0;
}

int CProcessInterfaceA1C::GetNmKey(string& sKey)
{
	sKey = "A1接口客户端连接";
	return 0;
}