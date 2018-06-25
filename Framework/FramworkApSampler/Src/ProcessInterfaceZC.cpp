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
void CProcessInterfaceZC::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltInterger;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = 4;
	stInfo.blLenIncludeHeader = true;
	stInfo.nFixHeadLen = 16;
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
函数描述:socket连接成功后，作为客户端被通知,一般用于触发认证报文发送
调用函数:通讯处理器对象回调
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
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
	m_csZC.Unlock();
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

//对外提供的主要接口函数,供通讯处理器发送报文时调用
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

//接口间心跳报文
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
	sKey = "ZC接口客户端连接";
	return 0;
}