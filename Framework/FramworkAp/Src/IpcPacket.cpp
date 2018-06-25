#include <vector>
#include "Logger.h"
#include "strutils.h"
#include "IpcPacket.h"

using namespace std;
using namespace strutils;


//�������к�
unsigned int CIpcPacket::m_uiSID = 0;
CGessMutex	CIpcPacket::m_csSID;

CIpcPacket::CIpcPacket():
m_sCmdID("")
,m_sEncode("")
{
}

CIpcPacket::CIpcPacket(const string& sCmdID):
CPairPacket()
,m_sCmdID(sCmdID)
,m_sEncode("")
{
	AddParameter(GESS_API_NAME,sCmdID);
	//AddParameter("SID",GetSID());
}

CIpcPacket::~CIpcPacket()
{
}

/******************************************************************************
��������:�����ṩ�Ľӿں���,socket����ǰ�����ĸ�ʽ������װ
���ú���:
��������:
�������:
�������:unsigned int & usLen�������ڴ����ݿ鳤��
�������:
����ֵ  :�������ڴ����ݿ��ַ
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
const char* CIpcPacket::Encode(unsigned int & usLen)
{
	m_sEncode = "";
	m_sEncode = AssembleBody(GESS_FLD_SEPERATOR,GESS_VAL_SEPERATOR);

	char szTmp[128];
	memset(szTmp,0x00,128);
	sprintf(szTmp,"%c0%dd",'%',IPC_LENGTH_BYTES);
	char szLen[128];
	sprintf(szLen,szTmp,m_sEncode.length());
	szLen[IPC_LENGTH_BYTES] = '\0';
	
	m_sEncode = szLen + m_sEncode;
	usLen = m_sEncode.length();
	return m_sEncode.c_str();
}

/******************************************************************************
��������:�����ṩ�Ľӿں���,�յ������������ݿ����ý��뱨��
���ú���:
��������:
�������:const char * pData �������ݿ��ڴ��ַ
	     unsigned int nLength �������ݿ鳤��
�������:
�������:
����ֵ  :��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CIpcPacket::Decode(const char * pData, unsigned int nLength)
{
	char* pcBuf = new char[nLength+1];
	memcpy(pcBuf,pData,nLength);
	pcBuf[nLength] = '\0';
	std::string sPacket = pcBuf;
	delete []pcBuf;

	std::string sBody = sPacket.substr(IPC_LENGTH_BYTES,nLength-IPC_LENGTH_BYTES);
	ParseBody(sBody,GESS_FLD_SEPERATOR,GESS_VAL_SEPERATOR);
}

const string& CIpcPacket::GetCmdID()
{
	std::string sApiName = (GESS_API_NAME);
	GetParameterVal(sApiName,m_sCmdID);
	return m_sCmdID;
}

//��δ�ã���ȡ��ˮ
long CIpcPacket::GetSID()
{
	m_csSID.Lock();
	m_uiSID++;
	m_csSID.Unlock();
	return m_uiSID;
}