#ifndef _PACKET_BODY_STRUCT_TRADE_RISK_H                 
#define _PACKET_BODY_STRUCT_TRADE_RISK_H

#include <string>
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

//----------------------------------------------���Ľӿ� [3061] ����

// �ṹ����:���տͻ���������
typedef struct tagSubscriberReq
{
	int          oper_flag            ; //������־    1������2��ȡ��
	string       teller_id            ; //���ԱID    
	string       branch_id            ; //�����Ĵ������ID    
}SubscriberReq,*PSubscriberReq;


// �ṹ����:���տͻ����Ľ����Ӧ
typedef struct tagSubscriberRsp
{
	int          oper_flag            ; //������־    1������2: ȡ��
}SubscriberRsp,*PSubscriberRsp;


//----------------------------------------------���Ľӿ� [3062] ����

// �ṹ����:���տͻ���ϸ����
typedef struct tagRiskCustDetailReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       branch_id            ; //����������    
	string		 cust_type			  ; //�ͻ�����
	string		 acct_type			  ; //�ͻ�����  ���� �� ����
	string		 cust_no			  ; //�ͻ���
	string		 cust_name			  ; //�ͻ�����
	string		 risk_degree2		  ; //���ն�
	string		 bk_acct_no  		  ; //���п���
	string       top_number           ; //���տͻ�����    �����ȫ��
}RiskCustDetailReq,*PRiskCustDetailReq;


// �ṹ����:���տͻ���ϸ��Ӧ
typedef struct tagRiskCustDetailRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg risk_result          ; ////���տͻ����    �ֶΣ��ͻ��š��ͻ���ơ��ͻ����𡢷��ն�1�����ն�2�����յȼ����ͻ�׷���ߡ��ͻ����ǿƽ�ߡ��ͻ�����ǿƽ�ߡ����շ��յȼ�����Ա��֤�𡢽�������֤���ܱ�֤��׷��������ӯ���������ʽ𡢽��ճ�����˻����͡��ͻ�׷�������ߡ��������͡����շ������͡�����׷����������������
}RiskCustDetailRsp,*PRiskCustDetailRsp;


//----------------------------------------------���Ľӿ� [3063] ����

// �ṹ����:�ͻ���ϸ��Ϣ����
typedef struct tagCustSpecReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       acct_no              ; //�ͻ���    
}CustSpecReq,*PCustSpecReq;


// �ṹ����:�ͻ���ϸ��Ϣ��Ӧ
typedef struct tagCustSpecRsp
{
	int          oper_flag            ; //������־    1����ѯ
	string       acct_no              ; //�ͻ���   
	//add yanfy 2010-07-10
	int	     except_type          ; //����ͻ���־	
	string   exceptdatetime;		 //����ͻ��ĳ�ʱ���ڼ�ʱ��


	string       cust_abbr            ; //�ͻ����
	string       cust_type            ; //�ͻ�����
	string       contact_no           ; //����   
    string       mobile_phone         ; //�ֻ�
	string       bank_id              ; //���д���    
	string       bk_acct_no           ; //�����˺�    
	string       branch_id            ; //�����̱��    
	string       branch_name          ; //����������    
	string       curr_bal             ; //�ͻ����    
	string       froz_order           ; //��������   
	string       froz_other           ; //��������    
	string       curr_can_use         ; //�����ʽ�   
	string       risk_curr_can_use         ; //�����ʽ�   
	string       margin_mem           ; //��Ա��֤�� 
	string       margin_exch          ; //��������֤�� 
	string       margin_total         ; //�ֱֲܳ�֤��    
	string       surplus              ; //����ӯ��    
	string       f_in_out_bal         ; //���ճ����    
	string       in_out_bal_tm        ; //�����ʱ��    
	string       risk_deg1            ; //���ն�1
	string       risk_deg2            ; //���ն�2
	string       debt_call_line       ; //׷��������
	string       debt_mem             ; //׷����
	string       debt_exch_rel        ; //���ǿƽ��
	string       debt_exch_abs        ; //����ǿƽ��
	string       risk_grade_id        ; //���յȼ�    
	string       risk_type            ; //��������  
	string       debt_call            ; //׷�����    
	string       risk_type_yda        ; //���շ�������
	string       risk_deg_yda         ; //���շ��յȼ�
	string       debt_call_yda        ; //����׷�����
	string       risk_days            ; //������������
	//��� add by zww 2015-6-10
	string		 offset_margin_mem	  ; //��Ա��ֶ�ȱ�֤��
	string		 offset_margin_exch	  ; //��������ֶ�ȱ�֤��
	string		 curr_margin_mem	  ; //��Ա���ұ�֤��
	string		 curr_margin_exch	  ; //���������ұ�֤��
	string		 offset_quota_today	  ; //�����ܿ��ó�ֶ��
	string		 offset_quota_avaliable;//��ǰ���ó�ֶ��

	ArrayListMsg alm_stor_info        ; //�����Ϣ    �ֶΣ�Ʒ�ִ��룬������������ÿ�桢�ܶ��� 
	ArrayListMsg alm_posi_info        ; //�ֲ���Ϣ    �ֶΣ���Լ���롢��ͷ�ֲ���������ͷ�ֲ־��ۡ���ͷ�����ۡ���ͷ�ֲ���������ͷ�ֲ־��ۡ���ͷ�����ۡ�����ӯ��������۸�
	ArrayListMsg alm_broker_info      ; //�����Ϣ    �ֶΣ��ͻ��������ƣ��ͻ��������������ֻ�������
	ArrayListMsg alm_cov_posi_info    ; //�����Ϣ    �ֶΣ��ɽ����� ������ �������� ��Լ���� �ͷŽ�������֤�� �ͷŻ�Ա��֤�� �ͷ��ܱ�֤�� �ɽ�ʱ�� �ɽ��۸� �ɽ����� ��ƽ��־
	ArrayListMsg alm_posi_detail      ; //�ֲ���ˮ��Ϣ  �ֶΣ���Լ����,��ձ�־,��λ����,����ʱ��,��λ����,��λ����,���ᱣ֤��,����ӯ��
}CustSpecRsp,*PCustSpecRsp;


