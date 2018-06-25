#ifndef _PACKET_BODY_STRUCT_TRADE_RISK_H                 
#define _PACKET_BODY_STRUCT_TRADE_RISK_H

#include <string>
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

//----------------------------------------------报文接口 [3061] 定义

// 结构定义:风险客户订阅请求
typedef struct tagSubscriberReq
{
	int          oper_flag            ; //操作标志    1：订阅2：取消
	string       teller_id            ; //监控员ID    
	string       branch_id            ; //被订阅代理机构ID    
}SubscriberReq,*PSubscriberReq;


// 结构定义:风险客户订阅结果响应
typedef struct tagSubscriberRsp
{
	int          oper_flag            ; //操作标志    1：订阅2: 取消
}SubscriberRsp,*PSubscriberRsp;


//----------------------------------------------报文接口 [3062] 定义

// 结构定义:风险客户明细请求
typedef struct tagRiskCustDetailReq
{
	int          oper_flag            ; //操作标志    1：查询
	string       branch_id            ; //代理机构编号    
	string		 cust_type			  ; //客户级别
	string		 acct_type			  ; //客户类型  法人 和 个人
	string		 cust_no			  ; //客户号
	string		 cust_name			  ; //客户姓名
	string		 risk_degree2		  ; //风险度
	string		 bk_acct_no  		  ; //银行卡号
	string       top_number           ; //风险客户排名    不填查全部
}RiskCustDetailReq,*PRiskCustDetailReq;


// 结构定义:风险客户明细响应
typedef struct tagRiskCustDetailRsp
{
	int          oper_flag            ; //操作标志    1：查询
	ArrayListMsg risk_result          ; ////风险客户结果    字段：客户号、客户简称、客户级别、风险度1、风险度2、风险等级、客户追保线、客户相对强平线、客户绝对强平线、上日风险等级、会员保证金、交易所保证金、总保证金、追保金额、浮动盈亏、可用资金、今日出入金、账户类型、客户追保计算线、风险类型、上日风险类型、昨日追保金额、连续风险天数
}RiskCustDetailRsp,*PRiskCustDetailRsp;


//----------------------------------------------报文接口 [3063] 定义

// 结构定义:客户详细信息请求
typedef struct tagCustSpecReq
{
	int          oper_flag            ; //操作标志    1：查询
	string       acct_no              ; //客户号    
}CustSpecReq,*PCustSpecReq;


// 结构定义:客户详细信息响应
typedef struct tagCustSpecRsp
{
	int          oper_flag            ; //操作标志    1：查询
	string       acct_no              ; //客户号   
	//add yanfy 2010-07-10
	int	     except_type          ; //例外客户标志	
	string   exceptdatetime;		 //例外客户的超时日期及时间


	string       cust_abbr            ; //客户简称
	string       cust_type            ; //客户级别
	string       contact_no           ; //座机   
    string       mobile_phone         ; //手机
	string       bank_id              ; //银行代码    
	string       bk_acct_no           ; //银行账号    
	string       branch_id            ; //代理商编号    
	string       branch_name          ; //代理商名称    
	string       curr_bal             ; //客户余额    
	string       froz_order           ; //报单冻结   
	string       froz_other           ; //其它冻结    
	string       curr_can_use         ; //可用资金   
	string       risk_curr_can_use         ; //可用资金   
	string       margin_mem           ; //会员保证金 
	string       margin_exch          ; //交易所保证金 
	string       margin_total         ; //总持仓保证金    
	string       surplus              ; //浮动盈亏    
	string       f_in_out_bal         ; //当日出入金    
	string       in_out_bal_tm        ; //出入金时间    
	string       risk_deg1            ; //风险度1
	string       risk_deg2            ; //风险度2
	string       debt_call_line       ; //追保计算线
	string       debt_mem             ; //追保线
	string       debt_exch_rel        ; //相对强平线
	string       debt_exch_abs        ; //绝对强平线
	string       risk_grade_id        ; //风险等级    
	string       risk_type            ; //风险类型  
	string       debt_call            ; //追保金额    
	string       risk_type_yda        ; //上日风险类型
	string       risk_deg_yda         ; //上日风险等级
	string       debt_call_yda        ; //上日追保金额
	string       risk_days            ; //连续风险天数
	//充抵 add by zww 2015-6-10
	string		 offset_margin_mem	  ; //会员充抵额度保证金
	string		 offset_margin_exch	  ; //交易所充抵额度保证金
	string		 curr_margin_mem	  ; //会员货币保证金
	string		 curr_margin_exch	  ; //交易所货币保证金
	string		 offset_quota_today	  ; //今日总可用充抵额度
	string		 offset_quota_avaliable;//当前可用充抵额度

	ArrayListMsg alm_stor_info        ; //库存信息    字段：品种代码，库存总量、可用库存、总冻结 
	ArrayListMsg alm_posi_info        ; //持仓信息    字段：合约代码、多头持仓数量、多头持仓均价、多头开均价、空头持仓数量、空头持仓均价、空头开均价、浮动盈亏、计算价格
	ArrayListMsg alm_broker_info      ; //库存信息    字段：客户经理名称，客户经理代理机构、手机、座机
	ArrayListMsg alm_cov_posi_info    ; //库存信息    字段：成交单号 报单号 买卖方向 合约代码 释放交易所保证金 释放会员保证金 释放总保证金 成交时间 成交价格 成交数量 开平标志
	ArrayListMsg alm_posi_detail      ; //持仓流水信息  字段：合约代码,多空标志,仓位日期,开仓时间,仓位数量,仓位单价,冻结保证金,浮动盈余
}CustSpecRsp,*PCustSpecRsp;


