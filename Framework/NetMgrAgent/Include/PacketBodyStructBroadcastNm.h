#ifndef _PACKET_BODY_STRUCT_BROADCAST_NMAGENT_H
#define _PACKET_BODY_STRUCT_BROADCAST_NMAGENT_H
#include <string>
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

namespace nmagent
{
//----------------------------------------------���Ľӿ� [onEventNotify] ����

// �ṹ����:onEventNotify
typedef struct tagEventNotify
{
	int          oper_flag            ; //������־    1���㲥
	string       date_time            ; //����ʱ��    
	int          grade                ; //��Ҫ�ȼ�    0һ���¼�1��Ҫ�¼�
	int          evt_type             ; //�¼�����    0 ���¼� 2 track�¼�
	int          evt_category         ; //�¼����    ����
	string       evt_content          ; //�¼�����    
	int          host_id              ; //����id    
	int          node_id              ; //�ڵ�id    
	string       actor_id             ; //����Աid    
}EventNotify,*PEventNotify;



//----------------------------------------------���Ľӿ� [onAlarmNotify] ����

// �ṹ����:onAlarmNotify
typedef struct tagAlarmNotify
{
	int          oper_flag            ; //������־    1���㲥
	unsigned int          seq_no               ; //��ˮ��    
	string       active_time          ; //����ʱ��    
	int          alm_grade_to         ; //�澯����    
	int          alm_grade_from       ; //�澯����    
	string       trigger_val          ; //����ֵ    
	string       alm_content          ; //�澯����    
	string       inactive_time        ; //����ʱ��    
	int          ack_required         ; //�Ƿ���ȷ��    
	string       ack_actor_id         ; //ȷ����id    
	int          host_id              ; //����id    
	int          node_id              ; //�ڵ�id    
	string       oid                  ; //�����id    
	string       oid_ins                  ; //�����ʵ��id    
}AlarmNotify,*PAlarmNotify;


//----------------------------------------------���Ľӿ� [onNodeMibTblChg] ����

// �ṹ����:onNodeMibTblChg
typedef struct tagNodeMibTblChg
{
	int          oper_flag            ; //������־ 1�����Ӽ�¼ 2��ɾ����¼
	string       rec_oid              ; //��¼��֧OID
	string		 rec_key              ; //��¼KEY 
	int          host_id              ; //����id    
	int          node_id              ; //�ڵ�id	   
}NodeMibTblChg,*PNodeMibTblChg;

}

#endif
