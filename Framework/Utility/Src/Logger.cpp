/******************************************************************************
��    Ȩ:��������������ϵͳ���޹�˾.
ģ������:Logger.cpp
������	:��ΰ
��������:2008.07.22
��    ��:1.0				
ģ������:��װ��־��¼,����
��Ҫ����:GetInstance() ��ȡ��־��ʵ��
         Log() ������־��¼�Ľӿں���
�޸ļ�¼:
******************************************************************************/
#include "NetLogDev.h"
#include "ConsoleLogDev.h"
#include "FileLogDev.h"
#include "Logger.h"
#include "osdepend.h"
#include <iostream>


using namespace std;

CLogger::CLogger(void)
:m_pNetLogDev(0)
 ,m_bStop(true)
{
}

CLogger::~CLogger(void)
{
}

int CLogger::Initial(CConfig * pCfg)
{
	vector<string> vValues;
	string sValue;

	pCfg->GetProperty("type", vValues);
	if (vValues.size() < 1)
	{
		cout << "��־���������" << endl;
		return -1;
	}

	size_t nSize = vValues.size();
	cout << nSize << "����־�豸" << endl;

	CLogDevice * pLogDev = 0;
	for (size_t i = 0; i < nSize; i++)
	{   // ������־�豸
		cout << "��־�豸" << vValues[i] << endl;
		
		CConfig * pTypeCfg = pCfg->GetProperties(vValues[i]);
		if (pTypeCfg == 0)
		{
			cout << "��־�豸" << vValues[i] << "ȱ������" << endl;
			continue;
		}
		// ���������豸ʵ��
		pTypeCfg->GetProperty("device", sValue);
		if (sValue.compare("console") == 0)
		{
			pLogDev = new CConsoleLogDev(this);
			m_vecDevs.push_back(pLogDev);
		}
		else if (sValue.compare("file") == 0)
		{
			pLogDev = new CFileLogDev(this);
			m_vecDevs.push_back(pLogDev);
		}
		else if (sValue.compare("netlog") == 0)
		{
			m_pNetLogDev = new CNetLogDev(this);			
			pLogDev = m_pNetLogDev;
			m_vecDevs.push_back(pLogDev);
		}
		else
		{
			cout << "Ŀǰ��֧������Ϊ" << sValue << "����־�豸" << endl;
			continue;
		}

		if (pLogDev->Initial(pTypeCfg) != 0)
		{
			cout << "��־�豸" << vValues[i] << "��ʼ��ʧ��" << endl;
			continue;
		}
	}

	return 0;
}


void CLogger::Finish()
{
	Stop();

	for (vector<CLogDevice *>::iterator it = m_vecDevs.begin(); it != m_vecDevs.end(); ++it)
	{
		if (*it != 0)
		{
			(*it)->Finish();
			delete *it;
		}
	}
	m_pNetLogDev = 0;
}

int CLogger::Start()
{
	// �򵥱����ظ�����
	if (!m_bStop)
		return 0;

	cout << "������־" << endl;

	for (vector<CLogDevice *>::iterator it = m_vecDevs.begin(); it != m_vecDevs.end(); ++it)
	{
		if (*it != 0)
		{
			if ((*it)->Open() != 0)
			{   // ��ʧ�ܣ�������豸
				(*it)->Finish();
				delete *it;
			}
		}
	}

	m_bStop = false;
	return 0;
}

void CLogger::Stop()
{
	m_bStop = true;
}

int CLogger::Log(const char * cszFile, long nLine, GESS_LOG_LEVEL nLevel, int nReturn, const char * cszFmt, ...)
{
	va_list ap;

	char szBuf[MAX_LOG_TEXT];
	va_start(ap, cszFmt);
	vsnprintf(szBuf, sizeof(szBuf) - 1, cszFmt, ap);
	va_end(ap);

	Log(cszFile, nLine, nLevel, szBuf);

	return nReturn;
}

void CLogger::Log(const char * cszFile, long nLine, GESS_LOG_LEVEL nLevel, const char * cszText)
{
	if (m_bStop)
	{
		
	}
	else
	{   // ʹ����־�豸��¼
		for (vector<CLogDevice *>::iterator it = m_vecDevs.begin(); it != m_vecDevs.end(); ++it)
		{
			if ((*it) != 0)
				(*it)->Log(cszFile, nLine, nLevel, cszText);
		}
	}
}

bool CLogger::RegisterNetLog(CSubscriber* p)
{
	if (0 == m_pNetLogDev)
		return false;

	m_pNetLogDev->Register(p);
	return true;
}

void CLogger::UnRegisterNetLog(CSubscriber* p)
{
	if (0 == m_pNetLogDev)
		return;

	m_pNetLogDev->UnRegister(p);
}