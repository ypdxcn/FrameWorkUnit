#ifndef _PACKET_STRUCT_TRANSFER_BROADCAST_RISK_H                 
#define _PACKET_STRUCT_TRANSFER_BROADCAST_RISK_H    
#include "BroadcastPacket.h"
#include "PacketBodyStructBroadcastRisk.h"

class CPacketStructBroadcastRisk
{
//A1接口
public:
	///////////////////////////////////////////////////////////////////////////////
	//如下是报文工具自动生成
	///////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------报文接口 [onRecvRtnSpotMatch] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnSpotMatch
	static int Packet2Struct(SpotMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"          , stBody.matchNo );
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.clientType);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.price);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.localOrderNo);
		pkt.GetParameterVal("matchType"         , stBody.matchType);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnSpotMatch
	static int Struct2Packet(SpotMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"          , stBody.matchNo );
		pkt.AddParameter("buyOrSell"         , stBody.buyOrSell);
		pkt.AddParameter("clientID"          , stBody.clientID);
		pkt.AddParameter("clientType"        , stBody.clientType);
		pkt.AddParameter("memberID"          , stBody.memberID);
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("matchDate"         , stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.matchTime);
		pkt.AddParameter("price"             , stBody.price);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("orderNo"           , stBody.orderNo);
		pkt.AddParameter("localOrderNo"      , stBody.localOrderNo);
		pkt.AddParameter("matchType"         , stBody.matchType);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnForwardMatch] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnForwardMatch
	static int Packet2Struct(ForwardMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.matchNo);
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.clientType);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.price);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("marginRate"        , stBody.marginRate);
		pkt.GetParameterVal("rateType"          , stBody.rateType);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.localOrderNo);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnForwardMatch
	static int Struct2Packet(ForwardMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           , stBody.matchNo);
		pkt.AddParameter("buyOrSell"         , stBody.buyOrSell);
		pkt.AddParameter("clientID"          , stBody.clientID);
		pkt.AddParameter("clientType"        , stBody.clientType);
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("memberID"          , stBody.memberID);
		pkt.AddParameter("matchDate"         , stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.matchTime);
		pkt.AddParameter("price"             , stBody.price);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("marginRate"        , stBody.marginRate);
		pkt.AddParameter("rateType"          , stBody.rateType);
		pkt.AddParameter("orderNo"           , stBody.orderNo);
		pkt.AddParameter("localOrderNo"      , stBody.localOrderNo);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnDeferMatch] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnDeferMatch
	static int Packet2Struct(DeferMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.matchNo);
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.clientType);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.price);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("offsetFlag"        , stBody.offsetFlag);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.localOrderNo);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnDeferMatch
	static int Struct2Packet(DeferMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           , stBody.matchNo);
		pkt.AddParameter("buyOrSell"         , stBody.buyOrSell);
		pkt.AddParameter("clientID"          , stBody.clientID);
		pkt.AddParameter("clientType"        , stBody.clientType);
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("memberID"          , stBody.memberID);
		pkt.AddParameter("matchDate"         , stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.matchTime);
		pkt.AddParameter("price"             , stBody.price);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("offsetFlag"        , stBody.offsetFlag);
		pkt.AddParameter("orderNo"           , stBody.orderNo);
		pkt.AddParameter("localOrderNo"      , stBody.localOrderNo);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppMatch] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnDeferDeliveryAppMatch
	static int Packet2Struct(DeferDeliveryAppMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.matchNo);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("LocalOrderNo"      , stBody.LocalOrderNo);
		pkt.GetParameterVal("middleFlag"        , stBody.middleFlag);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnDeferDeliveryAppMatch
	static int Struct2Packet(DeferDeliveryAppMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           , stBody.matchNo);
		pkt.AddParameter("clientID"          , stBody.clientID);
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("memberID"          , stBody.memberID);
		pkt.AddParameter("buyOrSell"         , stBody.buyOrSell);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("matchDate"         , stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.matchTime);
		pkt.AddParameter("orderNo"           , stBody.orderNo);
		pkt.AddParameter("LocalOrderNo"      , stBody.LocalOrderNo);
		pkt.AddParameter("middleFlag"        , stBody.middleFlag);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		return 0;
	}


	
	//----------------------------------------------报文接口 [onRecvRtnETFMatch] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnETFMatch
	static int Packet2Struct(ETFMatch& stBody, CBroadcastPacket& pkt)			//add by luobaolin 2013-3-19
	{
		pkt.GetParameterVal("orderNo"         		 , stBody.orderNo			);
		pkt.GetParameterVal("b_etf_trade_type"        	 , stBody.b_etf_trade_type	    );
		pkt.GetParameterVal("acct_no"        			 , stBody.acct_no				);
		pkt.GetParameterVal("etf_id"        			 , stBody.etf_id				);
		pkt.GetParameterVal("exch_date"        			 , stBody.exch_date			    );
		pkt.GetParameterVal("prod_code1"          		 , stBody.prod_code1			);
		pkt.GetParameterVal("day_cash_balance1"          , stBody.day_cash_balance1	    );
		pkt.GetParameterVal("weight1"          			 , stBody.weight1				);
		pkt.GetParameterVal("prod_code2"          		 , stBody.prod_code2			);
		pkt.GetParameterVal("day_cash_balance2"          , stBody.day_cash_balance2	    );
		pkt.GetParameterVal("weight2"         			 , stBody.weight2				);
		pkt.GetParameterVal("prod_code3"        		 , stBody.prod_code3			);
		pkt.GetParameterVal("day_cash_balance3"          , stBody.day_cash_balance3	    );
		pkt.GetParameterVal("weight3"          			 , stBody.weight3			    );
		pkt.GetParameterVal("prod_code4"       		     , stBody.prod_code4			);
		pkt.GetParameterVal("day_cash_balance4"          , stBody.day_cash_balance4	    );
		pkt.GetParameterVal("weight4"          			 , stBody.weight4				);
		pkt.GetParameterVal("prod_code5"       		     , stBody.prod_code5			);
		pkt.GetParameterVal("day_cash_balance5"          , stBody.day_cash_balance5	    );
		pkt.GetParameterVal("weight5"         			 , stBody.weight5				);
		pkt.GetParameterVal("froz_trans_fee"         	 , stBody.froz_trans_fee		);
		pkt.GetParameterVal("froz_diff_fee"         	 , stBody.froz_diff_fee 		);
		pkt.GetParameterVal("local_order_no"            , stBody.local_order_no		    );
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnETFMatch
	static int Struct2Packet(ETFMatch& stBody, CBroadcastPacket& pkt)			//add by luobaolin 2013-3-19
	{
		pkt.AddParameter("orderNo"         		 , stBody.orderNo			);
		pkt.AddParameter("b_etf_trade_type"        	 , stBody.b_etf_trade_type	    );
		pkt.AddParameter("acct_no"        			 , stBody.acct_no				);
		pkt.AddParameter("etf_id"        			 , stBody.etf_id				);
		pkt.AddParameter("exch_date"        		 , stBody.exch_date				);
		pkt.AddParameter("prod_code1"          		 , stBody.prod_code1			);
		pkt.AddParameter("day_cash_balance1"         , stBody.day_cash_balance1		);
		pkt.AddParameter("weight1"          		 , stBody.weight1			    );
		pkt.AddParameter("prod_code2"          		 , stBody.prod_code2			);
		pkt.AddParameter("day_cash_balance2"         , stBody.day_cash_balance2		);
		pkt.AddParameter("weight2"         			 , stBody.weight2				);
		pkt.AddParameter("prod_code3"        		 , stBody.prod_code3			);
		pkt.AddParameter("day_cash_balance3"         , stBody.day_cash_balance3		);
		pkt.AddParameter("weight3"          		 , stBody.weight3				);
		pkt.AddParameter("prod_code4"       		 , stBody.prod_code4			);
		pkt.AddParameter("day_cash_balance4"         , stBody.day_cash_balance4		);
		pkt.AddParameter("weight4"          		 , stBody.weight4				);
		pkt.AddParameter("prod_code5"       		 , stBody.prod_code5			);
		pkt.AddParameter("day_cash_balance5"         , stBody.day_cash_balance5		);
		pkt.AddParameter("weight5"         			 , stBody.weight5				);
		pkt.AddParameter("froz_trans_fee"         	 , stBody.froz_trans_fee		);
		pkt.AddParameter("froz_diff_fee"         	 , stBody.froz_diff_fee 		);
		pkt.AddParameter("local_order_no"           , stBody.local_order_no		);
		return 0;
	}


	//----------------------------------------------报文接口 [onRecvSpotQuotation] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvSpotQuotation
	static int Packet2Struct(SpotQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("lastClose"         , stBody.lastClose);
		pkt.GetParameterVal("open"              , stBody.open);
		pkt.GetParameterVal("high"              , stBody.high);
		pkt.GetParameterVal("low"               , stBody.low);
		pkt.GetParameterVal("last"              , stBody.last);
		pkt.GetParameterVal("close"             , stBody.close);
		pkt.GetParameterVal("bid1"              , stBody.bid1);
		pkt.GetParameterVal("bidLot1"           , stBody.bidLot1);
		pkt.GetParameterVal("bid2"              , stBody.bid2);
		pkt.GetParameterVal("bidLot2"           , stBody.bidLot2);
		pkt.GetParameterVal("bid3"              , stBody.bid3);
		pkt.GetParameterVal("bidLot3"           , stBody.bidLot3);
		pkt.GetParameterVal("bid4"              , stBody.bid4);
		pkt.GetParameterVal("bidLot4"           , stBody.bidLot4);
		pkt.GetParameterVal("bid5"              , stBody.bid5);
		pkt.GetParameterVal("bidLot5"           , stBody.bidLot5);
		pkt.GetParameterVal("ask1"              , stBody.ask1);
		pkt.GetParameterVal("askLot1"           , stBody.askLot1);
		pkt.GetParameterVal("ask2"              , stBody.ask2);
		pkt.GetParameterVal("askLot2"           , stBody.askLot2);
		pkt.GetParameterVal("ask3"              , stBody.ask3);
		pkt.GetParameterVal("askLot3"           , stBody.askLot3);
		pkt.GetParameterVal("ask4"              , stBody.ask4);
		pkt.GetParameterVal("askLot4"           , stBody.askLot4);
		pkt.GetParameterVal("ask5"              , stBody.ask5);
		pkt.GetParameterVal("askLot5"           , stBody.askLot5);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("weight"            , stBody.weight);
		pkt.GetParameterVal("highLimit"         , stBody.highLimit);
		pkt.GetParameterVal("lowLimit"          , stBody.lowLimit);
		pkt.GetParameterVal("upDown"            , stBody.upDown);
		pkt.GetParameterVal("upDownRate"        , stBody.upDownRate);
		pkt.GetParameterVal("turnOver"          , stBody.turnOver);
		pkt.GetParameterVal("average"           , stBody.average);
		pkt.GetParameterVal("quoteDate"         , stBody.quoteDate);
		pkt.GetParameterVal("quoteTime"         , stBody.quoteTime);
		pkt.GetParameterVal("sequenceNo"        , stBody.sequenceNo);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvSpotQuotation
	static int Struct2Packet(SpotQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("lastClose"         , stBody.lastClose);
		pkt.AddParameter("open"              , stBody.open);
		pkt.AddParameter("high"              , stBody.high);
		pkt.AddParameter("low"               , stBody.low);
		pkt.AddParameter("last"              , stBody.last);
		pkt.AddParameter("close"             , stBody.close);
		pkt.AddParameter("bid1"              , stBody.bid1);
		pkt.AddParameter("bidLot1"           , stBody.bidLot1);
		pkt.AddParameter("bid2"              , stBody.bid2);
		pkt.AddParameter("bidLot2"           , stBody.bidLot2);
		pkt.AddParameter("bid3"              , stBody.bid3);
		pkt.AddParameter("bidLot3"           , stBody.bidLot3);
		pkt.AddParameter("bid4"              , stBody.bid4);
		pkt.AddParameter("bidLot4"           , stBody.bidLot4);
		pkt.AddParameter("bid5"              , stBody.bid5);
		pkt.AddParameter("bidLot5"           , stBody.bidLot5);
		pkt.AddParameter("ask1"              , stBody.ask1);
		pkt.AddParameter("askLot1"           , stBody.askLot1);
		pkt.AddParameter("ask2"              , stBody.ask2);
		pkt.AddParameter("askLot2"           , stBody.askLot2);
		pkt.AddParameter("ask3"              , stBody.ask3);
		pkt.AddParameter("askLot3"           , stBody.askLot3);
		pkt.AddParameter("ask4"              , stBody.ask4);
		pkt.AddParameter("askLot4"           , stBody.askLot4);
		pkt.AddParameter("ask5"              , stBody.ask5);
		pkt.AddParameter("askLot5"           , stBody.askLot5);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("weight"            , stBody.weight);
		pkt.AddParameter("highLimit"         , stBody.highLimit);
		pkt.AddParameter("lowLimit"          , stBody.lowLimit);
		pkt.AddParameter("upDown"            , stBody.upDown);
		pkt.AddParameter("upDownRate"        , stBody.upDownRate);
		pkt.AddParameter("turnOver"          , stBody.turnOver);
		pkt.AddParameter("average"           , stBody.average);
		pkt.AddParameter("quoteDate"         , stBody.quoteDate);
		pkt.AddParameter("quoteTime"         , stBody.quoteTime);
		pkt.AddParameter("sequenceNo"        , stBody.sequenceNo);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvForwardQuotation] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvForwardQuotation
	static int Packet2Struct(ForwardQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("lastSettle"        , stBody.lastSettle);
		pkt.GetParameterVal("lastClose"         , stBody.lastClose);
		pkt.GetParameterVal("open"              , stBody.open);
		pkt.GetParameterVal("high"              , stBody.high);
		pkt.GetParameterVal("low"               , stBody.low);
		pkt.GetParameterVal("last"              , stBody.last);
		pkt.GetParameterVal("close"             , stBody.close);
		pkt.GetParameterVal("settle"            , stBody.settle);
		pkt.GetParameterVal("bid1"              , stBody.bid1);
		pkt.GetParameterVal("bidLot1"           , stBody.bidLot1);
		pkt.GetParameterVal("bid2"              , stBody.bid2);
		pkt.GetParameterVal("bidLot2"           , stBody.bidLot2);
		pkt.GetParameterVal("bid3"              , stBody.bid3);
		pkt.GetParameterVal("bidLot3"           , stBody.bidLot3);
		pkt.GetParameterVal("bid4"              , stBody.bid4);
		pkt.GetParameterVal("bidLot4"           , stBody.bidLot4);
		pkt.GetParameterVal("bid5"              , stBody.bid5);
		pkt.GetParameterVal("bidLot5"           , stBody.bidLot5);
		pkt.GetParameterVal("ask1"              , stBody.ask1);
		pkt.GetParameterVal("askLot1"           , stBody.askLot1);
		pkt.GetParameterVal("ask2"              , stBody.ask2);
		pkt.GetParameterVal("askLot2"           , stBody.askLot2);
		pkt.GetParameterVal("ask3"              , stBody.ask3);
		pkt.GetParameterVal("askLot3"           , stBody.askLot3);
		pkt.GetParameterVal("ask4"              , stBody.ask4);
		pkt.GetParameterVal("askLot4"           , stBody.askLot4);
		pkt.GetParameterVal("ask5"              , stBody.ask5);
		pkt.GetParameterVal("askLot5"           , stBody.askLot5);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("weight"            , stBody.weight);
		pkt.GetParameterVal("highLimit"         , stBody.highLimit);
		pkt.GetParameterVal("lowLimit"          , stBody.lowLimit);
		pkt.GetParameterVal("Posi"              , stBody.Posi);
		pkt.GetParameterVal("upDown"            , stBody.upDown);
		pkt.GetParameterVal("upDownRate"        , stBody.upDownRate);
		pkt.GetParameterVal("turnOver"          , stBody.turnOver);
		pkt.GetParameterVal("average"           , stBody.average);
		pkt.GetParameterVal("quoteDate"         , stBody.quoteDate);
		pkt.GetParameterVal("quoteTime"         , stBody.quoteTime);
		pkt.GetParameterVal("sequenceNo"        , stBody.sequenceNo);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvForwardQuotation
	static int Struct2Packet(ForwardQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("lastSettle"        , stBody.lastSettle);
		pkt.AddParameter("lastClose"         , stBody.lastClose);
		pkt.AddParameter("open"              , stBody.open);
		pkt.AddParameter("high"              , stBody.high);
		pkt.AddParameter("low"               , stBody.low);
		pkt.AddParameter("last"              , stBody.last);
		pkt.AddParameter("close"             , stBody.close);
		pkt.AddParameter("settle"            , stBody.settle);
		pkt.AddParameter("bid1"              , stBody.bid1);
		pkt.AddParameter("bidLot1"           , stBody.bidLot1);
		pkt.AddParameter("bid2"              , stBody.bid2);
		pkt.AddParameter("bidLot2"           , stBody.bidLot2);
		pkt.AddParameter("bid3"              , stBody.bid3);
		pkt.AddParameter("bidLot3"           , stBody.bidLot3);
		pkt.AddParameter("bid4"              , stBody.bid4);
		pkt.AddParameter("bidLot4"           , stBody.bidLot4);
		pkt.AddParameter("bid5"              , stBody.bid5);
		pkt.AddParameter("bidLot5"           , stBody.bidLot5);
		pkt.AddParameter("ask1"              , stBody.ask1);
		pkt.AddParameter("askLot1"           , stBody.askLot1);
		pkt.AddParameter("ask2"              , stBody.ask2);
		pkt.AddParameter("askLot2"           , stBody.askLot2);
		pkt.AddParameter("ask3"              , stBody.ask3);
		pkt.AddParameter("askLot3"           , stBody.askLot3);
		pkt.AddParameter("ask4"              , stBody.ask4);
		pkt.AddParameter("askLot4"           , stBody.askLot4);
		pkt.AddParameter("ask5"              , stBody.ask5);
		pkt.AddParameter("askLot5"           , stBody.askLot5);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("weight"            , stBody.weight);
		pkt.AddParameter("highLimit"         , stBody.highLimit);
		pkt.AddParameter("lowLimit"          , stBody.lowLimit);
		pkt.AddParameter("Posi"              , stBody.Posi);
		pkt.AddParameter("upDown"            , stBody.upDown);
		pkt.AddParameter("upDownRate"        , stBody.upDownRate);
		pkt.AddParameter("turnOver"          , stBody.turnOver);
		pkt.AddParameter("average"           , stBody.average);
		pkt.AddParameter("quoteDate"         , stBody.quoteDate);
		pkt.AddParameter("quoteTime"         , stBody.quoteTime);
		pkt.AddParameter("sequenceNo"        , stBody.sequenceNo);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvDeferQuotation] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvDeferQuotation
	static int Packet2Struct(DeferQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("lastSettle"        , stBody.lastSettle);
		pkt.GetParameterVal("lastClose"         , stBody.lastClose);
		pkt.GetParameterVal("open"              , stBody.open);
		pkt.GetParameterVal("high"              , stBody.high);
		pkt.GetParameterVal("low"               , stBody.low);
		pkt.GetParameterVal("last"              , stBody.last);
		pkt.GetParameterVal("close"             , stBody.close);
		pkt.GetParameterVal("settle"            , stBody.settle);
		pkt.GetParameterVal("bid1"              , stBody.bid1);
		pkt.GetParameterVal("bidLot1"           , stBody.bidLot1);
		pkt.GetParameterVal("bid2"              , stBody.bid2);
		pkt.GetParameterVal("bidLot2"           , stBody.bidLot2);
		pkt.GetParameterVal("bid3"              , stBody.bid3);
		pkt.GetParameterVal("bidLot3"           , stBody.bidLot3);
		pkt.GetParameterVal("bid4"              , stBody.bid4);
		pkt.GetParameterVal("bidLot4"           , stBody.bidLot4);
		pkt.GetParameterVal("bid5"              , stBody.bid5);
		pkt.GetParameterVal("bidLot5"           , stBody.bidLot5);
		pkt.GetParameterVal("ask1"              , stBody.ask1);
		pkt.GetParameterVal("askLot1"           , stBody.askLot1);
		pkt.GetParameterVal("ask2"              , stBody.ask2);
		pkt.GetParameterVal("askLot2"           , stBody.askLot2);
		pkt.GetParameterVal("ask3"              , stBody.ask3);
		pkt.GetParameterVal("askLot3"           , stBody.askLot3);
		pkt.GetParameterVal("ask4"              , stBody.ask4);
		pkt.GetParameterVal("askLot4"           , stBody.askLot4);
		pkt.GetParameterVal("ask5"              , stBody.ask5);
		pkt.GetParameterVal("askLot5"           , stBody.askLot5);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("weight"            , stBody.weight);
		pkt.GetParameterVal("highLimit"         , stBody.highLimit);
		pkt.GetParameterVal("lowLimit"          , stBody.lowLimit);
		pkt.GetParameterVal("Posi"              , stBody.Posi);
		pkt.GetParameterVal("upDown"            , stBody.upDown);
		pkt.GetParameterVal("upDownRate"        , stBody.upDownRate);
		pkt.GetParameterVal("turnOver"          , stBody.turnOver);
		pkt.GetParameterVal("average"           , stBody.average);
		pkt.GetParameterVal("quoteDate"         , stBody.quoteDate);
		pkt.GetParameterVal("quoteTime"         , stBody.quoteTime);
		pkt.GetParameterVal("sequenceNo"        , stBody.sequenceNo);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvDeferQuotation
	static int Struct2Packet(DeferQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("lastSettle"        , stBody.lastSettle);
		pkt.AddParameter("lastClose"         , stBody.lastClose);
		pkt.AddParameter("open"              , stBody.open);
		pkt.AddParameter("high"              , stBody.high);
		pkt.AddParameter("low"               , stBody.low);
		pkt.AddParameter("last"              , stBody.last);
		pkt.AddParameter("close"             , stBody.close);
		pkt.AddParameter("settle"            , stBody.settle);
		pkt.AddParameter("bid1"              , stBody.bid1);
		pkt.AddParameter("bidLot1"           , stBody.bidLot1);
		pkt.AddParameter("bid2"              , stBody.bid2);
		pkt.AddParameter("bidLot2"           , stBody.bidLot2);
		pkt.AddParameter("bid3"              , stBody.bid3);
		pkt.AddParameter("bidLot3"           , stBody.bidLot3);
		pkt.AddParameter("bid4"              , stBody.bid4);
		pkt.AddParameter("bidLot4"           , stBody.bidLot4);
		pkt.AddParameter("bid5"              , stBody.bid5);
		pkt.AddParameter("bidLot5"           , stBody.bidLot5);
		pkt.AddParameter("ask1"              , stBody.ask1);
		pkt.AddParameter("askLot1"           , stBody.askLot1);
		pkt.AddParameter("ask2"              , stBody.ask2);
		pkt.AddParameter("askLot2"           , stBody.askLot2);
		pkt.AddParameter("ask3"              , stBody.ask3);
		pkt.AddParameter("askLot3"           , stBody.askLot3);
		pkt.AddParameter("ask4"              , stBody.ask4);
		pkt.AddParameter("askLot4"           , stBody.askLot4);
		pkt.AddParameter("ask5"              , stBody.ask5);
		pkt.AddParameter("askLot5"           , stBody.askLot5);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("weight"            , stBody.weight);
		pkt.AddParameter("highLimit"         , stBody.highLimit);
		pkt.AddParameter("lowLimit"          , stBody.lowLimit);
		pkt.AddParameter("Posi"              , stBody.Posi);
		pkt.AddParameter("upDown"            , stBody.upDown);
		pkt.AddParameter("upDownRate"        , stBody.upDownRate);
		pkt.AddParameter("turnOver"          , stBody.turnOver);
		pkt.AddParameter("average"           , stBody.average);
		pkt.AddParameter("quoteDate"         , stBody.quoteDate);
		pkt.AddParameter("quoteTime"         , stBody.quoteTime);
		pkt.AddParameter("sequenceNo"        , stBody.sequenceNo);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnSpotInstStateUpdate] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnSpotInstStateUpdate
	static int Packet2Struct(SpotInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("tradeState"        , stBody.tradeState);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnSpotInstStateUpdate
	static int Struct2Packet(SpotInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("tradeState"        , stBody.tradeState);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnForwardInstStateUpdate] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnForwardInstStateUpdate
	static int Packet2Struct(ForwardInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("tradeState"        , stBody.tradeState);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnForwardInstStateUpdate
	static int Struct2Packet(ForwardInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("tradeState"        , stBody.tradeState);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnDeferInstStateUpdate] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnDeferInstStateUpdate
	static int Packet2Struct(DeferInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("tradeState"        , stBody.tradeState);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnDeferInstStateUpdate
	static int Struct2Packet(DeferInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("tradeState"        , stBody.tradeState);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnSpotMarketStateUpdate] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnSpotMarketStateUpdate
	static int Packet2Struct(SpotMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("marketID"          , stBody.marketID);
		pkt.GetParameterVal("marketState"       , stBody.marketState);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnSpotMarketStateUpdate
	static int Struct2Packet(SpotMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("marketID"          , stBody.marketID);
		pkt.AddParameter("marketState"       , stBody.marketState);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnForwardMarketStateUpdate] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnForwardMarketStateUpdate
	static int Packet2Struct(ForwardMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("marketID"          , stBody.marketID);
		pkt.GetParameterVal("marketState"       , stBody.marketState);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnForwardMarketStateUpdate
	static int Struct2Packet(ForwardMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("marketID"          , stBody.marketID);
		pkt.AddParameter("marketState"       , stBody.marketState);
		return 0;
	}



	//----------------------------------------------报文接口 [onRecvRtnDeferMarketStateUpdate] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnDeferMarketStateUpdate
	static int Packet2Struct(DeferMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("marketID"          , stBody.marketID);
		pkt.GetParameterVal("marketState"       , stBody.marketState);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnDeferMarketStateUpdate
	static int Struct2Packet(DeferMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("marketID"          , stBody.marketID);
		pkt.AddParameter("marketState"       , stBody.marketState);
		return 0;
	}



	//----------------------------------------------报文接口 [onAcctCapitalAccess] 报文结构相关解析
	// 报文解析：报文 -> 结构    onAcctCapitalAccess
	static int Packet2Struct(AcctCapitalAccess& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("fund_src_type"     , stBody.fund_src_type);
		pkt.GetParameterVal("serial_no"         , stBody.serial_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("access_way"        , stBody.access_way);
		pkt.GetParameterVal("amount"            , stBody.amount);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onAcctCapitalAccess
	static int Struct2Packet(AcctCapitalAccess& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("fund_src_type"     , stBody.fund_src_type);
		pkt.AddParameter("serial_no"         , stBody.serial_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("access_way"        , stBody.access_way);
		pkt.AddParameter("amount"            , stBody.amount);
		return 0;
	}



	//----------------------------------------------报文接口 [onCustInfoChange] 报文结构相关解析
	// 报文解析：报文 -> 结构    onCustInfoChange
	static int Packet2Struct(CustInfoChange& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("update_flag"       , stBody.update_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("member_id"         , stBody.member_id);
		pkt.GetParameterVal("cust_abbr"         , stBody.cust_abbr);
		pkt.GetParameterVal("m_fare_model_id"   , stBody.m_Fare_model_id);
		pkt.GetParameterVal("b_fare_model_id"   , stBody.b_Fare_model_id);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("acct_stat"         , stBody.acct_stat);
		pkt.GetParameterVal("branch_id"         , stBody.branch_ID);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onCustInfoChange
	static int Struct2Packet(CustInfoChange& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("update_flag"       , stBody.update_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("member_id"         , stBody.member_id);
		pkt.AddParameter("cust_abbr"         , stBody.cust_abbr);
		pkt.AddParameter("m_fare_model_id"   , stBody.m_Fare_model_id);
		pkt.AddParameter("b_fare_model_id"   , stBody.b_Fare_model_id);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("acct_stat"         , stBody.acct_stat);
		pkt.AddParameter("branch_id"         , stBody.branch_ID);
		return 0;
	}


	//----------------------------------------------报文接口 [onCustCancelNotify] 报文结构相关解析
	// 报文解析：报文 -> 结构    onCustCancelNotify
	static int Packet2Struct(CustCancelNotify& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("acct_no"			    , stBody.acct_no);
		pkt.GetParameterVal("cancel_sys_date"       , stBody.cancel_sys_date);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onCustInfoChange
	static int Struct2Packet(CustCancelNotify& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("cancel_sys_date"       , stBody.cancel_sys_date);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		return 0;
	}


	//----------------------------------------------报文接口 [onAck] 报文结构相关解析
	// 报文解析：报文 -> 结构    onAck
	static int Packet2Struct(Ack& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("ack"               , stBody.ack);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onAck
	static int Struct2Packet(Ack& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("ack"               , stBody.ack);
		return 0;
	}

//F2接口 
public:
	///////////////////////////////////////////////////////////////////////////////
	//如下是报文工具自动生成
	///////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------报文接口 [onBranchRiskStat] 报文结构相关解析
	// 报文解析：报文 -> 结构    onBranchRiskStat
	static int Packet2Struct(BranchRiskStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("rtn_result"        , stBody.rtn_result);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onBranchRiskStat
	static int Struct2Packet(BranchRiskStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("rtn_result"        , stBody.rtn_result);
		return 0;
	}


	//----------------------------------------------报文接口 [onCustRiskChangeNtf] 报文结构相关解析
	// 报文解析：报文 -> 结构    onCustRiskChangeNtf
	static int Packet2Struct(CustRiskChangeNtf& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("cust_abbr"         , stBody.cust_abbr);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("cust_type"         , stBody.cust_type);
		pkt.GetParameterVal("branch_id"         , stBody.branch_id);
		pkt.GetParameterVal("branch_name"       , stBody.branch_name);
		pkt.GetParameterVal("debt_mem"          , stBody.debt_mem);
		pkt.GetParameterVal("debt_exch_abs"     , stBody.debt_exch_abs);
		pkt.GetParameterVal("debt_exch_rel"     , stBody.debt_exch_rel);
		pkt.GetParameterVal("debt_call_line"    , stBody.debt_call_line);
		pkt.GetParameterVal("risk_grade_yda"    , stBody.risk_grade_yda);
		pkt.GetParameterVal("risk_type_yda"     , stBody.risk_type_yda);
		pkt.GetParameterVal("risk_degree1_from"  , stBody.risk_degree1_from);
		pkt.GetParameterVal("risk_degree1_to"    , stBody.risk_degree1_to);
		pkt.GetParameterVal("risk_degree2_from"  , stBody.risk_degree2_from);
		pkt.GetParameterVal("risk_degree2_to"    , stBody.risk_degree2_to);
		pkt.GetParameterVal("risk_grade_from"   , stBody.risk_grade_from);
		pkt.GetParameterVal("risk_grade_to"     , stBody.risk_grade_to);
		pkt.GetParameterVal("risk_type_from"    , stBody.risk_type_from);
		pkt.GetParameterVal("risk_type_to"      , stBody.risk_type_to);
		pkt.GetParameterVal("margin_exch_from"  , stBody.margin_exch_from);
		pkt.GetParameterVal("margin_mem_from"   , stBody.margin_mem_from);
		pkt.GetParameterVal("margin_total_from" , stBody.margin_total_from);
		pkt.GetParameterVal("margin_exch_to"    , stBody.margin_exch_to);
		pkt.GetParameterVal("margin_mem_to"     , stBody.margin_mem_to);
		pkt.GetParameterVal("margin_total_to"   , stBody.margin_total_to);
		pkt.GetParameterVal("curr_bal_from"     , stBody.curr_bal_from);
		pkt.GetParameterVal("curr_bal_to"       , stBody.curr_bal_to);
		pkt.GetParameterVal("float_surplus_from", stBody.float_surplus_from);
		pkt.GetParameterVal("float_surplus_to"  , stBody.float_surplus_to);
		pkt.GetParameterVal("call_margin_from"  , stBody.call_margin_from);
		pkt.GetParameterVal("call_margin_to"    , stBody.call_margin_to);
		pkt.GetParameterVal("creadit_amnt_from" , stBody.creadit_amnt_from);
		pkt.GetParameterVal("creadit_amnt_to"   , stBody.creadit_amnt_to);
		pkt.GetParameterVal("call_margin_yda"   , stBody.call_margin_yda);
		pkt.GetParameterVal("risk_days"         , stBody.risk_days);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onCustRiskChangeNtf
	static int Struct2Packet(CustRiskChangeNtf& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("cust_abbr"         , stBody.cust_abbr);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("cust_type"         , stBody.cust_type);
		pkt.AddParameter("branch_id"         , stBody.branch_id);
		pkt.AddParameter("branch_name"         , stBody.branch_name);
		pkt.AddParameter("debt_mem"          , stBody.debt_mem);
		pkt.AddParameter("debt_exch_abs"     , stBody.debt_exch_abs);
		pkt.AddParameter("debt_exch_rel"     , stBody.debt_exch_rel);
		pkt.AddParameter("debt_call_line"    , stBody.debt_call_line);
		pkt.AddParameter("risk_grade_yda"    , stBody.risk_grade_yda);
		pkt.AddParameter("risk_type_yda"     , stBody.risk_type_yda);
		pkt.AddParameter("risk_degree1_from"  , stBody.risk_degree1_from);
		pkt.AddParameter("risk_degree1_to"    , stBody.risk_degree1_to);
		pkt.AddParameter("risk_degree2_from"  , stBody.risk_degree2_from);
		pkt.AddParameter("risk_degree2_to"    , stBody.risk_degree2_to);
		pkt.AddParameter("risk_grade_from"   , stBody.risk_grade_from);
		pkt.AddParameter("risk_grade_to"     , stBody.risk_grade_to);
		pkt.AddParameter("risk_type_from"    , stBody.risk_type_from);
		pkt.AddParameter("risk_type_to"      , stBody.risk_type_to);
		pkt.AddParameter("margin_exch_from"  , stBody.margin_exch_from);
		pkt.AddParameter("margin_mem_from"   , stBody.margin_mem_from);
		pkt.AddParameter("margin_total_from" , stBody.margin_total_from);
		pkt.AddParameter("margin_exch_to"    , stBody.margin_exch_to);
		pkt.AddParameter("margin_mem_to"     , stBody.margin_mem_to);
		pkt.AddParameter("margin_total_to"   , stBody.margin_total_to);
		pkt.AddParameter("curr_bal_from"     , stBody.curr_bal_from);
		pkt.AddParameter("curr_bal_to"       , stBody.curr_bal_to);
		pkt.AddParameter("float_surplus_from", stBody.float_surplus_from);
		pkt.AddParameter("float_surplus_to"  , stBody.float_surplus_to);
		pkt.AddParameter("call_margin_from"  , stBody.call_margin_from);
		pkt.AddParameter("call_margin_to"    , stBody.call_margin_to);
		pkt.AddParameter("creadit_amnt_from" , stBody.creadit_amnt_from);
		pkt.AddParameter("creadit_amnt_to"   , stBody.creadit_amnt_to);
		pkt.AddParameter("call_margin_yda"   , stBody.call_margin_yda);
		pkt.AddParameter("risk_days"        , stBody.risk_days);
		
		return 0;
	}

	//----------------------------------------------报文接口 [onBaseTableUpdate] 报文结构相关解析
	// 报文解析：报文 -> 结构    onBaseTableUpdate
	static int Packet2Struct(BaseTableUpdate& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("table_name"        , stBody.table_name);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onBaseTableUpdate
	static int Struct2Packet(BaseTableUpdate& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("table_name"        , stBody.table_name);
		return 0;
	}

	//----------------------------------------------报文接口 [onSysInit] 报文结构相关解析
	// 报文解析：报文 -> 结构    onSysInit
	static int Packet2Struct(SysInitStru& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("old_exch_date"     , stBody.old_exch_date);
		pkt.GetParameterVal("new_exch_date"     , stBody.new_exch_date);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onSysInit
	static int Struct2Packet(SysInitStru& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("old_exch_date"     , stBody.old_exch_date);
		pkt.AddParameter("new_exch_date"     , stBody.new_exch_date);
		return 0;
	}

	//----------------------------------------------报文接口 [onSysStatChange] 报文结构相关解析
	// 报文解析：报文 -> 结构    onSysStatChange
	static int Packet2Struct(SysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("sys_date"          , stBody.sys_date);
		pkt.GetParameterVal("exch_date"         , stBody.exch_date);
		pkt.GetParameterVal("m_sys_stat"        , stBody.m_sys_stat);
		pkt.GetParameterVal("b_sys_stat"        , stBody.b_sys_stat);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onSysStatChange
	static int Struct2Packet(SysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("sys_date"          , stBody.sys_date);
		pkt.AddParameter("exch_date"         , stBody.exch_date);
		pkt.AddParameter("m_sys_stat"        , stBody.m_sys_stat);
		pkt.AddParameter("b_sys_stat"        , stBody.b_sys_stat);
		return 0;
	}

	//----------------------------------------------报文接口 [onBourseSysStatChange] 报文结构相关解析 add by zww 2015-5-20
	// 报文解析：报文 -> 结构    onBourseSysStatChange
	static int Packet2Struct(BourseSysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("sys_date"          , stBody.sys_date);
		pkt.GetParameterVal("exch_date"         , stBody.exch_date);
//		pkt.GetParameterVal("m_sys_stat"        , stBody.m_sys_stat);
		pkt.GetParameterVal("b_sys_stat"        , stBody.b_sys_stat);
		pkt.GetParameterVal("bourse_id"        , stBody.bourse_id);
		return 0;
	}


	// 报文解析： 结构 -> 报文    onBourseSysStatChange
	static int Struct2Packet(BourseSysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("sys_date"          , stBody.sys_date);
		pkt.AddParameter("exch_date"         , stBody.exch_date);
//		pkt.AddParameter("m_sys_stat"        , stBody.m_sys_stat);
		pkt.AddParameter("b_sys_stat"        , stBody.b_sys_stat);
		pkt.AddParameter("bourse_id"        , stBody.bourse_id);
		return 0;
	}

	//-----------------------------------------------报文接口 [onForceCovOrderNtf] 报文结构相关解析 add by liuwei 2012-10-22
	// 报文解析：报文 -> 结构 onForceCovOrderNtf
	static int Packet2Struct(ForceCovOrderNtf &stBody, CBroadcastPacket &pkt)
	{
		pkt.GetParameterVal("oper_flag",              stBody.oper_flag);
		pkt.GetParameterVal("client_serial_no",       stBody.client_serial_no);
		pkt.GetParameterVal("local_order_no",         stBody.local_order_no);
		pkt.GetParameterVal("rsp_order_msg",          stBody.rsp_order_msg);
		pkt.GetParameterVal("f_order_no",		 stBody.f_order_no);
		pkt.GetParameterVal("state",                  stBody.state);

		return 0;
	}

	// 报文解析：结构 -> 报文  onForceCovOrderNet
	static int Struct2Packet(ForceCovOrderNtf &stBody, CBroadcastPacket &pkt)
	{
		pkt.AddParameter("oper_flag",        stBody.oper_flag);
		pkt.AddParameter("client_serial_no", stBody.client_serial_no);
		pkt.AddParameter("local_order_no",   stBody.local_order_no);
		pkt.AddParameter("rsp_order_msg",    stBody.rsp_order_msg);
		pkt.AddParameter("f_order_no",		 stBody.f_order_no);
		pkt.AddParameter("state",            stBody.state);

		return 0;
	}

	//-------------------------------------------------报文接口 [onForceCovOrderCancelNtf] 报文结构相关解析 add by liuwei 2012-10-22
	static int Packet2Struct(ForceCovOrderCancelNtf &stBody, CBroadcastPacket &pkt)
	{
		pkt.GetParameterVal("oper_flag", stBody.oper_flag);
		pkt.GetParameterVal("client_serial_no", stBody.client_serial_no);
		pkt.GetParameterVal("local_order_no", stBody.local_order_no);

		return 0;
	}

	static int Struct2Packet(ForceCovOrderCancelNtf & stBody, CBroadcastPacket &pkt)
	{
		pkt.AddParameter("oper_flag", stBody.oper_flag);
		pkt.AddParameter("client_serial_no", stBody.client_serial_no);
		pkt.AddParameter("local_order_no", stBody.local_order_no);

		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRtnFpMatch] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnFpMatch
	static int Packet2Struct(FpMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("MatchNo"       , stBody.MatchNo     );
		pkt.GetParameterVal("MatchDate"     , stBody.MatchDate   );
		pkt.GetParameterVal("DeliDate"      , stBody.DeliDate    );
		pkt.GetParameterVal("MatchGame"     , stBody.MatchGame   );
		pkt.GetParameterVal("MatchRound"    , stBody.MatchRound  );
		pkt.GetParameterVal("MemberID"      , stBody.MemberID    );
		pkt.GetParameterVal("AcctNo"        , stBody.AcctNo      );
		pkt.GetParameterVal("ProdCode"      , stBody.ProdCode    );
		pkt.GetParameterVal("Bs"            , stBody.Bs          );
		pkt.GetParameterVal("MatchPrice"    , stBody.MatchPrice  );
		pkt.GetParameterVal("MatchAmount"   , stBody.MatchAmount );
		pkt.GetParameterVal("EntrPhase"     , stBody.EntrPhase   );
		pkt.GetParameterVal("IsAllocate"    , stBody.IsAllocate  );

		return 0;
	}


	// 报文解析： 结构 -> 报文    onRecvRtnFpMatch
	static int Struct2Packet(FpMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("MatchNo"       , stBody.MatchNo     );
		pkt.AddParameter("MatchDate"     , stBody.MatchDate   );
		pkt.AddParameter("DeliDate"      , stBody.DeliDate    );
		pkt.AddParameter("MatchGame"     , stBody.MatchGame   );
		pkt.AddParameter("MatchRound"    , stBody.MatchRound  );
		pkt.AddParameter("MemberID"      , stBody.MemberID    );
		pkt.AddParameter("AcctNo"        , stBody.AcctNo      );
		pkt.AddParameter("ProdCode"      , stBody.ProdCode    );
		pkt.AddParameter("Bs"            , stBody.Bs          );
		pkt.AddParameter("MatchPrice"    , stBody.MatchPrice  );
		pkt.AddParameter("MatchAmount"   , stBody.MatchAmount );
		pkt.AddParameter("EntrPhase"     , stBody.EntrPhase   );
		pkt.AddParameter("IsAllocate"    , stBody.IsAllocate  );

		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRtnFpQuotation] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnFpQuotation
	static int Packet2Struct(FpQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("ProdCode"          ,stBody.ProdCode       );    
		pkt.GetParameterVal("ProdName"          ,stBody.ProdName       );    
		pkt.GetParameterVal("ExchDate"          ,stBody.ExchDate       );    
		pkt.GetParameterVal("GameID"            ,stBody.GameID         );    
		pkt.GetParameterVal("Price"             ,stBody.Price          );    
		pkt.GetParameterVal("IsSettlePrice"     ,stBody.IsSettlePrice  );    
		pkt.GetParameterVal("MatchVolume"       ,stBody.MatchVolume    );    
		pkt.GetParameterVal("InitPrice"         ,stBody.InitPrice      );    
		pkt.GetParameterVal("Rounds"            ,stBody.Rounds         ); 

		return 0;

	}

	// 报文解析： 结构 -> 报文    onRecvRtnFpQuotation
	static int Struct2Packet(FpQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("ProdCode"          ,stBody.ProdCode       );          
		pkt.AddParameter("ProdName"          ,stBody.ProdName       );          
		pkt.AddParameter("ExchDate"          ,stBody.ExchDate       );          
		pkt.AddParameter("GameID"            ,stBody.GameID         );          
		pkt.AddParameter("Price"             ,stBody.Price          );          
		pkt.AddParameter("IsSettlePrice"     ,stBody.IsSettlePrice  );          
		pkt.AddParameter("MatchVolume"       ,stBody.MatchVolume    );          
		pkt.AddParameter("InitPrice"         ,stBody.InitPrice      );          
		pkt.AddParameter("Rounds"            ,stBody.Rounds         );   

		return 0;

	}


	//----------------------------------------------报文接口 [onRecvRtnFpRoundQuotation] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRtnFpRoundQuotation
	static int Packet2Struct(FpRoundQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("ProdCode"          ,stBody.ProdCode        ); 
		pkt.GetParameterVal("ProdName"          ,stBody.ProdName        ); 
		pkt.GetParameterVal("ExchDate"          ,stBody.ExchDate        ); 
		pkt.GetParameterVal("GameID"            ,stBody.GameID          ); 
		pkt.GetParameterVal("RoundID"           ,stBody.RoundID         ); 
		pkt.GetParameterVal("Price"             ,stBody.Price           ); 
		pkt.GetParameterVal("Adjust"            ,stBody.Adjust          ); 
		pkt.GetParameterVal("BidLot"            ,stBody.BidLot          ); 
		pkt.GetParameterVal("AskLot"            ,stBody.AskLot          ); 
		pkt.GetParameterVal("LastSettlePrice"   ,stBody.LastSettlePrice ); 
		pkt.GetParameterVal("QuoteTime"         ,stBody.QuoteTime       ); 
		pkt.GetParameterVal("SequenceNo"        ,stBody.SequenceNo      ); 


		return 0;

	}

	// 报文解析： 结构 -> 报文    onRecvRtnFpRoundQuotation
	static int Struct2Packet(FpRoundQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("ProdCode"          ,stBody.ProdCode        );  
		pkt.AddParameter("ProdName"          ,stBody.ProdName        );  
		pkt.AddParameter("ExchDate"          ,stBody.ExchDate        );  
		pkt.AddParameter("GameID"            ,stBody.GameID          );  
		pkt.AddParameter("RoundID"           ,stBody.RoundID         );  
		pkt.AddParameter("Price"             ,stBody.Price           );  
		pkt.AddParameter("Adjust"            ,stBody.Adjust          );  
		pkt.AddParameter("BidLot"            ,stBody.BidLot          );  
		pkt.AddParameter("AskLot"            ,stBody.AskLot          );  
		pkt.AddParameter("LastSettlePrice"   ,stBody.LastSettlePrice );  
		pkt.AddParameter("QuoteTime"         ,stBody.QuoteTime       );  
		pkt.AddParameter("SequenceNo"        ,stBody.SequenceNo      );  

		return 0;

	}


	//----------------------------------------------报文接口 [onRecvRspFpOrder] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRspFpOrder
	static int Packet2Struct(FpOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("OrderNo"           ,stBody.OrderNo     );  
		pkt.GetParameterVal("LocalOrderNo"      ,stBody.LocalOrderNo);  
		pkt.GetParameterVal("MemberID"          ,stBody.MemberID    );  
		pkt.GetParameterVal("AcctNo"            ,stBody.AcctNo      );  
		pkt.GetParameterVal("ProdCode"          ,stBody.ProdCode    );  
		pkt.GetParameterVal("Bs"                ,stBody.Bs          );  
		pkt.GetParameterVal("OrderType"         ,stBody.OrderType   );  
		pkt.GetParameterVal("Amount"            ,stBody.Amount      );  
		pkt.GetParameterVal("ApplyDate"         ,stBody.ApplyDate   );  
		pkt.GetParameterVal("ApplyTime"         ,stBody.ApplyTime   );  
		pkt.GetParameterVal("EntrPhase"         ,stBody.EntrPhase   );  
		pkt.GetParameterVal("GameID"            ,stBody.GameID      );  
		pkt.GetParameterVal("RoundID"			,stBody.RoundID     );  
		pkt.GetParameterVal("EntrPrice"         ,stBody.EntrPrice   );  
		pkt.GetParameterVal("orderStatus"            ,stBody.Status      );  

		return 0;
	}

	// 报文解析： 结构 -> 报文    onRecvRspFpOrder
	static int Struct2Packet(FpOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("OrderNo"           ,stBody.OrderNo     );                     
		pkt.AddParameter("LocalOrderNo"      ,stBody.LocalOrderNo);                     
		pkt.AddParameter("MemberID"          ,stBody.MemberID    );                     
		pkt.AddParameter("AcctNo"            ,stBody.AcctNo      );                     
		pkt.AddParameter("ProdCode"          ,stBody.ProdCode    );                     
		pkt.AddParameter("Bs"                ,stBody.Bs          );                     
		pkt.AddParameter("OrderType"         ,stBody.OrderType   );                     
		pkt.AddParameter("Amount"            ,stBody.Amount      );                     
		pkt.AddParameter("ApplyDate"         ,stBody.ApplyDate   );                     
		pkt.AddParameter("ApplyTime"         ,stBody.ApplyTime   );                     
		pkt.AddParameter("EntrPhase"         ,stBody.EntrPhase   );  
		pkt.AddParameter("GameID"            ,stBody.GameID      );  
		pkt.AddParameter("RoundID"			 ,stBody.RoundID     );  
		pkt.AddParameter("EntrPrice"         ,stBody.EntrPrice   );  
		pkt.AddParameter("orderStatus"            ,stBody.Status      );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRspFpOrderCancel] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRspFpOrderCancel
	static int Packet2Struct(FpOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("MemberID"         ,stBody.MemberID        );    
		pkt.GetParameterVal("AcctNo"           ,stBody.AcctNo          );    
		pkt.GetParameterVal("ProdCode"         ,stBody.ProdCode        );    
		pkt.GetParameterVal("EntrPhase"        ,stBody.EntrPhase       );    
		pkt.GetParameterVal("Bs"               ,stBody.Bs              );    
		pkt.GetParameterVal("CancelAmount"     ,stBody.CancelAmount    ); 
		pkt.GetParameterVal("GameID"           ,stBody.GameID		   );  
		pkt.GetParameterVal("RoundID"		   ,stBody.RoundID		   );  
		pkt.GetParameterVal("Status"           ,stBody.Status		   );  
		pkt.GetParameterVal("RootID"           ,stBody.RootID		   );
		return 0;
	}

	// 报文解析： 结构 -> 报文    onRecvRspFpOrderCancel
	static int Struct2Packet(FpOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("MemberID"         ,stBody.MemberID        );  
		pkt.AddParameter("AcctNo"           ,stBody.AcctNo          );  
		pkt.AddParameter("ProdCode"         ,stBody.ProdCode        );  
		pkt.AddParameter("EntrPhase"        ,stBody.EntrPhase       );  
		pkt.AddParameter("Bs"               ,stBody.Bs              );  
		pkt.AddParameter("CancelAmount"     ,stBody.CancelAmount    ); 
		pkt.AddParameter("GameID"           ,stBody.GameID			);  
		pkt.AddParameter("RoundID"			,stBody.RoundID			);  
		pkt.AddParameter("Status"           ,stBody.Status			);
		pkt.AddParameter("RootID"           ,stBody.RootID		    );
		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRspFpOrderFullCancel] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRspFpOrderFullCancel
	static int Packet2Struct(FpOrderFullCancel& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("GameID"              ,stBody.GameID         );  
		pkt.GetParameterVal("RoundID"             ,stBody.RoundID        );  
		pkt.GetParameterVal("ProdCode"            ,stBody.ProdCode       );  
		pkt.GetParameterVal("Bs"                  ,stBody.Bs             );  
		pkt.GetParameterVal("NeedCancel"          ,stBody.NeedCancel     );  
		pkt.GetParameterVal("NewRoundPrice"       ,stBody.NewRoundPrice  );       

		return 0;
	}

	// 报文解析： 结构 -> 报文    onRecvRspFpOrderFullCancel
	static int Struct2Packet(FpOrderFullCancel& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("GameID"              ,stBody.GameID         );
		pkt.AddParameter("RoundID"             ,stBody.RoundID        );
		pkt.AddParameter("ProdCode"            ,stBody.ProdCode       );
		pkt.AddParameter("Bs"                  ,stBody.Bs             );
		pkt.AddParameter("NeedCancel"          ,stBody.NeedCancel     );
		pkt.AddParameter("NewRoundPrice"       ,stBody.NewRoundPrice  );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRspFpFrCancel] 报文结构相关解析
	// 报文解析：报文 -> 结构    onRecvRspFpFrCancel
	static int Packet2Struct(FpFrCancel& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("ExchDate"          ,stBody.ExchDate    );
		pkt.GetParameterVal("ProdCode"          ,stBody.ProdCode    );
		pkt.GetParameterVal("GameID"            ,stBody.GameID      );
		pkt.GetParameterVal("RoundID"           ,stBody.RoundID     );
		pkt.GetParameterVal("Bs"                ,stBody.Bs          );
		pkt.GetParameterVal("CancelAmount"      ,stBody.CancelAmount);
		pkt.GetParameterVal("MemberID"          ,stBody.MemberID    );
		pkt.GetParameterVal("AcctNo"            ,stBody.AcctNo      );

		return 0;
	}

	// 报文解析： 结构 -> 报文    onRecvRspFpFrCancel
	static int Struct2Packet(FpFrCancel& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("ExchDate"          ,stBody.ExchDate    );  
		pkt.AddParameter("ProdCode"          ,stBody.ProdCode    );  
		pkt.AddParameter("GameID"            ,stBody.GameID      );  
		pkt.AddParameter("RoundID"           ,stBody.RoundID     );  
		pkt.AddParameter("Bs"                ,stBody.Bs          );  
		pkt.AddParameter("CancelAmount"      ,stBody.CancelAmount);  
		pkt.AddParameter("MemberID"          ,stBody.MemberID    );  
		pkt.AddParameter("AcctNo"            ,stBody.AcctNo      );  

		return 0;
	}




	//----------------------------------------------报文接口 [onCapitalHandle] 报文结构相关解析
	// 报文解析：报文 -> 结构    onCapitalHandle
	static int Packet2Struct(CapitalHandle& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("bank_no"        ,stBody.bank_no        );
		pkt.GetParameterVal("acct_no"        ,stBody.acct_no        );
		pkt.GetParameterVal("capital"        ,stBody.capital        );
		pkt.GetParameterVal("serial_no"      ,stBody.serial_no      );
		pkt.GetParameterVal("business_type"  ,stBody.business_type  );
		return 0;
	}

	// 报文解析： 结构 -> 报文    onCapitalHandle
	static int Struct2Packet(CapitalHandle& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("bank_no"       ,stBody.bank_no       );  
		pkt.AddParameter("acct_no"       ,stBody.acct_no       );  
		pkt.AddParameter("capital"       ,stBody.capital       );  
		pkt.AddParameter("serial_no"     ,stBody.serial_no     );  
		pkt.AddParameter("business_type" ,stBody.business_type );  
		return 0;
	}

};

#endif