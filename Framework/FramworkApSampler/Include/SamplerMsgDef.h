
#ifndef _SAMPLER_MSG_DEF_H_
#define _SAMPLER_MSG_DEF_H_
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
 * ��������ϢЭ��ʹ�õ�˽���ֶ�
 */
#define MSG_LOGIN_ID 		(int)0x00001000	// ��¼ID
#define MSG_LOGIN_PWD		(int)0x00001001	// ��¼����
#define MSG_LOGIN_PWD_ENC	(int)0x00001002	// ������ܷ�ʽ
#define MSG_LOGIN_RESULT	(int)0x00001003	// ��¼���
#define MSG_SUBSCRIP_RESULT	(int)0x00001004	// ��¼���
//#define MSG_QUOTATION_NUM	(unsigned short)0x1005	// �����¼��
#define MSG_QUOTATION_RECS	(int)0x1006	// �����¼


#define YL_LOGIN				(unsigned long)0x00000001
#define YL_LOGIN_RSP			(unsigned long)0x80000001
#define YL_SUBSCRIP				(unsigned long)0x00000002
#define	YL_SUBSCRIP_RSP			(unsigned long)0x80000002
#define YL_HELLO				(unsigned long)0x00000003
#define	YL_HELLO_RSP			(unsigned long)0x80000003

#define	YL_QUOTATION			(unsigned long)0x00000004
#endif // _MSG_DEF_H_