//----------------------------------------------���Ľӿ� [3064] ����

// �ṹ����:������ʾ��ѯ����
typedef struct tagRiskNotifyQueryReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       branch_id            ; //����������    
	string		 acct_type			  ; //�˻�����
	string		 cust_type			  ; //�ͻ�����
	string       begin_time           ; //��ʼʱ��    
	string       end_time             ; //����ʱ��    
	string       acct_no              ; //�ͻ���    
	string       tip_type             ; //��ʾ����    tip_type1��ʾ2׷��֪ͨ3ǿƽ֪ͨ
	string       risk_grade_src       ; //Դ���յȼ�  
	string       risk_grade_des       ; //Ŀ�ķ��յȼ� 
}RiskNotifyQueryReq,*PRiskNotifyQueryReq;


// �ṹ����:������ʾ��ѯ��Ӧ
typedef struct tagRiskNotifyQueryRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg alm_result           ; //��ѯ���    �ֶΣ�ʱ�䡢Դ���յȼ���Ŀ����յȼ����ͻ��š��ͻ���ơ��ͻ������˻����͡����ն�1�����ն�2��׷����֪ͨ���⡢֪ͨ���ݡ������̡������̼��
}RiskNotifyQueryRsp,*PRiskNotifyQueryRsp;

//----------------------------------------------���Ľӿ� [3065] ����

// �ṹ����:δȫ���ɽ���ǿƽ����ѯ
typedef struct tagNotDealFCQueryReq
{
	int            oper_flag      ; // ������־    1����ѯ
	ArrayListMsg   acct_no_list   ; // �ͻ����б�֧��ͬʱ��ѯ���
	string         acct_no        ; // �ͻ���    
}NotDealFCQueryReq,*PNotDealFCQueryReq;


// �ṹ����:δȫ���ɽ���ǿƽ����ѯ��Ӧ
typedef struct tagNotDealFCQueryRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg f_order_result       ; //��ѯ���    �ֶΣ������š���Լ���롢��������ί�м۸�ί���������ɽ�����������״̬��ƽ�����͡�������Դ
}NotDealFCQueryRsp,*PNotDealFCQueryRsp;


//----------------------------------------------���Ľӿ� [3066] ����

// �ṹ����:����ǿƽ������
typedef struct tagFCOrderSubmitReq
{
	int          oper_flag            ; //������־    1����ѯ
	int          source_falg          ; //���ɱ�־    1�ֹ� 2�Զ�
	string       acct_no              ; //�ͻ���    
	string       date                 ; //����    
	string       curr_bal             ; //�������    
	string       curr_can_use         ; //�����ʽ�  
	string       margin_exch          ; //�������ֱֲ�֤��    
	string       margin_mem           ; //��Ա�ֱֲ�֤��    
	string       margin_total         ; //�ֱֲܳ�֤��    
	string       risk_degree1         ; //���ն�1
	string       risk_degree2         ; //���ն�2    
	string       risk_grade_id        ; //���յȼ�   
	string       risk_grade_yda       ; //���շ��յȼ�   
	string       float_surplus        ; //����ӯ��    
	string       prod_price           ; //��Լ�۸�    ������Լ�۸�
	string       fc_order             ; //�������    
	string       prod_code            ; //��Լ����    
	string       buyorsell            ; //��������    
	string       price                ; //ί�м۸�    
	int          volume               ; //ί������    
	string       lbatchno             ; //���κ�    
	string       f_order_no           ; //ǿƽ����    
	string       teller_id            ; //���Ա    
	string       debt_call            ; //��ǰ׷�����
	string       debt_call_yda        ; //����׷����� 
	string       risk_type            ; //���շ������
	string       risk_type_yda        ; //���շ������
	string       risk_days            ; //������������
}FCOrderSubmitReq,*PFCOrderSubmitReq;


// �ṹ����:����ǿƽ��������Ӧ
typedef struct tagFCOrderSubmitRsp
{
	int          oper_flag            ; //������־    1����ѯ
	string       acct_no              ; //�ͻ���    
	string       serial_no            ; //�������    
	string       f_order_no           ; //ǿƽ����    
	string       local_order_no       ; //���ر�����    
	int          order_state          ; //ǿƽ��״̬    order_state
}FCOrderSubmitRsp,*PFCOrderSubmitRsp;


//----------------------------------------------���Ľӿ� [3067] ����

// �ṹ����:�����Զ�ǿƽ������
typedef struct tagAutoGenFCOrderReq
{
	int          oper_flag            ; //������־ 1����ѯ
	string       acct_no              ; //�ͻ���    
	string       risk_grade_id        ; //���յȼ�    
	string       fc_mode              ; //ǿƽ��ʽ 1�м� 2�޼� 3ͣ��� 4 ָ���۸�
	string       lbatchno             ; //���κ�    
	string       teller_id            ; //���Ա 
	ArrayListMsg posi_result          ; //��Լ���������򡢼۸�����
	ArrayListMsg cov_price_info		  ;//ƽ�ּ۸���Ϣ    ��Լ���롢��ƽ�ּ۸񡢿ղ�ƽ�ּ۸�
	char         risk_target          ; // ǿƽĿ�꣬0��������1��׷����2�����ǿƽ
}AutoGenFCOrderReq,*PAutoGenFCOrderReq;