//----------------------------------------------报文接口 [3064] 定义

// 结构定义:风险提示查询请求
typedef struct tagRiskNotifyQueryReq
{
	int          oper_flag            ; //操作标志    1：查询
	string       branch_id            ; //代理机构编号    
	string		 acct_type			  ; //账户类型
	string		 cust_type			  ; //客户级别
	string       begin_time           ; //开始时间    
	string       end_time             ; //结束时间    
	string       acct_no              ; //客户号    
	string       tip_type             ; //提示类型    tip_type1提示2追保通知3强平通知
	string       risk_grade_src       ; //源风险等级  
	string       risk_grade_des       ; //目的风险等级 
}RiskNotifyQueryReq,*PRiskNotifyQueryReq;


// 结构定义:风险提示查询响应
typedef struct tagRiskNotifyQueryRsp
{
	int          oper_flag            ; //操作标志    1：查询
	ArrayListMsg alm_result           ; //查询结果    字段：时间、源风险等级、目标风险等级、客户号、客户简称、客户级别、账户类型、风险度1、风险度2、追保金额、通知标题、通知内容、代理商、代理商简称
}RiskNotifyQueryRsp,*PRiskNotifyQueryRsp;

//----------------------------------------------报文接口 [3065] 定义

// 结构定义:未全部成交的强平单查询
typedef struct tagNotDealFCQueryReq
{
	int            oper_flag      ; // 操作标志    1：查询
	ArrayListMsg   acct_no_list   ; // 客户号列表，支持同时查询多个
	string         acct_no        ; // 客户号    
}NotDealFCQueryReq,*PNotDealFCQueryReq;


// 结构定义:未全部成交的强平单查询响应
typedef struct tagNotDealFCQueryRsp
{
	int          oper_flag            ; //操作标志    1：查询
	ArrayListMsg f_order_result       ; //查询结果    字段：报单号、合约代码、买卖方向、委托价格、委托数量、成交数量、报单状态、平仓类型、操作来源
}NotDealFCQueryRsp,*PNotDealFCQueryRsp;


//----------------------------------------------报文接口 [3066] 定义

// 结构定义:发送强平单请求
typedef struct tagFCOrderSubmitReq
{
	int          oper_flag            ; //操作标志    1：查询
	int          source_falg          ; //生成标志    1手工 2自动
	string       acct_no              ; //客户号    
	string       date                 ; //日期    
	string       curr_bal             ; //当日余额    
	string       curr_can_use         ; //可用资金  
	string       margin_exch          ; //交易所持仓保证金    
	string       margin_mem           ; //会员持仓保证金    
	string       margin_total         ; //总持仓保证金    
	string       risk_degree1         ; //风险度1
	string       risk_degree2         ; //风险度2    
	string       risk_grade_id        ; //风险等级   
	string       risk_grade_yda       ; //上日风险等级   
	string       float_surplus        ; //浮动盈亏    
	string       prod_price           ; //合约价格    多条合约价格
	string       fc_order             ; //生成序号    
	string       prod_code            ; //合约代码    
	string       buyorsell            ; //买卖方向    
	string       price                ; //委托价格    
	int          volume               ; //委托数量    
	string       lbatchno             ; //批次号    
	string       f_order_no           ; //强平单号    
	string       teller_id            ; //监控员    
	string       debt_call            ; //当前追保金额
	string       debt_call_yda        ; //上日追保金额 
	string       risk_type            ; //当日风险类别
	string       risk_type_yda        ; //上日风险类别
	string       risk_days            ; //连续风险天数
}FCOrderSubmitReq,*PFCOrderSubmitReq;


// 结构定义:发送强平单请求响应
typedef struct tagFCOrderSubmitRsp
{
	int          oper_flag            ; //操作标志    1：查询
	string       acct_no              ; //客户号    
	string       serial_no            ; //生成序号    
	string       f_order_no           ; //强平单号    
	string       local_order_no       ; //本地报单号    
	int          order_state          ; //强平单状态    order_state
}FCOrderSubmitRsp,*PFCOrderSubmitRsp;


//----------------------------------------------报文接口 [3067] 定义

// 结构定义:生成自动强平单请求
typedef struct tagAutoGenFCOrderReq
{
	int          oper_flag            ; //操作标志 1：查询
	string       acct_no              ; //客户号    
	string       risk_grade_id        ; //风险等级    
	string       fc_mode              ; //强平方式 1市价 2限价 3停板价 4 指定价格
	string       lbatchno             ; //批次号    
	string       teller_id            ; //监控员 
	ArrayListMsg posi_result          ; //合约、买卖方向、价格、数量
	ArrayListMsg cov_price_info		  ;//平仓价格信息    合约代码、仓平仓价格、空仓平仓价格
	char         risk_target          ; // 强平目标，0：正常；1：追保；2：相对强平
}AutoGenFCOrderReq,*PAutoGenFCOrderReq;


