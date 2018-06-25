#include "NetMgrModule.h"

// H1 �ӿ� [1911]����������Ϣ��ѯ���� ��ҵ��ʵ��
int CNetMgrModule::OnHostCfgReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);   //ʵ��ת��
		HEADER_REQ stHeaderReq;
		HostCfgReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		HostCfgRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);
                                                                                         
		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;

		ArrayListMsg aMsg;
		aMsg.AddValue("1000");
		aMsg.AddValue("aps-tzq");
		aMsg.AddValue("168.33.112.182");
		aMsg.AddValue("WindowsXP");
		aMsg.AddValue("1.0");
		aMsg.AddValue("0");
		stBodyRsp.host_cfg.AddValue(aMsg);

		//������Ӧ����
		CTradePacket pktRsp;
		CPacketStructTradeNm::HeadReq2Rsp(stHeaderReq,stHeaderRsp);
		pktRsp.SetHeader(stHeaderRsp);
		CPacketStructTradeNm::Struct2Packet(stBodyRsp,pktRsp);

		//ת������
		m_pCpMgr->Forward(pktRsp,m_ulKey);
		

		return 0;
	}
	catch(std::bad_cast)
	{
		CRLog(E_ERROR,"%s","packet error!");
		return -1;
	}
};
