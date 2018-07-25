#pragma once
#include "Comm.h"
#include "WorkThread.h"

#include "SamplerPacket.h"//1.数据结构的定义   2.协议的编解码

class CSamplerPacket;
class MainCPMgr;
class CServiceHandle :	public CConnectPointAsyn,public CWorkThread
{
public:
	CServiceHandle();
	~CServiceHandle();

public:

	virtual int  Init(CConfig* pConfig) override;
	virtual int  Start() override;
	virtual void Stop() override;
	virtual void Finish() override;

	//连接点下层实体收到报文向上(向内)转发的接口
	virtual int OnRecvPacket(CPacket &GessPacket) override;

	//连接点上层实体如连接点管理器向下(向外)转发报文的接口
	virtual int SendPacket(CPacket &GessPacket) override;

	//绑定连接点管理器接口
	virtual void Bind(CConnectPointManager* pCpMgr, const unsigned long& ulKey) override;


private:
	//定义成员函数指针
	typedef int (CServiceHandle::*MFP_PktHandleApi)(CSamplerPacket& pkt);
	//报文命令字与报文处理成员函数映射结构
	typedef struct tagPktCmd2Api
	{
		string sApiName;						//报文ApiName或交易代码
		MFP_PktHandleApi pMemberFunc;			//报文处理函数指针
	} PktCmd2Api;
	//报文命令字与报文处理成员函数映射表
	static PktCmd2Api m_PktCmd2Api[];
	int RunPacketHandleApi(CSamplerPacket& pkt);

	MainCPMgr*      m_pCvgCpMgr;//保存主线程指针，用于回调
	unsigned long	m_ulKey;
	CConfig*		m_pCfg;
	string			m_sNodeID;

	//数据队列
	std::deque<CSamplerPacket> m_deqService;
	CCondMutex	m_deqCondMutex;

	//线程循环
	int ThreadEntry();
	int End();



	//路由的业务处理函数
	int OnRecvLoginRsp(CSamplerPacket& pkt);
	int OnRecvSubscripRsp(CSamplerPacket& pkt);
	int OnRecvLogoutRsp(CSamplerPacket& pkt);
	int OnRecvUnSubscripRsp(CSamplerPacket& pkt);
	//int OnRecvHelloRsp(CSamplerPacket& pkt);

	int OnRecvLogin(CSamplerPacket& pkt);
	int OnRecvSubscrip(CSamplerPacket& pkt);
	int OnRecvLogout(CSamplerPacket& pkt);
	int OnRecvUnSubscrip(CSamplerPacket& pkt);
	int OnRecvHello(CSamplerPacket& pkt);
};