// �ṹ����:�����Զ�ǿƽ����Ӧ
typedef struct tagAutoGenFCOrderRsp
{
	int          oper_flag            ; //������־    1����ѯ
	string       lbatchno             ; //���κ�    
	ArrayListMsg alm_result           ; //���ɽ��    �ֶ�˳�򣺿ͻ��š�ǿƽ���š���Լ���������򡢼۸�����
}AutoGenFCOrderRsp,*PAutoGenFCOrderRsp;


	//----------------------------------------------���Ľӿ� [3069] ����

// �ṹ����:ǿƽ����ѯ����
typedef struct tagFCOrderQueryReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       acct_no              ; //�ͻ���    
	string       branch_id            ; //�����̱��    
	string		 acct_type			  ; //�˻�����
	string		 cust_type			  ; //�ͻ�����
	string       instid               ; //��Լ����    
	string       gene_type            ; //���ɷ�ʽ    
	string       f_teller_id          ; //ǿƽ����Ա
	string       begin_date           ; //��ʼ����    
	string       end_date             ; //��������  
	ArrayListMsg order_status_set     ; //����״̬    
}FCOrderQueryReq,*PFCOrderQueryReq;


// �ṹ����:ǿƽ����ѯ��Ӧ
typedef struct tagFCOrderQueryRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg alm_result           ; //��ѯ���    �ֶ�˳�򣺱�����, �ͻ���, �ͻ����,��Լ����������ί�м۸�ί���������ɽ��۸񣬱���״̬��ǿƽ���ţ�ǿƽ����Ա����������Ա��ί��ʱ�䣬����ʱ�䣬�����̱�ţ������̼��
}FCOrderQueryRsp,*PFCOrderQueryRsp;


//----------------------------------------------���Ľӿ� [3070] ����

// �ṹ����:ǿƽ����������
typedef struct tagFCOrderCancelReq
{
	int          oper_flag            ; //������־    1:�޸� 
	string       order_no             ; //������    
}FCOrderCancelReq,*PFCOrderCancelReq;


// �ṹ����:ǿƽ��������Ӧ
typedef struct tagFCOrderCancelRsp
{
	int          oper_flag            ; //������־    1:�޸� 
	string       order_no             ; //������    
}FCOrderCancelRsp,*PFCOrderCancelRsp;

//----------------------------------------------���Ľӿ� [3311] ����

// �ṹ����:ǿƽ����������
typedef struct tagFCOrderCancelBatchReq
{
	int          oper_flag            ; //������־    1:�޸� 
	ArrayListMsg       order_no             ; //������    
}FCOrderCancelBatchReq,*PFCOrderCancelBatchReq;


// �ṹ����:ǿƽ��������Ӧ
typedef struct tagFCOrderCancelBatchRsp
{
	int          oper_flag            ; //������־    1:�޸� 
// 	string       order_no             ; //������    
}FCOrderCancelBatchRsp,*PFCOrderCancelBatchRsp;

//----------------------------------------------���Ľӿ� [3088] ����

// �ṹ����:���յȼ���ѯ
typedef struct tagRiskGradeQueryReq
{
	int          oper_flag            ; //������־    1:�޸� 
}RiskGradeQueryReq,*PRiskGradeQueryReq;


// �ṹ����:���յȼ���ѯ
typedef struct tagRiskGradeQueryRsp
{
	int          oper_flag            ; //������־    1:��ѯ
	ArrayListMsg query_result         ; //��ѯ���    ������ţ��������ƣ���ɫ
}RiskGradeQueryRsp,*PRiskGradeQueryRsp;

//----------------------------------------------���Ľӿ� [3081] ����

// �ṹ����:�������ñ���
typedef struct tagRiskStateParaReq
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 2������3��ɾ��
	string       obj_type             ; //��������    obj_type1�������2 �˻�����3 �ͻ�
	string       obj_id               ; //���ö���    ��Ӧ���͵ı��
	string       debt_mem_value       ; //׷����    
	string       debt_exch_value      ; //ǿƽ��    
	string       debt_call_value      ; //׷��������    
	ArrayListMsg obj_content          ; //��������    �ֶΣ����յȼ����, ������Сֵ���������ֵ
}RiskStateParaReq,*PRiskStateParaReq;


// �ṹ����:�������ñ���
typedef struct tagRiskStateParaRsp
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 2������3��ɾ��
	ArrayListMsg alm_result          ; //�ͻ�,�������,�˻�����,�ͻ�����,���ǿƽ��,׷��������,��������(ArrayListMsg �ֶΣ�������������,������Сֵ���������ֵ )
	string       obj_type             ; //��������    obj_type1�������2 �˻�����3 �ͻ�
	string       obj_id               ; //���ö���    ��Ӧ���͵ı��
	// 	string       debt_mem_value       ; //׷����    
	string       debt_exch_value      ; //ǿƽ��    
	string       debt_call_value      ; //׷��������    
	ArrayListMsg obj_content          ; //��������    �ֶΣ����յȼ����, ������Сֵ���������ֵ

}RiskStateParaRsp,*PRiskStateParaRsp;

	//----------------------------------------------���Ľӿ� [3082] ����

// �ṹ����:�������ñ���
typedef struct tagRiskhandleParaReq
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	string       handle_id            ; //������    
	string       handle_name          ; //��������    
	string       handle_method        ; //����ʽ    
	HashtableMsg para_set             ; //�����������    �����š��������ơ�����ʽ
}RiskhandleParaReq,*PRiskhandleParaReq;


// �ṹ����:�������ñ���
typedef struct tagRiskhandleParaRsp
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	string       handle_id            ; //������    
	string       handle_name          ; //��������    
	string       handle_method        ; //����ʽ    
	HashtableMsg para_set             ; //�����������    �����š��������ơ�����ʽ
}RiskhandleParaRsp,*PRiskhandleParaRsp;


