
#ifndef _MSG_DEF_H_
#define _MSG_DEF_H_
/**
 * ��Ϣ���ֶζ���
 * 
 * ��Ź���
 *  - 16λ������ʾ��ͬ��Ϣ�ֶ�
 *  - �����ֶδ�0x0001��ʼ��ţ��궨���ڱ�ͷ�ļ���
 *  - ˽���ֶδ�0x1000��ʼ��ţ�ÿ����Ŷΰ���0x0400����ţ��궨�岻�����ڱ�ͷ�ļ���
 *  - ˽���ֶεı�Ŷη������Ԥ���ڱ��ļ���ĩβ��ע
 */

/*
 * ��������ϢЭ��ʹ�õĹ����ֶ�
 */
#define MSG_PKG_LENGTH	(int)0x00000140	// ��Ϣ������
#define MSG_CMD_ID		(int)0x00000141	// ��Ϣָ�����ͣ���CommandID
#define MSG_SEQ_ID		(int)0x00000142	// ��Ϣ�����к�
#define MSG_BODY_LEN	(int)0x00000143	// ��Ϣ��MSG_BODY�ĳ���
#define MSG_NODE_ID 	(int)0x00000144	// �ڵ�ID


#endif // _MSG_DEF_H_
