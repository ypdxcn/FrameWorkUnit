#ifndef _FILE_LOG_DEV_H
#define _FILE_LOG_DEV_H

#include "GessDate.h"
#include "GessTime.h"
#include "LogDevice.h"
#include "Gess.h"

class UTIL_CLASS CFileLogDev : public CLogDevice
{
public:
	CFileLogDev(CLogger * pLogger);
	~CFileLogDev(void);

public:
	int Initial(CConfig * pCfg);
	int Open(void);
	void Close(void);
	void Finish();

	void Log(const char * cszFile, long nLine, GESS_LOG_LEVEL nLevel, const char * cszText);
private:
	typedef struct tagLogFile
	{
		std::string sFileName;		//��־�ļ���
		FILE * pfLogFile;			//��־�ļ����
		size_t nFileSize;			//��־�ļ���С
		int nFlag;					//0�û����� 1ȱʡ
	} LOG_FILE, *PLOG_FILE;
private:
	int Open(GESS_LOG_LEVEL eLevel);
	int SwitchSize(LOG_FILE* pLogFile);
	int SwitchDate();

	std::string m_sPostfix;			//��־�ļ���׺
	std::string m_sPrefix;			//��־�ļ�ǰ׺
	std::string m_sFilePathAbs;		//��־�ļ�Ŀ¼·���̶�����
	std::string m_sFilePathRel;		//��־�ļ�Ŀ¼·���仯����
	std::string m_sFilePath;		//��־�ļ�Ŀ¼·��
	size_t m_nMaxSize;				//��־�ļ����ߴ�

	LOG_FILE*	m_stLevelLogFile[E_LOG_LEVEL_MAX];
	map<string,LOG_FILE *>	m_mapLogFile;
	CGessDate	m_oDate;
};
#endif