
#ifndef _SAMPLER_MSG_DEF_H_
#define _SAMPLER_MSG_DEF_H_
/**
 * 消息体字段定义
 * 
 * 编号规则
 *  - 16位整数表示不同消息字段
 *  - 公共字段从0x0001开始编号，宏定义在本头文件中
 *  - 私有字段从0x1000开始编号，每个编号段包含0x0400个编号，宏定义不包含在本头文件中
 *  - 私有字段的编号段分配必须预先在本文件的末尾标注
 */

/*
 * 定长块消息协议使用的私有字段
 */
#define MSG_LOGIN_ID 		(int)0x00001000	// 登录ID
#define MSG_LOGIN_PWD		(int)0x00001001	// 登录密码
#define MSG_LOGIN_PWD_ENC	(int)0x00001002	// 密码加密方式
#define MSG_LOGIN_RESULT	(int)0x00001003	// 登录结果
#define MSG_SUBSCRIP_RESULT	(int)0x00001004	// 登录结果
//#define MSG_QUOTATION_NUM	(unsigned short)0x1005	// 行情记录数
#define MSG_QUOTATION_RECS	(int)0x1006	// 行情记录


#define YL_LOGIN				(unsigned long)0x00000001
#define YL_LOGIN_RSP			(unsigned long)0x80000001
#define YL_SUBSCRIP				(unsigned long)0x00000002
#define	YL_SUBSCRIP_RSP			(unsigned long)0x80000002
#define YL_HELLO				(unsigned long)0x00000003
#define	YL_HELLO_RSP			(unsigned long)0x80000003

#define	YL_QUOTATION			(unsigned long)0x00000004
#endif // _MSG_DEF_H_
