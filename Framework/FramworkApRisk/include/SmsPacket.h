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
typedef struct tagSmsHead   //������ͷ
{

	char len[LEN+1];   //���ĳ���,���������ֶεĳ���
    char seq[SEQ+1];    //���ݰ����к�
	char pkg_type[PKGTYPE+1];  //��������
	char pkg_src[PKGSRC+1];  //������Դ
	char tran_code[TRANCODE+1]; //���״���
	char priority[PRIORITY+1];  //���ȼ�
	char tran_date[TRADATE+1]; //���ŷ������� yymmdd
	char tran_time[TRATIME+1]; //���ŷ���ʱ�� HHNNSSmmm
	char ra_flag[RAFLAG+1];   //����/Ӧ���ʶ R-���� A-Ӧ��
	char enc_flag[ENCFLAG+1];   //���ܱ�־ Y-���� ����-������
	char totals[TOTALS+1]; //���ļ�¼�� ����ʱ����1�����ʱ�����ܰ���
	char rec_no[RECNO+1];  //��ǰ����� ����ʱ����1�����ʱ����ʵ�ʵİ���
	char fields[FIELDS+1];  //������е��ֶ���
	char succ_flag[SUCCFLAG+1];   //Ӧ��ʱ�������1��-�ɹ�������-ʧ�ܡ�ʧ��ԭ���ڷ��ذ���������
	char reserved[RESERVED+1];  //����

} SMS_HEADER,*PSMS_HEADER;
//�����ֶ�
typedef struct tagSmsField   
{
	char fid[FID+1];   //�ֶ����
    char flen[FLEN+1];    //�ֶγ�
	char fdata[DATALEN];  //��������

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
	string m_sEncode;		//�������ַ���
};

#endif