#include "NetMgrModule.h"

// H1 �ӿ� [1915]ģ���ͼ����������Ϣ��ѯ���� ��ҵ��ʵ��
int CNetMgrModule::OnItemAnalogCfgReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);   //ʵ��ת��
		HEADER_REQ stHeaderReq;
		ItemAnalogCfgReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		ItemAnalogCfgRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;
		//�������Ϣ    ������ʶ, ��Сֵ, ���ֵ, ���ȣ���λ����ֵ����ʱ���
		ArrayListMsg aMsg1;
		aMsg1.AddValue("1.1.1.1.1");
		aMsg1.AddValue("0");
		aMsg1.AddValue("100");
		aMsg1.AddValue("2");
		aMsg1.AddValue("1");
		aMsg1.AddValue("10");
		aMsg1.AddValue("10");
		stBodyRsp.item_cfg.AddValue(aMsg1);
			
		ArrayListMsg aMsg2;
		aMsg2.AddValue("1.1.1.2.1");
		aMsg2.AddValue("0");
		aMsg2.AddValue("100");
		aMsg2.AddValue("2");
		aMsg2.AddValue("1");
		aMsg2.AddValue("10");
		aMsg2.AddValue("10");
		stBodyRsp.item_cfg.AddValue(aMsg2);
			
		ArrayListMsg aMsg3;
		aMsg3.AddValue("1.1.1.2.2");
		aMsg3.AddValue("0");
		aMsg3.AddValue("100");
		aMsg3.AddValue("2");
		aMsg3.AddValue("1");
		aMsg3.AddValue("10");
		aMsg3.AddValue("10");
		stBodyRsp.item_cfg.AddValue(aMsg3);

			
		ArrayListMsg aMsg4;
		aMsg4.AddValue("1.1.1.2.3");
		aMsg4.AddValue("0");
		aMsg4.AddValue("100");
		aMsg4.AddValue("2");
		aMsg4.AddValue("1");
		aMsg4.AddValue("10");
		aMsg4.AddValue("10");
		stBodyRsp.item_cfg.AddValue(aMsg4);

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
