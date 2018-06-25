#ifndef _PACKET_BODY_STRUCT_TRADE_NMAGENT_H
#define _PACKET_BODY_STRUCT_TRADE_NMAGENT_H
#include <string>
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

namespace nmagent
{
//----------------------------------------------���Ľӿ� [1921] ����

// �ṹ����:��ѯ��������ÿռ�����
typedef struct tagQueryItemCfgReq
{
	int             oper_flag            ; //������־    1����ѯ
	string          host_id              ; //����id    
	string          node_id              ; //�ڵ�id    
}QueryItemCfgReq,*PQueryItemCfgReq;


// �ṹ����:��ѯ��������ÿռ�Ӧ��
typedef struct tagQueryItemCfgRsp
{
	int				oper_flag            ; //������־    1����ѯ
	string          host_id              ; //����id    
	string          node_id              ; //�ڵ�id    
	ArrayListMsg result               ; //��ѯ���    �����oid
}QueryItemCfgRsp,*PQueryItemCfgRsp;



//----------------------------------------------���Ľӿ� [1922] ����

// �ṹ����:��ѯ���������
typedef struct tagQueryItemReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       host_id              ; //����id    
	string       node_id              ; //�ڵ�id    
	string       rw_flag              ; //��д��ʶ    
	string       item_type            ; //���������    
	string       item_oid             ; //�����id    
}QueryItemReq,*PQueryItemReq;


// �ṹ����:��ѯ�����Ӧ��
typedef struct tagQueryItemRsp
{
	int             oper_flag            ; //������־    1����ѯ
	string          host_id              ; //����id    
	string          node_id              ; //�ڵ�id    
	ArrayListMsg result               ; //��ѯ���    �����oid,��ǰֵ,��������,ʱ���,�澯״̬
}QueryItemRsp,*PQueryItemRsp;



//----------------------------------------------���Ľӿ� [1923] ����

// �ṹ����:��ѯ�澯����
typedef struct tagAlmQueryReq
{
	int             oper_flag            ; //������־    1����ѯ
	string          host_id              ; //����id    
	string          node_id              ; //�ڵ�id    
	string          item_oid             ; //�����id    
}AlmQueryReq,*PAlmQueryReq;


// �ṹ����:��ѯ�澯Ӧ��
typedef struct tagAlmQueryRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg result               ; //��ѯ���    ����id���ڵ�id�������oid, ��ˮ�ţ�����ʱ�䣬�澯���𣬴���ֵ���澯���ݣ�����ʱ�䣬�Ƿ���ȷ�ϣ�ȷ����id
}AlmQueryRsp,*PAlmQueryRsp;



//----------------------------------------------���Ľӿ� [1924] ����

// �ṹ����:��ѯ�¼�����
typedef struct tagEvtQueryReq
{
	int             oper_flag            ; //������־    1����ѯ
	string          host_id              ; //����id    
	string          node_id              ; //�ڵ�id    
}EvtQueryReq,*PEvtQueryReq;


// �ṹ����:��ѯ�¼�Ӧ��
typedef struct tagEvtQueryRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg result               ; //��ѯ���    ����id���ڵ�id������ʱ�䣬��Ҫ�ȼ����¼����ͣ��¼�����¼����ݣ�����Աid
}EvtQueryRsp,*PEvtQueryRsp;



//----------------------------------------------���Ľӿ� [1925] ����

// �ṹ����:������������
typedef struct tagItemControlReq
{
	int          oper_flag            ; //������־    1������
	string          host_id              ; //����id    
	string          node_id              ; //�ڵ�id    
	string       item_oid             ; //�����id    
	string       dst_val              ; //Ŀ��ֵ    
}ItemControlReq,*PItemControlReq;


// �ṹ����:��������Ӧ��
typedef struct tagItemControlRsp
{
	int          oper_flag            ; //������־    1������
}ItemControlRsp,*PItemControlRsp;


