#ifndef _PACKET_BODY_STRUCT_BROADCAST_RISK_H                 
#define _PACKET_BODY_STRUCT_BROADCAST_RISK_H

#include <string>
#include "ArrayListMsg.h"

//F2�ӿ�
//----------------------------------------------���Ľӿ� [onBranchRiskStat] ����

// �ṹ����:onBranchRiskStat
typedef struct tagBranchRiskStat
{
	int          oper_flag            ; //������־    1���㲥
	ArrayListMsg rtn_result           ; //ͳ�ƽ��    �ֶΣ����������š�����������ơ�ǿƽ�ͻ�����ǿƽ�ͻ��ٷֱȡ�׷���ͻ�����׷���ͻ��ٷֱȡ�׷������������
}BranchRiskStat,*PBranchRiskStat;



//----------------------------------------------���Ľӿ� [onCustRiskChangeNtf] ����

// �ṹ����:onCustRiskChangeNtf
typedef struct tagCustRiskChangeNtf
{
	int          oper_flag            ; //������־    1���㲥
	string       acct_no              ; //�ͻ���    
	string       cust_abbr            ; //�ͻ����
	string       acct_type            ; //�ͻ�����
	string       cust_type            ; //�ͻ�����
	string       branch_id            ; //�����̺�   
	string		 branch_name		  ; //����������
	string       debt_mem             ; //�ͻ�׷����    
	string       debt_exch_abs        ; //�ͻ����ǿƽ��    
	string       debt_exch_rel        ; //�ͻ�����ǿƽ��    
	string       debt_call_line       ; //�ͻ�׷��������
	string       risk_grade_yda       ; //���շ��յȼ�
	string       risk_type_yda        ; //���շ�������  
	string       risk_degree1_from     ; //�仯ǰ���ն�1    
	string       risk_degree1_to       ; //�仯����ն�1 
	string       risk_degree2_from     ; //�仯ǰ���ն�2    
	string       risk_degree2_to       ; //�仯����ն�2  
	string       risk_grade_from      ; //�仯ǰ���յȼ�    
	string       risk_grade_to        ; //�仯����յȼ�    
	string       risk_type_from       ; //�仯ǰ��������    
	string       risk_type_to         ; //�仯���������   
	string       margin_exch_from     ; //�仯ǰ��������֤��
	string       margin_mem_from      ; //�仯ǰ��Ա��֤��
	string       margin_total_from    ; //�仯ǰ�ܱ�֤��    
	string       margin_exch_to       ; //�仯��������֤�� 
	string       margin_mem_to        ; //�仯���Ա��֤��  
	string       margin_total_to      ; //�仯���ܱ�֤��  
	string       curr_bal_from        ; //�仯ǰ�����ʽ�    
	string       curr_bal_to          ; //�仯������ʽ�    
	string       float_surplus_from   ; //�仯ǰ����ӯ��    
	string       float_surplus_to     ; //�仯�󸡶�ӯ��    
	string       call_margin_from     ; //�仯ǰ׷�����    
	string       call_margin_to       ; //�仯��׷�����    
	string       creadit_amnt_from    ; //�仯ǰ���ճ����    
	string       creadit_amnt_to      ; //�仯���ճ����    
	string       risk_days            ; //������������
	string       call_margin_yda      ; //����׷�����
	string       cust_mobile		  ; //�ͻ��ֻ���

}CustRiskChangeNtf,*PCustRiskChangeNtf;


//A1�ӿ�
//�����Ǳ������ɹ����Զ�����
//----------------------------------------------���Ľӿ� [onRecvRtnSpotMatch] ����

// �ṹ����:onRecvRtnSpotMatch
typedef struct tagSpotMatch
{
	string       matchNo              ; //�ɽ����    
	char         buyOrSell            ; //��������    
	string       clientID             ; //�ͻ�����    
	char         clientType           ; //�ͻ�����    
	string       memberID             ; //��Ա����    
	string       instID               ; //��Լ����    
	string       matchDate            ; //�ɽ�����    
	string       matchTime            ; //�ɽ�ʱ��    
	double       price                ; //�۸�    
	int          volume               ; //����    
	string       orderNo              ; //ϵͳ������    
	string       localOrderNo         ; //�������ر��    
	char         matchType            ; //����    
	string       acctNo               ; //�ͻ���    
}SpotMatch,*PSpotMatch;


