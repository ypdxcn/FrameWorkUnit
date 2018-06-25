#include "NetMgrModule.h"

// H1 �ӿ� [1914]�����MIB������Ϣ��ѯ���� ��ҵ��ʵ��
int CNetMgrModule::OnItemMibCfgReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);   //ʵ��ת��
		HEADER_REQ stHeaderReq;
		ItemMibCfgReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		ItemMibCfgRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;
		//�������Ϣ    ������ʶ, ��д��־, ���������, ����
		ArrayListMsg aMsg1;
		aMsg1.AddValue("1.1.1.1.1");
		aMsg1.AddValue("0");
		aMsg1.AddValue("1");
		aMsg1.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg1);

		ArrayListMsg aMsg2;
		aMsg2.AddValue("1.1.1.2.1");
		aMsg2.AddValue("0");
		aMsg2.AddValue("1");
		aMsg2.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg2);

		ArrayListMsg aMsg3;
		aMsg3.AddValue("1.1.1.2.2");
		aMsg3.AddValue("0");
		aMsg3.AddValue("1");
		aMsg3.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg3);

		ArrayListMsg aMsg4;
		aMsg4.AddValue("1.1.1.2.3");
		aMsg4.AddValue("0");
		aMsg4.AddValue("1");
		aMsg4.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg4);


		ArrayListMsg aMsg5;
		aMsg5.AddValue("1.1.1.3.1");
		aMsg5.AddValue("0");
		aMsg5.AddValue("1");
		aMsg5.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg5);

		ArrayListMsg aMsg6;
		aMsg6.AddValue("1.1.1.3.2.1.1");
		aMsg6.AddValue("0");
		aMsg6.AddValue("1");
		aMsg6.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg6);

		ArrayListMsg aMsg7;
		aMsg7.AddValue("1.1.1.3.2.1.2");
		aMsg7.AddValue("0");
		aMsg7.AddValue("1");
		aMsg7.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg7);

		ArrayListMsg aMsg8;
		aMsg8.AddValue("1.1.1.3.2.1.3");
		aMsg8.AddValue("0");
		aMsg8.AddValue("1");
		aMsg8.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg8);

		ArrayListMsg aMsg9;
		aMsg9.AddValue("1.1.1.3.2.1.4");
		aMsg9.AddValue("0");
		aMsg9.AddValue("1");
		aMsg9.AddValue("0");
		stBodyRsp.mib_cfg.AddValue(aMsg9);


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