// 结构定义:生成自动强平单响应
typedef struct tagAutoGenFCOrderRsp
{
	int          oper_flag            ; //操作标志    1：查询
	string       lbatchno             ; //批次号    
	ArrayListMsg alm_result           ; //生成结果    字段顺序：客户号、强平单号、合约、买卖方向、价格、数量
}AutoGenFCOrderRsp,*PAutoGenFCOrderRsp;


	//----------------------------------------------报文接口 [3069] 定义

// 结构定义:强平单查询请求
typedef struct tagFCOrderQueryReq
{
	int          oper_flag            ; //操作标志    1：查询
	string       acct_no              ; //客户号    
	string       branch_id            ; //代理商编号    
	string		 acct_type			  ; //账户类型
	string		 cust_type			  ; //客户级别
	string       instid               ; //合约代码    
	string       gene_type            ; //生成方式    
	string       f_teller_id          ; //强平操作员
	string       begin_date           ; //开始日期    
	string       end_date             ; //结束日期  
	ArrayListMsg order_status_set     ; //报单状态    
}FCOrderQueryReq,*PFCOrderQueryReq;


// 结构定义:强平单查询响应
typedef struct tagFCOrderQueryRsp
{
	int          oper_flag            ; //操作标志    1：查询
	ArrayListMsg alm_result           ; //查询结果    字段顺序：报单号, 客户号, 客户简称,合约，买卖方向，委托价格，委托数量，成交价格，报单状态，强平单号，强平操作员，撤单操作员，委托时间，撤销时间，代理商编号，代理商简称
}FCOrderQueryRsp,*PFCOrderQueryRsp;


//----------------------------------------------报文接口 [3070] 定义

// 结构定义:强平单撤销请求
typedef struct tagFCOrderCancelReq
{
	int          oper_flag            ; //操作标志    1:修改 
	string       order_no             ; //报单号    
}FCOrderCancelReq,*PFCOrderCancelReq;


// 结构定义:强平单撤销响应
typedef struct tagFCOrderCancelRsp
{
	int          oper_flag            ; //操作标志    1:修改 
	string       order_no             ; //报单号    
}FCOrderCancelRsp,*PFCOrderCancelRsp;

//----------------------------------------------报文接口 [3311] 定义

// 结构定义:强平单撤销请求
typedef struct tagFCOrderCancelBatchReq
{
	int          oper_flag            ; //操作标志    1:修改 
	ArrayListMsg       order_no             ; //报单号    
}FCOrderCancelBatchReq,*PFCOrderCancelBatchReq;


// 结构定义:强平单撤销响应
typedef struct tagFCOrderCancelBatchRsp
{
	int          oper_flag            ; //操作标志    1:修改 
// 	string       order_no             ; //报单号    
}FCOrderCancelBatchRsp,*PFCOrderCancelBatchRsp;

//----------------------------------------------报文接口 [3088] 定义

// 结构定义:风险等级查询
typedef struct tagRiskGradeQueryReq
{
	int          oper_flag            ; //操作标志    1:修改 
}RiskGradeQueryReq,*PRiskGradeQueryReq;


// 结构定义:风险等级查询
typedef struct tagRiskGradeQueryRsp
{
	int          oper_flag            ; //操作标志    1:查询
	ArrayListMsg query_result         ; //查询结果    级别代号，级别名称，颜色
}RiskGradeQueryRsp,*PRiskGradeQueryRsp;

//----------------------------------------------报文接口 [3081] 定义

// 结构定义:参数配置报文
typedef struct tagRiskStateParaReq
{
	int          oper_flag            ; //操作标志    0：查询1：修改 2：新增3：删除
	string       obj_type             ; //设置类型    obj_type1代理机构2 账户类型3 客户
	string       obj_id               ; //设置对象    对应类型的编号
	string       debt_mem_value       ; //追保线    
	string       debt_exch_value      ; //强平线    
	string       debt_call_value      ; //追保计算线    
	ArrayListMsg obj_content          ; //对象内容    字段：风险等级编号, 级别最小值，级别最大值
}RiskStateParaReq,*PRiskStateParaReq;


// 结构定义:参数配置报文
typedef struct tagRiskStateParaRsp
{
	int          oper_flag            ; //操作标志    0：查询1：修改 2：新增3：删除
	ArrayListMsg alm_result          ; //客户,代理机构,账户类型,客户级别,相对强平线,追保计算线,对象内容(ArrayListMsg 字段：基础风险类型,级别最小值，级别最大值 )
	string       obj_type             ; //设置类型    obj_type1代理机构2 账户类型3 客户
	string       obj_id               ; //设置对象    对应类型的编号
	// 	string       debt_mem_value       ; //追保线    
	string       debt_exch_value      ; //强平线    
	string       debt_call_value      ; //追保计算线    
	ArrayListMsg obj_content          ; //对象内容    字段：风险等级编号, 级别最小值，级别最大值

}RiskStateParaRsp,*PRiskStateParaRsp;

	//----------------------------------------------报文接口 [3082] 定义

// 结构定义:参数配置报文
typedef struct tagRiskhandleParaReq
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	string       handle_id            ; //处理编号    
	string       handle_name          ; //处理名称    
	string       handle_method        ; //处理方式    
	HashtableMsg para_set             ; //级别参数集合    处理编号、处理名称、处理方式
}RiskhandleParaReq,*PRiskhandleParaReq;