//----------------------------------------------���Ľӿ� [onRecvRtnForwardMatch] ����

// �ṹ����:onRecvRtnForwardMatch
typedef struct tagForwardMatch
{
	string       matchNo              ; //�ɽ����    
	char         buyOrSell            ; //��������    
	string       clientID             ; //�ͻ�����    
	char         clientType           ; //�ͻ�����    
	string       instID               ; //��Լ����    
	string       memberID             ; //��Ա����    
	string       matchDate            ; //�ɽ�����    
	string       matchTime            ; //�ɽ�ʱ��    
	double       price                ; //�۸�    
	int          volume               ; //����    
	double       marginRate           ; //��֤����    
	char         rateType             ; //��֤������    
	string       orderNo              ; //ϵͳ������    
	string       localOrderNo         ; //�������ر��    
	string       acctNo               ; //�ͻ���    
}ForwardMatch,*PForwardMatch;


//----------------------------------------------���Ľӿ� [onRecvRtnDeferMatch] ����

// �ṹ����:onRecvRtnDeferMatch
typedef struct tagDeferMatch
{
	string       matchNo              ; //�ɽ����    
	char         buyOrSell            ; //��������    
	string       clientID             ; //�ͻ�����    
	char         clientType           ; //�ͻ�����    
	string       instID               ; //��Լ����    
	string       memberID             ; //��Ա����    
	string       matchDate            ; //�ɽ�����    
	string       matchTime            ; //�ɽ�ʱ��    
	double       price                ; //�۸�    
	int          volume               ; //����    
	char         offsetFlag           ; //��ƽ��־    
	string       orderNo              ; //ϵͳ������    
	string       localOrderNo         ; //�������ر��    
	string       acctNo               ; //�ͻ���    
}DeferMatch,*PDeferMatch;


//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppMatch] ����

// �ṹ����:onRecvRtnDeferDeliveryAppMatch
typedef struct tagDeferDeliveryAppMatch
{
	string       matchNo              ; //�ɽ����    
	string       clientID             ; //�ͻ�����    
	string       instID               ; //��Լ����    
	string       memberID             ; //��Ա����    
	char         buyOrSell            ; //��������    
	int          volume               ; //����    
	string       matchDate            ; //�ɽ�����    
	string       matchTime            ; //�ɽ�ʱ��    
	string       orderNo              ; //������    
	string       LocalOrderNo         ; //�������ر��    
	char         middleFlag           ; //�Ƿ�Ϊ������    
	string       acctNo               ; //�ͻ���    
}DeferDeliveryAppMatch,*PDeferDeliveryAppMatch;


//----------------------------------------------���Ľӿ� [onRecvRtnETFMatch] ����

