#pragma once
#include "Comm.h"
#include "WorkThread.h"

#include "SamplerPacket.h"//1.���ݽṹ�Ķ���   2.Э��ı����

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

	//���ӵ��²�ʵ���յ���������(����)ת���Ľӿ�
	virtual int OnRecvPacket(CPacket &GessPacket) override;

	//���ӵ��ϲ�ʵ�������ӵ����������(����)ת�����ĵĽӿ�
	virtual int SendPacket(CPacket &GessPacket) override;

	//�����ӵ�������ӿ�
	virtual void Bind(CConnectPointManager* pCpMgr, const unsigned long& ulKey) override;


private:
	//�����Ա����ָ��
	typedef int (CServiceHandle::*MFP_PktHandleApi)(CSamplerPacket& pkt);
	//�����������뱨�Ĵ����Ա����ӳ��ṹ
	typedef struct tagPktCmd2Api
	{
		string sApiName;						//����ApiName���״���
		MFP_PktHandleApi pMemberFunc;			//���Ĵ�����ָ��
	} PktCmd2Api;
	//�����������뱨�Ĵ����Ա����ӳ���
	static PktCmd2Api m_PktCmd2Api[];
	int RunPacketHandleApi(CSamplerPacket& pkt);

	MainCPMgr*      m_pCvgCpMgr;//�������߳�ָ�룬���ڻص�
	unsigned long	m_ulKey;
	CConfig*		m_pCfg;
	string			m_sNodeID;

	//���ݶ���
	std::deque<CSamplerPacket> m_deqService;
	CCondMutex	m_deqCondMutex;

	//�߳�ѭ��
	int ThreadEntry();
	int End();



	//·�ɵ�ҵ������
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