// 结构定义:参数配置报文
typedef struct tagRiskhandleParaRsp
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	string       handle_id            ; //处理编号    
	string       handle_name          ; //处理名称    
	string       handle_method        ; //处理方式    
	HashtableMsg para_set             ; //级别参数集合    处理编号、处理名称、处理方式
}RiskhandleParaRsp,*PRiskhandleParaRsp;


//----------------------------------------------报文接口 [3084] 定义

// 结构定义:参数配置报文
typedef struct tagRiskNotifyParaReq
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	string       tip_type             ; //风险通知类型    tip_type1提示2追保通知3强平通知
	string       risk_grade_src       ; //源风险等级  
	string       risk_grade_des       ; //目的风险等级 
	string       notify_content       ; //提示内容    
}RiskNotifyParaReq,*PRiskNotifyParaReq;


// 结构定义:参数配置报文
typedef struct tagRiskNotifyParaRsp
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	ArrayListMsg notify_content_set   ; //查询结果   风险通知类型、源风险等级、目标风险等级、提示内容
}RiskNotifyParaRsp,*PRiskNotifyParaRsp;


	//----------------------------------------------报文接口 [3085] 定义

// 结构定义:参数配置报文
typedef struct tagForceCoverParaReq
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	ArrayListMsg prod_set             ; //合约顺序参数    合约代码、买卖方向、合约顺序值
}ForceCoverParaReq,*PForceCoverParaReq;


// 结构定义:参数配置报文
typedef struct tagForceCoverParaRsp
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	ArrayListMsg prod_set             ; //合约顺序参数    合约代码、买卖方向、合约顺序值
}ForceCoverParaRsp,*PForceCoverParaRsp;


	//----------------------------------------------报文接口 [3086] 定义

// 结构定义:参数配置报文
typedef struct tagBranchAuthParaReq
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	ArrayListMsg branch_set           ; //代理商    字段：代理商号、是否授权
}BranchAuthParaReq,*PBranchAuthParaReq;


// 结构定义:参数配置报文
typedef struct tagBranchAuthParaRsp
{
	int          oper_flag            ; //操作标志    0：查询1：修改 
	ArrayListMsg branch_set           ; //代理商    字段：代理商号、是否授权
}BranchAuthParaRsp,*PBranchAuthParaRsp;

	//----------------------------------------------报文接口 [3091] 定义

// 结构定义:交易统一请求报文
typedef struct tagRiskCustQueryReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       branch_id            ; //代理商编号 
	string		 acct_type			  ; //账户类型
	string		 cust_type			  ; //客户级别
	string       acct_no              ; //客户号    
	string       risk_grade_id        ; //风险等级    
	int			start_no;			//起始记录数
	int			page_no;			//	第几页
	int			page_size;			//	页大小
	int			total_record;		//	总记录条数
}RiskCustQueryReq,*PRiskCustQueryReq;


// 结构定义:交易统一请求报文
typedef struct tagRiskCustQueryRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	int			start_no;			//起始记录数
	int			page_no;			//	第几页
	int			page_size;			//	页大小
	int			total_record;		//	总记录条数
	ArrayListMsg alm_result           ; //查询结果    字段：客户号、客户简称、风险度、风险等级、可用资金、持仓保证金、浮动盈亏、追保金额、代理商编号、代理商名称
}RiskCustQueryRsp,*PRiskCustQueryRsp;

	//----------------------------------------------报文接口 [3093] 定义

// 结构定义:风险试算请求报文体，支持分页
typedef struct tagRiskTestCalReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       p_branch_id          ; //监控员所属代理商号  
	string       branch_id            ; //代理商号    
	string       acct_no              ; //客户号    
	string       acct_type            ; //账户类型
	string       cust_type            ; //客户级别
	ArrayListMsg instid               ; //合约    合约代码、合约价格、调整保证金率
	int          page_no              ; //页码
	int          page_size            ; //页大小
	int          total_record         ; //符合记录总条数
	ArrayListMsg risk_level           ; //要返回的客户的风险等级
}RiskTestCalReq,*PRiskTestCalReq;


// 结构定义:内部划转申请/复核的响应报文体
typedef struct tagRiskTestCalRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	int          page_no              ; //页码
	int          page_size            ; //页大小
	int          total_record         ; //符合记录总条数
	ArrayListMsg cal_result           ; //计算结果    字段顺序：客户号，客户简称，预测风险度，预测风险等级，可用资金，预测保证金，预测浮动盈亏，预测追保金额，代理商编号，代理商名称，客户级别
}RiskTestCalRsp,*PRiskTestCalRsp;

	//----------------------------------------------报文接口 [3094] 定义

// 结构定义:资金冻结解冻的请求报文体
typedef struct tagRiskCustAllReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       begin_date           ; //开始日期    
	string       end_date             ; //结束日期    
	string       branch_id            ; //代理商编号    
	string		 acct_type			  ; //账户类型
	string		 cust_type			  ; //客户级别
	string       risk_grade_id        ; //风险等级    
}RiskCustAllReq,*PRiskCustAllReq;


