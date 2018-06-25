#ifndef _PACKET_BODY_STRUCT_BROADCAST_RISK_H                 
#define _PACKET_BODY_STRUCT_BROADCAST_RISK_H

#include <string>
#include "ArrayListMsg.h"

//F2接口
//----------------------------------------------报文接口 [onBranchRiskStat] 定义

// 结构定义:onBranchRiskStat
typedef struct tagBranchRiskStat
{
	int          oper_flag            ; //操作标志    1：广播
	ArrayListMsg rtn_result           ; //统计结果    字段：代理机构编号、代理机构名称、强平客户数、强平客户百分比、追保客户数、追保客户百分比、追保金额、浮动亏损
}BranchRiskStat,*PBranchRiskStat;



//----------------------------------------------报文接口 [onCustRiskChangeNtf] 定义

// 结构定义:onCustRiskChangeNtf
typedef struct tagCustRiskChangeNtf
{
	int          oper_flag            ; //操作标志    1：广播
	string       acct_no              ; //客户号    
	string       cust_abbr            ; //客户简称
	string       acct_type            ; //客户类型
	string       cust_type            ; //客户级别
	string       branch_id            ; //代理商号   
	string		 branch_name		  ; //代理商名称
	string       debt_mem             ; //客户追保线    
	string       debt_exch_abs        ; //客户相对强平线    
	string       debt_exch_rel        ; //客户绝对强平线    
	string       debt_call_line       ; //客户追保计算线
	string       risk_grade_yda       ; //上日风险等级
	string       risk_type_yda        ; //上日风险类型  
	string       risk_degree1_from     ; //变化前风险度1    
	string       risk_degree1_to       ; //变化后风险度1 
	string       risk_degree2_from     ; //变化前风险度2    
	string       risk_degree2_to       ; //变化后风险度2  
	string       risk_grade_from      ; //变化前风险等级    
	string       risk_grade_to        ; //变化后风险等级    
	string       risk_type_from       ; //变化前风险类型    
	string       risk_type_to         ; //变化后风险类型   
	string       margin_exch_from     ; //变化前交易所保证金
	string       margin_mem_from      ; //变化前会员保证金
	string       margin_total_from    ; //变化前总保证金    
	string       margin_exch_to       ; //变化后交易所保证金 
	string       margin_mem_to        ; //变化后会员保证金  
	string       margin_total_to      ; //变化后总保证金  
	string       curr_bal_from        ; //变化前可用资金    
	string       curr_bal_to          ; //变化后可用资金    
	string       float_surplus_from   ; //变化前浮动盈亏    
	string       float_surplus_to     ; //变化后浮动盈亏    
	string       call_margin_from     ; //变化前追保金额    
	string       call_margin_to       ; //变化后追保金额    
	string       creadit_amnt_from    ; //变化前当日出入金    
	string       creadit_amnt_to      ; //变化后当日出入金    
	string       risk_days            ; //连续风险天数
	string       call_margin_yda      ; //上日追保金额
	string       cust_mobile		  ; //客户手机号

}CustRiskChangeNtf,*PCustRiskChangeNtf;


//A1接口
//如下是报文生成工具自动生成
//----------------------------------------------报文接口 [onRecvRtnSpotMatch] 定义

// 结构定义:onRecvRtnSpotMatch
typedef struct tagSpotMatch
{
	string       matchNo              ; //成交编号    
	char         buyOrSell            ; //买卖方向    
	string       clientID             ; //客户代码    
	char         clientType           ; //客户类型    
	string       memberID             ; //会员代码    
	string       instID               ; //合约代码    
	string       matchDate            ; //成交日期    
	string       matchTime            ; //成交时间    
	double       price                ; //价格    
	int          volume               ; //数量    
	string       orderNo              ; //系统报单号    
	string       localOrderNo         ; //报单本地编号    
	char         matchType            ; //类型    
	string       acctNo               ; //客户号    
}SpotMatch,*PSpotMatch;


//----------------------------------------------报文接口 [onRecvRtnForwardMatch] 定义

