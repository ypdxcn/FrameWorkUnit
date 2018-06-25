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
void CProcessInterfaceF1S::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltCharactersDec;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = LENGTH_BYTES;
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

		//判重？
		std::string sKey = GessPacket.RouteKey();
		OnRecvPacket(sKey,GessPacket);
	}

	return 0;
}


// 作服务端接收到连接后回调
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
函数描述:socket连接中断后则被通知,可根据协议要求进行处理
调用函数:通讯处理器对象回调
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
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

//对外提供的主要接口函数,供通讯处理器发送报文时调用
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
//处理定时器超时
int CProcessInterfaceF1S::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csF1S.Lock();
	if (m_uiCountNoAlive >= 1)
	{//超过链路最大空闲时间未收到报文，则发送心跳
		if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		{//重发心跳次数超过规定次数则准备关闭
			nRtn = -1;
			ReqClose();
		}
		else
		{//重置定时器间隔
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

//发送心跳
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

//处理心态检测报文
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
	sKey = "F1接口服务端连接.";
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