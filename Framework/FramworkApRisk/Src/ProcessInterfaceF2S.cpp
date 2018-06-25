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
void CProcessInterfaceF2S::GetPacketInfo(PacketInfo & stInfo)
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

// 作服务端接收到连接后回调
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
函数描述:socket连接中断后则被通知,可根据协议要求进行处理
调用函数:通讯处理器对象回调
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
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

//对外提供的主要接口函数,供通讯处理器发送报文时调用
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
//处理登录报文
//int CProcessInterfaceF2S::OnLogin(CBroadcastPacket & GessPacket)
//{
//	//检查应答报文才置状态
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
//		CRLog(E_PROINFO,"%s","TS认证成功");
//	else
//		CRLog(E_PROINFO,"TS认证失败:%s,%s",sNodeID,sPassword);
//
//	return 0;
//}

//处理心态检测报文
int CProcessInterfaceF2S::OnHello(CBroadcastPacket & GessPacket)
{
	//检查应答报文才置状态
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

//处理定时器超时
int CProcessInterfaceF2S::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csF2S.Lock();
	if (m_uiCountNoAlive >= 1)
	{//超过链路最大空闲时间未收到报文，则发送心跳
		//if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		//{//重发心跳次数超过规定次数则准备关闭
		//	nRtn = -1;
		//	ReqClose();
		//}
		//else
		//{//重置定时器间隔
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

//发送心跳
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
	sKey = "F2接口服务端连接.";
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