#include "NetMgrModule.h"

// H1 �ӿ� [1916]�����ͼ����������Ϣ��ѯ���� ��ҵ��ʵ��
int CNetMgrModule::OnItemDigitalCfgReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);   //ʵ��ת��
		HEADER_REQ stHeaderReq;
		ItemDigitalCfgReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		ItemDigitalCfgRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;
        //�������Ϣ    ������ʶ, ״ֵ̬������
		ArrayListMsg aMsg;
		aMsg.AddValue("1.1.1.3.1");
		aMsg.AddValue("0");
		aMsg.AddValue("1");
		stBodyRsp.item_cfg.AddValue(aMsg);

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
