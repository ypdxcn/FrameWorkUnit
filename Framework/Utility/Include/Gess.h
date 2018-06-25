#ifndef _GESS_H
#define _GESS_H

#include "osdepend.h"
#include "Config.h"
#include <map>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <bitset>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

#ifdef _WIN32
#ifdef UTIL_EXPORTS
#define UTIL_API			__declspec(dllexport)
#define UTIL_CLASS		__declspec(dllexport)
#else
#define UTIL_API			__declspec(dllimport)
#define UTIL_CLASS		__declspec(dllimport)
#endif
#else
#define UTIL_API
#define UTIL_CLASS
#endif

#define FILE_INFO	__FUNCTION__, __LINE__

#define DEFUALT_CONF_PATH       "cfg"
#define DEFUALT_LOG_PATH       "log"

enum GESS_LOG_LEVEL
{	
	E_CRITICAL	= 0,	//���ش���
	E_ERROR,			//һ�����
	E_WARNING,			//����
	E_NOTICE,			//ͨ��
	E_SYSINFO,			//ϵͳ��Ϣ	
	E_PROINFO,			//Э����Ϣ
	E_APPINFO,			//Ӧ����Ϣ
	E_DEBUG,			//������Ϣ
	E_STATICS,			//ͳ����Ϣ
	//E_ALL,			//��������
	//E_NONE,			//
	E_LOG_LEVEL_MAX
};

//��װposix������
#ifndef PTHREAD_MUTEX_RECURSIVE_NP
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#endif
class UTIL_CLASS CGessMutex
{
public:
	CGessMutex()
	{
		pthread_mutexattr_init(&m_attr);
		pthread_mutexattr_settype(&m_attr,PTHREAD_MUTEX_RECURSIVE_NP);	
		pthread_mutex_init(&m_mutexPosix, &m_attr);
	}
	~CGessMutex(){pthread_mutex_destroy(&m_mutexPosix);}

	void Lock() {pthread_mutex_lock(&m_mutexPosix);}
	void Unlock() {pthread_mutex_unlock(&m_mutexPosix);}

private:
	pthread_mutexattr_t m_attr;
	pthread_mutex_t	m_mutexPosix;
};

//��װposix��������
class UTIL_CLASS CCondMutex
{
public:
	CCondMutex()
	{
		pthread_mutexattr_init(&m_attr);
		pthread_mutexattr_settype(&m_attr,PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init(&m_mutexPosix, &m_attr);
		pthread_cond_init(&m_condPosix, 0);
	}
	~CCondMutex()
	{
		pthread_mutex_destroy(&m_mutexPosix);
		pthread_cond_destroy(&m_condPosix);
	}

	void Lock(){pthread_mutex_lock(&m_mutexPosix);}
	void Unlock(){pthread_mutex_unlock(&m_mutexPosix);}
	void Wait(){pthread_cond_wait(&m_condPosix, & m_mutexPosix);}
	int TimeWaitAbs(struct timespec& tInterval){return pthread_cond_timedwait(&m_condPosix, &m_mutexPosix, &tInterval);}
	void Signal(){pthread_cond_signal(&m_condPosix);}
	void SignalAll(){pthread_cond_broadcast(&m_condPosix);}
private:
	pthread_mutexattr_t m_attr;
	pthread_mutex_t	m_mutexPosix;
	pthread_cond_t  m_condPosix;
};

//
class UTIL_CLASS CGessGuard
{
public:
	CGessGuard(CGessMutex& mutex):m_mutexGuard(mutex)
	{
		m_mutexGuard.Lock();
	}
	~CGessGuard(){m_mutexGuard.Unlock();}
private:
	CGessMutex& m_mutexGuard;
};

//
class UTIL_CLASS CMutexGuard
{
public:
	CMutexGuard(CGessMutex& mutex):m_mutexGuard(mutex)
	{
		m_mutexGuard.Lock();
	}
	~CMutexGuard(){m_mutexGuard.Unlock();}
private:
	CGessMutex& m_mutexGuard;
};

//
class UTIL_CLASS CCondMutexGuard
{
public:
	CCondMutexGuard(CCondMutex& mutex):m_mutexCondGuard(mutex)
	{
		m_mutexCondGuard.Lock();
	}
	~CCondMutexGuard(){m_mutexCondGuard.Unlock();}
private:
	CCondMutex& m_mutexCondGuard;
};

//POSIX�ź�������Ӧ��װ����
class UTIL_CLASS CGessSem
{
public:
	CGessSem()
	{
		//��ʼ��Ϊ0
		if (0 != sem_init(&m_sem, 0, 0))
		{
			//CRLog(E_ERROR, "sem_init err");
		}
	}
	CGessSem(int nVal)
	{
		if (0 != sem_init(&m_sem, 0, nVal))
		{
			//CRLog(E_ERROR, "sem_init err");
		}
	}
	~CGessSem(){sem_destroy(&m_sem);}

