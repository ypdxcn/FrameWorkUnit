#include "NetMgrModule.h"
//#include "NetMgr.h"

// H1 �ӿ� [1921]��ѯ��������ÿռ����� ��ҵ��ʵ��
int CNetMgrModule::OnQueryItemCfgReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);   //ʵ��ת��

		HEADER_REQ stHeaderReq;
		QueryItemCfgReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		QueryItemCfgRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		//ҵ��ʵ��......
		stBodyRsp.host_id = stBodyReq.host_id;
		stBodyRsp.node_id = stBodyReq.node_id;
		stBodyRsp.oper_flag = stBodyReq.oper_flag;
		
		map<string, vector<string> >::iterator itmapOid2Ins;
		vector<string>::iterator itvOidIns;

		for(itmapOid2Ins = m_mapOid2Ins.begin(); itmapOid2Ins != m_mapOid2Ins.end(); ++itmapOid2Ins)
		{
			for(itvOidIns = (*itmapOid2Ins).second.begin(); itvOidIns != (*itmapOid2Ins).second.end(); ++itvOidIns)
			{
				ArrayListMsg aMsg;
				aMsg.AddValue(*itvOidIns);
				stBodyRsp.result.AddValue(aMsg);
			}
		}

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


