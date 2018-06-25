/******************************************************************************
��    Ȩ:��������������ϵͳ���޹�˾.
ģ������:OfferingPacket.cpp
������	:��ΰ
��������:2008.07.22
��    ��:1.0				
ģ������:��װ���ڱ��̻����ı������
��Ҫ����:Decode(...) �յ������������ݿ����ý��뱨��
	     Encode()   socket����ǰ�����ĸ�ʽ������װ
	     GetCmdID() ��ȡ�����ּ�ApiName
	     GetKey()��ȡ����key,��RootID
		 SetKey()���ñ���key,��RootID
		 SetNodeType()���ñ���ͷ�ڵ�����
		 SetNodeID()���ñ���ͷ�ڵ�ID
�޸ļ�¼:
******************************************************************************/

#include <vector>
#include "Logger.h"
#include "strutils.h"
#include "LinePacket.h"

using namespace std;
using namespace strutils;

CPacketLineReq::CPacketLineReq():
m_sCmdID("")
,m_sEncode("")
{
}

CPacketLineReq::CPacketLineReq(const string& sLine)
:m_sEncode(sLine)
{
}

CPacketLineReq::~CPacketLineReq()
{
}

/******************************************************************************
��������:�����ṩ�Ľӿں���,socket����ǰ�����ĸ�ʽ������װ
�������:unsigned int & usLen�������ڴ����ݿ鳤��
����ֵ  :�������ڴ����ݿ��ַ
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
const char* CPacketLineReq::Encode(unsigned int & usLen)
{
	vector<string>::iterator it;
	for (it = m_vecPara.begin(); it != m_vecPara.end(); ++it)
	{
		m_sEncode += (*it);
	}
	
	usLen = m_sEncode.length();
	return m_sEncode.c_str();
}

/******************************************************************************
��������:�����ṩ�Ľӿں���,�յ������������ݿ����ý��뱨��
�������:const char * pData �������ݿ��ڴ��ַ
	     unsigned int nLength �������ݿ鳤��
����ֵ  :��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CPacketLineReq::Decode(const char * pData, unsigned int uiLength)
{
	string sLine("");
	for (unsigned int i = 0; i < uiLength; i++)
	{
		sLine.append(1,pData[i]);
	}

	m_vecPara = explodeQuoted(" ", sLine);

	if (!m_vecPara.empty())
		m_sCmdID = m_vecPara[0];
}

/******************************************************************************
��������:��ȡ���������ּ�ApiName
����ֵ  :���������ּ�ApiName
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
const string& CPacketLineReq::GetCmdID()
{
	return m_sCmdID;
}

void CPacketLineReq::AddCmdID(const string& sCmdID)
{
	m_sCmdID = sCmdID;

	m_vecPara.insert(m_vecPara.begin(),sCmdID);
}

void CPacketLineReq::AddPara(const string& sCmdID)
{
	m_vecPara.push_back(sCmdID);
}

int CPacketLineReq::GetPara(vector<string>& vecPara)
{
	size_t nSize = m_vecPara.size();
	for (size_t i = 1; i < nSize; i++)
	{
		vecPara.push_back(m_vecPara[i]);
	}

	return 0;
}

CPacketLineRsp::CPacketLineRsp()
:m_sEncode("")
,m_sCmdID("")
{
}

CPacketLineRsp::CPacketLineRsp(const string& sLine)
:m_sEncode(sLine)
,m_sCmdID("")
{
}

CPacketLineRsp::~CPacketLineRsp()
{
}

void CPacketLineRsp::AddRspMsg(const string& sMsg)
{
	m_sEncode = sMsg;
}

string CPacketLineRsp::GetRspMsg()
{
	return m_sEncode;
}

const char* CPacketLineRsp::Encode(unsigned int & uiLength)
{
	uiLength = m_sEncode.length();
	return m_sEncode.c_str();	
}

void  CPacketLineRsp::Decode(const char * pData, unsigned int uiLength)
{
	m_sEncode.clear();
	for (unsigned int i = 0; i < uiLength; i++)
	{
		m_sEncode.append(1,pData[i]);
	}
}