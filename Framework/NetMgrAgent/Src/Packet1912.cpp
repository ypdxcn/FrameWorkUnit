#include "NetMgrModule.h"

// H1 �ӿ� [1912]�ڵ�������Ϣ��ѯ���� ��ҵ��ʵ��
int CNetMgrModule::OnNodeCfgReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);   //ʵ��ת��
		HEADER_REQ stHeaderReq;
		NodeCfgReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		NodeCfgRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;

		//����ID,�ڵ�ID,�ڵ�����,�ڵ����ͣ��ڵ����ԣ����������˿�, ���������˿�,��������ID
		ArrayListMsg aMsg;
		aMsg.AddValue("1000");
		aMsg.AddValue("1001");
		aMsg.AddValue("HRM");
		aMsg.AddValue("1");
		aMsg.AddValue("0");
		aMsg.AddValue("2001");
		aMsg.AddValue("2222");
		aMsg.AddValue("B00000");
		stBodyRsp.node_cfg.AddValue(aMsg);

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
