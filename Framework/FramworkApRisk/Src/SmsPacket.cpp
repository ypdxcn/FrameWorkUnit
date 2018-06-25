#include "SmsPacket.h"

CSmsPacket::CSmsPacket():m_sCmdID("")
{}

CSmsPacket::~CSmsPacket(){}

const string & CSmsPacket::GetCmdID()
{
	return m_sCmdID;
}
/************************************************************************
�����յ��ı���
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

	//���ĳ���,���������ֶεĳ���
	memcpy(m_header.len,pPos,LEN); 
	pPos+=LEN;
	
	//���ݰ����к�
	memcpy(m_header.seq,pPos,SEQ); 
	pPos+=SEQ;
	
	//��������
	memcpy(m_header.pkg_type,pPos,PKGTYPE); 
	pPos+=PKGTYPE;

	//������Դ
	memcpy(m_header.pkg_src,pPos,PKGSRC); 
	pPos+=PKGSRC;

	//���״���
	memcpy(m_header.tran_code,pPos,TRANCODE); 
	pPos+=TRANCODE;

	//���ȼ�
	memcpy(m_header.priority,pPos,PRIORITY); 
	pPos+=PRIORITY;

	//���ŷ������� yymmdd
	memcpy(m_header.tran_date,pPos,TRADATE); 
	pPos+=TRADATE;

	//���ŷ���ʱ�� HHNNSSmmm
	memcpy(m_header.tran_time,pPos,TRATIME); 
	pPos+=TRATIME;

	//����/Ӧ���ʶ R-���� A-Ӧ��
	memcpy(m_header.ra_flag,pPos,RAFLAG); 
	pPos+=RAFLAG;

	//���ܱ�־ Y-���� ����-������
	memcpy(m_header.enc_flag,pPos,ENCFLAG); 
	pPos+=ENCFLAG;

	//���ļ�¼�� ����ʱ����1�����ʱ�����ܰ���
	memcpy(m_header.totals,pPos,TOTALS); 
	pPos+=TOTALS;

	//��ǰ����� ����ʱ����1�����ʱ����ʵ�ʵİ���
	memcpy(m_header.rec_no,pPos,RECNO); 
	pPos+=RECNO;

	//������е��ֶ���
	memcpy(m_header.fields,pPos,FIELDS); 
	pPos+=FIELDS;

	//Ӧ��ʱ�������1��-�ɹ�������-ʧ�ܡ�ʧ��ԭ���ڷ��ذ���������
	memcpy(m_header.succ_flag,pPos,SUCCFLAG); 
	pPos+=SUCCFLAG;

	//����
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

		//�ֶ����
		memcpy(temp.fid,pPos,FID); 
		pPos+=FID;
		
		//�ֶγ���
		memcpy(temp.flen,pPos,FLEN); 
		pPos+=FLEN;
		
		int flen=atoi(temp.flen);
		//�ֶγ���
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
���ķ���ǰ�ӽṹ��ת��Ϊ�ֽ���
************************************************************************/
const char* CSmsPacket::Encode(unsigned int &usLen)
{
	char temp[128];
	char code[1024];
	m_sEncode="";	

	//���ݰ����к�
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',SEQ);
	sprintf(code,temp,m_header.seq);  
	m_sEncode+=code;

	//��������
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',PKGTYPE);
	sprintf(code,temp,m_header.pkg_type);  
	m_sEncode+=code;

	//������Դ
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',PKGSRC);
	sprintf(code,temp,m_header.pkg_src);  
	m_sEncode+=code;

	//���״���
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TRANCODE);
	sprintf(code,temp,m_header.tran_code);  
	m_sEncode+=code;

	//���ȼ�
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',PRIORITY);
	sprintf(code,temp,m_header.priority);  
	m_sEncode+=code;

	//���ŷ������� yymmdd
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TRADATE);
	sprintf(code,temp,m_header.tran_date);  
	m_sEncode+=code;

	//���ŷ���ʱ�� HHNNSSmmm
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TRATIME);
	sprintf(code,temp,m_header.tran_time);  
	m_sEncode+=code;

	//����/Ӧ���ʶ R-���� A-Ӧ��
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',RAFLAG);
	sprintf(code,temp,m_header.ra_flag);  
	m_sEncode+=code;

	//���ܱ�־ Y-���� ����-������
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',ENCFLAG);
	sprintf(code,temp,m_header.enc_flag);  
	m_sEncode+=code;

	//���ļ�¼�� ����ʱ����1�����ʱ�����ܰ���
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',TOTALS);
	sprintf(code,temp,m_header.totals);  
	m_sEncode+=code;

	//��ǰ����� ����ʱ����1�����ʱ����ʵ�ʵİ���
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',RECNO);
	sprintf(code,temp,m_header.rec_no);  
	m_sEncode+=code;

	//������е��ֶ���
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%dd",'%',FIELDS);
	sprintf(code,temp,m_fields.size());  
	m_sEncode+=code;

	//Ӧ��ʱ�������1��-�ɹ�������-ʧ�ܡ�ʧ��ԭ���ڷ��ذ���������
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',SUCCFLAG);
	sprintf(code,temp,m_header.succ_flag);  
	m_sEncode+=code;

	//����
	memset(temp,0x00,sizeof(temp));
	memset(code,0x00,sizeof(code));
	sprintf(temp,"%c%ds",'%',RESERVED);
	sprintf(code,temp,m_header.reserved);  
	m_sEncode+=code;
	
	//����ֶ�
	for (size_t i=0;i< m_fields.size();i++)
	{
		
		//�ֶ����
		memset(temp,0x00,sizeof(temp));
		memset(code,0x00,sizeof(code));
		sprintf(temp,"%c%ds",'%',FID);

		ArrayListMsg aMsg = m_fields.GetValue(i);
		string s=aMsg.GetValue<string>(0);
		sprintf(code,temp,s.c_str());  
		m_sEncode+=code;

		//�ֶγ���
		memset(temp,0x00,sizeof(temp));
		memset(code,0x00,sizeof(code));
		sprintf(temp,"%c%ds",'%',FLEN);
		s=aMsg.GetValue<string>(1);
		sprintf(code,temp,s.c_str());  
		m_sEncode+=code;

		//�ֶ�����
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

	//���ĳ���,���������ֶεĳ���
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