// 结构定义:资金冻结解冻的响应报文体
typedef struct tagRiskCustAllRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	ArrayListMsg risk_cust            ; //风险客户集    字段：客户号、客户简称、代理商号、名称、风险度、风险等级、可用资金、浮动盈亏、追保金额、当日出入金
}RiskCustAllRsp,*PRiskCustAllRsp;

	//----------------------------------------------报文接口 [3095] 定义

// 结构定义:交易保证金解冻的请求报文体
typedef struct tagRiskDistQueryReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       begin_date           ; //开始日期    
	string       end_date             ; //结束日期    
	string       branch_id            ; //代理商编号    
}RiskDistQueryReq,*PRiskDistQueryReq;


// 结构定义:交易保证金解冻的响应报文体
typedef struct tagRiskDistQueryRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	string       branch_id            ; //代理商编号    
	ArrayListMsg risk_dist            ; //风险度分布    风险等级，客户数
}RiskDistQueryRsp,*PRiskDistQueryRsp;

	//----------------------------------------------报文接口 [3096] 定义

// 结构定义:基础保证金的请求报文体
typedef struct tagBranchDistQueryReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       begin_time           ; //开始时间    
	string       end_time             ; //结束时间    
	ArrayListMsg risk_level           ; //风险度起始值    
}BranchDistQueryReq,*PBranchDistQueryReq;


// 结构定义:基础保证金的响应报文体
typedef struct tagBranchDistQueryRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	ArrayListMsg branch_id            ; //代理商分布    代理商、客户总数、对应风险客户数
}BranchDistQueryRsp,*PBranchDistQueryRsp;

	//----------------------------------------------报文接口 [3097] 定义

// 结构定义:平仓试算的请求报文体
typedef struct tagTryCloseReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       acct_no              ; //客户号    
	ArrayListMsg close_para           ; //平仓参数    合约代码, 平仓方向, 平仓价格, 平仓数量
}TryCloseReq,*PTryCloseReq;


// 结构定义:平仓试算的响应报文体
typedef struct tagTryCloseRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	string       cust_id              ; //客户号    
	string       curr_bal             ; //预计可用资金  
	string       margin_exch          ; //预计交易所保证金  
	string       margin_mem           ; //预计会员保证金  
	string       margin_total         ; //预计总保证金    
	string       float_surplus        ; //预计浮动盈亏    
	string       risk_degree1         ; //预计风险度1    
	string       risk_degree2         ; //预计风险度2    
	string       risk_grade           ; //预计风险等级    
	string       risk_type            ; //预计风险类型    
	string       call_debt           ; //预计追保金额
	//充抵 add by zww 2015-6-10
	string		 offset_margin_mem	  ; //会员充抵额度保证金
	string		 offset_margin_exch	  ; //交易所充抵额度保证金
	string		 curr_margin_mem	  ; //会员货币保证金
	string		 curr_margin_exch	  ; //交易所货币保证金
	string		 offset_quota_today	  ; //今日总可用充抵额度
	string		 offset_quota_avaliable;//当前可用充抵额度
}TryCloseRsp,*PTryCloseRsp;

	//----------------------------------------------报文接口 [3098] 定义

// 结构定义:合约行情查询的请求报文体
typedef struct tagProdQuotationReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       prod_code            ; //和约代码    
}ProdQuotationReq,*PProdQuotationReq;


// 结构定义:合约行情查询的响应报文体
typedef struct tagProdQuotationRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	ArrayListMsg quotaion_result      ; //和约行情信息    合约代码, 最新价，买价1，卖价5，涨停板价，跌停板价
}ProdQuotationRsp,*PProdQuotationRsp;
//----------------------------------------------报文接口 [3306] 定义

// 结构定义:交易员品种盈亏清单
typedef struct tagRiskProfitLossReq
{
	int    oper_flag     ;	  //操作标志    0：查询   1：新增 2：修改 3：删除
	string acct_no      ;    //自营交易员客户号      
}RiskProfitLossReq,*PRiskProfitLossReq;


// 结构定义:参数配置报文
typedef struct tagRiskProfitLossRsp
{
	int          oper_flag        ;   //操作标志    0：查询
	ArrayListMsg amt_result       ;   //内容
}RiskProfitLossRsp,*PRiskProfitLossRsp;
// 结构定义:自营预警参数配置
typedef struct tagRiskAlarmParaReq
{
	int    oper_flag     ;	  //操作标志    0：查询   1：新增 2：修改 3：删除
	string index_id      ;    //序号        
	string prod_code     ;    //预警项      
	string notify_obj    ;    //预警对象    
	string term_value    ;    //预警值      
	string notify_way    ;    //预警方式    
	string timeout       ;    //间隔时间    
	string term_type     ;    //预警条件    
	string begin_day     ;    //生效开始时间
	string end_day       ;    //生效结束时间
	string teller_id     ;    //操作员  
}RiskAlarmParaReq,*PRiskAlarmParaReq;


// 结构定义:参数配置报文
typedef struct tagRiskAlarmParaRsp
{
	int          oper_flag            ; //操作标志  0：查询   1：新增 2：修改 3：删除
	ArrayListMsg alm_result          ; //客户,代理机构,账户类型,客户级别,相对强平线,追保计算线,对象内容(ArrayListMsg 字段：基础风险类型,级别最小值，级别最大值 )
}RiskAlarmParaRsp,*PRiskAlarmParaRsp;