//----------------------------------------------���Ľӿ� [3084] ����

// �ṹ����:�������ñ���
typedef struct tagRiskNotifyParaReq
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	string       tip_type             ; //����֪ͨ����    tip_type1��ʾ2׷��֪ͨ3ǿƽ֪ͨ
	string       risk_grade_src       ; //Դ���յȼ�  
	string       risk_grade_des       ; //Ŀ�ķ��յȼ� 
	string       notify_content       ; //��ʾ����    
}RiskNotifyParaReq,*PRiskNotifyParaReq;


// �ṹ����:�������ñ���
typedef struct tagRiskNotifyParaRsp
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	ArrayListMsg notify_content_set   ; //��ѯ���   ����֪ͨ���͡�Դ���յȼ���Ŀ����յȼ�����ʾ����
}RiskNotifyParaRsp,*PRiskNotifyParaRsp;


	//----------------------------------------------���Ľӿ� [3085] ����

// �ṹ����:�������ñ���
typedef struct tagForceCoverParaReq
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	ArrayListMsg prod_set             ; //��Լ˳�����    ��Լ���롢�������򡢺�Լ˳��ֵ
}ForceCoverParaReq,*PForceCoverParaReq;


// �ṹ����:�������ñ���
typedef struct tagForceCoverParaRsp
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	ArrayListMsg prod_set             ; //��Լ˳�����    ��Լ���롢�������򡢺�Լ˳��ֵ
}ForceCoverParaRsp,*PForceCoverParaRsp;


	//----------------------------------------------���Ľӿ� [3086] ����

// �ṹ����:�������ñ���
typedef struct tagBranchAuthParaReq
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	ArrayListMsg branch_set           ; //������    �ֶΣ������̺š��Ƿ���Ȩ
}BranchAuthParaReq,*PBranchAuthParaReq;


// �ṹ����:�������ñ���
typedef struct tagBranchAuthParaRsp
{
	int          oper_flag            ; //������־    0����ѯ1���޸� 
	ArrayListMsg branch_set           ; //������    �ֶΣ������̺š��Ƿ���Ȩ
}BranchAuthParaRsp,*PBranchAuthParaRsp;

	//----------------------------------------------���Ľӿ� [3091] ����

// �ṹ����:����ͳһ������
typedef struct tagRiskCustQueryReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       branch_id            ; //�����̱�� 
	string		 acct_type			  ; //�˻�����
	string		 cust_type			  ; //�ͻ�����
	string       acct_no              ; //�ͻ���    
	string       risk_grade_id        ; //���յȼ�    
	int			start_no;			//��ʼ��¼��
	int			page_no;			//	�ڼ�ҳ
	int			page_size;			//	ҳ��С
	int			total_record;		//	�ܼ�¼����
}RiskCustQueryReq,*PRiskCustQueryReq;


// �ṹ����:����ͳһ������
typedef struct tagRiskCustQueryRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	int			start_no;			//��ʼ��¼��
	int			page_no;			//	�ڼ�ҳ
	int			page_size;			//	ҳ��С
	int			total_record;		//	�ܼ�¼����
	ArrayListMsg alm_result           ; //��ѯ���    �ֶΣ��ͻ��š��ͻ���ơ����նȡ����յȼ��������ʽ𡢳ֱֲ�֤�𡢸���ӯ����׷���������̱�š�����������
}RiskCustQueryRsp,*PRiskCustQueryRsp;

	//----------------------------------------------���Ľӿ� [3093] ����

// �ṹ����:���������������壬֧�ַ�ҳ
typedef struct tagRiskTestCalReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       p_branch_id          ; //���Ա���������̺�  
	string       branch_id            ; //�����̺�    
	string       acct_no              ; //�ͻ���    
	string       acct_type            ; //�˻�����
	string       cust_type            ; //�ͻ�����
	ArrayListMsg instid               ; //��Լ    ��Լ���롢��Լ�۸񡢵�����֤����
	int          page_no              ; //ҳ��
	int          page_size            ; //ҳ��С
	int          total_record         ; //���ϼ�¼������
	ArrayListMsg risk_level           ; //Ҫ���صĿͻ��ķ��յȼ�
}RiskTestCalReq,*PRiskTestCalReq;


// �ṹ����:�ڲ���ת����/���˵���Ӧ������
typedef struct tagRiskTestCalRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	int          page_no              ; //ҳ��
	int          page_size            ; //ҳ��С
	int          total_record         ; //���ϼ�¼������
	ArrayListMsg cal_result           ; //������    �ֶ�˳�򣺿ͻ��ţ��ͻ���ƣ�Ԥ����նȣ�Ԥ����յȼ��������ʽ�Ԥ�Ᵽ֤��Ԥ�⸡��ӯ����Ԥ��׷���������̱�ţ����������ƣ��ͻ�����
}RiskTestCalRsp,*PRiskTestCalRsp;

	//----------------------------------------------���Ľӿ� [3094] ����

// �ṹ����:�ʽ𶳽�ⶳ����������
typedef struct tagRiskCustAllReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       begin_date           ; //��ʼ����    
	string       end_date             ; //��������    
	string       branch_id            ; //�����̱��    
	string		 acct_type			  ; //�˻�����
	string		 cust_type			  ; //�ͻ�����
	string       risk_grade_id        ; //���յȼ�    
}RiskCustAllReq,*PRiskCustAllReq;


