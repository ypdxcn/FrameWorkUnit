#ifndef _PACKET_STRUCT_TRANSFER_TRADE_RISK_H                 
#define _PACKET_STRUCT_TRANSFER_TRADE_RISK_H    

#include "TradePacket.h"
#include "PacketBodyStructTradeRisk.h"

class CPacketStructTradeRisk
{
public:
	static void HeadReq2Rsp(HEADER_REQ& stHeadReq,HEADER_RSP& stHeadRsp)
	{
		//strcpy from req to rsp
		memset(&stHeadRsp,0x00,sizeof(HEADER_RSP));
		strcpy(stHeadRsp.area_code,stHeadReq.area_code);
		strcpy(stHeadRsp.branch_id,stHeadReq.branch_id);
		strcpy(stHeadRsp.exch_code,stHeadReq.exch_code);
		strcpy(stHeadRsp.msg_flag,stHeadReq.msg_flag);
		strcpy(stHeadRsp.msg_type,stHeadReq.msg_type);
		strcpy(stHeadRsp.seq_no,stHeadReq.seq_no);
		strcpy(stHeadRsp.term_type,stHeadReq.term_type);
		strcpy(stHeadRsp.user_id,stHeadReq.user_id);
		strcpy(stHeadRsp.user_type,stHeadReq.user_type);
		strcpy(stHeadRsp.rsp_code,"00000000");
	}

	//----------------------------------------------报文接口 [3061] 报文结构相关解析
	// 报文解析：报文 -> 结构    风险客户订阅请求
	static int Packet2Struct(SubscriberReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("teller_id"         , stBody.teller_id);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		return 0;
	};

	// 报文解析：报文 -> 结构    风险客户订阅结果响应
	static int Packet2Struct(SubscriberRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	};


	// 报文解析： 结构 -> 报文    风险客户订阅请求
	static int Struct2Packet(SubscriberReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("teller_id"         , stBody.teller_id);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		return 0;
	};


	// 报文解析： 结构 -> 报文    风险客户订阅结果响应
	static int Struct2Packet(SubscriberRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		return 0;
	};

	//----------------------------------------------报文接口 [3062] 报文结构相关解析
	// 报文解析：报文 -> 结构    风险客户明细请求
	static int Packet2Struct(RiskCustDetailReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("bk_acct_no"         , stBody.bk_acct_no);
		pkt.GetParameterVal("cust_name"         , stBody.cust_name);
		pkt.GetParameterVal("cust_no"         , stBody.cust_no);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("risk_degree2"         , stBody.risk_degree2);
		pkt.GetParameterVal("top_number"        , stBody.top_number);
		return 0;
	}