//----------------------------------------------报文接口 [3303] 定义
// 结构定义:自动强平例外条件配置请求报文体
typedef struct tagHandleSmsReq
{
	int          oper_flag            ; //操作标志    0：查询 1：修改 2:修改 3：删除
	ArrayListMsg  alm_result  ; //类型值 多类组合

}HandleSmsReq,*PHandleSmsReq;


// 结构定义:修改最小变动单位的响应报文体
typedef struct tagHandleSmsRsp
{
	int              oper_flag            ; //操作标志    0：查询 1：修改 
}HandleSmsRsp,*PHandleSmsRsp;



//----------------------------------------------报文接口 [3302] 定义
// 结构定义:修改最小变动单位的请求报文体
typedef struct tagAlterMinUnitReq
{
	int       oper_flag           ; //操作标志    0：查询 1：修改 
	string    prod_code          ;//合约代码
	string    min_unit           ;
	string	  quote_dot			 ; //延期与交割品种的最大价格点差 
	int		  mincatchtime;		    //已找到对应交割品种的持续时间
	int		  maxcatchtime;			//未找到对应交割品种的持续时间
	string	  varietyCode;			//合约对应的交割品种列表，用","分隔
}AlterMinUnitReq,*PAlterMinUnitReq;


// 结构定义:修改最小变动单位的响应报文体
typedef struct tagAlterMinUnitRsp
{
	int              oper_flag            ; //操作标志    0：查询 1：修改 
	ArrayListMsg     alm_result     ;      //合约代码,最小变动量 
}AlterMinUnitRsp,*PAlterMinUnitRsp;

//----------------------------------------------报文接口 [3301] 定义
// 结构定义:自动强平例外条件配置请求报文体
typedef struct tagAutoForceExecptConditionReq
{
	int          oper_flag            ; //操作标志    0：查询 1：修改 2:修改 3：删除
	string       obj_type             ; //设置类型    1客户 2客户级别 3 账户类型 4代理机构
	string       except_date_time     ; //例外日期时间
	ArrayListMsg       type_value      ; //类型值 多类组合
	
}AutoForceExecptConditionReq,*PAutoForceExecptConditionReq;


// 结构定义:合约行情查询的响应报文体
typedef struct  tagAutoForceExecptConditionRsp
{
	int          oper_flag            ; //操作标志    0：查询 1：修改 2:修改 3：删除
	ArrayListMsg  value_list          ;  //值列表
} AutoForceExecptConditionRsp,*PAutoForceExecptConditionRsp;


//----------------------------------------------报文接口 [3100] 定义
// 结构定义:短信通知参数配置请求报文
typedef struct tagSmsParaReq
{
	int          oper_flag            ; //操作标志    0：查询 1：修改
	string       acct_type            ; //账户类型
	string       risk_type            ; //风险类型
	string       sms_content          ; //通知内容模板
}SmsParaReq,*PSmsParaReq;


// 结构定义:合约行情查询的响应报文体
typedef struct tagSmsParaRsp
{
	int          oper_flag            ; //操作标志    0：查询  1：修改
	ArrayListMsg sms_content_set      ; //账户类型、通知内容模板
}SmsParaRsp,*PSmsParaRsp;


//----------------------------------------------报文接口 [3099] 定义
// 结构定义:客户风险度请求报文体
typedef struct tagCustRiskDegreeQueryReq
{
	int          oper_flag            ; //操作标志    0：查询 1：修改
	string		 acct_no			  ; //客户号  _VER_25_PSBC版本用到
}CustRiskDegreeQueryReq,*PCustRiskDegreeQueryReq;


// 结构定义:客户风险度响应报文体
typedef struct tagCustRiskDegreeQueryRsq
{
	int          oper_flag            ; //操作标志    0：查询  1：修改
	string       risk_degree          ; //风险度1  为兼容结算中心老版本客户端
	string       risk_degree1          ; //风险度1
	string       risk_degree2          ; //风险度2
	string       risk_grade           ; //风险等级
	string		 risk_type           	;    //风险类型        
	string 		 debt_call_line       ;    //客户追保计算线  
	string 		 debt_mem             ;    //客户追保线      
	string 		 debt_exch_rel        ;    //客户相对强平线  
	string 		 debt_exch_abs        ;    //客户绝对强平线  
	string 		 margin_mem           ;    //会员保证金      
	string 		 margin_exch          ;    //交易所保证金    
	string 		 debt_call            ;    //追保金额        
	string 		 surplus              ;    //浮动盈亏        
	string 		 risk_curr_can_use   ;    //可用资金        
	string 		 acct_type            ;    //账户类型        
	string 		 f_in_out_bal         ;    //今日出入金      
	string 		 risk_type_yda        ;    //上日风险类型    
	string 		 risk_deg_yda         ;    //上日风险等级    
	string 		 debt_call_yda        ;    //昨日追保金额    
	string 		 risk_days            ;    //昨日连续风险天数

}CustRiskDegreeQueryRsq,*PCustRiskDegreeQueryRsq;
	///////////////////////////////////////////////////////////////////