// 结构定义:onRecvRtnForwardMatch
typedef struct tagForwardMatch
{
	string       matchNo              ; //成交编号    
	char         buyOrSell            ; //买卖方向    
	string       clientID             ; //客户代码    
	char         clientType           ; //客户类型    
	string       instID               ; //合约代码    
	string       memberID             ; //会员代码    
	string       matchDate            ; //成交日期    
	string       matchTime            ; //成交时间    
	double       price                ; //价格    
	int          volume               ; //数量    
	double       marginRate           ; //保证金率    
	char         rateType             ; //保证金类型    
	string       orderNo              ; //系统报单号    
	string       localOrderNo         ; //报单本地编号    
	string       acctNo               ; //客户号    
}ForwardMatch,*PForwardMatch;


//----------------------------------------------报文接口 [onRecvRtnDeferMatch] 定义

// 结构定义:onRecvRtnDeferMatch
typedef struct tagDeferMatch
{
	string       matchNo              ; //成交编号    
	char         buyOrSell            ; //买卖方向    
	string       clientID             ; //客户代码    
	char         clientType           ; //客户类型    
	string       instID               ; //合约代码    
	string       memberID             ; //会员代码    
	string       matchDate            ; //成交日期    
	string       matchTime            ; //成交时间    
	double       price                ; //价格    
	int          volume               ; //数量    
	char         offsetFlag           ; //开平标志    
	string       orderNo              ; //系统报单号    
	string       localOrderNo         ; //报单本地编号    
	string       acctNo               ; //客户号    
}DeferMatch,*PDeferMatch;


//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppMatch] 定义

// 结构定义:onRecvRtnDeferDeliveryAppMatch
typedef struct tagDeferDeliveryAppMatch
{
	string       matchNo              ; //成交序号    
	string       clientID             ; //客户代码    
	string       instID               ; //合约代码    
	string       memberID             ; //会员代码    
	char         buyOrSell            ; //买卖方向    
	int          volume               ; //数量    
	string       matchDate            ; //成交日期    
	string       matchTime            ; //成交时间    
	string       orderNo              ; //报单号    
	string       LocalOrderNo         ; //报单本地编号    
	char         middleFlag           ; //是否为中立仓    
	string       acctNo               ; //客户号    
}DeferDeliveryAppMatch,*PDeferDeliveryAppMatch;


//----------------------------------------------报文接口 [onRecvRtnETFMatch] 定义

// 结构定义:onRecvRtnETFMatch
typedef struct tagETFMatch				//add by luobaolin 2013-3-19		
{
	string		orderNo			; //金交所ETF交易编号
	string		b_etf_trade_type	; //ETF交易类型		
	string		acct_no				; //客户号
	string		etf_id				; //ETF基金代码
	string		exch_date			; //交易日期		
	string		prod_code1			; //合约代码1		
	double		day_cash_balance1	; //T日预估现金差额1
	double		weight1				; //重量1			
	string		prod_code2			; //合约代码2		
	double		day_cash_balance2	; //T日预估现金差额2
	double		weight2				; //重量2			
	string		prod_code3			; //合约代码3		
	double		day_cash_balance3	; //T日预估现金差额3
	double 		weight3				; //重量3			
	string		prod_code4			; //合约代码4		
	double		day_cash_balance4	; //T日预估现金差额4
	double		weight4				; //重量4			
	string		prod_code5			; //合约代码5		
	double		day_cash_balance5	; //T日预估现金差额5
	double		weight5				; //重量5	
	double      froz_trans_fee      ; //冻结运保费
	double      froz_diff_fee       ; //冻结溢短
	string		local_order_no		; //本地编号	

	tagETFMatch()
	{
		orderNo = "";
		b_etf_trade_type = "";
		acct_no = "";
		etf_id = "";
		exch_date = "";
		prod_code1 = "";
		day_cash_balance1 = 0.0;
		weight1 = 0.0;
		prod_code2 = "";
		day_cash_balance2 = 0.0;
		weight2 = 0.0;
		prod_code3 = "";
		day_cash_balance3 = 0.0;
		weight3 = 0.0;
		prod_code4 = "";
		day_cash_balance4 = 0.0;
		weight4 = 0.0;
		prod_code5 = "";
		day_cash_balance5 = 0.0;
		weight5 = 0.0;
		froz_trans_fee = 0.0;
		froz_diff_fee = 0.0;
		local_order_no = "";
	}
}ETFMatch,*PtagETFMatch;

//----------------------------------------------报文接口 [onRecvSpotQuotation] 定义

