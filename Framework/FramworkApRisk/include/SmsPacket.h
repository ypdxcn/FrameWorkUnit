#ifndef _SMS_PACKET_H
#define _SMS_PACKET_H

#include "Gess.h"
#include "CommApRisk.h"
#include "PairPacket.h"
#include "strutils.h"
#include "ArrayListMsg.h"
using namespace strutils;


#define LEN 		         6U
#define SEQ                 10U
#define PKGTYPE              1U
#define PKGSRC               2U
#define TRANCODE             6U
#define PRIORITY             1U
#define TRADATE              6U
#define TRATIME              9U
#define RAFLAG               1U
#define ENCFLAG              1U
#define TOTALS               6U
#define RECNO                6U
#define FIELDS               2U
#define SUCCFLAG             1U
#define RESERVED             6U

#define FID                  2U
#define FLEN                 4U
#define DATALEN           1024U

#define SMS_PACKET_LEN		LEN
typedef struct tagSmsHead   //请求报文头
{

	char len[LEN+1];   //报文长度,不包含本字段的长度
    char seq[SEQ+1];    //数据包序列号
	char pkg_type[PKGTYPE+1];  //报文类型
	char pkg_src[PKGSRC+1];  //报文来源
	char tran_code[TRANCODE+1]; //交易代码
	char priority[PRIORITY+1];  //优先级
	char tran_date[TRADATE+1]; //短信发送日期 yymmdd
	char tran_time[TRATIME+1]; //短信发送时间 HHNNSSmmm
	char ra_flag[RAFLAG+1];   //请求/应答标识 R-请求 A-应答
	char enc_flag[ENCFLAG+1];   //加密标志 Y-加密 其它-不加密
	char totals[TOTALS+1]; //包的记录数 单包时，填1。多包时，填总包数
	char rec_no[RECNO+1];  //当前包序号 单包时，填1。多包时，填实际的包号
	char fields[FIELDS+1];  //填报文体中的字段数
	char succ_flag[SUCCFLAG+1];   //应答时，必填。‘1’-成功；其它-失败。失败原因将在返回包中描述。
	char reserved[RESERVED+1];  //保留

} SMS_HEADER,*PSMS_HEADER;
//报文字段
typedef struct tagSmsField   
{
	char fid[FID+1];   //字段序号
    char flen[FLEN+1];    //字段长
	char fdata[DATALEN];  //报文类型

} SmsField,*PSmsField;


class COMMAPRISK_CLASS  CSmsPacket:public CPacket
{
public:
	 CSmsPacket();
	~CSmsPacket();

	void  Decode(const char * pData, unsigned int nLength);
	const char* Encode(unsigned int & usLen);
	const string & GetCmdID();
	void SetHeader(SMS_HEADER & header);
	void AddField(SmsField & field);
	void  GetHeader(SMS_HEADER & header);
	string  GetFiledByFid(string & fid);
	void  GetFields(ArrayListMsg & fields);
private:
	ArrayListMsg m_fields;	
	SMS_HEADER m_header;
	string m_sCmdID;
	string m_sEncode;		//编码后的字符串
};

#endif