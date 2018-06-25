#include "NetMgrModule.h"

// H1 �ӿ� [1925]������������ ��ҵ��ʵ��
int CNetMgrModule::OnItemControlReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);
		HEADER_REQ stHeaderReq;
		ItemControlReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		ItemControlRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		CRLog(E_PROINFO,"Ŀ�Ľڵ��:%s��������:%s��OID:%s",stBodyReq.node_id.c_str(),stBodyReq.host_id.c_str(),stBodyReq.item_oid.c_str());
		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;


		//������Ӧ����
		CTradePacket pktRsp;
		CPacketStructTradeNm::HeadReq2Rsp(stHeaderReq,stHeaderRsp);
		pktRsp.SetHeader(stHeaderRsp);
		CPacketStructTradeNm::Struct2Packet(stBodyRsp,pktRsp);

		//ת������
		m_pCpMgr->Forward(pktRsp,m_ulKey);

		//���ƽӿ�
		CNetMgr::Instance()->OperateItem(stBodyReq.item_oid,1,stBodyReq.dst_val,"");
		return 0;
	}
	catch(std::bad_cast)
	{
		CRLog(E_ERROR,"%s","packet error!");
		return -1;
	}

};