// 结构定义:onRecvSpotQuotation
typedef struct tagSpotQuotation
{
	string       instID               ; //合约代码    
	string       name                 ; //合约名称    
	double       lastClose            ; //昨收盘    
	double       open                 ; //开盘价    
	double       high                 ; //最高价    
	double       low                  ; //最低价    
	double       last                 ; //最新价    
	double       close                ; //收盘价    
	double       bid1                 ; //买价1    
	int          bidLot1              ; //买量1    
	double       bid2                 ; //买价2    
	int          bidLot2              ; //买量2    
	double       bid3                 ; //买价3    
	int          bidLot3              ; //买量3    
	double       bid4                 ; //买价4    
	int          bidLot4              ; //买量4    
	double       bid5                 ; //买价5    
	int          bidLot5              ; //买量5    
	double       ask1                 ; //卖价1    
	int          askLot1              ; //卖量1    
	double       ask2                 ; //卖价2    
	int          askLot2              ; //卖量2    
	double       ask3                 ; //卖价3    
	int          askLot3              ; //卖量3    
	double       ask4                 ; //卖价4    
	int          askLot4              ; //卖量4    
	double       ask5                 ; //卖价5    
	int          askLot5              ; //卖量5    
	int          volume               ; //成交量（双边）    
	int          weight               ; //成交（双边）重量    
	double       highLimit            ; //涨停板    
	double       lowLimit             ; //跌停板    
	double       upDown               ; //涨跌    
	double       upDownRate           ; //涨跌幅度    
	double       turnOver             ; //成交额    
	double       average              ; //均价    
	string       quoteDate            ; //行情日期    
	string       quoteTime            ; //行情时间    
	int          sequenceNo           ; //行情序号    
}SpotQuotation,*PSpotQuotation;


//----------------------------------------------报文接口 [onRecvForwardQuotation] 定义

// 结构定义:onRecvForwardQuotation
typedef struct tagForwardQuotation
{
	string       instID               ; //合约代码    
	string       name                 ; //合约名称    
	double       lastSettle           ; //昨结算    
	double       lastClose            ; //昨收盘    
	double       open                 ; //开盘价    
	double       high                 ; //最高价    
	double       low                  ; //最低价    
	double       last                 ; //最新价    
	double       close                ; //收盘价    
	double       settle               ; //结算价    
	double       bid1                 ; //买价1    
	int          bidLot1              ; //买量1    
	double       bid2                 ; //买价2    
	int          bidLot2              ; //买量2    
	double       bid3                 ; //买价3    
	int          bidLot3              ; //买量3    
	double       bid4                 ; //买价4    
	int          bidLot4              ; //买量4    
	double       bid5                 ; //买价5    
	int          bidLot5              ; //买量5    
	double       ask1                 ; //卖价1    
	int          askLot1              ; //卖量1    
	double       ask2                 ; //卖价2    
	int          askLot2              ; //卖量2    
	double       ask3                 ; //卖价>3    
	int          askLot3              ; //卖量3    
	double       ask4                 ; //卖价4    
	int          askLot4              ; //卖量4    
	double       ask5                 ; //卖价5    
	int          askLot5              ; //卖量5    
	int          volume               ; //成交量    
	int          weight               ; //成交（双边）重量    
	double       highLimit            ; //涨停板    
	double       lowLimit             ; //跌停板    
	int          Posi                 ; //持仓量    
	double       upDown               ; //涨跌    
	double       upDownRate           ; //涨跌幅度    
	double       turnOver             ; //成交额    
	double       average              ; //均价    
	string       quoteDate            ; //行情日期    
	string       quoteTime            ; //行情时间    
	int          sequenceNo           ; //行情序号    
}ForwardQuotation,*PForwardQuotation;


//----------------------------------------------报文接口 [onRecvDeferQuotation] 定义

