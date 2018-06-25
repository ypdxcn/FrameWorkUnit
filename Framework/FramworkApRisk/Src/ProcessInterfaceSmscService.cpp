
#include "TradePacket.h"
#include "ProcessInterfaceSmscService.h"
#include "Logger.h"

CProcessInterfaceSmscService::GessPktInfo CProcessInterfaceSmscService::m_GessPktInfo = 
{
	DEFAULT_IDLE_TIMEOUT,
	DEFAULT_HELLO_RESEND_INTERVAL,
	DEFAULT_HELLO_RESEND_COUNT,
	false
};
bool CProcessInterfaceSmscService::m_blGessPktInfoInited = false;

CProcessInterfaceSmscService::CProcessInterfaceSmscService()
:m_pCfg(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceSmscService::~CProcessInterfaceSmscService(void)
{
}

//初始化
int CProcessInterfaceSmscService::Init(CConfig * pCfg)
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

			CConfig* pCfgGlobal = pCfg->GetCfgGlobal();
			pCfgGlobal->GetProperty("node_type",m_GessPktInfo.node_type);
			pCfgGlobal->GetProperty("node_id",m_GessPktInfo.node_id);
			pCfgGlobal->GetProperty("host_id",m_GessPktInfo.node_name);
			pCfgGlobal->GetProperty("host_id",m_GessPktInfo.host_id);	
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
void CProcessInterfaceSmscService::GetPacketInfo(PacketInfo & stInfo)
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
int CProcessInterfaceSmscService::OnPacket(char * pData, size_t nSize)
{
	CTradePacket GessPacket;
	GessPacket.Decode(pData, nSize);

	m_csA2C.Lock();
	m_uiCountNoAlive = 0;
	m_csA2C.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();
	if (sCmdID == "1902")
	{
		return OnHello(GessPacket);
	}

	CRLog(E_PROINFO,"SMSC %s",GessPacket.Print().c_str());
	OnRecvPacket(GessPacket);
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
int CProcessInterfaceSmscService::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"SMSC OnConnect socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	CreateTimer(m_GessPktInfo.ulIdleInterval);
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
void CProcessInterfaceSmscService::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"SMSC OnClose socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	DestroyTimer();
}


//对外提供的主要接口函数,供通讯处理器发送报文时调用
int CProcessInterfaceSmscService::SendPacket(CPacket & SendGessPacket)
{
	try
	{

		CTradePacket & pkt = dynamic_cast<CTradePacket&>(SendGessPacket);
		//
		unsigned int  nLen = 0;
		const char* pcBuf = pkt.Encode(nLen);
		
		CRLog(E_PROINFO,"SMSC %s",pcBuf);

		int nRtn = 0;
		//m_csA2C.Lock();
		//int nSend = SendData(pcBuf,nLen);
		int nSend = CAppProcess::SendPacket(SendGessPacket);
		//m_csA2C.Unlock();
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
int CProcessInterfaceSmscService::OnSend(int nSize)
{
	return 0;
}
*/
//处理定时器超时
int CProcessInterfaceSmscService::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csA2C.Lock();
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
	m_csA2C.Unlock();
	return nRtn;
}

/******************************************************************************
函数描述:接口间心跳报文
调用函数:OnPacket()
被调函数:SendData,编码后直接通过socket发送
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CProcessInterfaceSmscService::SendHello()
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
	
	unsigned int  nLen = 0;
	const char* pcBuf = pktHello.Encode(nLen);	
	//m_csA2C.Lock();
	//int nSend = SendData(pcBuf,nLen);
	int nSend =CAppProcess::SendPacket(pktHello);
	//m_csA2C.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}

	CRLog(E_PROINFO,"SMSC %s",pcBuf);

	return 0;
}

//收到Hello后处理
int CProcessInterfaceSmscService::OnHello(CTradePacket& GessPacket)
{
	if (HEAD_RSP == GessPacket.PktType())
	{
		unsigned int  nLen = 0;
		const char* pcBuf = GessPacket.Encode(nLen);

		CRLog(E_PROINFO,"SMSC %s",pcBuf);

		return 0;
	}

	//区分请求和应答
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

	unsigned int  nLen = 0;
	const char* pcBuf = pktRsp.Encode(nLen);
	//m_csA2C.Lock();
	//int nSend = SendData(pcBuf,nLen);
	int nSend =CAppProcess::SendPacket(pktRsp);
	//m_csA2C.Unlock();
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}

	CRLog(E_PROINFO,"SMSC send %s",pcBuf);


	return 0;
}


int CProcessInterfaceSmscService::GetNmKey(string& sKey)
{
	sKey = "A2接口客户端连接";
	return 0;
}