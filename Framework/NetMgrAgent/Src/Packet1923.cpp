#include "NetMgrModule.h"
#include "GessDateTime.h"

// H1 �ӿ� [1923]��ѯ�澯���� ��ҵ��ʵ��
int CNetMgrModule::OnAlmQueryReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);
		HEADER_REQ stHeaderReq;
		AlmQueryReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		AlmQueryRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;

		vector<CAlarm> vmAlam;
		//��ѯ�澯�ӿ�
	    CNetMgr::Instance()->QueryAlarm(vmAlam);

		vector<CAlarm>::iterator itAlm;
		for (itAlm = vmAlam.begin(); itAlm != vmAlam.end(); ++itAlm)
		{
			ArrayListMsg aMsg;
			aMsg.AddValue(stBodyReq.host_id);
			aMsg.AddValue(stBodyReq.node_id);
			aMsg.AddValue((*itAlm).m_sOidIns);
			aMsg.AddValue((*itAlm).m_uiSeqNo);
			aMsg.AddValue(CGessDateTime::ToString((*itAlm).m_tmLastActive));
			aMsg.AddValue("");//֪ͨ��ʽ

			aMsg.AddValue((*itAlm).m_nAlmGradeFrom);
			aMsg.AddValue((*itAlm).m_nAlmGradeTo);//Ŀ��
			
			aMsg.AddValue((*itAlm).m_sTrigVal);//ֵ
			aMsg.AddValue((*itAlm).m_sAlmContent);
			aMsg.AddValue(CGessDateTime::ToString((*itAlm).m_tmLastInactive));

			//�Ƿ���Ҫȷ��
			aMsg.AddValue("0");
			//����һ��ȷ����ID
			aMsg.AddValue("monitor");
			aMsg.AddValue((*itAlm).m_sOid);
			stBodyRsp.result.AddValue(aMsg);
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