// �ṹ����:�ʽ𶳽�ⶳ����Ӧ������
typedef struct tagRiskCustAllRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	ArrayListMsg risk_cust            ; //���տͻ���    �ֶΣ��ͻ��š��ͻ���ơ������̺š����ơ����նȡ����յȼ��������ʽ𡢸���ӯ����׷�������ճ����
}RiskCustAllRsp,*PRiskCustAllRsp;

	//----------------------------------------------���Ľӿ� [3095] ����

// �ṹ����:���ױ�֤��ⶳ����������
typedef struct tagRiskDistQueryReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       begin_date           ; //��ʼ����    
	string       end_date             ; //��������    
	string       branch_id            ; //�����̱��    
}RiskDistQueryReq,*PRiskDistQueryReq;


// �ṹ����:���ױ�֤��ⶳ����Ӧ������
typedef struct tagRiskDistQueryRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	string       branch_id            ; //�����̱��    
	ArrayListMsg risk_dist            ; //���նȷֲ�    ���յȼ����ͻ���
}RiskDistQueryRsp,*PRiskDistQueryRsp;

	//----------------------------------------------���Ľӿ� [3096] ����

// �ṹ����:������֤�����������
typedef struct tagBranchDistQueryReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       begin_time           ; //��ʼʱ��    
	string       end_time             ; //����ʱ��    
	ArrayListMsg risk_level           ; //���ն���ʼֵ    
}BranchDistQueryReq,*PBranchDistQueryReq;


// �ṹ����:������֤�����Ӧ������
typedef struct tagBranchDistQueryRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	ArrayListMsg branch_id            ; //�����̷ֲ�    �����̡��ͻ���������Ӧ���տͻ���
}BranchDistQueryRsp,*PBranchDistQueryRsp;

	//----------------------------------------------���Ľӿ� [3097] ����

// �ṹ����:ƽ���������������
typedef struct tagTryCloseReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       acct_no              ; //�ͻ���    
	ArrayListMsg close_para           ; //ƽ�ֲ���    ��Լ����, ƽ�ַ���, ƽ�ּ۸�, ƽ������
}TryCloseReq,*PTryCloseReq;


// �ṹ����:ƽ���������Ӧ������
typedef struct tagTryCloseRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	string       cust_id              ; //�ͻ���    
	string       curr_bal             ; //Ԥ�ƿ����ʽ�  
	string       margin_exch          ; //Ԥ�ƽ�������֤��  
	string       margin_mem           ; //Ԥ�ƻ�Ա��֤��  
	string       margin_total         ; //Ԥ���ܱ�֤��    
	string       float_surplus        ; //Ԥ�Ƹ���ӯ��    
	string       risk_degree1         ; //Ԥ�Ʒ��ն�1    
	string       risk_degree2         ; //Ԥ�Ʒ��ն�2    
	string       risk_grade           ; //Ԥ�Ʒ��յȼ�    
	string       risk_type            ; //Ԥ�Ʒ�������    
	string       call_debt           ; //Ԥ��׷�����
	//��� add by zww 2015-6-10
	string		 offset_margin_mem	  ; //��Ա��ֶ�ȱ�֤��
	string		 offset_margin_exch	  ; //��������ֶ�ȱ�֤��
	string		 curr_margin_mem	  ; //��Ա���ұ�֤��
	string		 curr_margin_exch	  ; //���������ұ�֤��
	string		 offset_quota_today	  ; //�����ܿ��ó�ֶ��
	string		 offset_quota_avaliable;//��ǰ���ó�ֶ��
}TryCloseRsp,*PTryCloseRsp;

	//----------------------------------------------���Ľӿ� [3098] ����

// �ṹ����:��Լ�����ѯ����������
typedef struct tagProdQuotationReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       prod_code            ; //��Լ����    
}ProdQuotationReq,*PProdQuotationReq;


// �ṹ����:��Լ�����ѯ����Ӧ������
typedef struct tagProdQuotationRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	ArrayListMsg quotaion_result      ; //��Լ������Ϣ    ��Լ����, ���¼ۣ����1������5����ͣ��ۣ���ͣ���
}ProdQuotationRsp,*PProdQuotationRsp;
//----------------------------------------------���Ľӿ� [3306] ����

// �ṹ����:����ԱƷ��ӯ���嵥
typedef struct tagRiskProfitLossReq
{
	int    oper_flag     ;	  //������־    0����ѯ   1������ 2���޸� 3��ɾ��
	string acct_no      ;    //��Ӫ����Ա�ͻ���      
}RiskProfitLossReq,*PRiskProfitLossReq;


// �ṹ����:�������ñ���
typedef struct tagRiskProfitLossRsp
{
	int          oper_flag        ;   //������־    0����ѯ
	ArrayListMsg amt_result       ;   //����
}RiskProfitLossRsp,*PRiskProfitLossRsp;
// �ṹ����:��ӪԤ����������
typedef struct tagRiskAlarmParaReq
{
	int    oper_flag     ;	  //������־    0����ѯ   1������ 2���޸� 3��ɾ��
	string index_id      ;    //���        
	string prod_code     ;    //Ԥ����      
	string notify_obj    ;    //Ԥ������    
	string term_value    ;    //Ԥ��ֵ      
	string notify_way    ;    //Ԥ����ʽ    
	string timeout       ;    //���ʱ��    
	string term_type     ;    //Ԥ������    
	string begin_day     ;    //��Ч��ʼʱ��
	string end_day       ;    //��Ч����ʱ��
	string teller_id     ;    //����Ա  
}RiskAlarmParaReq,*PRiskAlarmParaReq;


// �ṹ����:�������ñ���
typedef struct tagRiskAlarmParaRsp
{
	int          oper_flag            ; //������־  0����ѯ   1������ 2���޸� 3��ɾ��
	ArrayListMsg alm_result          ; //�ͻ�,�������,�˻�����,�ͻ�����,���ǿƽ��,׷��������,��������(ArrayListMsg �ֶΣ�������������,������Сֵ���������ֵ )
}RiskAlarmParaRsp,*PRiskAlarmParaRsp;