// 结构定义:onRecvDeferQuotation
typedef struct tagDeferQuotation
{
	string       instID               ; //合约代码    
	string       name                 ; //合约名称    
	double       lastSettle           ; //昨结算    
	double       lastClose            ; //昨收盘    
	double       open                 ; //开盘价    
	double       high                 ; //最高价    
	double       low                  ; //最低价    
	double       last                 ; //最新价    
	double       close                ; //收盘价    
	double       settle               ; //结算价    
	double       bid1                 ; //买价1    
	int          bidLot1              ; //买量1    
	double       bid2                 ; //买价2    
	int          bidLot2              ; //买量2    
	double       bid3                 ; //买价3    
	int          bidLot3              ; //买量3    
	double       bid4                 ; //买价4    
	int          bidLot4              ; //买量4    
	double       bid5                 ; //买价5    
	int          bidLot5              ; //买量5    
	double       ask1                 ; //卖价1    
	int          askLot1              ; //卖量1    
	double       ask2                 ; //卖价2    
	int          askLot2              ; //卖量2    
	double       ask3                 ; //卖价>3    
	int          askLot3              ; //卖量3    
	double       ask4                 ; //卖价4    
	int          askLot4              ; //卖量4    
	double       ask5                 ; //卖价5    
	int          askLot5              ; //卖量5    
	int          volume               ; //成交量    
	int          weight               ; //成交（双边）重量    
	double       highLimit            ; //涨停板    
	double       lowLimit             ; //跌停板    
	int          Posi                 ; //持仓量    
	double       upDown               ; //涨跌    
	string       upDownRate           ; //涨跌幅度    
	string       turnOver             ; //成交额    
	double       average              ; //均价    
	string       quoteDate            ; //行情日期    
	string       quoteTime            ; //行情时间    
	int          sequenceNo           ; //行情序号    
	tagDeferQuotation()
	{
		instID        ="";    ; //合约代码    
		name          ="";    ; //合约名称    
		lastSettle    =0.0;    ; //昨结算    
		lastClose     =0.0;    ; //昨收盘    
		open          =0.0;    ; //开盘价    
		high          =0.0;    ; //最高价    
		low           =0.0;    ; //最低价    
		last          =0.0;    ; //最新价    
		close         =0.0;    ; //收盘价    
		settle        =0.0;    ; //结算价    
		bid1          =0.0;    ; //买价1    
		bidLot1       =0;    ; //买量1    
		bid2          =0.0;    ; //买价2    
		bidLot2       =0;    ; //买量2    
		bid3          =0.0;    ; //买价3    
		bidLot3       =0;    ; //买量3    
		bid4          =0.0;    ; //买价4    
		bidLot4       =0;    ; //买量4    
		bid5          =0.0;    ; //买价5    
		bidLot5       =0;    ; //买量5    
		ask1          =0.0;    ; //卖价1    
		askLot1       =0;    ; //卖量1    
		ask2          =0.0;    ; //卖价2    
		askLot2       =0;    ; //卖量2    
		ask3          =0.0;    ; //卖价>3    
		askLot3       =0;    ; //卖量3    
		ask4          =0.0;    ; //卖价4    
		askLot4       =0;    ; //卖量4    
		ask5          =0.0;    ; //卖价5    
		askLot5       =0;    ; //卖量5    
		volume        =0;    ; //成交量    
		weight        =0;    ; //成交（双边）重量    
		highLimit     =0.0;    ; //涨停板    
		lowLimit      =0.0;    ; //跌停板    
		Posi          =0;    ; //持仓量    
		upDown        =0.0;    ; //涨跌    
		upDownRate    ="";    ; //涨跌幅度    
		turnOver      ="";    ; //成交额    
		average       =0.0;    ; //均价    
		quoteDate     ="";    ; //行情日期    
		quoteTime     ="";    ; //行情时间    
		sequenceNo    =0;    ; //行情序号    
	}
}DeferQuotation,*PDeferQuotation;


//----------------------------------------------报文接口 [onRecvRtnSpotInstStateUpdate] 定义

// 结构定义:onRecvRtnSpotInstStateUpdate
typedef struct tagSpotInstState
{
	string       instID               ; //合约代码    
	char         tradeState           ; //合约交易状态    
}SpotInstState,*PSpotInstState;


//----------------------------------------------报文接口 [onRecvRtnForwardInstStateUpdate] 定义

// 结构定义:onRecvRtnForwardInstStateUpdate
typedef struct tagForwardInstState
{
	string       instID               ; //合约代码    
	char         tradeState           ; //合约交易状态    
}ForwardInstState,*PForwardInstState;


//----------------------------------------------报文接口 [onRecvRtnDeferInstStateUpdate] 定义