//A2接口报文
//----------------------------------------------报文接口 [3052] 定义

// 结构定义:强平报单
typedef struct tagForceCovOder
{
	int          oper_flag            ; //操作标志    1：强平报单
	string       client_serial_no     ; //客户端流水号    强平单号
	string       acct_no              ; //客户号    
	string       cust_id              ; //客户代码    
	string       bank_no              ; //银行卡号    
	string       b_market_id          ; //交易市场    b_market_id
	string       prod_code            ; //合约代码    
	string       offset_flag          ; //开平标志    b_offset_flag
	string       deli_flag            ; //交收标志    b_deli_flag
	string       bs                   ; //交易方向    b_buyorsell
	string       entr_price           ; //委托价格    
	int          entr_amount          ; //委托数量    
	string       cov_type             ; //平仓方式    cov_type
	string       match_type           ; //成交类型    b_match_type
	string       src_match_no         ; //仓位编号    指定平仓的原成交编号
	string       order_send_type      ; //报单发送方式    order_send_type
}ForceCovOder,*PForceCovOder;


// 结构定义:强平报单响应
typedef struct tagForceCovOderAck
{
	int          oper_flag            ; //操作标志    1：强平报单
	string       client_serial_no     ; //客户端流水号    强平单号		
	string       local_order_no       ; //本地报单号 
}ForceCovOderAck,*PForceCovOderAck;


	//----------------------------------------------报文接口 [3053] 定义

// 结构定义:强平撤单
typedef struct tagForceCovOderCancel
{
	int          oper_flag            ; //操作标志    1：强平撤单 
	string       cancel_order_no      ; //被撤单报单号    
}ForceCovOderCancel,*PForceCovOderCancel;


// 结构定义:强平撤单响应
typedef struct tagForceCovOderCancelAck
{
	int          oper_flag            ; //操作标志    1：强平撤单
}ForceCovOderCancelAck,*PForceCovOderCancelAck;


	//报单回报
typedef struct tagDeferRtnOrder
{
	string       client_serial_no;
	string       orderNo;				//报单号        (not null)
	string       clientID;				//客户代码       (not null)
	string       instID;				//合约代码       (not null)
	string       memberID;				//会员代码       (not null)
	char         buyOrSell;				//买卖方向       (not null)
	string       applyDate;				//申报日期
	string       applyTime;				//申报时间
	char         offSetFlag;			//开平仓标志      (not null)
	string       price;					//价格                       (not null)
	int          amount;				//数量            (not null)
	int          remainAmount;			//剩余数量
	string       cancelTime;			//撤消时间
	char         status;				//状态
	string       localOrderNo;			//本地报单号          (not null)
	string       margin;				//保证金率
	char         marginType;			//保证金类型           (not null)
	string       traderID;				//交易员代码          (not null)
	string       cancelID;				//撤消员代码
	char         matchType;		
	string       acctNo               ; //客户号    
} DeferRtnOrder,*PDeferRtnOrder;

////////////////////////////////////////////////////////////////////
// 结构定义:代理机构风险统计清单查询请求报文
typedef struct tagBranchRiskStatQryReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       branch_id            ; //代理机构    
}BranchRiskStatQryReq,*PBranchRiskStatQryReq;



// 结构定义:代理机构风险统计清单查询请求报文
typedef struct tagBranchRiskStatQryRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	ArrayListMsg       rtn_result            ; //统计结果  字段：代理机构编号、代理机构名称、追债客户数、爆仓客户数、强平客户数、绝对强平客户数、追保客户数、正常客户数、追保金额、浮动亏损、总浮动盈亏、可用资金总、交易所保证金、会员保证金、总保证金、总今日入金、总今日出金    
}BranchRiskStatQryRsp,*PBranchRiskStatQryRsp;


//--------------------------------------------------------------报文接口[3307]定义 开始 add by liuwei 2012-8-16
//结构定义：三级代理机构风险指标查询请求报文
typedef struct tagSubAgentRiskIndexQueryReq
{
	int          oper_flag            ; //操作标志    1：查询 
	string       branch_id            ; //机构代码，为空则查询所有三级代理机构
}SubAgentRiskIndexQueryReq, *PSubAgentRiskIndexQueryReq;

//结构定义：三级代理机构风险指标查询响应报文
typedef struct tagSubAgentRiskIndexQueryRsp
{
	int          oper_flag            ; //操作标志    1：查询 
	ArrayListMsg alm_result           ; //查询结果，字段：机构代码，总保证金，总会员保证金，总浮动盈亏，风险度2大于1的客户的可用资金；
}SubAgentRiskIndexQueryRsp, *PSubAgentRiskIndexQueryRsp;
//--------------------------------------------------------------报文接口[3307]定义 结束 add by liuwei 2012-8-16

//---------------------------------------------------------------报文接口[3308]定义 开始 add by liuwei 2012-8-16
//结构定义：三级代理机构风险参数配置请求报文
typedef struct tagSubAgentRiskParaSetReq
{
	int          oper_flag            ; //操作标志    0：查询；1：修改
	ArrayListMsg query_condition      ; //查询条件    字段：机构代码，阀值类型，阀值数值；（1、oper_flag=0，服务端只校验机构代码，后面忽略，机构代码为空则查询所有三级代理机构，2、oper_flag=1，均为必填项，后4个字段必须大于0，小于1；）
}SubAgentRiskParaSetReq, *PSubAgentRiskParaSetReq;