//----------------------------------------------���Ľӿ� [3303] ����
// �ṹ����:�Զ�ǿƽ��������������������
typedef struct tagHandleSmsReq
{
	int          oper_flag            ; //������־    0����ѯ 1���޸� 2:�޸� 3��ɾ��
	ArrayListMsg  alm_result  ; //����ֵ �������

}HandleSmsReq,*PHandleSmsReq;


// �ṹ����:�޸���С�䶯��λ����Ӧ������
typedef struct tagHandleSmsRsp
{
	int              oper_flag            ; //������־    0����ѯ 1���޸� 
}HandleSmsRsp,*PHandleSmsRsp;



//----------------------------------------------���Ľӿ� [3302] ����
// �ṹ����:�޸���С�䶯��λ����������
typedef struct tagAlterMinUnitReq
{
	int       oper_flag           ; //������־    0����ѯ 1���޸� 
	string    prod_code          ;//��Լ����
	string    min_unit           ;
	string	  quote_dot			 ; //�����뽻��Ʒ�ֵ����۸��� 
	int		  mincatchtime;		    //���ҵ���Ӧ����Ʒ�ֵĳ���ʱ��
	int		  maxcatchtime;			//δ�ҵ���Ӧ����Ʒ�ֵĳ���ʱ��
	string	  varietyCode;			//��Լ��Ӧ�Ľ���Ʒ���б���","�ָ�
}AlterMinUnitReq,*PAlterMinUnitReq;


// �ṹ����:�޸���С�䶯��λ����Ӧ������
typedef struct tagAlterMinUnitRsp
{
	int              oper_flag            ; //������־    0����ѯ 1���޸� 
	ArrayListMsg     alm_result     ;      //��Լ����,��С�䶯�� 
}AlterMinUnitRsp,*PAlterMinUnitRsp;

//----------------------------------------------���Ľӿ� [3301] ����
// �ṹ����:�Զ�ǿƽ��������������������
typedef struct tagAutoForceExecptConditionReq
{
	int          oper_flag            ; //������־    0����ѯ 1���޸� 2:�޸� 3��ɾ��
	string       obj_type             ; //��������    1�ͻ� 2�ͻ����� 3 �˻����� 4�������
	string       except_date_time     ; //��������ʱ��
	ArrayListMsg       type_value      ; //����ֵ �������
	
}AutoForceExecptConditionReq,*PAutoForceExecptConditionReq;


// �ṹ����:��Լ�����ѯ����Ӧ������
typedef struct  tagAutoForceExecptConditionRsp
{
	int          oper_flag            ; //������־    0����ѯ 1���޸� 2:�޸� 3��ɾ��
	ArrayListMsg  value_list          ;  //ֵ�б�
} AutoForceExecptConditionRsp,*PAutoForceExecptConditionRsp;


//----------------------------------------------���Ľӿ� [3100] ����
// �ṹ����:����֪ͨ��������������
typedef struct tagSmsParaReq
{
	int          oper_flag            ; //������־    0����ѯ 1���޸�
	string       acct_type            ; //�˻�����
	string       risk_type            ; //��������
	string       sms_content          ; //֪ͨ����ģ��
}SmsParaReq,*PSmsParaReq;


// �ṹ����:��Լ�����ѯ����Ӧ������
typedef struct tagSmsParaRsp
{
	int          oper_flag            ; //������־    0����ѯ  1���޸�
	ArrayListMsg sms_content_set      ; //�˻����͡�֪ͨ����ģ��
}SmsParaRsp,*PSmsParaRsp;


//----------------------------------------------���Ľӿ� [3099] ����
// �ṹ����:�ͻ����ն���������
typedef struct tagCustRiskDegreeQueryReq
{
	int          oper_flag            ; //������־    0����ѯ 1���޸�
	string		 acct_no			  ; //�ͻ���  _VER_25_PSBC�汾�õ�
}CustRiskDegreeQueryReq,*PCustRiskDegreeQueryReq;


// �ṹ����:�ͻ����ն���Ӧ������
typedef struct tagCustRiskDegreeQueryRsq
{
	int          oper_flag            ; //������־    0����ѯ  1���޸�
	string       risk_degree          ; //���ն�1  Ϊ���ݽ��������ϰ汾�ͻ���
	string       risk_degree1          ; //���ն�1
	string       risk_degree2          ; //���ն�2
	string       risk_grade           ; //���յȼ�
	string		 risk_type           	;    //��������        
	string 		 debt_call_line       ;    //�ͻ�׷��������  
	string 		 debt_mem             ;    //�ͻ�׷����      
	string 		 debt_exch_rel        ;    //�ͻ����ǿƽ��  
	string 		 debt_exch_abs        ;    //�ͻ�����ǿƽ��  
	string 		 margin_mem           ;    //��Ա��֤��      
	string 		 margin_exch          ;    //��������֤��    
	string 		 debt_call            ;    //׷�����        
	string 		 surplus              ;    //����ӯ��        
	string 		 risk_curr_can_use   ;    //�����ʽ�        
	string 		 acct_type            ;    //�˻�����        
	string 		 f_in_out_bal         ;    //���ճ����      
	string 		 risk_type_yda        ;    //���շ�������    
	string 		 risk_deg_yda         ;    //���շ��յȼ�    
	string 		 debt_call_yda        ;    //����׷�����    
	string 		 risk_days            ;    //����������������

}CustRiskDegreeQueryRsq,*PCustRiskDegreeQueryRsq;
	///////////////////////////////////////////////////////////////////