// 结构定义:onRecvRtnDeferInstStateUpdate
typedef struct tagDeferInstState
{
	string       instID               ; //合约代码    
	char         tradeState           ; //合约交易状态    
}DeferInstState,*PDeferInstState;


//----------------------------------------------报文接口 [onRecvRtnSpotMarketStateUpdate] 定义

// 结构定义:onRecvRtnSpotMarketStateUpdate
typedef struct tagSpotMarketState
{
	string       marketID             ; //市场代码    
	char         marketState          ; //市场交易状态    
}SpotMarketState,*PSpotMarketState;


//----------------------------------------------报文接口 [onRecvRtnForwardMarketStateUpdate] 定义

// 结构定义:onRecvRtnForwardMarketStateUpdate
typedef struct tagForwardMarketState
{
	string       marketID             ; //市场代码    
	char         marketState          ; //市场交易状态    
}ForwardMarketState,*PForwardMarketState;


//----------------------------------------------报文接口 [onRecvRtnDeferMarketStateUpdate] 定义

// 结构定义:onRecvRtnDeferMarketStateUpdate
typedef struct tagDeferMarketState
{
	string       marketID             ; //市场代码    
	char         marketState          ; //市场交易状态    
}DeferMarketState,*PDeferMarketState;


//----------------------------------------------报文接口 [onAcctCapitalAccess] 定义

// 结构定义:onAcctCapitalAccess
typedef struct tagAcctCapitalAccess
{
	string       fund_src_type        ; //资金来源类型    fund_src_type
	string       serial_no            ; //操作流水号    
	string       acct_no              ; //客户号    
	int          access_way           ; //存取方向    出入方向access_way
	double       amount               ; //转账金额    
}AcctCapitalAccess,*PAcctCapitalAccess;


//----------------------------------------------报文接口 [onCustInfoChange] 定义

// 结构定义:onCustInfoChange
typedef struct tagCustInfoChange
{
	int          update_flag          ; //更改标志    1：增加2：修改3：删除
	string       acct_no              ; //客户号    
	string       member_id            ; //会员编号    
	string       cust_abbr            ; //客户简称    
	string       m_Fare_model_id      ; //会员费用模版ID    
	string       b_Fare_model_id      ; //交易所费用模版ID    
	string       acct_type            ; //账户类型    acct_type
	string       acct_stat            ; //账户状态    
	string       branch_ID            ; //所属代理机构    
}CustInfoChange,*PCustInfoChange;

// 结构定义:onCustCancelNotify
typedef struct tagCustCancelNotify
{
	int          update_flag          ; //更改标志    1：增加2：修改3：删除
	string       acct_no              ; //客户号    
	string       cancel_sys_date      ; //销户日期
}CustCancelNotify,*PCustCancelNotify;


//----------------------------------------------报文接口 [onAck] 定义

// 结构定义:onAck
typedef struct tagAck
{
	string       ack                  ; //确认    
}Ack,*PAck;

//----------------------------------------------报文接口 [onBaseTableUpdate] 定义

// 结构定义:onBaseTableUpdate
typedef struct tagBaseTableUpdate
{
	string       table_name           ; //表名    已支持的表名：bank_infobank_mer_code_infobranch_infobroker_infocode_tablefare_model_defacct_fare_detailfare_model_detailinstID_defsystem_parateller_infovariety
}BaseTableUpdate,*PBaseTableUpdate;


//----------------------------------------------报文接口 [onSysInit] 定义

// 结构定义:onSysInit
typedef struct tagSysInit
{
	string       old_exch_date        ; //原交易日期    
	string       new_exch_date        ; //新交易日期    
}SysInitStru,*PSysInitStru;

//----------------------------------------------报文接口 [onSysStatChange] 定义

// 结构定义:onSysStatChange
typedef struct tagSysStat
{
	string       sys_date             ; //系统日期    
	string       exch_date            ; //交易日期    
	string       m_sys_stat           ; //二级系统状态    m_sys_stat
	string       b_sys_stat           ; //交易所系统状态    b_sys_stat
}SysStat,*PSysStat;

//----------------------------------------------报文接口 [onBourseSysStatChange] 定义 add by zww 2015-5-20

