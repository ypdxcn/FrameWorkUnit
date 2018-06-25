#include "SmsPacket.h"

CSmsPacket::CSmsPacket():m_sCmdID("")
{}

CSmsPacket::~CSmsPacket(){}

const string & CSmsPacket::GetCmdID()
{
	return m_sCmdID;
}
/************************************************************************
解码收到的报文
************************************************************************/
void CSmsPacket::Decode(const char *pData, unsigned int nLength)
{
	memset(m_header.seq,0x00,sizeof(m_header.seq));

	memset(m_header.pkg_type,0x00,sizeof(m_header.pkg_type));

	memset(m_header.pkg_src,0x00,sizeof(m_header.pkg_src));

	memset(m_header.tran_code,0x00,sizeof(m_header.tran_code));

	memset(m_header.priority,0x00,sizeof(m_header.priority));
	
	memset(m_header.tran_date,0x00,sizeof(m_header.tran_date));

	memset(m_header.tran_time,0x00,sizeof(m_header.tran_time));

	memset(m_header.ra_flag,0x00,sizeof(m_header.ra_flag));

	memset(m_header.enc_flag,0x00,sizeof(m_header.enc_flag));

	memset(m_header.totals,0x00,sizeof(m_header.totals));

	memset(m_header.rec_no,0x00,sizeof(m_header.rec_no));

	memset(m_header.succ_flag,0x00,sizeof(m_header.succ_flag));
	memset(m_header.reserved,0x00,sizeof(m_header.reserved));

	const char* pPos = pData;

	//报文长度,不包含本字段的长度
	memcpy(m_header.len,pPos,LEN); 
	pPos+=LEN;
	
	//数据包序列号
	memcpy(m_header.seq,pPos,SEQ); 
	pPos+=SEQ;
	
	//报文类型
	memcpy(m_header.pkg_type,pPos,PKGTYPE); 
	pPos+=PKGTYPE;

	//报文来源
	memcpy(m_header.pkg_src,pPos,PKGSRC); 
	pPos+=PKGSRC;

	//交易代码
	memcpy(m_header.tran_code,pPos,TRANCODE); 
	pPos+=TRANCODE;

	//优先级
	memcpy(m_header.priority,pPos,PRIORITY); 
	pPos+=PRIORITY;

	//短信发送日期 yymmdd
	memcpy(m_header.tran_date,pPos,TRADATE); 
	pPos+=TRADATE;

	//短信发送时间 HHNNSSmmm
	memcpy(m_header.tran_time,pPos,TRATIME); 
	pPos+=TRATIME;

	//请求/应答标识 R-请求 A-应答
	memcpy(m_header.ra_flag,pPos,RAFLAG); 
	pPos+=RAFLAG;

	//加密标志 Y-加密 其它-不加密
	memcpy(m_header.enc_flag,pPos,ENCFLAG); 
	pPos+=ENCFLAG;

	//包的记录数 单包时，填1。多包时，填总包数
	memcpy(m_header.totals,pPos,TOTALS); 
	pPos+=TOTALS;

	//当前包序号 单包时，填1。多包时，填实际的包号
	memcpy(m_header.rec_no,pPos,RECNO); 
	pPos+=RECNO;

	//填报文体中的字段数
	memcpy(m_header.fields,pPos,FIELDS); 
	pPos+=FIELDS;

	//应答时，必填。‘1’-成功；其它-失败。失败原因将在返回包中描述。
	memcpy(m_header.succ_flag,pPos,SUCCFLAG); 
	pPos+=SUCCFLAG;

	//保留
	memcpy(m_header.reserved,pPos,RESERVED); 
	pPos+=RESERVED;

	int n=atoi(m_header.fields);

	m_fields.clear();
	for(int i=0;i<n;i++)
	{
		SmsField temp;
		memset(temp.fid,0x00,sizeof(temp.fid));
		memset(temp.fdata,0x00,sizeof(temp.fdata));
		memset(temp.flen,0x00,sizeof(temp.flen));

		//字段序号
		memcpy(temp.fid,pPos,FID); 
		pPos+=FID;
		
		//字段长度
		memcpy(temp.flen,pPos,FLEN); 
		pPos+=FLEN;
		
		int flen=atoi(temp.flen);
		//字段长度
		memcpy(temp.fdata,pPos,flen); 
		pPos+=flen;

		ArrayListMsg msg;
		msg.AddValue(temp.fid);
		msg.AddValue(temp.flen);
		msg.AddValue(temp.fdata);
		m_fields.AddValue(msg);

	}

}
/************************************************************************
报文发送前从结构体转化为字节流
************************************************************************/
const char* CSmsPacket::Encode(unsigned int &usLen)
{
	char temp[128];
	char code[1024];
	m_sEncode="";	

	//数据包序列号
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',SEQ);
	sprintf(code,temp,m_header.seq);  
	m_sEncode+=code;

	//报文类型
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',PKGTYPE);
	sprintf(code,temp,m_header.pkg_type);  
	m_sEncode+=code;

	//报文来源
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',PKGSRC);
	sprintf(code,temp,m_header.pkg_src);  
	m_sEncode+=code;

	//交易代码
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TRANCODE);
	sprintf(code,temp,m_header.tran_code);  
	m_sEncode+=code;

	//优先级
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',PRIORITY);
	sprintf(code,temp,m_header.priority);  
	m_sEncode+=code;

	//短信发送日期 yymmdd
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TRADATE);
	sprintf(code,temp,m_header.tran_date);  
	m_sEncode+=code;

	//短信发送时间 HHNNSSmmm
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TRATIME);
	sprintf(code,temp,m_header.tran_time);  
	m_sEncode+=code;

	//请求/应答标识 R-请求 A-应答
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',RAFLAG);
	sprintf(code,temp,m_header.ra_flag);  
	m_sEncode+=code;

	//加密标志 Y-加密 其它-不加密
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',ENCFLAG);
	sprintf(code,temp,m_header.enc_flag);  
	m_sEncode+=code;

	//包的记录数 单包时，填1。多包时，填总包数
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TOTALS);
	sprintf(code,temp,m_header.totals);  
	m_sEncode+=code;

	//当前包序号 单包时，填1。多包时，填实际的包号
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',RECNO);
	sprintf(code,temp,m_header.rec_no);  
	m_sEncode+=code;

	//填报文体中的字段数
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%dd",'%',FIELDS);
	sprintf(code,temp,m_fields.size());  
	m_sEncode+=code;

	//应答时，必填。‘1’-成功；其它-失败。失败原因将在返回包中描述。
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',SUCCFLAG);
	sprintf(code,temp,m_header.succ_flag);  
	m_sEncode+=code;

	//保留
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',RESERVED);
	sprintf(code,temp,m_header.reserved);  
	m_sEncode+=code;
	
	//添加字段
	for (size_t i=0;i< m_fields.size();i++)
	{
		
		//字段序号
		memset(temp,0x00,sizeof(temp));
		memset(code,0x00,sizeof(code));
		sprintf(temp,"%c%ds",'%',FID);

		ArrayListMsg aMsg = m_fields.GetValue(i);
		string s=aMsg.GetValue<string>(0);
		sprintf(code,temp,s.c_str());  
		m_sEncode+=code;

		//字段长度
		memset(temp,0x00,sizeof(temp));
		memset(code,0x00,sizeof(code));
		sprintf(temp,"%c%ds",'%',FLEN);
		s=aMsg.GetValue<string>(1);
		sprintf(code,temp,s.c_str());  
		m_sEncode+=code;

		//字段内容
		memset(code,0x00,sizeof(code));
		s=aMsg.GetValue<string>(2);
		sprintf(code,"%s",s.c_str()); 
		m_sEncode+=code;
	}
	
	//_itoa(m_sEncode.length(),m_header.len,10);
	int length=0;
	for(int i=0;i<(int)m_sEncode.length();i++)
	{
		if(m_sEncode.at(i)>128)
		{
			i++;
		}
		length++;
	}
	
	memset(m_header.len,0x00,sizeof(m_header.len));
	sprintf(m_header.len,"%u",length);

	//报文长度,不包含本字段的长度
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',LEN);
	sprintf(code,temp,m_header.len);  
	m_sEncode=code+m_sEncode;
	
	usLen=m_sEncode.length();

	return m_sEncode.c_str();
}

void CSmsPacket::SetHeader(SMS_HEADER & header)
{
	m_header=header;
}

void CSmsPacket::AddField(SmsField & field)
{
	ArrayListMsg msg;
	msg.AddValue(field.fid);
	msg.AddValue(field.flen);
	msg.AddValue(field.fdata);
	m_fields.AddValue(msg);
}

void CSmsPacket::GetFields(ArrayListMsg &fields)
{
	fields=m_fields;
}
void CSmsPacket::GetHeader(SMS_HEADER & header)
{
	header=m_header;
}

string CSmsPacket::GetFiledByFid(std::string &fid)
{
	string find="";
	ArrayListMsg aMsg;
	for (size_t i=0;i< m_fields.size();i++)
	{
		aMsg = m_fields.GetValue(i);
		string s=aMsg.GetValue<string>(0);
		if(fid==s)
		{
			find=aMsg.GetValue<string>(2);
			break;
		}
	}
	return find;
}
