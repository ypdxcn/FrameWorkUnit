#include "NetMgrModule.h"

// H1 �ӿ� [1924]��ѯ�¼����� ��ҵ��ʵ��
int CNetMgrModule::OnEvtQueryReq(CPacket& pktTrade)
{
	try
	{
		CTradePacket & pkt = dynamic_cast<CTradePacket&>(pktTrade);
		HEADER_REQ stHeaderReq;
		EvtQueryReq stBodyReq;

		HEADER_RSP stHeaderRsp;
		EvtQueryRsp stBodyRsp;

		pkt.GetHeader(stHeaderReq);
		CPacketStructTradeNm::Packet2Struct(stBodyReq, pkt);

		//ҵ��ʵ��......
		stBodyRsp.oper_flag = stBodyReq.oper_flag;

		vector<CEventSimple> vmSimpleEvt;
		//��ѯ���¼��ӿ�
		CNetMgr::Instance()->QueryEvtSimple(vmSimpleEvt);

		vector<CEventSimple>::iterator itEvt;	
		for (itEvt = vmSimpleEvt.begin(); itEvt != vmSimpleEvt.end(); ++itEvt)
		{
			//��ѯ���    ����id���ڵ�id������ʱ�䣬��Ҫ�ȼ����¼����ͣ��¼�����¼����ݣ�����Աid
			ArrayListMsg aMsg;
			aMsg.AddValue(stBodyReq.host_id);
			aMsg.AddValue(stBodyReq.node_id);
			aMsg.AddValue((*itEvt).m_sDateTime);
			aMsg.AddValue((*itEvt).m_nGrade);
			aMsg.AddValue((*itEvt).m_nEvtType);
			aMsg.AddValue((*itEvt).m_nEvtCategory);
			aMsg.AddValue((*itEvt).m_sEvtContent);
			stBodyRsp.result.AddValue(aMsg);
		}


		vector<CEventTrack> vmTrackEvt;
		//��ѯ��׷���¼��ӿ�
		CNetMgr::Instance()->QueryEvtTrack(vmTrackEvt);

		vector<CEventTrack>::iterator itEvtTrack;
		for (itEvtTrack = vmTrackEvt.begin(); itEvtTrack != vmTrackEvt.end(); ++itEvtTrack)
		{
			//��ѯ���    ����id���ڵ�id������ʱ�䣬��Ҫ�ȼ����¼����ͣ��¼�����¼����ݣ�����Աid
			ArrayListMsg aMsg;
			aMsg.AddValue(stBodyReq.host_id);
			aMsg.AddValue(stBodyReq.node_id);
			aMsg.AddValue((*itEvtTrack).m_sDateTime);
			aMsg.AddValue((*itEvtTrack).m_nGrade);
			aMsg.AddValue((*itEvtTrack).m_nEvtType);
			aMsg.AddValue((*itEvtTrack).m_nEvtCategory);
			aMsg.AddValue((*itEvtTrack).m_sEvtContent);
			aMsg.AddValue((*itEvtTrack).m_sActorID);
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