//A2�ӿڱ���
//----------------------------------------------���Ľӿ� [3052] ����

// �ṹ����:ǿƽ����
typedef struct tagForceCovOder
{
	int          oper_flag            ; //������־    1��ǿƽ����
	string       client_serial_no     ; //�ͻ�����ˮ��    ǿƽ����
	string       acct_no              ; //�ͻ���    
	string       cust_id              ; //�ͻ�����    
	string       bank_no              ; //���п���    
	string       b_market_id          ; //�����г�    b_market_id
	string       prod_code            ; //��Լ����    
	string       offset_flag          ; //��ƽ��־    b_offset_flag
	string       deli_flag            ; //���ձ�־    b_deli_flag
	string       bs                   ; //���׷���    b_buyorsell
	string       entr_price           ; //ί�м۸�    
	int          entr_amount          ; //ί������    
	string       cov_type             ; //ƽ�ַ�ʽ    cov_type
	string       match_type           ; //�ɽ�����    b_match_type
	string       src_match_no         ; //��λ���    ָ��ƽ�ֵ�ԭ�ɽ����
	string       order_send_type      ; //�������ͷ�ʽ    order_send_type
}ForceCovOder,*PForceCovOder;


// �ṹ����:ǿƽ������Ӧ
typedef struct tagForceCovOderAck
{
	int          oper_flag            ; //������־    1��ǿƽ����
	string       client_serial_no     ; //�ͻ�����ˮ��    ǿƽ����		
	string       local_order_no       ; //���ر����� 
}ForceCovOderAck,*PForceCovOderAck;


	//----------------------------------------------���Ľӿ� [3053] ����

// �ṹ����:ǿƽ����
typedef struct tagForceCovOderCancel
{
	int          oper_flag            ; //������־    1��ǿƽ���� 
	string       cancel_order_no      ; //������������    
}ForceCovOderCancel,*PForceCovOderCancel;


// �ṹ����:ǿƽ������Ӧ
typedef struct tagForceCovOderCancelAck
{
	int          oper_flag            ; //������־    1��ǿƽ����
}ForceCovOderCancelAck,*PForceCovOderCancelAck;


	//�����ر�
typedef struct tagDeferRtnOrder
{
	string       client_serial_no;
	string       orderNo;				//������        (not null)
	string       clientID;				//�ͻ�����       (not null)
	string       instID;				//��Լ����       (not null)
	string       memberID;				//��Ա����       (not null)
	char         buyOrSell;				//��������       (not null)
	string       applyDate;				//�걨����
	string       applyTime;				//�걨ʱ��
	char         offSetFlag;			//��ƽ�ֱ�־      (not null)
	string       price;					//�۸�                       (not null)
	int          amount;				//����            (not null)
	int          remainAmount;			//ʣ������
	string       cancelTime;			//����ʱ��
	char         status;				//״̬
	string       localOrderNo;			//���ر�����          (not null)
	string       margin;				//��֤����
	char         marginType;			//��֤������           (not null)
	string       traderID;				//����Ա����          (not null)
	string       cancelID;				//����Ա����
	char         matchType;		
	string       acctNo               ; //�ͻ���    
} DeferRtnOrder,*PDeferRtnOrder;

////////////////////////////////////////////////////////////////////
// �ṹ����:�����������ͳ���嵥��ѯ������
typedef struct tagBranchRiskStatQryReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       branch_id            ; //�������    
}BranchRiskStatQryReq,*PBranchRiskStatQryReq;



// �ṹ����:�����������ͳ���嵥��ѯ������
typedef struct tagBranchRiskStatQryRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	ArrayListMsg       rtn_result            ; //ͳ�ƽ��  �ֶΣ����������š�����������ơ�׷ծ�ͻ��������ֿͻ�����ǿƽ�ͻ���������ǿƽ�ͻ�����׷���ͻ����������ͻ�����׷�������������ܸ���ӯ���������ʽ��ܡ���������֤�𡢻�Ա��֤���ܱ�֤���ܽ�������ܽ��ճ���    
}BranchRiskStatQryRsp,*PBranchRiskStatQryRsp;


//--------------------------------------------------------------���Ľӿ�[3307]���� ��ʼ add by liuwei 2012-8-16
//�ṹ���壺���������������ָ���ѯ������
typedef struct tagSubAgentRiskIndexQueryReq
{
	int          oper_flag            ; //������־    1����ѯ 
	string       branch_id            ; //�������룬Ϊ�����ѯ���������������
}SubAgentRiskIndexQueryReq, *PSubAgentRiskIndexQueryReq;

//�ṹ���壺���������������ָ���ѯ��Ӧ����
typedef struct tagSubAgentRiskIndexQueryRsp
{
	int          oper_flag            ; //������־    1����ѯ 
	ArrayListMsg alm_result           ; //��ѯ������ֶΣ��������룬�ܱ�֤���ܻ�Ա��֤���ܸ���ӯ�������ն�2����1�Ŀͻ��Ŀ����ʽ�
}SubAgentRiskIndexQueryRsp, *PSubAgentRiskIndexQueryRsp;
//--------------------------------------------------------------���Ľӿ�[3307]���� ���� add by liuwei 2012-8-16

//---------------------------------------------------------------���Ľӿ�[3308]���� ��ʼ add by liuwei 2012-8-16
//�ṹ���壺��������������ղ�������������
typedef struct tagSubAgentRiskParaSetReq
{
	int          oper_flag            ; //������־    0����ѯ��1���޸�
	ArrayListMsg query_condition      ; //��ѯ����    �ֶΣ��������룬��ֵ���ͣ���ֵ��ֵ����1��oper_flag=0�������ֻУ��������룬������ԣ���������Ϊ�����ѯ�����������������2��oper_flag=1����Ϊ�������4���ֶα������0��С��1����
}SubAgentRiskParaSetReq, *PSubAgentRiskParaSetReq;