//结构定义：三级代理机构风险参数配置响应报文
typedef struct tagSubAgentRiskParaSetRsp
{
	int          oper_flag            ; //操作标志    0：查询；1：修改
	ArrayListMsg alm_result           ; //查询结果    字段：机构代码，机构名称，阀值类型，阀值数值；
}SubAgentRiskParaSetRsp, *PSubAgentRiskParaSetRsp;
//---------------------------------------------------------------报文接口[3308]定义 结束 add by liuwei 2012-8-16

//--------------------------------------------------报文接口 [3309] 定义 开始 add by liuwei 2012-9-4
// 结构定义:批量生成自动强平单请求
typedef struct tagAutoGenFCOrderBatchReq
{
	int          oper_flag            ; //操作标志 1：查询
	ArrayListMsg gen_condition        ; //生成条件 字段：客户号、批次号、风险等级
	string       fc_mode              ; //强平方式 1市价 2限价 3停板价 4 指定价格
	string       teller_id            ; //监控员 
	ArrayListMsg posi_result          ; //合约、买卖方向、价格、数量
	ArrayListMsg cov_price_info		  ;//平仓价格信息    合约代码、仓平仓价格、空仓平仓价格
	char         risk_target          ; // 强平目标，0：正常；1：追保；2：相对强平
}AutoGenFCOrderBatchReq,*PAutoGenFCOrderBatchReq;


// 结构定义:批量生成自动强平单响应
typedef struct tagAutoGenFCOrdeBatchrRsp
{
	int          oper_flag            ; //操作标志    1：查询
	ArrayListMsg alm_result           ; //生成结果    字段顺序：客户号、强平单号、合约、买卖方向、价格、数量、批次号、rsp_msg
}AutoGenFCOrderBatchRsp,*PAutoGenFCOrderBatchRsp;
//--------------------------------------------------报文接口 [3309] 定义 结束 add by liuwei 2012-9-4

//--------------------------------------------------报文接口 [3310] 定义 开始 add by liuwei 2012-9-4
// 结构定义:批量发送强平单请求
typedef struct tagFCOrderSubmitBatchReq
{
	int          oper_flag            ; //操作标志    1：查询
	ArrayListMsg force_order          ; //强平单条件 字段：生成标志、客户号、日期、生成序号、合约代码、买卖方向、委托价格、委托数量、批次号、强平单号、监控员
}FCOrderSubmitBatchReq,*PFCOrderSubmitBatchReq;


// 结构定义:批量发送强平单请求响应
typedef struct tagFCOrderSubmitBatchRsp
{
	int          oper_flag            ; //操作标志    1：查询
	ArrayListMsg alm_result           ; //处理结果 字段：客户号、生成序号、强平单号、本地报单号强平单状态、rsp_msg
}FCOrderSubmitBatchRsp,*PFCOrderSubmitBatchRsp;
//--------------------------------------------------报文接口 [3310] 定义 结束 add by liuwei 2012-9-4

//----------------------------------------------报文接口 [3312] 定义

// 结构定义:风险试算请求报文体，支持分页
typedef struct tagInOutCustListReq
{
	int          oper_flag            ; //操作标志    0：查询 
	string       branch_id            ; //代理商号    
	ArrayListMsg instid               ; //合约    合约代码、合约价格、调整保证金率
	int          page_no              ; //页码
	int          page_size            ; //页大小
	int          total_record         ; //符合记录总条数
}InOutCustListReq,*PInOutCustListReq;


// 结构定义:内部划转申请/复核的响应报文体
typedef struct tagInOutCustListRsp
{
	int          oper_flag            ; //操作标志    0：查询 
	ArrayListMsg cal_result           ; //计算结果    字段顺序：客户号，客户简称，出入金方向，出入金数量，出入金流水号，预测风险度1，预测风险度2，预测风险等级，可用资金，预测会员保证金，预测交易所保证金，预测总保证金，预测浮动盈亏，预测追保金额，代理商编号，代理机构名称，连续风险天数
}InOutCustListRsp,*PInOutCustListRsp;

// 结构定义:交易统一请求报文
typedef struct tagRiskCustQueryReqByTrade
{
	int          oper_flag            ; //操作标志    0：查询 
	string       branch_id            ; //代理商编号 
	string		 acct_type			  ; //账户类型
	string		 cust_type			  ; //客户级别
	string		 account_no			  ; //银行账号
	string       acct_no              ; //客户号    
	string       risk_grade_id        ; //风险等级    
}RiskCustQueryReqByTrade,*PRiskCustQueryReqByTrade;


// 结构定义:交易统一请求报文
typedef struct tagRiskCustQueryRspByTrade
{
	int          oper_flag            ; //操作标志    0：查询 
	HashtableMsg alm_result           ; //查询结果    字段：客户号 客户简称 客户级别 账户类型 风险度1 风险度2  风险等级 可用资金 会员保证金 交易所保证金 总保证金 浮动盈亏 追保金额 代理商编号 代理商名称 客户手机号 +银行账号
}RiskCustQueryRspByTrade,*PRiskCustQueryRspByTrade;

#endif