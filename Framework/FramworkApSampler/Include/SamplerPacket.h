#ifndef _SAMPLER_PACKET_H
#define _SAMPLER_PACKET_H
#include "CommApSampler.h"
#include "MsgBlock.h"
#include "MsgDef.h"
#include "SamplerMsgDef.h"
#include "strutils.h"

using namespace strutils;

//
typedef struct tagSamplerPktHead   //����ͷ
{
	unsigned int uiLen;
	unsigned int uiCmdID;
	unsigned int uiSeqID;
	unsigned int uiNodeID;
} SAMPLER_PKT_HEADER,*PSAMPLER_PKT_HEADER;

typedef struct tagCodeInfo
{
	//unsigned short m_usMarketType;
	unsigned int m_usMarketType;
	char           m_acCode[8];
}CODE_INFO,*PCODE_INFO;

typedef struct	tagBidAskUnit
{ 
	tagBidAskUnit()
	{
		m_uiVol = 0;
		m_uiPrice = 0;
	}
	unsigned int m_uiVol;		//ί��
	unsigned int m_uiPrice;	    //ί��
} BID_ASK_UNIT,*PBID_ASK_UNIT;

typedef struct tagQuotation
{
	CODE_INFO m_CodeInfo;		//��Լ��Ϣ[8]

	unsigned int m_uiSeqNo;     //����
	unsigned int m_uiDate;
	unsigned int m_uiTime; 
	unsigned int m_uilastClose; //����
	unsigned int m_uiLastSettle;//���
	unsigned int m_uiSettle;    //����
	unsigned int m_uiOpenPrice; //����
	unsigned int m_uiHigh;      //��߼�
	unsigned int m_uiLow;       //��ͼ�
	unsigned int m_uiClose;     //���̼�
	unsigned int m_uiHighLimit;
	unsigned int m_uiLowLimit;	
	unsigned int m_uiLast;      //���¼�
	unsigned int m_uiAverage;   //����
	unsigned int m_uiVolume;    //�ɽ���
	unsigned int m_uiWeight;    //�ɽ�����
	unsigned int m_uiTurnOver;  //�ɽ����
	unsigned int m_uiChiCangLiang;//�ֲ���
	unsigned int m_uiLastChiCangLiang;//���ճֲ���
	BID_ASK_UNIT     m_Bid[5];
	BID_ASK_UNIT     m_Ask[5];
} QUOTATION,*PQUOTATION;

#define QUOTATION_REC_SIZE sizeof(QUOTATION) //128

class COMMAPSAMPLER_CLASS CSamplerPacket : public CMsgBlock, public CPacketRouteable
{
public:
	CSamplerPacket();
	CSamplerPacket(unsigned long uiCmdID);
	CSamplerPacket(CMessage& msg, unsigned long uiCmdID = 0xFFFFFFFF);
	virtual ~CSamplerPacket(void);

	const string& GetCmdID();
	std::string RouteKey();

	void  Decode(const char * pData, unsigned int nLength);
	const char* Encode(unsigned int & usLen);
private:
	string m_sCmdID;

public:

	// ������Ϣ�����뺯��
	BEGIN_PKG_DECODE(4, 4)
		PKG_DECODE_HANDLE(YL_LOGIN, Login)
		PKG_DECODE_HANDLE(YL_LOGIN_RSP, LoginRsp)
		PKG_DECODE_HANDLE(YL_SUBSCRIP, Subscrip)
		PKG_DECODE_HANDLE(YL_SUBSCRIP_RSP, SubscripRsp)
		PKG_DECODE_HANDLE(YL_HELLO, Hello)
		PKG_DECODE_HANDLE(YL_HELLO_RSP, HelloRsp)
		PKG_DECODE_HANDLE(YL_QUOTATION, Quotation)
	END_PKG_DECODE()

	// ������Ϣ�����뺯��
	BEGIN_PKG_ENCODE
		PKG_ENCODE_HANDLE(YL_LOGIN, Login)
		PKG_ENCODE_HANDLE(YL_LOGIN_RSP, LoginRsp)
		PKG_ENCODE_HANDLE(YL_SUBSCRIP, Subscrip)
		PKG_ENCODE_HANDLE(YL_SUBSCRIP_RSP, SubscripRsp)
		PKG_ENCODE_HANDLE(YL_HELLO, Hello)
		PKG_ENCODE_HANDLE(YL_HELLO_RSP, HelloRsp)
		PKG_ENCODE_HANDLE(YL_QUOTATION, Quotation)
	END_PKG_ENCODE()

	// ����ÿ��ͨ��ԭ��
	// Header  
#define SAMP_HEADER() \
		FIELD_INT32(MSG_PKG_LENGTH) \
		FIELD_INT32(MSG_CMD_ID) \
		FIELD_INT32(MSG_SEQ_ID) \
		FIELD_INT32(MSG_NODE_ID)

	// Login  
	BEGIN_PKG_FIELD(Login)
		SAMP_HEADER()
		FIELD_OCTSTR(MSG_LOGIN_ID, 20)
		FIELD_OCTSTR(MSG_LOGIN_PWD, 20)
		FIELD_INT32(MSG_LOGIN_PWD_ENC)
	END_PKG_FIELD()

    //Login  Rsp
	BEGIN_PKG_FIELD(LoginRsp)
		SAMP_HEADER()
		FIELD_INT32(MSG_LOGIN_RESULT)
	END_PKG_FIELD()

    // Subscrip
	BEGIN_PKG_FIELD(Subscrip)
		SAMP_HEADER()
	END_PKG_FIELD()

    // SubscripRsp
	BEGIN_PKG_FIELD(SubscripRsp)
		SAMP_HEADER()
		FIELD_INT32(MSG_SUBSCRIP_RESULT)
	END_PKG_FIELD()

	// Hello
	BEGIN_PKG_FIELD(Hello)
		SAMP_HEADER()
	END_PKG_FIELD()

    // HelloRsp
	BEGIN_PKG_FIELD(HelloRsp)
		SAMP_HEADER()
	END_PKG_FIELD()


	// Quotaion
	BEGIN_PKG_FIELD(Quotation)
		SAMP_HEADER()
		FIELD_REC16(MSG_QUOTATION_RECS,QUOTATION_REC_SIZE);
	END_PKG_FIELD()
};

#endif