// 结构定义:onBourseSysStatChange
typedef struct tagBourseSysStat
{
	string       sys_date             ; //系统日期    
	string       exch_date            ; //交易日期    
	//string       m_sys_stat           ; //二级系统状态    m_sys_stat
	string       b_sys_stat           ; //交易所系统状态    b_sys_stat
	string		 bourse_id			  ; //交易所 "10"-上金所
}BourseSysStat,*PBourseSysStat;

//---------------------------------------------- 报文接口 [onForceCovOrderNtf] add by liuwei 2012-10-22

// 结构定义：onForceCovOrderNtf
typedef struct tagForceCovOderNtf
{
	int          oper_flag; // 操作标志 1：广播
	string       client_serial_no; //客户端流水号：本地序号
	string       local_order_no; // 本地报单号
	string		 f_order_no; //强平单号
	string       rsp_order_msg;         // 应答信息
	string       state;
}ForceCovOrderNtf, *PForceCovOrderNtf;

//---------------------------------------------- 报文接口 [onForceCovOrderCancelNtf] add by liuwei 2012-10-23

// 结构定义：onForceCovOrderCancelNtf
typedef struct tagForceCovOderCancelNtf
{
	int          oper_flag; // 操作标志 1：广播
	string       client_serial_no; //客户端流水号
	string       local_order_no; // 本地报单号
}ForceCovOrderCancelNtf, *PForceCovOrderCancelNtf;

//----------------------------------------------报文接口 [onRecvRtnFpMatch] 定义

// 结构定义:onRecvRtnFpMatch
typedef struct tagFpMatch
{
	string     MatchNo    ;         //成交单号   
	string     MatchDate  ;         //成交日期   
	string     DeliDate   ;         //交割日期   
	string     MatchGame  ;         //成交场次   
	int        MatchRound ;         //成交轮次   
	string     MemberID   ;         //会员编号   
	string     AcctNo     ;         //客户号     
	string     ProdCode   ;         //合约       
	char       Bs         ;         //买卖方向
	double     MatchPrice ;         //成交手数 
	int        MatchAmount;         //成交手数   
	string     EntrPhase  ;         //申报阶段   
	int        IsAllocate ;         //是否为分摊 

	tagFpMatch()
	{
		MatchNo="";     
		MatchDate="";   
		DeliDate="";    
		MatchGame="";   
		MatchRound=0;  
		MemberID="";    
		AcctNo="";      
		ProdCode="";    
		Bs=0;          
		MatchPrice=0.0;  
		MatchAmount=0; 
		EntrPhase="";   
		IsAllocate=0;  

	}

}FpMatch,*PFpMatch;


//----------------------------------------------报文接口 [onRecvRtnFpQuotation] 定义

// 结构定义:onRecvRtnFpQuotation
typedef struct tagFpQuotation
{
	string      ProdCode           ;//合约代码      
	string      ProdName           ;//合约名称      
	string      ExchDate           ;//交易日期      
	string      GameID             ;//场次编号      
	double      Price              ;//价格          
	string      IsSettlePrice      ;//是否是结算价  
	int         MatchVolume        ;//成交量（双边）
	double      InitPrice          ;//初始价        
	int         Rounds             ;//轮数          
}FpQuotation,*PFpQuotation;


//----------------------------------------------报文接口 [onRecvRspFpOrder] 定义

// 结构定义:onRecvRspFpOrder
typedef struct tagFpOrder
{
	string      OrderNo           ;//报单号    
	string      LocalOrderNo      ;//本地报单号
	string      MemberID          ;//会员编号  
	string      AcctNo            ;//客户号    
	string      ProdCode          ;//合约      
	char        Bs                ;//买卖方向  
	string      OrderType         ;//报单类型  
	int         Amount            ;//委托手数  
	string      ApplyDate         ;//委托日期  
	string      ApplyTime         ;//委托时间  
	string      EntrPhase         ;//申报阶段  
	string      GameID            ;//场次编号
	int         RoundID			  ;//轮次编号
	double      EntrPrice         ;//委托价格
	string      Status            ;//委托状态

	tagFpOrder()
	{
		OrderNo="";     
		LocalOrderNo="";
		MemberID="";    
		AcctNo="";      
		ProdCode="";    
		Bs=0;           
		OrderType="";   
		Amount=0;       
		ApplyDate="";   
		ApplyTime="";   
		EntrPhase="";   
		GameID="";      
		RoundID=0;      
		EntrPrice=0.0;  
		Status="";      

	}


}FpOrder,*PFpOrder;