//�ṹ���壺��������������ղ���������Ӧ����
typedef struct tagSubAgentRiskParaSetRsp
{
	int          oper_flag            ; //������־    0����ѯ��1���޸�
	ArrayListMsg alm_result           ; //��ѯ���    �ֶΣ��������룬�������ƣ���ֵ���ͣ���ֵ��ֵ��
}SubAgentRiskParaSetRsp, *PSubAgentRiskParaSetRsp;
//---------------------------------------------------------------���Ľӿ�[3308]���� ���� add by liuwei 2012-8-16

//--------------------------------------------------���Ľӿ� [3309] ���� ��ʼ add by liuwei 2012-9-4
// �ṹ����:���������Զ�ǿƽ������
typedef struct tagAutoGenFCOrderBatchReq
{
	int          oper_flag            ; //������־ 1����ѯ
	ArrayListMsg gen_condition        ; //�������� �ֶΣ��ͻ��š����κš����յȼ�
	string       fc_mode              ; //ǿƽ��ʽ 1�м� 2�޼� 3ͣ��� 4 ָ���۸�
	string       teller_id            ; //���Ա 
	ArrayListMsg posi_result          ; //��Լ���������򡢼۸�����
	ArrayListMsg cov_price_info		  ;//ƽ�ּ۸���Ϣ    ��Լ���롢��ƽ�ּ۸񡢿ղ�ƽ�ּ۸�
	char         risk_target          ; // ǿƽĿ�꣬0��������1��׷����2�����ǿƽ
}AutoGenFCOrderBatchReq,*PAutoGenFCOrderBatchReq;


// �ṹ����:���������Զ�ǿƽ����Ӧ
typedef struct tagAutoGenFCOrdeBatchrRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg alm_result           ; //���ɽ��    �ֶ�˳�򣺿ͻ��š�ǿƽ���š���Լ���������򡢼۸����������κš�rsp_msg
}AutoGenFCOrderBatchRsp,*PAutoGenFCOrderBatchRsp;
//--------------------------------------------------���Ľӿ� [3309] ���� ���� add by liuwei 2012-9-4

//--------------------------------------------------���Ľӿ� [3310] ���� ��ʼ add by liuwei 2012-9-4
// �ṹ����:��������ǿƽ������
typedef struct tagFCOrderSubmitBatchReq
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg force_order          ; //ǿƽ������ �ֶΣ����ɱ�־���ͻ��š����ڡ�������š���Լ���롢��������ί�м۸�ί�����������κš�ǿƽ���š����Ա
}FCOrderSubmitBatchReq,*PFCOrderSubmitBatchReq;


// �ṹ����:��������ǿƽ��������Ӧ
typedef struct tagFCOrderSubmitBatchRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg alm_result           ; //������ �ֶΣ��ͻ��š�������š�ǿƽ���š����ر�����ǿƽ��״̬��rsp_msg
}FCOrderSubmitBatchRsp,*PFCOrderSubmitBatchRsp;
//--------------------------------------------------���Ľӿ� [3310] ���� ���� add by liuwei 2012-9-4

//----------------------------------------------���Ľӿ� [3312] ����

// �ṹ����:���������������壬֧�ַ�ҳ
typedef struct tagInOutCustListReq
{
	int          oper_flag            ; //������־    0����ѯ 
	string       branch_id            ; //�����̺�    
	ArrayListMsg instid               ; //��Լ    ��Լ���롢��Լ�۸񡢵�����֤����
	int          page_no              ; //ҳ��
	int          page_size            ; //ҳ��С
	int          total_record         ; //���ϼ�¼������
}InOutCustListReq,*PInOutCustListReq;


// �ṹ����:�ڲ���ת����/���˵���Ӧ������
typedef struct tagInOutCustListRsp
{
	int          oper_flag            ; //������־    0����ѯ 
	ArrayListMsg cal_result           ; //������    �ֶ�˳�򣺿ͻ��ţ��ͻ���ƣ�������򣬳�����������������ˮ�ţ�Ԥ����ն�1��Ԥ����ն�2��Ԥ����յȼ��������ʽ�Ԥ���Ա��֤��Ԥ�⽻������֤��Ԥ���ܱ�֤��Ԥ�⸡��ӯ����Ԥ��׷���������̱�ţ�����������ƣ�������������
}InOutCustListRsp,*PInOutCustListRsp;

// �ṹ����:����ͳһ������
typedef struct tagRiskCustQueryReqByTrade
{
	int          oper_flag            ; //������־    0����ѯ 
	string       branch_id            ; //�����̱�� 
	string		 acct_type			  ; //�˻�����
	string		 cust_type			  ; //�ͻ�����
	string		 account_no			  ; //�����˺�
	string       acct_no              ; //�ͻ���    
	string       risk_grade_id        ; //���յȼ�    
}RiskCustQueryReqByTrade,*PRiskCustQueryReqByTrade;


// �ṹ����:����ͳһ������
typedef struct tagRiskCustQueryRspByTrade
{
	int          oper_flag            ; //������־    0����ѯ 
	HashtableMsg alm_result           ; //��ѯ���    �ֶΣ��ͻ��� �ͻ���� �ͻ����� �˻����� ���ն�1 ���ն�2  ���յȼ� �����ʽ� ��Ա��֤�� ��������֤�� �ܱ�֤�� ����ӯ�� ׷����� �����̱�� ���������� �ͻ��ֻ��� +�����˺�
}RiskCustQueryRspByTrade,*PRiskCustQueryRspByTrade;

#endif