// �ṹ����:onRecvRtnETFMatch
typedef struct tagETFMatch				//add by luobaolin 2013-3-19		
{
	string		orderNo			; //����ETF���ױ��
	string		b_etf_trade_type	; //ETF��������		
	string		acct_no				; //�ͻ���
	string		etf_id				; //ETF�������
	string		exch_date			; //��������		
	string		prod_code1			; //��Լ����1		
	double		day_cash_balance1	; //T��Ԥ���ֽ���1
	double		weight1				; //����1			
	string		prod_code2			; //��Լ����2		
	double		day_cash_balance2	; //T��Ԥ���ֽ���2
	double		weight2				; //����2			
	string		prod_code3			; //��Լ����3		
	double		day_cash_balance3	; //T��Ԥ���ֽ���3
	double 		weight3				; //����3			
	string		prod_code4			; //��Լ����4		
	double		day_cash_balance4	; //T��Ԥ���ֽ���4
	double		weight4				; //����4			
	string		prod_code5			; //��Լ����5		
	double		day_cash_balance5	; //T��Ԥ���ֽ���5
	double		weight5				; //����5	
	double      froz_trans_fee      ; //�����˱���
	double      froz_diff_fee       ; //�������
	string		local_order_no		; //���ر��	

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

//----------------------------------------------���Ľӿ� [onRecvSpotQuotation] ����

// �ṹ����:onRecvSpotQuotation
typedef struct tagSpotQuotation
{
	string       instID               ; //��Լ����    
	string       name                 ; //��Լ����    
	double       lastClose            ; //������    
	double       open                 ; //���̼�    
	double       high                 ; //��߼�    
	double       low                  ; //��ͼ�    
	double       last                 ; //���¼�    
	double       close                ; //���̼�    
	double       bid1                 ; //���1    
	int          bidLot1              ; //����1    
	double       bid2                 ; //���2    
	int          bidLot2              ; //����2    
	double       bid3                 ; //���3    
	int          bidLot3              ; //����3    
	double       bid4                 ; //���4    
	int          bidLot4              ; //����4    
	double       bid5                 ; //���5    
	int          bidLot5              ; //����5    
	double       ask1                 ; //����1    
	int          askLot1              ; //����1    
	double       ask2                 ; //����2    
	int          askLot2              ; //����2    
	double       ask3                 ; //����3    
	int          askLot3              ; //����3    
	double       ask4                 ; //����4    
	int          askLot4              ; //����4    
	double       ask5                 ; //����5    
	int          askLot5              ; //����5    
	int          volume               ; //�ɽ�����˫�ߣ�    
	int          weight               ; //�ɽ���˫�ߣ�����    
	double       highLimit            ; //��ͣ��    
	double       lowLimit             ; //��ͣ��    
	double       upDown               ; //�ǵ�    
	double       upDownRate           ; //�ǵ�����    
	double       turnOver             ; //�ɽ���    
	double       average              ; //����    
	string       quoteDate            ; //��������    
	string       quoteTime            ; //����ʱ��    
	int          sequenceNo           ; //�������    
}SpotQuotation,*PSpotQuotation;


//----------------------------------------------���Ľӿ� [onRecvForwardQuotation] ����

// �ṹ����:onRecvForwardQuotation
typedef struct tagForwardQuotation
{
	string       instID               ; //��Լ����    
	string       name                 ; //��Լ����    
	double       lastSettle           ; //�����    
	double       lastClose            ; //������    
	double       open                 ; //���̼�    
	double       high                 ; //��߼�    
	double       low                  ; //��ͼ�    
	double       last                 ; //���¼�    
	double       close                ; //���̼�    
	double       settle               ; //�����    
	double       bid1                 ; //���1    
	int          bidLot1              ; //����1    
	double       bid2                 ; //���2    
	int          bidLot2              ; //����2    
	double       bid3                 ; //���3    
	int          bidLot3              ; //����3    
	double       bid4                 ; //���4    
	int          bidLot4              ; //����4    
	double       bid5                 ; //���5    
	int          bidLot5              ; //����5    
	double       ask1                 ; //����1    
	int          askLot1              ; //����1    
	double       ask2                 ; //����2    
	int          askLot2              ; //����2    
	double       ask3                 ; //����>3    
	int          askLot3              ; //����3    
	double       ask4                 ; //����4    
	int          askLot4              ; //����4    
	double       ask5                 ; //����5    
	int          askLot5              ; //����5    
	int          volume               ; //�ɽ���    
	int          weight               ; //�ɽ���˫�ߣ�����    
	double       highLimit            ; //��ͣ��    
	double       lowLimit             ; //��ͣ��    
	int          Posi                 ; //�ֲ���    
	double       upDown               ; //�ǵ�    
	double       upDownRate           ; //�ǵ�����    
	double       turnOver             ; //�ɽ���    
	double       average              ; //����    
	string       quoteDate            ; //��������    
	string       quoteTime            ; //����ʱ��    
	int          sequenceNo           ; //�������    
}ForwardQuotation,*PForwardQuotation;


//----------------------------------------------���Ľӿ� [onRecvDeferQuotation] ����

// �ṹ����:onRecvDeferQuotation
typedef struct tagDeferQuotation
{
	string       instID               ; //��Լ����    
	string       name                 ; //��Լ����    
	double       lastSettle           ; //�����    
	double       lastClose            ; //������    
	double       open                 ; //���̼�    
	double       high                 ; //��߼�    
	double       low                  ; //��ͼ�    
	double       last                 ; //���¼�    
	double       close                ; //���̼�    
	double       settle               ; //�����    
	double       bid1                 ; //���1    
	int          bidLot1              ; //����1    
	double       bid2                 ; //���2    
	int          bidLot2              ; //����2    
	double       bid3                 ; //���3    
	int          bidLot3              ; //����3    
	double       bid4                 ; //���4    
	int          bidLot4              ; //����4    
	double       bid5                 ; //���5    
	int          bidLot5              ; //����5    
	double       ask1                 ; //����1    
	int          askLot1              ; //����1    
	double       ask2                 ; //����2    
	int          askLot2              ; //����2    
	double       ask3                 ; //����>3    
	int          askLot3              ; //����3    
	double       ask4                 ; //����4    
	int          askLot4              ; //����4    
	double       ask5                 ; //����5    
	int          askLot5              ; //����5    
	int          volume               ; //�ɽ���    
	int          weight               ; //�ɽ���˫�ߣ�����    
	double       highLimit            ; //��ͣ��    
	double       lowLimit             ; //��ͣ��    
	int          Posi                 ; //�ֲ���    
	double       upDown               ; //�ǵ�    
	string       upDownRate           ; //�ǵ�����    
	string       turnOver             ; //�ɽ���    
	double       average              ; //����    
	string       quoteDate            ; //��������    
	string       quoteTime            ; //����ʱ��    
	int          sequenceNo           ; //�������    
	tagDeferQuotation()
	{
		instID        ="";    ; //��Լ����    
		name          ="";    ; //��Լ����    
		lastSettle    =0.0;    ; //�����    
		lastClose     =0.0;    ; //������    
		open          =0.0;    ; //���̼�    
		high          =0.0;    ; //��߼�    
		low           =0.0;    ; //��ͼ�    
		last          =0.0;    ; //���¼�    
		close         =0.0;    ; //���̼�    
		settle        =0.0;    ; //�����    
		bid1          =0.0;    ; //���1    
		bidLot1       =0;    ; //����1    
		bid2          =0.0;    ; //���2    
		bidLot2       =0;    ; //����2    
		bid3          =0.0;    ; //���3    
		bidLot3       =0;    ; //����3    
		bid4          =0.0;    ; //���4    
		bidLot4       =0;    ; //����4    
		bid5          =0.0;    ; //���5    
		bidLot5       =0;    ; //����5    
		ask1          =0.0;    ; //����1    
		askLot1       =0;    ; //����1    
		ask2          =0.0;    ; //����2    
		askLot2       =0;    ; //����2    
		ask3          =0.0;    ; //����>3    
		askLot3       =0;    ; //����3    
		ask4          =0.0;    ; //����4    
		askLot4       =0;    ; //����4    
		ask5          =0.0;    ; //����5    
		askLot5       =0;    ; //����5    
		volume        =0;    ; //�ɽ���    
		weight        =0;    ; //�ɽ���˫�ߣ�����    
		highLimit     =0.0;    ; //��ͣ��    
		lowLimit      =0.0;    ; //��ͣ��    
		Posi          =0;    ; //�ֲ���    
		upDown        =0.0;    ; //�ǵ�    
		upDownRate    ="";    ; //�ǵ�����    
		turnOver      ="";    ; //�ɽ���    
		average       =0.0;    ; //����    
		quoteDate     ="";    ; //��������    
		quoteTime     ="";    ; //����ʱ��    
		sequenceNo    =0;    ; //�������    
	}
}DeferQuotation,*PDeferQuotation;


//----------------------------------------------���Ľӿ� [onRecvRtnSpotInstStateUpdate] ����

// �ṹ����:onRecvRtnSpotInstStateUpdate
typedef struct tagSpotInstState
{
	string       instID               ; //��Լ����    
	char         tradeState           ; //��Լ����״̬    
}SpotInstState,*PSpotInstState;


//----------------------------------------------���Ľӿ� [onRecvRtnForwardInstStateUpdate] ����

// �ṹ����:onRecvRtnForwardInstStateUpdate
typedef struct tagForwardInstState
{
	string       instID               ; //��Լ����    
	char         tradeState           ; //��Լ����״̬    
}ForwardInstState,*PForwardInstState;


//----------------------------------------------���Ľӿ� [onRecvRtnDeferInstStateUpdate] ����

// �ṹ����:onRecvRtnDeferInstStateUpdate
typedef struct tagDeferInstState
{
	string       instID               ; //��Լ����    
	char         tradeState           ; //��Լ����״̬    
}DeferInstState,*PDeferInstState;


//----------------------------------------------���Ľӿ� [onRecvRtnSpotMarketStateUpdate] ����

// �ṹ����:onRecvRtnSpotMarketStateUpdate
typedef struct tagSpotMarketState
{
	string       marketID             ; //�г�����    
	char         marketState          ; //�г�����״̬    
}SpotMarketState,*PSpotMarketState;


//----------------------------------------------���Ľӿ� [onRecvRtnForwardMarketStateUpdate] ����

// �ṹ����:onRecvRtnForwardMarketStateUpdate
typedef struct tagForwardMarketState
{
	string       marketID             ; //�г�����    
	char         marketState          ; //�г�����״̬    
}ForwardMarketState,*PForwardMarketState;


//----------------------------------------------���Ľӿ� [onRecvRtnDeferMarketStateUpdate] ����

// �ṹ����:onRecvRtnDeferMarketStateUpdate
typedef struct tagDeferMarketState
{
	string       marketID             ; //�г�����    
	char         marketState          ; //�г�����״̬    
}DeferMarketState,*PDeferMarketState;


//----------------------------------------------���Ľӿ� [onAcctCapitalAccess] ����

// �ṹ����:onAcctCapitalAccess
typedef struct tagAcctCapitalAccess
{
	string       fund_src_type        ; //�ʽ���Դ����    fund_src_type
	string       serial_no            ; //������ˮ��    
	string       acct_no              ; //�ͻ���    
	int          access_way           ; //��ȡ����    ���뷽��access_way
	double       amount               ; //ת�˽��    
}AcctCapitalAccess,*PAcctCapitalAccess;


//----------------------------------------------���Ľӿ� [onCustInfoChange] ����

// �ṹ����:onCustInfoChange
typedef struct tagCustInfoChange
{
	int          update_flag          ; //���ı�־    1������2���޸�3��ɾ��
	string       acct_no              ; //�ͻ���    
	string       member_id            ; //��Ա���    
	string       cust_abbr            ; //�ͻ����    
	string       m_Fare_model_id      ; //��Ա����ģ��ID    
	string       b_Fare_model_id      ; //����������ģ��ID    
	string       acct_type            ; //�˻�����    acct_type
	string       acct_stat            ; //�˻�״̬    
	string       branch_ID            ; //�����������    
}CustInfoChange,*PCustInfoChange;

// �ṹ����:onCustCancelNotify
typedef struct tagCustCancelNotify
{
	int          update_flag          ; //���ı�־    1������2���޸�3��ɾ��
	string       acct_no              ; //�ͻ���    
	string       cancel_sys_date      ; //��������
}CustCancelNotify,*PCustCancelNotify;


//----------------------------------------------���Ľӿ� [onAck] ����

// �ṹ����:onAck
typedef struct tagAck
{
	string       ack                  ; //ȷ��    
}Ack,*PAck;

//----------------------------------------------���Ľӿ� [onBaseTableUpdate] ����

// �ṹ����:onBaseTableUpdate
typedef struct tagBaseTableUpdate
{
	string       table_name           ; //����    ��֧�ֵı�����bank_infobank_mer_code_infobranch_infobroker_infocode_tablefare_model_defacct_fare_detailfare_model_detailinstID_defsystem_parateller_infovariety
}BaseTableUpdate,*PBaseTableUpdate;


//----------------------------------------------���Ľӿ� [onSysInit] ����

// �ṹ����:onSysInit
typedef struct tagSysInit
{
	string       old_exch_date        ; //ԭ��������    
	string       new_exch_date        ; //�½�������    
}SysInitStru,*PSysInitStru;

//----------------------------------------------���Ľӿ� [onSysStatChange] ����

// �ṹ����:onSysStatChange
typedef struct tagSysStat
{
	string       sys_date             ; //ϵͳ����    
	string       exch_date            ; //��������    
	string       m_sys_stat           ; //����ϵͳ״̬    m_sys_stat
	string       b_sys_stat           ; //������ϵͳ״̬    b_sys_stat
}SysStat,*PSysStat;

//----------------------------------------------���Ľӿ� [onBourseSysStatChange] ���� add by zww 2015-5-20

// �ṹ����:onBourseSysStatChange
typedef struct tagBourseSysStat
{
	string       sys_date             ; //ϵͳ����    
	string       exch_date            ; //��������    
	//string       m_sys_stat           ; //����ϵͳ״̬    m_sys_stat
	string       b_sys_stat           ; //������ϵͳ״̬    b_sys_stat
	string		 bourse_id			  ; //������ "10"-�Ͻ���
}BourseSysStat,*PBourseSysStat;

//---------------------------------------------- ���Ľӿ� [onForceCovOrderNtf] add by liuwei 2012-10-22

// �ṹ���壺onForceCovOrderNtf
typedef struct tagForceCovOderNtf
{
	int          oper_flag; // ������־ 1���㲥
	string       client_serial_no; //�ͻ�����ˮ�ţ��������
	string       local_order_no; // ���ر�����
	string		 f_order_no; //ǿƽ����
	string       rsp_order_msg;         // Ӧ����Ϣ
	string       state;
}ForceCovOrderNtf, *PForceCovOrderNtf;

//---------------------------------------------- ���Ľӿ� [onForceCovOrderCancelNtf] add by liuwei 2012-10-23

// �ṹ���壺onForceCovOrderCancelNtf
typedef struct tagForceCovOderCancelNtf
{
	int          oper_flag; // ������־ 1���㲥
	string       client_serial_no; //�ͻ�����ˮ��
	string       local_order_no; // ���ر�����
}ForceCovOrderCancelNtf, *PForceCovOrderCancelNtf;

//----------------------------------------------���Ľӿ� [onRecvRtnFpMatch] ����

// �ṹ����:onRecvRtnFpMatch
typedef struct tagFpMatch
{
	string     MatchNo    ;         //�ɽ�����   
	string     MatchDate  ;         //�ɽ�����   
	string     DeliDate   ;         //��������   
	string     MatchGame  ;         //�ɽ�����   
	int        MatchRound ;         //�ɽ��ִ�   
	string     MemberID   ;         //��Ա���   
	string     AcctNo     ;         //�ͻ���     
	string     ProdCode   ;         //��Լ       
	char       Bs         ;         //��������
	double     MatchPrice ;         //�ɽ����� 
	int        MatchAmount;         //�ɽ�����   
	string     EntrPhase  ;         //�걨�׶�   
	int        IsAllocate ;         //�Ƿ�Ϊ��̯ 

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


//----------------------------------------------���Ľӿ� [onRecvRtnFpQuotation] ����

// �ṹ����:onRecvRtnFpQuotation
typedef struct tagFpQuotation
{
	string      ProdCode           ;//��Լ����      
	string      ProdName           ;//��Լ����      
	string      ExchDate           ;//��������      
	string      GameID             ;//���α��      
	double      Price              ;//�۸�          
	string      IsSettlePrice      ;//�Ƿ��ǽ����  
	int         MatchVolume        ;//�ɽ�����˫�ߣ�
	double      InitPrice          ;//��ʼ��        
	int         Rounds             ;//����          
}FpQuotation,*PFpQuotation;


//----------------------------------------------���Ľӿ� [onRecvRspFpOrder] ����

// �ṹ����:onRecvRspFpOrder
typedef struct tagFpOrder
{
	string      OrderNo           ;//������    
	string      LocalOrderNo      ;//���ر�����
	string      MemberID          ;//��Ա���  
	string      AcctNo            ;//�ͻ���    
	string      ProdCode          ;//��Լ      
	char        Bs                ;//��������  
	string      OrderType         ;//��������  
	int         Amount            ;//ί������  
	string      ApplyDate         ;//ί������  
	string      ApplyTime         ;//ί��ʱ��  
	string      EntrPhase         ;//�걨�׶�  
	string      GameID            ;//���α��
	int         RoundID			  ;//�ִα��
	double      EntrPrice         ;//ί�м۸�
	string      Status            ;//ί��״̬

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


//----------------------------------------------���Ľӿ� [onRecvRspFpOrderCancel] ����

// �ṹ����:onRecvRspFpOrderCancel
typedef struct tagFpOrderCancel
{
	string    MemberID          ;//��Ա���
	string    AcctNo            ;//�ͻ���  
	string    ProdCode          ;//��Լ    
	string    EntrPhase         ;//�걨�׶�
	char      Bs                ;//��������
	int       CancelAmount      ;//��������
	string    GameID            ;//���α��
	int       RoundID			;//�ִα��
	string    Status            ;//ί��״̬
	string    RootID		    ;//�������أ����ݿ��ж����Ŵ�ŵ�ֵ����RootID

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


//----------------------------------------------���Ľӿ� [onRecvRspFpOrderFullCancel] ����

// �ṹ����:onRecvRspFpOrderFullCancel
typedef struct tagFpOrderFullCancel
{
	string    GameID            ;//���α��    
	int       RoundID           ;//�ִα��    
	string    ProdCode          ;//��Լ        
	char      Bs                ;//��������    
	string    NeedCancel        ;//�Ƿ���Ҫȫ��
	double    NewRoundPrice     ;//��һ�ּ۸� 

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


//----------------------------------------------���Ľӿ� [onRecvRtnFpRoundQuotation] ����

// �ṹ����:onRecvRtnFpRoundQuotation
typedef struct tagFpRoundQuotation
{
	string      ProdCode            ;//��Լ����
	string      ProdName            ;//��Լ����
	string      ExchDate            ;//��������
	string      GameID              ;//���α��
	int         RoundID             ;//�ִα��
	double      Price               ;//�۸�    
	double      Adjust              ;//�䶯    
	int         BidLot              ;//����    
	int         AskLot              ;//����    
	double      LastSettlePrice     ;//������
	string      QuoteTime           ;//����ʱ��
	string      SequenceNo          ;//�������

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


//----------------------------------------------���Ľӿ� [onRecvRspFpFrCancel] ����

// �ṹ����:onRecvRspFpFrCancel
typedef struct tagFpFrCancel
{
	string      ExchDate            ;//��������
	string      ProdCode            ;//��Լ    
	string      GameID              ;//���α��
	int         RoundID             ;//�ִα��
	char        Bs                  ;//��������
	int         CancelAmount        ;//��������
	string      MemberID            ;//��Ա��  
	string      AcctNo              ;//�ͻ���

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


//----------------------------------------------���Ľӿ� [onCapitalChange] ����

// �ṹ����:onRecvRspFpFrCancel
typedef struct tagCapitalHandle
{
	string      bank_no            ;//��Ա��  
	string      acct_no              ;//�ͻ���
	double      capital             ;//�ͻ��䶯���
	string      serial_no            ;//��ˮ��
	string		business_type        ;//ҵ������


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