	// 报文解析：报文 -> 结构    风险客户明细响应
	static int Packet2Struct(RiskCustDetailRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("risk_result"       , stBody.risk_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    风险客户明细请求
	static int Struct2Packet(RiskCustDetailReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("bk_acct_no"         , stBody.bk_acct_no);
		pkt.AddParameter("cust_name"         , stBody.cust_name);
		pkt.AddParameter("cust_no"         , stBody.cust_no);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("risk_degree2"         , stBody.risk_degree2);
		pkt.AddParameter("top_number"        , stBody.top_number);
		return 0;
	}


	// 报文解析： 结构 -> 报文    风险客户明细响应
	static int Struct2Packet(RiskCustDetailRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("risk_result"       , stBody.risk_result);
		return 0;
	}

	//----------------------------------------------报文接口 [3063] 报文结构相关解析
	// 报文解析：报文 -> 结构    客户详细信息请求
	static int Packet2Struct(CustSpecReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		return 0;
	}

	// 报文解析：报文 -> 结构    客户详细信息响应
	static int Packet2Struct(CustSpecRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_abbr"         , stBody.cust_abbr);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("contact_no"        , stBody.contact_no);
		pkt.GetParameterVal("mobile_phone"        , stBody.mobile_phone);
		pkt.GetParameterVal("bank_id"           , stBody.bank_id);
		pkt.GetParameterVal("bk_acct_no"        , stBody.bk_acct_no);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("branch_name"       , stBody.branch_name);
		pkt.GetParameterVal("curr_bal"          , stBody.curr_bal);
		pkt.GetParameterVal("froz_order"        , stBody.froz_order);
		pkt.GetParameterVal("froz_other"        , stBody.froz_other);
		pkt.GetParameterVal("curr_can_use"      , stBody.curr_can_use);
		pkt.GetParameterVal("margin_exch"       , stBody.margin_exch );
		pkt.GetParameterVal("margin_mem"        , stBody.margin_mem );
		pkt.GetParameterVal("margin_total"      , stBody.margin_total );
		pkt.GetParameterVal("surplus"           , stBody.surplus);
		pkt.GetParameterVal("f_in_out_bal"      , stBody.f_in_out_bal);
		pkt.GetParameterVal("in_out_bal_tm"     , stBody.in_out_bal_tm);
		pkt.GetParameterVal("risk_deg1"         , stBody.risk_deg1);
		pkt.GetParameterVal("risk_deg2"         , stBody.risk_deg2);
		pkt.GetParameterVal("debt_call_line"    , stBody.debt_call_line);
		pkt.GetParameterVal("debt_mem"          , stBody.debt_mem);
		pkt.GetParameterVal("debt_exch_rel"     , stBody.debt_exch_rel);
		pkt.GetParameterVal("debt_exch_abs"     , stBody.debt_exch_abs);
		pkt.GetParameterVal("risk_type"         , stBody.risk_type);
		pkt.GetParameterVal("risk_grade_id"     , stBody.risk_grade_id);
		pkt.GetParameterVal("debt_call"         , stBody.debt_call);
		pkt.GetParameterVal("risk_type_yda"     , stBody.risk_type_yda);
		pkt.GetParameterVal("risk_deg_yda"      , stBody.risk_deg_yda);
		pkt.GetParameterVal("debt_call_yda"     , stBody.debt_call_yda);
		pkt.GetParameterVal("risk_days"         , stBody.risk_days);
		pkt.GetParameterVal("alm_stor_info"     , stBody.alm_stor_info);
		pkt.GetParameterVal("alm_posi_info"     , stBody.alm_posi_info);
		pkt.GetParameterVal("alm_posi_detail" , stBody.alm_posi_info);
		pkt.GetParameterVal("alm_broker_info"     , stBody.alm_broker_info);
		pkt.GetParameterVal("alm_cov_posi_info"     , stBody.alm_cov_posi_info);
		//充抵 add by zww 2015-6-10 没有充抵业务也不影响
		pkt.GetParameterVal("offset_margin_mem" , stBody.offset_margin_mem);
		pkt.GetParameterVal("offset_margin_exch" , stBody.offset_margin_exch);
		pkt.GetParameterVal("curr_margin_mem" , stBody.curr_margin_mem);
		pkt.GetParameterVal("curr_margin_exch" , stBody.curr_margin_exch);
		pkt.GetParameterVal("offset_quota_avaliable" , stBody.offset_quota_avaliable);
		pkt.GetParameterVal("offset_quota_today" , stBody.offset_quota_today);
		return 0;
	}


	// 报文解析： 结构 -> 报文    客户详细信息请求
	static int Struct2Packet(CustSpecReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		return 0;
	}


	// 报文解析： 结构 -> 报文    客户详细信息响应
	static int Struct2Packet(CustSpecRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);

		pkt.AddParameter("except_type",       stBody.except_type);
		pkt.AddParameter("except_datetime",   stBody.exceptdatetime);

		pkt.AddParameter("cust_abbr"         , stBody.cust_abbr);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("contact_no"        , stBody.contact_no);
		pkt.AddParameter("mobile_phone"        , stBody.mobile_phone);
		pkt.AddParameter("bank_id"           , stBody.bank_id);
		pkt.AddParameter("bk_acct_no"        , stBody.bk_acct_no);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("branch_name"       , stBody.branch_name);
		pkt.AddParameter("curr_bal"          , stBody.curr_bal);
		pkt.AddParameter("froz_order"        , stBody.froz_order);
		pkt.AddParameter("froz_other"        , stBody.froz_other);
		pkt.AddParameter("curr_can_use"      , stBody.curr_can_use);
		pkt.AddParameter("risk_curr_can_use"      , stBody.risk_curr_can_use);
		pkt.AddParameter("margin_exch"       , stBody.margin_exch );
		pkt.AddParameter("margin_mem"        , stBody.margin_mem );
		pkt.AddParameter("margin_total"      , stBody.margin_total );
		pkt.AddParameter("surplus"           , stBody.surplus);
		pkt.AddParameter("f_in_out_bal"      , stBody.f_in_out_bal);
		pkt.AddParameter("in_out_bal_tm"     , stBody.in_out_bal_tm);
		pkt.AddParameter("risk_deg1"         , stBody.risk_deg1);
		pkt.AddParameter("risk_deg2"         , stBody.risk_deg2);
		pkt.AddParameter("debt_call_line"    , stBody.debt_call_line);
		pkt.AddParameter("debt_mem"          , stBody.debt_mem);
		pkt.AddParameter("debt_exch_rel"     , stBody.debt_exch_rel);
		pkt.AddParameter("debt_exch_abs"     , stBody.debt_exch_abs);
		pkt.AddParameter("risk_type"         , stBody.risk_type);
		pkt.AddParameter("risk_grade_id"     , stBody.risk_grade_id);
		pkt.AddParameter("debt_call"         , stBody.debt_call);
		pkt.AddParameter("risk_type_yda"     , stBody.risk_type_yda);
		pkt.AddParameter("risk_deg_yda"      , stBody.risk_deg_yda);
		pkt.AddParameter("debt_call_yda"     , stBody.debt_call_yda);
		pkt.AddParameter("risk_days"         , stBody.risk_days);
		pkt.AddParameter("alm_stor_info"     , stBody.alm_stor_info);
		pkt.AddParameter("alm_posi_info"     , stBody.alm_posi_info);
		pkt.AddParameter("alm_posi_detail"	 , stBody.alm_posi_detail);  //持仓流水信息
		pkt.AddParameter("alm_broker_info"   , stBody.alm_broker_info);
		pkt.AddParameter("alm_cov_posi_info" , stBody.alm_cov_posi_info);
		//充抵 add by zww 2015-6-10 没有充抵业务也不影响
		pkt.AddParameter("offset_margin_mem" , stBody.offset_margin_mem);
		pkt.AddParameter("offset_margin_exch" , stBody.offset_margin_exch);
		pkt.AddParameter("curr_margin_mem" , stBody.curr_margin_mem);
		pkt.AddParameter("curr_margin_exch" , stBody.curr_margin_exch);
		pkt.AddParameter("offset_quota_avaliable" , stBody.offset_quota_avaliable);
		pkt.AddParameter("offset_quota_today" , stBody.offset_quota_today);
		return 0;
	}



	//----------------------------------------------报文接口 [3064] 报文结构相关解析
	// 报文解析：报文 -> 结构    风险提示查询请求
	static int Packet2Struct(RiskNotifyQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("begin_time"        , stBody.begin_time);
		pkt.GetParameterVal("end_time"          , stBody.end_time);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("tip_type"          , stBody.tip_type);
		pkt.GetParameterVal("risk_grade_src"    , stBody.risk_grade_src);
		pkt.GetParameterVal("risk_grade_des"    , stBody.risk_grade_des);
		return 0;
	}

	// 报文解析：报文 -> 结构    风险提示查询响应
	static int Packet2Struct(RiskNotifyQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    风险提示查询请求
	static int Struct2Packet(RiskNotifyQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("begin_time"        , stBody.begin_time);
		pkt.AddParameter("end_time"          , stBody.end_time);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("tip_type"          , stBody.tip_type);
		pkt.AddParameter("risk_grade_src"    , stBody.risk_grade_src);
		pkt.AddParameter("risk_grade_des"    , stBody.risk_grade_des);
		return 0;
	}


	// 报文解析： 结构 -> 报文    风险提示查询响应
	static int Struct2Packet(RiskNotifyQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	}



	//----------------------------------------------报文接口 [3065] 报文结构相关解析
	// 报文解析：报文 -> 结构    未全部成交的强平单查询
	static int Packet2Struct(NotDealFCQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no_list"      , stBody.acct_no_list);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		return 0;
	}

	// 报文解析：报文 -> 结构    未全部成交的强平单查询响应
	static int Packet2Struct(NotDealFCQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("f_order_result"    , stBody.f_order_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    未全部成交的强平单查询
	static int Struct2Packet(NotDealFCQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no_list"           , stBody.acct_no_list);
		return 0;
	}


	// 报文解析： 结构 -> 报文    未全部成交的强平单查询响应
	static int Struct2Packet(NotDealFCQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("f_order_result"    , stBody.f_order_result);
		return 0;
	}



	//----------------------------------------------报文接口 [3066] 报文结构相关解析
	// 报文解析：报文 -> 结构    发送强平单请求
	static int Packet2Struct(FCOrderSubmitReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("source_falg"       , stBody.source_falg);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("date"              , stBody.date);
		pkt.GetParameterVal("curr_bal"          , stBody.curr_bal);
		pkt.GetParameterVal("curr_can_use"      , stBody.curr_can_use);
		pkt.GetParameterVal("margin_exch"       , stBody.margin_exch);
		pkt.GetParameterVal("margin_mem"        , stBody.margin_mem);
		pkt.GetParameterVal("margin_total"      , stBody.margin_total);
		pkt.GetParameterVal("risk_degree1"       , stBody.risk_degree1);
		pkt.GetParameterVal("risk_degree2"       , stBody.risk_degree2);
		pkt.GetParameterVal("risk_grade_id"     , stBody.risk_grade_id);
		pkt.GetParameterVal("risk_grade_yda"     , stBody.risk_grade_yda);
		pkt.GetParameterVal("float_surplus"     , stBody.float_surplus);
		pkt.GetParameterVal("prod_price"        , stBody.prod_price);
		pkt.GetParameterVal("fc_order"          , stBody.fc_order);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		pkt.GetParameterVal("buyorsell"         , stBody.buyorsell);
		pkt.GetParameterVal("price"             , stBody.price);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("lbatchno"          , stBody.lbatchno);
		pkt.GetParameterVal("f_order_no"        , stBody.f_order_no);
		pkt.GetParameterVal("teller_id"         , stBody.teller_id);
		pkt.GetParameterVal("debt_call"         , stBody.debt_call);
		pkt.GetParameterVal("debt_call_yda"     , stBody.debt_call_yda);
		pkt.GetParameterVal("risk_type"         , stBody.risk_type);
		pkt.GetParameterVal("risk_type_yda"     , stBody.risk_type_yda);
		pkt.GetParameterVal("risk_days"         , stBody.risk_days);
		return 0;
	}

	// 报文解析：报文 -> 结构    发送强平单请求响应
	static int Packet2Struct(FCOrderSubmitRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("serial_no"         , stBody.serial_no);
		pkt.GetParameterVal("f_order_no"        , stBody.f_order_no);
		pkt.GetParameterVal("local_order_no"    , stBody.local_order_no);
		pkt.GetParameterVal("order_state"       , stBody.order_state);
		return 0;
	}


	// 报文解析： 结构 -> 报文    发送强平单请求
	static int Struct2Packet(FCOrderSubmitReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("source_falg"       , stBody.source_falg);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("date"              , stBody.date);
		pkt.AddParameter("curr_bal"          , stBody.curr_bal);
		pkt.AddParameter("curr_can_use"      , stBody.curr_can_use);
		pkt.AddParameter("margin_exch"       , stBody.margin_exch);
		pkt.AddParameter("margin_mem"        , stBody.margin_mem);
		pkt.AddParameter("margin_total"      , stBody.margin_total);
		pkt.AddParameter("risk_degree1"       , stBody.risk_degree1);
		pkt.AddParameter("risk_degree2"       , stBody.risk_degree2);
		pkt.AddParameter("risk_grade_id"     , stBody.risk_grade_id);
		pkt.AddParameter("float_surplus"     , stBody.float_surplus);
		pkt.AddParameter("prod_price"        , stBody.prod_price);
		pkt.AddParameter("fc_order"          , stBody.fc_order);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("buyorsell"         , stBody.buyorsell);
		pkt.AddParameter("price"             , stBody.price);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("lbatchno"          , stBody.lbatchno);
		pkt.AddParameter("f_order_no"        , stBody.f_order_no);
		pkt.AddParameter("teller_id"         , stBody.teller_id);
		pkt.AddParameter("debt_call"         , stBody.debt_call);
		pkt.AddParameter("debt_call_yda"     , stBody.debt_call_yda);
		pkt.AddParameter("risk_type"         , stBody.risk_type);
		pkt.AddParameter("risk_type_yda"     , stBody.risk_type_yda);
		pkt.AddParameter("risk_days"         , stBody.risk_days);
		return 0;
	}


	// 报文解析： 结构 -> 报文    发送强平单请求响应
	static int Struct2Packet(FCOrderSubmitRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("serial_no"         , stBody.serial_no);
		pkt.AddParameter("f_order_no"        , stBody.f_order_no);
		pkt.AddParameter("local_order_no"    , stBody.local_order_no);
		pkt.AddParameter("order_state"       , stBody.order_state);
		return 0;
	}



	//----------------------------------------------报文接口 [3067] 报文结构相关解析
	// 报文解析：报文 -> 结构    生成自动强平单请求
	static int Packet2Struct(AutoGenFCOrderReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("risk_grade_id"     , stBody.risk_grade_id);
		pkt.GetParameterVal("fc_mode"			, stBody.fc_mode);
		pkt.GetParameterVal("lbatchno"          , stBody.lbatchno);
		pkt.GetParameterVal("teller_id"         , stBody.teller_id);
		pkt.GetParameterVal("posi_result"       , stBody.posi_result);
		pkt.GetParameterVal("cov_price_info"       , stBody.cov_price_info);
		pkt.GetParameterVal("risk_target"       , stBody.risk_target);
		return 0;
	}

	// 报文解析：报文 -> 结构    生成自动强平单响应
	static int Packet2Struct(AutoGenFCOrderRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("lbatchno"          , stBody.lbatchno);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    生成自动强平单请求
	static int Struct2Packet(AutoGenFCOrderReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("risk_grade_id"     , stBody.risk_grade_id);
		pkt.AddParameter("fc_mode"			 , stBody.fc_mode);
		pkt.AddParameter("lbatchno"          , stBody.lbatchno);
		pkt.AddParameter("teller_id"         , stBody.teller_id);
		pkt.AddParameter("cov_price_info"         , stBody.cov_price_info);
		pkt.AddParameter("risk_target"         , stBody.risk_target);
		return 0;
	}


	// 报文解析： 结构 -> 报文    生成自动强平单响应
	static int Struct2Packet(AutoGenFCOrderRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("lbatchno"          , stBody.lbatchno);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	}



	//----------------------------------------------报文接口 [3069] 报文结构相关解析
	// 报文解析：报文 -> 结构    强平单查询请求
	static int Packet2Struct(FCOrderQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("instid"            , stBody.instid);
		pkt.GetParameterVal("gene_type"         , stBody.gene_type);
		pkt.GetParameterVal("f_teller_id"       , stBody.f_teller_id);
		pkt.GetParameterVal("begin_date"        , stBody.begin_date);
		pkt.GetParameterVal("end_date"          , stBody.end_date);
		pkt.GetParameterVal("order_status_set"  , stBody.order_status_set);
		return 0;
	}

	// 报文解析：报文 -> 结构    强平单查询响应
	static int Packet2Struct(FCOrderQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平单查询请求
	static int Struct2Packet(FCOrderQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("instid"            , stBody.instid);
		pkt.AddParameter("gene_type"         , stBody.gene_type);
		pkt.AddParameter("f_teller_id"       , stBody.f_teller_id);
		pkt.AddParameter("begin_date"        , stBody.begin_date);
		pkt.AddParameter("end_date"          , stBody.end_date);
		pkt.AddParameter("order_status_set"  , stBody.order_status_set);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平单查询响应
	static int Struct2Packet(FCOrderQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	}



	//----------------------------------------------报文接口 [3070] 报文结构相关解析
	// 报文解析：报文 -> 结构    强平单撤销请求
	static int Packet2Struct(FCOrderCancelReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("order_no"          , stBody.order_no);
		return 0;
	}

	// 报文解析：报文 -> 结构    强平单撤销响应
	static int Packet2Struct(FCOrderCancelRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("order_no"          , stBody.order_no);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平单撤销请求
	static int Struct2Packet(FCOrderCancelReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("order_no"          , stBody.order_no);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平单撤销响应
	static int Struct2Packet(FCOrderCancelRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("order_no"          , stBody.order_no);
		return 0;
	}


	//----------------------------------------------报文接口 [3311] 报文结构相关解析 add by liuwei 2012-10-23
	static int Packet2Struct(FCOrderCancelBatchReq &stBody, CTradePacket &pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		pkt.GetParameterVal("order_no", stBody.order_no);
		return 0;
	}
	static int Packet2Struct(FCOrderCancelBatchRsp &stBody, CTradePacket &pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		return 0;
	}
	static int Struct2Packet(FCOrderCancelBatchReq & stBody, CTradePacket &pkt)
	{
		pkt.AddParameter("oper_flag", stBody.oper_flag);
		pkt.AddParameter("order_no", stBody.order_no);
		return 0;
	}
	static int Struct2Packet(FCOrderCancelBatchRsp &stBody, CTradePacket &pkt)
	{
		pkt.AddParameter("oper_flag", stBody.oper_flag);
		return 0;
	}


	//----------------------------------------------报文接口 [3088] 报文结构相关解析
	// 报文解析：报文 -> 结构    风险等级查询
	static int Packet2Struct(RiskGradeQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	}

	// 报文解析：报文 -> 结构    风险等级查询
	static int Packet2Struct(RiskGradeQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("query_result"      , stBody.query_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    风险等级查询
	static int Struct2Packet(RiskGradeQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		return 0;
	}


	// 报文解析： 结构 -> 报文    风险等级查询
	static int Struct2Packet(RiskGradeQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("query_result"      , stBody.query_result);
		return 0;
	}



	//----------------------------------------------报文接口 [3081] 报文结构相关解析
	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(RiskStateParaReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("obj_type"          , stBody.obj_type);
		pkt.GetParameterVal("obj_id"            , stBody.obj_id);
		pkt.GetParameterVal("debt_mem_value"    , stBody.debt_mem_value);
		pkt.GetParameterVal("debt_exch_value"   , stBody.debt_exch_value);
		pkt.GetParameterVal("debt_call_value"   , stBody.debt_call_value);
		pkt.GetParameterVal("obj_content"       , stBody.obj_content);
		return 0;
	}

	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(RiskStateParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		pkt.GetParameterVal("obj_type"        , stBody.obj_type);
		pkt.GetParameterVal("obj_id"        , stBody.obj_id);
		pkt.GetParameterVal("debt_exch_value"        , stBody.debt_exch_value);
		pkt.GetParameterVal("debt_call_value"        , stBody.debt_call_value);
		pkt.GetParameterVal("obj_content"        , stBody.obj_content);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(RiskStateParaReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("obj_type"          , stBody.obj_type);
		pkt.AddParameter("obj_id"            , stBody.obj_id);
		pkt.AddParameter("debt_mem_value"    , stBody.debt_mem_value);
		pkt.AddParameter("debt_exch_value"   , stBody.debt_exch_value);
		pkt.AddParameter("debt_call_value"   , stBody.debt_call_value);
		pkt.AddParameter("obj_content"       , stBody.obj_content);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(RiskStateParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		pkt.AddParameter("obj_type"        , stBody.obj_type);
		pkt.AddParameter("obj_id"        , stBody.obj_id);
		pkt.AddParameter("debt_exch_value"        , stBody.debt_exch_value);
		pkt.AddParameter("debt_call_value"        , stBody.debt_call_value);
		pkt.AddParameter("obj_content"        , stBody.obj_content);
		return 0;
	}


	//----------------------------------------------报文接口 [3082] 报文结构相关解析
	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(RiskhandleParaReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("handle_id"         , stBody.handle_id);
		pkt.GetParameterVal("handle_name"       , stBody.handle_name);
		pkt.GetParameterVal("handle_method"     , stBody.handle_method);
		pkt.GetParameterVal("para_set"          , stBody.para_set);
		return 0;
	}

	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(RiskhandleParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("handle_id"         , stBody.handle_id);
		pkt.GetParameterVal("handle_name"       , stBody.handle_name);
		pkt.GetParameterVal("handle_method"     , stBody.handle_method);
		pkt.GetParameterVal("para_set"          , stBody.para_set);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(RiskhandleParaReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("handle_id"         , stBody.handle_id);
		pkt.AddParameter("handle_name"       , stBody.handle_name);
		pkt.AddParameter("handle_method"     , stBody.handle_method);
		pkt.AddParameter("para_set"          , stBody.para_set);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(RiskhandleParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("handle_id"         , stBody.handle_id);
		pkt.AddParameter("handle_name"       , stBody.handle_name);
		pkt.AddParameter("handle_method"     , stBody.handle_method);
		pkt.AddParameter("para_set"          , stBody.para_set);
		return 0;
	}



	//----------------------------------------------报文接口 [3084] 报文结构相关解析
	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(RiskNotifyParaReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("tip_type"          , stBody.tip_type);
		pkt.GetParameterVal("risk_grade_src"    , stBody.risk_grade_src);
		pkt.GetParameterVal("risk_grade_des"    , stBody.risk_grade_des);
		pkt.GetParameterVal("notify_content"    , stBody.notify_content);
		return 0;
	}

	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(RiskNotifyParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("notify_content_set"          , stBody.notify_content_set);
		return 0;
	}
	
	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(RiskNotifyParaReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("tip_type"          , stBody.tip_type);
		pkt.AddParameter("risk_grade_src"    , stBody.risk_grade_src);
		pkt.AddParameter("risk_grade_des"    , stBody.risk_grade_des);
		pkt.AddParameter("notify_content"    , stBody.notify_content);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(RiskNotifyParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("notify_content_set"          , stBody.notify_content_set);
		
		return 0;
	}



	//----------------------------------------------报文接口 [3085] 报文结构相关解析
	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(ForceCoverParaReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("prod_set"          , stBody.prod_set);
		return 0;
	}

	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(ForceCoverParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("prod_set"          , stBody.prod_set);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(ForceCoverParaReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("prod_set"          , stBody.prod_set);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(ForceCoverParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("prod_set"          , stBody.prod_set);
		return 0;
	}



	//----------------------------------------------报文接口 [3086] 报文结构相关解析
	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(BranchAuthParaReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_set"        , stBody.branch_set);
		return 0;
	}

	// 报文解析：报文 -> 结构    参数配置报文
	static int Packet2Struct(BranchAuthParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_set"        , stBody.branch_set);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(BranchAuthParaReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_set"        , stBody.branch_set);
		return 0;
	}


	// 报文解析： 结构 -> 报文    参数配置报文
	static int Struct2Packet(BranchAuthParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_set"        , stBody.branch_set);
		return 0;
	}



	//----------------------------------------------报文接口 [3091] 报文结构相关解析
	// 报文解析：报文 -> 结构    交易统一请求报文
	static int Packet2Struct(RiskCustQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("risk_grade_id"     , stBody.risk_grade_id);
		pkt.GetParameterVal("start_no"          , stBody.start_no);			
		pkt.GetParameterVal("page_no"           , stBody.page_no);
		pkt.GetParameterVal("page_size"         , stBody.page_size);
		pkt.GetParameterVal("total_record"      , stBody.total_record);
		return 0;
	}

	// 报文解析：报文 -> 结构    交易统一请求报文
	static int Packet2Struct(RiskCustQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    交易统一请求报文
	static int Struct2Packet(RiskCustQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("risk_grade_id"     , stBody.risk_grade_id);
		pkt.AddParameter("start_no"          , stBody.start_no);			
		pkt.AddParameter("page_no"           , stBody.page_no);
		pkt.AddParameter("page_size"         , stBody.page_size);
		pkt.AddParameter("total_record"      , stBody.total_record);
		return 0;
	}
	

	// 报文解析： 结构 -> 报文    交易统一请求报文
	static int Struct2Packet(RiskCustQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	}



	//----------------------------------------------报文接口 [3093] 报文结构相关解析
	// 报文解析：报文 -> 结构    内部划转申请/复核的请求报文体
	static int Packet2Struct(RiskTestCalReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("p_branch_id"         , stBody.p_branch_id);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("instid"            , stBody.instid);
		pkt.GetParameterVal("page_no"            , stBody.page_no);
		pkt.GetParameterVal("page_size"            , stBody.page_size);
		pkt.GetParameterVal("total_record"            , stBody.total_record);
		pkt.GetParameterVal("risk_level"        , stBody.risk_level);  // add by liuwei 2012-7-16
		return 0;
	}

	// 报文解析：报文 -> 结构   风险试算响应报文体，支持分页
	static int Packet2Struct(RiskTestCalRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("page_no"         , stBody.page_no);
		pkt.GetParameterVal("page_size"         , stBody.page_size);
		pkt.GetParameterVal("total_record"         , stBody.total_record);
		pkt.GetParameterVal("cal_result"        , stBody.cal_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文   风险试算请求报文体，支持分页
	static int Struct2Packet(RiskTestCalReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("p_branch_id"       , stBody.p_branch_id);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("instid"            , stBody.instid);
		pkt.AddParameter("page_no"            , stBody.page_no);
		pkt.AddParameter("page_size"            , stBody.page_size);
		pkt.AddParameter("total_record"            , stBody.total_record);
		pkt.AddParameter("risk_level"        , stBody.risk_level);  // add by liuwei 2012-7-16
		return 0;
	}


	// 报文解析： 结构 -> 报文    内部划转申请/复核的响应报文体
	static int Struct2Packet(RiskTestCalRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("page_no"            , stBody.page_no);
		pkt.AddParameter("page_size"            , stBody.page_size);
		pkt.AddParameter("total_record"            , stBody.total_record);
		pkt.AddParameter("cal_result"        , stBody.cal_result);
		return 0;
	}



	//----------------------------------------------报文接口 [3094] 报文结构相关解析
	// 报文解析：报文 -> 结构    资金冻结解冻的请求报文体
	static int Packet2Struct(RiskCustAllReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("begin_date"        , stBody.begin_date);
		pkt.GetParameterVal("end_date"          , stBody.end_date);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("risk_grade_id"     , stBody.risk_grade_id);
		return 0;
	}

	// 报文解析：报文 -> 结构    资金冻结解冻的响应报文体
	static int Packet2Struct(RiskCustAllRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("risk_cust"         , stBody.risk_cust);
		return 0;
	}


	// 报文解析： 结构 -> 报文    资金冻结解冻的请求报文体
	static int Struct2Packet(RiskCustAllReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("begin_date"        , stBody.begin_date);
		pkt.AddParameter("end_date"          , stBody.end_date);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("risk_grade_id"     , stBody.risk_grade_id);
		return 0;
	}


	// 报文解析： 结构 -> 报文    资金冻结解冻的响应报文体
	static int Struct2Packet(RiskCustAllRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("risk_cust"         , stBody.risk_cust);
		return 0;
	}



	//----------------------------------------------报文接口 [3095] 报文结构相关解析
	// 报文解析：报文 -> 结构    交易保证金解冻的请求报文体
	static int Packet2Struct(RiskDistQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("begin_date"        , stBody.begin_date);
		pkt.GetParameterVal("end_date"          , stBody.end_date);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		return 0;
	}

	// 报文解析：报文 -> 结构    交易保证金解冻的响应报文体
	static int Packet2Struct(RiskDistQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("risk_dist"         , stBody.risk_dist);
		return 0;
	}


	// 报文解析： 结构 -> 报文    交易保证金解冻的请求报文体
	static int Struct2Packet(RiskDistQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("begin_date"        , stBody.begin_date);
		pkt.AddParameter("end_date"          , stBody.end_date);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		return 0;
	}


	// 报文解析： 结构 -> 报文    交易保证金解冻的响应报文体
	static int Struct2Packet(RiskDistQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("risk_dist"         , stBody.risk_dist);
		return 0;
	}


	//----------------------------------------------报文接口 [3096] 报文结构相关解析
	// 报文解析：报文 -> 结构    基础保证金的请求报文体
	static int Packet2Struct(BranchDistQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("begin_time"        , stBody.begin_time);
		pkt.GetParameterVal("end_time"          , stBody.end_time);
		pkt.GetParameterVal("risk_level"        , stBody.risk_level);
		return 0;
	}

	// 报文解析：报文 -> 结构    基础保证金的响应报文体
	static int Packet2Struct(BranchDistQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		return 0;
	}


	// 报文解析： 结构 -> 报文    基础保证金的请求报文体
	static int Struct2Packet(BranchDistQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("begin_time"        , stBody.begin_time);
		pkt.AddParameter("end_time"          , stBody.end_time);
		pkt.AddParameter("risk_level"        , stBody.risk_level);
		return 0;
	}


	// 报文解析： 结构 -> 报文    基础保证金的响应报文体
	static int Struct2Packet(BranchDistQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		return 0;
	}


	//----------------------------------------------报文接口 [3097] 报文结构相关解析
	// 报文解析：报文 -> 结构    平仓试算的请求报文体
	static int Packet2Struct(TryCloseReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("close_para"        , stBody.close_para);
		return 0;
	}

	// 报文解析：报文 -> 结构    平仓试算的响应报文体
	static int Packet2Struct(TryCloseRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("cust_id"           , stBody.cust_id);
		pkt.GetParameterVal("curr_bal"          , stBody.curr_bal);
		pkt.GetParameterVal("margin_exch"       , stBody.margin_exch);
		pkt.GetParameterVal("margin_mem"        , stBody.margin_mem);
		pkt.GetParameterVal("margin_total"      , stBody.margin_total);
		pkt.GetParameterVal("float_surplus"     , stBody.float_surplus);
		pkt.GetParameterVal("risk_degree1"      , stBody.risk_degree1);
		pkt.GetParameterVal("risk_degree2"      , stBody.risk_degree2);
		pkt.GetParameterVal("risk_grade"        , stBody.risk_grade);
		pkt.GetParameterVal("risk_type"         , stBody.risk_type);
		pkt.GetParameterVal("call_debt"         , stBody.call_debt);
		//充抵 add by zww 2015-6-10 没有充抵业务也不影响
		pkt.GetParameterVal("offset_margin_mem" , stBody.offset_margin_mem);
		pkt.GetParameterVal("offset_margin_exch" , stBody.offset_margin_exch);
		pkt.GetParameterVal("curr_margin_mem" , stBody.curr_margin_mem);
		pkt.GetParameterVal("curr_margin_exch" , stBody.curr_margin_exch);
		pkt.GetParameterVal("offset_quota_avaliable" , stBody.offset_quota_avaliable);
		pkt.GetParameterVal("offset_quota_today" , stBody.offset_quota_today);
		return 0;
	}


	// 报文解析： 结构 -> 报文    平仓试算的请求报文体
	static int Struct2Packet(TryCloseReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("close_para"        , stBody.close_para);
		return 0;
	}


	// 报文解析： 结构 -> 报文    平仓试算的响应报文体
	static int Struct2Packet(TryCloseRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("cust_id"           , stBody.cust_id);
		pkt.AddParameter("curr_bal"          , stBody.curr_bal);
		pkt.AddParameter("margin_exch"       , stBody.margin_exch);
		pkt.AddParameter("margin_mem"        , stBody.margin_mem);
		pkt.AddParameter("margin_total"      , stBody.margin_total);
		pkt.AddParameter("float_surplus"     , stBody.float_surplus);
		pkt.AddParameter("risk_degree1"      , stBody.risk_degree1);
		pkt.AddParameter("risk_degree2"      , stBody.risk_degree2);
		pkt.AddParameter("risk_grade"        , stBody.risk_grade);
		pkt.AddParameter("risk_type"         , stBody.risk_type);
		pkt.AddParameter("call_debt"       , stBody.call_debt);
		//充抵 add by zww 2015-6-10 没有充抵业务也不影响
		pkt.AddParameter("offset_margin_mem" , stBody.offset_margin_mem);
		pkt.AddParameter("offset_margin_exch" , stBody.offset_margin_exch);
		pkt.AddParameter("curr_margin_mem" , stBody.curr_margin_mem);
		pkt.AddParameter("curr_margin_exch" , stBody.curr_margin_exch);
		pkt.AddParameter("offset_quota_avaliable" , stBody.offset_quota_avaliable);
		pkt.AddParameter("offset_quota_today" , stBody.offset_quota_today);
		return 0;
	}

	//----------------------------------------------报文接口 [3098] 报文结构相关解析
	// 报文解析：报文 -> 结构    合约行情查询的请求报文体
	static int Packet2Struct(ProdQuotationReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("prod_code"         , stBody.prod_code);
		return 0;
	}

	// 报文解析：报文 -> 结构    合约行情查询的响应报文体
	static int Packet2Struct(ProdQuotationRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("quotaion_result"   , stBody.quotaion_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    合约行情查询的请求报文体
	static int Struct2Packet(ProdQuotationReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		return 0;
	}


	// 报文解析： 结构 -> 报文    合约行情查询的响应报文体
	static int Struct2Packet(ProdQuotationRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("quotaion_result"   , stBody.quotaion_result);
		return 0;
	}

	//----------------------------------------------报文接口 [3306] 报文结构相关解析
	// 报文解析： 结构 -> 报文    修改最小变动单位请求报文体
	static int Packet2Struct(RiskProfitLossReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"       , stBody.acct_no);
		return 0;
	}
	// 组建响应报文： 结构 -> 报文    修改最小变动单位应答报文体
	static int Struct2Packet(RiskProfitLossRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"       , stBody.oper_flag);
		pkt.AddParameter("amt_result"       , stBody.amt_result);
		return 0;
	}  


	//----------------------------------------------报文接口 [3302] 报文结构相关解析
	// 报文解析： 结构 -> 报文    修改最小变动单位请求报文体
	static int Struct2Packet(AlterMinUnitReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"       , stBody.oper_flag);
		pkt.AddParameter("min_unit"       , stBody.min_unit);
		pkt.AddParameter("prod_code"       , stBody.prod_code);
		pkt.AddParameter("mincatchtime", stBody.mincatchtime);
		pkt.AddParameter("maxcatchtime", stBody.maxcatchtime);
		pkt.AddParameter("varietycode" , stBody.varietyCode);
		return 0;
	}
	// 报文解析： 结构 -> 报文    修改最小变动单位应答报文体
	static int Struct2Packet(AlterMinUnitRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"       , stBody.oper_flag);
        pkt.AddParameter("alm_result"       , stBody.alm_result);
		return 0;
	}

	// 报文解析：报文 -> 结构  修改最小变动单位应答报文体
	static int Packet2Struct(AlterMinUnitRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"       , stBody.alm_result);
		return 0;
	}
	// 报文解析：报文 -> 结构  修改最小变动单位请求报文体
	static int Packet2Struct(AlterMinUnitReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("min_unit"       , stBody.min_unit);
	    pkt.GetParameterVal("prod_code"       , stBody.prod_code);
		pkt.GetParameterVal("quote_dot"       , stBody.quote_dot);
		pkt.GetParameterVal("mincatchtime", stBody.mincatchtime);
		pkt.GetParameterVal("maxcatchtime", stBody.maxcatchtime);
		pkt.GetParameterVal("varietycode" , stBody.varietyCode);
		return 0;
	}

	//----------------------------------------------报文接口 [3301] 报文结构相关解析
	// 报文解析：报文 -> 结构  手工短信通知处理
	static int Packet2Struct(HandleSmsReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		pkt.GetParameterVal("alm_result", stBody.alm_result);
		return 0;
	}
	// 报文解析： 结构 -> 报文    自动强平例外条件配置请求报文体
	static int Struct2Packet(HandleSmsRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"  , stBody.oper_flag);
		return 0;
	}



	//----------------------------------------------报文接口 [3301] 报文结构相关解析
	// 报文解析： 结构 -> 报文    自动强平例外条件配置请求报文体
	static int Struct2Packet(AutoForceExecptConditionReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"       , stBody.oper_flag);
		pkt.AddParameter("obj_type"        , stBody.obj_type);
		pkt.AddParameter("except_date_time" , stBody.except_date_time);
		pkt.AddParameter("type_value"      , stBody.type_value);
		return 0;
	}
	// 报文解析： 结构 -> 报文    自动强平例外条件配置请求报文体
	static int Struct2Packet(AutoForceExecptConditionRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("value_list"           , stBody.value_list);

		return 0;
	}

	// 报文解析：报文 -> 结构  自动强平例外条件配置请求报文体
	static int Packet2Struct(AutoForceExecptConditionRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("value_list"           , stBody.value_list);
		return 0;
	}
	// 报文解析：报文 -> 结构  自动强平例外条件配置请求报文体
	static int Packet2Struct(AutoForceExecptConditionReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("obj_type"        , stBody.obj_type);
		pkt.GetParameterVal("except_date_time" , stBody.except_date_time);
		pkt.GetParameterVal("type_value"      , stBody.type_value);
		return 0;
	}


    //----------------------------------------------报文接口 [3100] 报文结构相关解析
	// 报文解析： 结构 -> 报文    短信通知参数配置请求报文
	static int Struct2Packet(SmsParaReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_type"        , stBody.acct_type);
		pkt.AddParameter("risk_type"        , stBody.risk_type);
		pkt.AddParameter("sms_content"        , stBody.sms_content);
		return 0;
	}
	// 报文解析： 结构 -> 报文    短信通知参数配置应答报文
	static int Struct2Packet(SmsParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("sms_content_set"   , stBody.sms_content_set);
		return 0;
	}

	// 报文解析：报文 -> 结构  短信通知参数配置响应报文体
	static int Packet2Struct(SmsParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("sms_content_set"         , stBody.sms_content_set);
		return 0;
	}
	// 报文解析：报文 -> 结构  短信通知参数配置请求报文体
	static int Packet2Struct(SmsParaReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("risk_type"         , stBody.risk_type);
		pkt.GetParameterVal("sms_content"       , stBody.sms_content);
		return 0;
	}

	//----------------------------------------------报文接口 [3099] 报文结构相关解析
	// 报文解析： 结构 -> 报文    客户风险度请求报文体
	static int Struct2Packet(CustRiskDegreeQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"			,stBody.acct_no);
		return 0;
	}
	// 报文解析： 结构 -> 报文    客户风险度应答报文
	static int Struct2Packet(CustRiskDegreeQueryRsq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("risk_degree"   , stBody.risk_degree);
		pkt.AddParameter("risk_degree1"   , stBody.risk_degree1);
		pkt.AddParameter("risk_degree2"   , stBody.risk_degree2);
		pkt.AddParameter("risk_degree"   , stBody.risk_degree);
		pkt.AddParameter("risk_grade"   , stBody.risk_grade);
		pkt.AddParameter("risk_type",stBody.risk_type);				//风险类型
		pkt.AddParameter("debt_call_line",stBody.debt_call_line);	//客户追保计算线
		pkt.AddParameter("debt_mem",stBody.debt_mem);				//客户追保线
		pkt.AddParameter("debt_exch_rel",stBody.debt_exch_rel);		//客户相对强平线
		pkt.AddParameter("debt_exch_abs",stBody.debt_exch_abs);		//客户绝对强平线
		pkt.AddParameter("margin_mem",stBody.margin_mem);			//会员保证金
		pkt.AddParameter("margin_exch",stBody.margin_exch);			//交易所保证金
		pkt.AddParameter("debt_call",stBody.debt_call);				//追保金额
		pkt.AddParameter("surplus",stBody.surplus);					//浮动盈亏
		pkt.AddParameter("risk_curr_can_use",stBody.risk_curr_can_use);	//可用资金
		pkt.AddParameter("acct_type",stBody.acct_type);					//账户类型
		pkt.AddParameter("f_in_out_bal",stBody.f_in_out_bal);			//今日出入金
		pkt.AddParameter("risk_type_yda",stBody.risk_type_yda);			//上日风险类型
		pkt.AddParameter("risk_deg_yda",stBody.risk_deg_yda);			//上日风险等级
		pkt.AddParameter("debt_call_yda",stBody.debt_call_yda);			//昨日追保金额
		pkt.AddParameter("risk_days",stBody.risk_days);					//昨日连续风险天数				 
		return 0;
	}

	// 报文解析：报文 -> 结构  客户风险度响应报文体
	static int Packet2Struct(CustRiskDegreeQueryRsq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("risk_degree"         , stBody.risk_degree);
		pkt.GetParameterVal("risk_degree"         , stBody.risk_degree);
		pkt.GetParameterVal("risk_degree1"      , stBody.risk_degree1);
		pkt.GetParameterVal("risk_degree2"      , stBody.risk_degree2);
		pkt.GetParameterVal("risk_grade"        , stBody.risk_grade);
		return 0;
	}
	// 报文解析：报文 -> 结构   客户风险度请求报文体
	static int Packet2Struct(CustRiskDegreeQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	}

	//----------------------------------------------报文接口 [3052] 报文结构相关解析
	// 报文解析：报文 -> 结构    强平报单
	static int Packet2Struct(ForceCovOder& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("client_serial_no"  , stBody.client_serial_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_id"           , stBody.cust_id);
		pkt.GetParameterVal("bank_no"           , stBody.bank_no);
		pkt.GetParameterVal("b_market_id"       , stBody.b_market_id);
		pkt.GetParameterVal("prod_code"            , stBody.prod_code);
		pkt.GetParameterVal("offset_flag"       , stBody.offset_flag);
		pkt.GetParameterVal("deli_flag"         , stBody.deli_flag);
		pkt.GetParameterVal("bs"                , stBody.bs);
		pkt.GetParameterVal("entr_price"        , stBody.entr_price);
		pkt.GetParameterVal("entr_amount"       , stBody.entr_amount);
		pkt.GetParameterVal("cov_type"          , stBody.cov_type);
		pkt.GetParameterVal("match_type"        , stBody.match_type);
		pkt.GetParameterVal("src_match_no"      , stBody.src_match_no);
		pkt.GetParameterVal("order_send_type"   , stBody.order_send_type);
		return 0;
	}

	// 报文解析：报文 -> 结构    强平报单响应
	static int Packet2Struct(ForceCovOderAck& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("client_serial_no"  , stBody.client_serial_no);
		pkt.GetParameterVal("local_order_no"    , stBody.local_order_no);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平报单
	static int Struct2Packet(ForceCovOder& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("client_serial_no"  , stBody.client_serial_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("cust_id"           , stBody.cust_id);
		pkt.AddParameter("bank_no"           , stBody.bank_no);
		pkt.AddParameter("b_market_id"       , stBody.b_market_id);
		pkt.AddParameter("prod_code"         , stBody.prod_code);
		pkt.AddParameter("offset_flag"       , stBody.offset_flag);
		pkt.AddParameter("deli_flag"         , stBody.deli_flag);
		pkt.AddParameter("bs"                , stBody.bs);
		pkt.AddParameter("entr_price"        , stBody.entr_price);
		pkt.AddParameter("entr_amount"       , stBody.entr_amount);
		pkt.AddParameter("cov_type"          , stBody.cov_type);
		pkt.AddParameter("match_type"        , stBody.match_type);
		pkt.AddParameter("src_match_no"      , stBody.src_match_no);
		pkt.AddParameter("order_send_type"   , stBody.order_send_type);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平报单响应
	static int Struct2Packet(ForceCovOderAck& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("client_serial_no"  , stBody.client_serial_no);
		pkt.AddParameter("local_order_no"    , stBody.local_order_no);
		return 0;
	}

	//----------------------------------------------报文接口 [3053] 报文结构相关解析
	// 报文解析：报文 -> 结构    强平撤单
	static int Packet2Struct(ForceCovOderCancel& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("cancel_order_no"   , stBody.cancel_order_no);
		return 0;
	}

	// 报文解析：报文 -> 结构    强平撤单响应
	static int Packet2Struct(ForceCovOderCancelAck& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平撤单
	static int Struct2Packet(ForceCovOderCancel& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("cancel_order_no"   , stBody.cancel_order_no);
		return 0;
	}


	// 报文解析： 结构 -> 报文    强平撤单响应
	static int Struct2Packet(ForceCovOderCancelAck& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		return 0;
	}

	// 报文解析：报文 -> 结构
	static int Packet2Struct(DeferRtnOrder& stBody,CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("client_serial_no"         , stBody.client_serial_no);
		pkt.GetParameterVal("orderNo"         , stBody.orderNo);
		pkt.GetParameterVal("clientID"        , stBody.clientID);
		pkt.GetParameterVal("instID"		, stBody.instID);
		pkt.GetParameterVal("memberID"         , stBody.memberID);
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("applyDate"         , stBody.applyDate);
		pkt.GetParameterVal("applyTime"         , stBody.applyTime);
		pkt.GetParameterVal("offSetFlag"         , stBody.offSetFlag);
		pkt.GetParameterVal("price"         , stBody.price);
		pkt.GetParameterVal("amount"         , stBody.amount);
		pkt.GetParameterVal("remainAmount"         , stBody.remainAmount);
		pkt.GetParameterVal("cancelTime"         , stBody.cancelTime);
		pkt.GetParameterVal("localOrderNo"         , stBody.localOrderNo);
		pkt.GetParameterVal("margin"         , stBody.margin);
		pkt.GetParameterVal("marginType"         , stBody.marginType);
		pkt.GetParameterVal("traderID"         , stBody.traderID);
		pkt.GetParameterVal("cancelID"         , stBody.cancelID);
		pkt.GetParameterVal("matchType"         , stBody.matchType);
		pkt.GetParameterVal("acctNo"         , stBody.acctNo);

		return 0;
	}

	// 报文解析：结构 -> 报文
	static int Struct2Packet(DeferRtnOrder& stBody,CBroadcastPacket& pkt)
	{
		pkt.AddParameter("client_serial_no"         , stBody.client_serial_no);
		pkt.AddParameter("orderNo"         , stBody.orderNo);
		pkt.AddParameter("clientID"        , stBody.clientID);
		pkt.AddParameter("instID"		, stBody.instID);
		pkt.AddParameter("memberID"         , stBody.memberID);
		pkt.AddParameter("buyOrSell"         , stBody.buyOrSell);
		pkt.AddParameter("applyDate"         , stBody.applyDate);
		pkt.AddParameter("applyTime"         , stBody.applyTime);
		pkt.AddParameter("offSetFlag"         , stBody.offSetFlag);
		pkt.AddParameter("price"         , stBody.price);
		pkt.AddParameter("amount"         , stBody.amount);
		pkt.AddParameter("remainAmount"         , stBody.remainAmount);
		pkt.AddParameter("cancelTime"         , stBody.cancelTime);
		pkt.AddParameter("localOrderNo"         , stBody.localOrderNo);
		pkt.AddParameter("margin"         , stBody.margin);
		pkt.AddParameter("marginType"         , stBody.marginType);
		pkt.AddParameter("traderID"         , stBody.traderID);
		pkt.AddParameter("cancelID"         , stBody.cancelID);
		pkt.AddParameter("matchType"         , stBody.matchType);
		pkt.AddParameter("acctNo"         , stBody.acctNo);
		return 0;
	}

	static int Packet2Struct(RiskAlarmParaReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"       , stBody.oper_flag);
		pkt.GetParameterVal("index_id"        , stBody.index_id);
		pkt.GetParameterVal("prod_code"       , stBody.prod_code);
		pkt.GetParameterVal("notify_obj"      , stBody.notify_obj);
		pkt.GetParameterVal("term_value"      , stBody.term_value);
		pkt.GetParameterVal("notify_way"      , stBody.notify_way);
		pkt.GetParameterVal("timeout"         , stBody.timeout);
		pkt.GetParameterVal("term_type"       , stBody.term_type);
		pkt.GetParameterVal("begin_day"       , stBody.begin_day);
		pkt.GetParameterVal("end_day"         , stBody.end_day);
		pkt.GetParameterVal("teller_id"       , stBody.teller_id);


		pkt.GetParameterVal("teller_id"         , stBody.teller_id);

		return 0;
	};
	// 组建报文：结构 -> 报文
	static int Struct2Packet(RiskAlarmParaRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"   , stBody.alm_result);
		return 0;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 报文解析： 结构 -> 报文    代理机构风险统计清单查询请求报文
	static int Struct2Packet(BranchRiskStatQryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		return 0;
	}

	// 报文解析：报文 -> 结构    代理机构风险统计清单查询请求报文
	static int Packet2Struct(BranchRiskStatQryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		return 0;
	}
	// 报文解析： 结构 -> 报文    代理机构风险统计清单查询应答报文
	static int Struct2Packet(BranchRiskStatQryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("rtn_result"         , stBody.rtn_result);
		return 0;
	}

	// 报文解析：报文 -> 结构    代理机构风险统计清单查
	static int Packet2Struct(BranchRiskStatQryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("rtn_result"         , stBody.rtn_result);
		return 0;
	}

	//------------------------------------报文接口[3307]处理 开始 add by liuwei 2012-8-16
	//结构->报文  三级代理机构风险指标查询请求报文
	static int Struct2Packet(SubAgentRiskIndexQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag", stBody.oper_flag);
		pkt.AddParameter("branch_id", stBody.branch_id);
		return 0;
	}

	//报文->结构  三级代理机构风险指标查询请求报文
	static int Packet2Struct(SubAgentRiskIndexQueryReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		pkt.GetParameterVal("branch_id", stBody.branch_id);
		return 0;
	}

	//结构->报文  三级代理机构风险指标查询应答报文
	static int Struct2Packet(SubAgentRiskIndexQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag", stBody.oper_flag);
		pkt.AddParameter("alm_result", stBody.alm_result);
		return 0;
	}

	//报文->结构  三级代理机构风险指标查询应答报文
	static int Packet2Struct(SubAgentRiskIndexQueryRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		pkt.GetParameterVal("alm_result", stBody.alm_result);
		return 0;
	}
	//------------------------------------报文接口[3307]处理 结束 add by liuwei 2012-8-16

	//------------------------------------报文接口[3308]处理 开始 add by liuwei 2012-8-16
	//结构->报文  三级代理机构风险参数配置请求报文
	static int Struct2Packet(SubAgentRiskParaSetReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag", stBody.oper_flag);
		pkt.AddParameter("query_condition", stBody.query_condition);
		return 0;
	}

	//报文->结构  三级代理机构风险参数配置请求报文
	static int Packet2Struct(SubAgentRiskParaSetReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		pkt.GetParameterVal("query_condition", stBody.query_condition);
		return 0;
	}

	//结构->报文  三级代理机构风险参数配置应答报文
	static int Struct2Packet(SubAgentRiskParaSetRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag", stBody.oper_flag);
		pkt.AddParameter("alm_result", stBody.alm_result);
		return 0;
	}

	//报文->结构  三级代理机构风险参数配置应答报文
	static int Packet2Struct(SubAgentRiskParaSetRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		pkt.GetParameterVal("alm_result", stBody.alm_result);
		return 0;
	}
	//------------------------------------报文接口[3308]处理 结束 add by liuwei 2012-8-16

	//------------------------------------报文接口[3309]处理 开始 add by liuwei 2012-9-14
	// 报文解析：报文 -> 结构    生成自动强平单请求
	static int Packet2Struct(AutoGenFCOrderBatchReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("gen_condition"     , stBody.gen_condition);
		pkt.GetParameterVal("fc_mode"			, stBody.fc_mode);
		pkt.GetParameterVal("teller_id"         , stBody.teller_id);
		pkt.GetParameterVal("posi_result"       , stBody.posi_result);
		pkt.GetParameterVal("cov_price_info"       , stBody.cov_price_info);
		pkt.GetParameterVal("risk_target"       , stBody.risk_target);
		return 0;
	}

	// 报文解析：报文 -> 结构    生成自动强平单响应
	static int Packet2Struct(AutoGenFCOrderBatchRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    生成自动强平单请求
	static int Struct2Packet(AutoGenFCOrderBatchReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("gen_condition"     , stBody.gen_condition);
		pkt.AddParameter("fc_mode"			 , stBody.fc_mode);
		pkt.AddParameter("teller_id"         , stBody.teller_id);
		pkt.AddParameter("posi_result"       , stBody.posi_result);
		pkt.AddParameter("cov_price_info"    , stBody.cov_price_info);
		pkt.AddParameter("risk_target"       , stBody.risk_target);
		return 0;
	}


	// 报文解析： 结构 -> 报文    生成自动强平单响应
	static int Struct2Packet(AutoGenFCOrderBatchRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	}
	//------------------------------------报文接口[3309]处理 结束 add by liuwei 2012-9-14

	//------------------------------------报文接口[3310]处理 开始 add by liuwei 2012-9-14
	// 报文解析：报文 -> 结构    发送强平单请求
	static int Packet2Struct(FCOrderSubmitBatchReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("force_order"       , stBody.force_order);
		return 0;
	}

	// 报文解析：报文 -> 结构    发送强平单请求响应
	static int Packet2Struct(FCOrderSubmitBatchRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    发送强平单请求
	static int Struct2Packet(FCOrderSubmitBatchReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("force_order"       , stBody.force_order);
		return 0;
	}


	// 报文解析： 结构 -> 报文    发送强平单请求响应
	static int Struct2Packet(FCOrderSubmitBatchRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	}

	//------------------------------------报文接口[3310]处理 结束 add by liuwei 2012-9-14

	//----------------------------------------------报文接口 [3312] 报文结构相关解析
	// 报文解析：报文 -> 结构    内部划转申请/复核的请求报文体
	static int Packet2Struct(InOutCustListReq& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("instid"            , stBody.instid);
		pkt.GetParameterVal("page_no"            , stBody.page_no);
		pkt.GetParameterVal("page_size"            , stBody.page_size);
		pkt.GetParameterVal("total_record"            , stBody.total_record);
		return 0;
	}

	// 报文解析：报文 -> 结构   风险试算响应报文体，支持分页
	static int Packet2Struct(InOutCustListRsp& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("cal_result"        , stBody.cal_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文   风险试算请求报文体，支持分页
	static int Struct2Packet(InOutCustListReq& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("instid"            , stBody.instid);
		pkt.AddParameter("page_no"            , stBody.page_no);
		pkt.AddParameter("page_size"            , stBody.page_size);
		pkt.AddParameter("total_record"            , stBody.total_record);
		return 0;
	}


	// 报文解析： 结构 -> 报文    内部划转申请/复核的响应报文体
	static int Struct2Packet(InOutCustListRsp& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("cal_result"        , stBody.cal_result);
		return 0;
	}

	//----------------------------------------------报文接口 [3321] 报文结构相关解析
	// 报文解析：报文 -> 结构    交易统一请求报文
	static int Packet2Struct(RiskCustQueryReqByTrade& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("account_no"         , stBody.account_no);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("risk_grade_id"     , stBody.risk_grade_id);
		return 0;
	}

	// 报文解析：报文 -> 结构    交易统一请求报文
	static int Packet2Struct(RiskCustQueryRspByTrade& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("alm_result"        , stBody.alm_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    交易统一请求报文
	static int Struct2Packet(RiskCustQueryReqByTrade& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("account_no"         , stBody.account_no);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("risk_grade_id"     , stBody.risk_grade_id);
		return 0;
	}


	// 报文解析： 结构 -> 报文    交易统一请求报文
	static int Struct2Packet(RiskCustQueryRspByTrade& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("alm_result"        , stBody.alm_result);
		return 0;
	}

};

#endif