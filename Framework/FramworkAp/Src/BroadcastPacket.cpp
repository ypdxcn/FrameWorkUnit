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
#include "BroadcastPacket.h"

using namespace std;
using namespace strutils;

//�������к�
long CBroadcastPacket::m_uiSID = 0;
CGessMutex	CBroadcastPacket::m_csSID;

CBroadcastPacket::CBroadcastPacket():
m_sCmdID("")
,m_sEncode("")
{
}

CBroadcastPacket::CBroadcastPacket(const char* pcApiName):
CPairPacket()
,m_sCmdID(pcApiName)
,m_sEncode("")
{
	AddParameter(GESS_API_NAME,pcApiName);
}

CBroadcastPacket::~CBroadcastPacket()
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
const char* CBroadcastPacket::Encode(unsigned int & usLen)
{
	m_sEncode = "";
	m_sEncode += AssembleBody(GESS_FLD_SEPERATOR,GESS_VAL_SEPERATOR);

	char szTmp[128];
	memset(szTmp,0x00,128);
	sprintf(szTmp,"%c0%dd",'%',BROADCAST_LENGTH_BYTES);
	char szLen[128];
	sprintf(szLen,szTmp,m_sEncode.length());
	szLen[BROADCAST_LENGTH_BYTES] = '\0';
	
	m_sEncode = szLen + m_sEncode;
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
void CBroadcastPacket::Decode(const char * pData, unsigned int nLength)
{
	char* pcBuf = new char[nLength+1];
	memcpy(pcBuf,pData,nLength);
	pcBuf[nLength] = '\0';
	std::string sPacket = pcBuf;
	delete []pcBuf;

	sPacket = sPacket.substr(BROADCAST_LENGTH_BYTES,nLength-BROADCAST_LENGTH_BYTES);
	ParseBody(sPacket,GESS_FLD_SEPERATOR,GESS_VAL_SEPERATOR);
}

/******************************************************************************
��������:��ȡ���������ּ�ApiName
����ֵ  :���������ּ�ApiName
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
const string&CBroadcastPacket::GetCmdID()
{
	std::string sApiName = (GESS_API_NAME);
	GetParameterVal(sApiName,m_sCmdID);
	return m_sCmdID;
}

//��δ�ã���ȡ��ˮ
long CBroadcastPacket::GetSID()
{
	m_csSID.Lock();
	m_uiSID++;
	m_csSID.Unlock();
	return m_uiSID;
}