	int V(){return sem_post(&m_sem);}
	int P(){return sem_wait(&m_sem);}
	int Try(){return sem_trywait(&m_sem);}
private:
	sem_t m_sem;
};

//�����ļ�����
class UTIL_CLASS CConfig
{
public:
	virtual int GetProperty(const std::string & sKey, /*OUT*/std::string & sValue) = 0;
	virtual int GetProperty(const std::string & sKey, /*OUT*/std::vector<std::string> & vValues) = 0;

	virtual int GetProperty(const std::string & sKey, /*OUT*/std::string & sValue, const std::string & sDefault) = 0;
	virtual int GetProperty(const std::string & sKey, /*OUT*/std::vector<std::string> & vValues, const std::string & sDefault) = 0;

	virtual int SetProperty(const std::string & sKey, const std::string & sValue) = 0;
	virtual int SetProperty(const std::string & sKey, const std::vector<std::string> & vValues) = 0;

	virtual std::vector<std::string> GetKeys() = 0;
	virtual CConfig * GetProperties(const std::string & sBase) = 0;
	virtual void SetProperties(const std::string & sBase, CConfig * pCfg) = 0;

	virtual CConfig* GetCfgParent() = 0;
	virtual CConfig* GetCfgGlobal() = 0;
	virtual bool IsEmpty() = 0;
};

class UTIL_CLASS CGessTimer
{
public:
    virtual int TimeOut(const string& ulKey,unsigned long& ulTmSpan) = 0;
    virtual void TimerCanceled(const string& ulKey) = 0;
};

class UTIL_CLASS CGessTimerMgrIf
{
public:
	CGessTimerMgrIf(){}
	virtual ~CGessTimerMgrIf(){}

    virtual int Init(unsigned long ulTmSpan) = 0;
	virtual int Start() = 0;
	virtual void Stop() = 0;
	virtual void Finish() = 0;
    
    virtual int CreateTimer(CGessTimer* p, unsigned long ulTmSpan,const string& sKey) = 0;
    virtual int DestroyTimer(CGessTimer* p,const string& sKey) = 0;
};


class UTIL_CLASS CGessAbsTimer
{
public:
    virtual int TimeOut(const string& ulKey) = 0;
    virtual void TimerCanceled(const string& ulKey) = 0;
};

class CGessDate;
class CGessTime;
class CGessDateTime;
class UTIL_CLASS CGessAbsTimerMgrIf
{
public:
	virtual int CreateDayTimer(CGessAbsTimer* p, CGessTime& oTime, const string& sKey) = 0;
	virtual int DestroyDayTimer(CGessAbsTimer* p,const string& sKey) = 0;

	virtual int CreateWeekTimer(CGessAbsTimer* p, unsigned int uiWeekDay, CGessTime& oTime,const string& sKey) = 0;
	virtual int DestroyWeekTimer(CGessAbsTimer* p,const string& sKey) = 0;

	virtual int CreateMonthTimer(CGessAbsTimer* p, unsigned int uiMonthDay, CGessTime& oTime,const string& sKey) = 0;
	virtual int CreateMonthTimer(CGessAbsTimer* p, CGessDate& oDate, CGessTime& oTime,const string& sKey) = 0;
	virtual int CreateMonthTimer(CGessAbsTimer* p, CGessDateTime& oDateTime, const string& sKey) = 0;
	virtual int DestroyMonthTimer(CGessAbsTimer* p,const string& sKey) = 0;

	virtual int CreateYearTimer(CGessAbsTimer* p, unsigned int uiYearDay, CGessTime& oTime, const string& sKey) = 0;
	virtual int CreateYearTimer(CGessAbsTimer* p, unsigned int uiMonth, unsigned int uiDay, CGessTime& oTime, const string& sKey) = 0;
	virtual int CreateYearTimer(CGessAbsTimer* p, CGessDate& oDate, CGessTime& oTime, const string& sKey) = 0;
	virtual int CreateYearTimer(CGessAbsTimer* p, CGessDateTime& oDateTime, const string& sKey) = 0;
	virtual int DestroyYearTimer(CGessAbsTimer* p,const string& sKey) = 0;
};

#endif