//----------------------------------------------报文接口 [onRecvRspFpOrderCancel] 定义

// 结构定义:onRecvRspFpOrderCancel
typedef struct tagFpOrderCancel
{
	string    MemberID          ;//会员编号
	string    AcctNo            ;//客户号  
	string    ProdCode          ;//合约    
	string    EntrPhase         ;//申报阶段
	char      Bs                ;//买卖方向
	int       CancelAmount      ;//撤销手数
	string    GameID            ;//场次编号
	int       RoundID			;//轮次编号
	string    Status            ;//委托状态
	string    RootID		    ;//用于判重，数据库中订单号存放的值就是RootID

	tagFpOrderCancel()
	{
		MemberID="";    
		AcctNo="";      
		ProdCode="";    
		EntrPhase="";   
		Bs=0;           
		CancelAmount=0; 
		GameID="";      
		RoundID=0;      
		Status="";      
		RootID="";      
	}
}FpOrderCancel,*PFpOrderCancel;


//----------------------------------------------报文接口 [onRecvRspFpOrderFullCancel] 定义

// 结构定义:onRecvRspFpOrderFullCancel
typedef struct tagFpOrderFullCancel
{
	string    GameID            ;//场次编号    
	int       RoundID           ;//轮次编号    
	string    ProdCode          ;//合约        
	char      Bs                ;//买卖方向    
	string    NeedCancel        ;//是否需要全撤
	double    NewRoundPrice     ;//新一轮价格 

	tagFpOrderFullCancel()
	{
		GameID="";      
		RoundID=0;
		ProdCode=""; 
		Bs=0;           	
		NeedCancel="";     
		NewRoundPrice=0.0;
	}
}FpOrderFullCancel,*PFpOrderFullCancel;


//----------------------------------------------报文接口 [onRecvRtnFpRoundQuotation] 定义

// 结构定义:onRecvRtnFpRoundQuotation
typedef struct tagFpRoundQuotation
{
	string      ProdCode            ;//合约代码
	string      ProdName            ;//合约名称
	string      ExchDate            ;//交易日期
	string      GameID              ;//场次编号
	int         RoundID             ;//轮次编号
	double      Price               ;//价格    
	double      Adjust              ;//变动    
	int         BidLot              ;//买量    
	int         AskLot              ;//卖量    
	double      LastSettlePrice     ;//昨结算价
	string      QuoteTime           ;//行情时间
	string      SequenceNo          ;//行情序号

	tagFpRoundQuotation()
	{
		ProdCode="";         
		ProdName="";         
		ExchDate="";         
		GameID="";           
		RoundID=0;          
		Price=0.0;            
		Adjust=0.0;           
		BidLot=0;           
		AskLot=0;           
		LastSettlePrice=0.0; 
		QuoteTime="";        
		SequenceNo="";       
	}
}FpRoundQuotation,*PFpRoundQuotation;


//----------------------------------------------报文接口 [onRecvRspFpFrCancel] 定义

// 结构定义:onRecvRspFpFrCancel
typedef struct tagFpFrCancel
{
	string      ExchDate            ;//交易日期
	string      ProdCode            ;//合约    
	string      GameID              ;//场次编号
	int         RoundID             ;//轮次编号
	char        Bs                  ;//买卖方向
	int         CancelAmount        ;//撤销手数
	string      MemberID            ;//会员号  
	string      AcctNo              ;//客户号

	tagFpFrCancel()
	{
		ExchDate="";      
		ProdCode="";      
		GameID="";        
		RoundID=0;       
		Bs=0;            
		CancelAmount=0;  
		MemberID="";      
		AcctNo="";        

	}

}FpFrCancel,*PFpFrCancel;


//----------------------------------------------报文接口 [onCapitalChange] 定义

// 结构定义:onRecvRspFpFrCancel
typedef struct tagCapitalHandle
{
	string      bank_no            ;//会员号  
	string      acct_no              ;//客户号
	double      capital             ;//客户变动金额
	string      serial_no            ;//流水号
	string		business_type        ;//业务类型


	tagCapitalHandle()
	{
		bank_no = "";
		acct_no = "";
		capital = 0.0;
		serial_no = "";
		business_type = "";
	}

}CapitalHandle,*PCapitalHandle;

#endif