///////////////////////////////////////////////////////////////////
//----------------------------------------------���Ľӿ� [1911] ����

// �ṹ����:����������Ϣ��ѯ����
typedef struct tagHostCfgReq
{
	int          oper_flag            ; //������־    1����ѯ
	string          host_id              ; //����id    
}HostCfgReq,*PHostCfgReq;


// �ṹ����:����������Ϣ��ѯ��Ӧ
typedef struct tagHostCfgRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg host_cfg             ; //������Ϣ    ����ID,��������,����IP,����ϵͳ����,����ϵͳ�汾,λ��
}HostCfgRsp,*PHostCfgRsp;



//----------------------------------------------���Ľӿ� [1912] ����

// �ṹ����:�ڵ�������Ϣ��ѯ����
typedef struct tagNodeCfgReq
{
	int          oper_flag            ; //������־    1����ѯ
	string          host_id              ; //����id    
	string          node_id              ; //�ڵ�id    
}NodeCfgReq,*PNodeCfgReq;


// �ṹ����:�ڵ�������Ϣ��ѯӦ��
typedef struct tagNodeCfgRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg node_cfg             ; //�ڵ���Ϣ    ����ID,�ڵ�ID,�ڵ�����,�ڵ����ͣ��ڵ����ԣ����������˿�, ���������˿�,��������ID
}NodeCfgRsp,*PNodeCfgRsp;



//----------------------------------------------���Ľӿ� [1913] ����

// �ṹ����:MIB������Ϣ��ѯ����
typedef struct tagMibCfgReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       oid                  ; //mib�����ʶ    
}MibCfgReq,*PMibCfgReq;


// �ṹ����:MIB������Ϣ��ѯӦ��
typedef struct tagMibCfgRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg mib_cfg              ; //MIB��Ϣ    ������ʶ, ��ʶ���������������, �����ڵ�����, �����ڵ�, ��֧����
}MibCfgRsp,*PMibCfgRsp;



//----------------------------------------------���Ľӿ� [1914] ����

// �ṹ����:�����MIB������Ϣ��ѯ����
typedef struct tagItemMibCfgReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       oid                  ; //mib�����ʶ    
}ItemMibCfgReq,*PItemMibCfgReq;


// �ṹ����:�����MIB������Ϣ��ѯӦ��
typedef struct tagItemMibCfgRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg mib_cfg              ; //�������Ϣ    ������ʶ, ��д��־, ���������, ����
}ItemMibCfgRsp,*PItemMibCfgRsp;



//----------------------------------------------���Ľӿ� [1915] ����

// �ṹ����:ģ���ͼ����������Ϣ��ѯ����
typedef struct tagItemAnalogCfgReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       oid                  ; //mib�����ʶ    
}ItemAnalogCfgReq,*PItemAnalogCfgReq;


// �ṹ����:ģ���ͼ����������Ϣ��ѯӦ��
typedef struct tagItemAnalogCfgRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg item_cfg             ; //�������Ϣ    ������ʶ, ��Сֵ, ���ֵ, ���ȣ���λ����ֵ����ʱ���
}ItemAnalogCfgRsp,*PItemAnalogCfgRsp;



//----------------------------------------------���Ľӿ� [1916] ����

// �ṹ����:�����ͼ����������Ϣ��ѯ����
typedef struct tagItemDigitalCfgReq
{
	int          oper_flag            ; //������־    1����ѯ
	string       oid                  ; //mib�����ʶ    
}ItemDigitalCfgReq,*PItemDigitalCfgReq;


// �ṹ����:�����ͼ����������Ϣ��ѯӦ��
typedef struct tagItemDigitalCfgRsp
{
	int          oper_flag            ; //������־    1����ѯ
	ArrayListMsg item_cfg             ; //�������Ϣ    ������ʶ, ״ֵ̬������
}ItemDigitalCfgRsp,*PItemDigitalCfgRsp;

}
	

#endif
