#include "AbsTimerMgrWin32.h"
#include "Logger.h"
#include "strutils.h"

CAbsTimerMgrWin32::CAbsTimerMgrWin32(void)
:m_hEvt(NULL)
{
	for (int i = 0; i < MAXIMUM_WAIT_OBJECTS; i++)
	{
		m_WaitObj[i] = NULL;
	}
}

CAbsTimerMgrWin32::~CAbsTimerMgrWin32(void)
{
}

int CAbsTimerMgrWin32::Init()
{
	m_hEvt = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	return 0;
}

void CAbsTimerMgrWin32::Finish()
{
	CloseHandle(m_hEvt);
	m_hEvt = NULL;

	for (multimap<CGessAbsTimer*,T_DATE_TIMER*>::iterator it = m_mapAbsTimers.begin(); it != m_mapAbsTimers.end(); ++it)
	{
		CancelWaitableTimer((*it).second->hWaitableTimer);
		CloseHandle((*it).second->hWaitableTimer);
		delete (*it).second;
	}
	m_mapAbsTimers.clear();

	for (deque<T_DATE_TIMER*>::iterator itCreate = m_deqCreate.begin(); itCreate != m_deqCreate.end(); ++itCreate)
	{
		CloseHandle((*itCreate)->hWaitableTimer);
		delete *itCreate;
	}
	m_deqCreate.clear();

	for (deque<T_DATE_TIMER*>::iterator itCancel = m_deqCancel.begin(); itCancel != m_deqCancel.end(); ++itCancel)
	{
		CancelWaitableTimer((*itCancel)->hWaitableTimer);
		CloseHandle((*itCancel)->hWaitableTimer);
		delete *itCancel;
	}
	m_deqCancel.clear();
}

int CAbsTimerMgrWin32::Start()
{
	return BeginThread();
}

void CAbsTimerMgrWin32::Stop()
{
	EndThread();
}

int CAbsTimerMgrWin32::SetAbsTimer(T_DATE_TIMER* t)
{
	if (0 == t)
		return -1;

	SYSTEMTIME	st;
	FILETIME ftLocal,ftUTC;
	LARGE_INTEGER liUTC;
	long lPeriod = 0;
	switch (t->eType)
	{
	case E_TIMER_DAY:
		if (t->oTime.CompareNow() > 0)
		{
			st.wYear = CGessDate::ThisYear();
			st.wMonth = CGessDate::ThisMonth();
			st.wDayOfWeek = 0;
			st.wDay = CGessDate::ThisDay();
		}
		else
		{
			CGessDate oTheDay;
			oTheDay++;
			st.wYear = oTheDay.Year();
			st.wMonth = oTheDay.Month();
			st.wDayOfWeek = 0;
			st.wDay = oTheDay.Day();
		}
		lPeriod = 24*3600*1000;
		break;
	case E_TIMER_WEEK_DAY:
		{
			CGessDate oTheDay;
			oTheDay.Day2Today();
			if ( oTheDay.WeekDay() < t->nWeekDay)
			{	
				int nDayDiff = t->nWeekDay - oTheDay.WeekDay(); 
				oTheDay += nDayDiff;
			}
			else if (oTheDay.WeekDay() > t->nWeekDay)
			{
				int nDayDiff = 7 - oTheDay.WeekDay() + t->nWeekDay; 
				oTheDay += nDayDiff;
			}
			else
			{
				if (t->oTime.CompareNow() <= 0)
				{
					oTheDay += 7;
				}
			}
			st.wYear = oTheDay.Year();
			st.wMonth = oTheDay.Month();
			st.wDayOfWeek = oTheDay.WeekDay();
			st.wDay = oTheDay.Day();
		}
		lPeriod = 7*24*3600*1000;
		break;
	case E_TIMER_MONTH_DAY:
		return -1;
	case E_TIMER_YEAR_DAY:
		return -1;
	default:
		return -1;
	}

	st.wHour = t->oTime.Hour();
	st.wMinute = t->oTime.Minute();
	st.wSecond = t->oTime.Second();
	st.wMilliseconds = 0;

	SystemTimeToFileTime(&st, &ftLocal);
	LocalFileTimeToFileTime(&ftLocal,&ftUTC);
	liUTC.LowPart = ftUTC.dwLowDateTime;
	liUTC.HighPart = ftUTC.dwHighDateTime;

	switch (t->eType)
	{
	case E_TIMER_DAY:
	case E_TIMER_WEEK_DAY:
		if (!SetWaitableTimer(t->hWaitableTimer, &liUTC, lPeriod, 0, t, 0))
		{
			CRLog(E_ERROR,"SetWaitableTimer failed (%d)\n", GetLastError());
			CloseHandle(t->hWaitableTimer);
			t->pTimer->TimerCanceled(t->sKey);
			return -1;
		}
		break;
	default:
		return -1;
	}

	m_mapAbsTimers.insert(make_pair(t->pTimer,t));
	return 0;
}

void CAbsTimerMgrWin32::CancelAbsTimer(T_DATE_TIMER* t)
{
	if (0 != t)
	{
		CancelWaitableTimer(t->hWaitableTimer);
		CloseHandle(t->hWaitableTimer);		
	}
}

void CAbsTimerMgrWin32::HandleCancel()
{
	CMutexGuard oGuard(m_csAbsTimes);
	for (deque<T_DATE_TIMER*>::iterator itCancel = m_deqCancel.begin(); itCancel != m_deqCancel.end(); ++itCancel)
	{
		CancelAbsTimer(*itCancel);
		delete *itCancel;
	}
	m_deqCancel.clear();
}

void CAbsTimerMgrWin32::HandleCreate()
{
	CMutexGuard oGuard(m_csAbsTimes);
	for (deque<T_DATE_TIMER*>::iterator itCreate = m_deqCreate.begin(); itCreate != m_deqCreate.end(); ++itCreate)
	{
		if (-1 == SetAbsTimer(*itCreate))
		{
			delete *itCreate;
		}
	}
	m_deqCreate.clear();
}

int CAbsTimerMgrWin32::WaitObjs()
{
	int nCount = 1;
	m_WaitObj[0] = m_hEvt;

	CMutexGuard oGuard(m_csAbsTimes);
	for (multimap<CGessAbsTimer*,T_DATE_TIMER*>::iterator it = m_mapAbsTimers.begin(); it != m_mapAbsTimers.end(); ++it)
	{
		if (nCount < MAXIMUM_WAIT_OBJECTS)
		{
			m_WaitObj[nCount] = (*it).second->hWaitableTimer;
		}
		else
		{
			break;
		}
		nCount++;
	}
	return nCount;
}

int CAbsTimerMgrWin32::TimeOut(HANDLE hTimer)
{
	CMutexGuard oGuard(m_csAbsTimes);
	for (multimap<CGessAbsTimer*,T_DATE_TIMER*>::iterator it = m_mapAbsTimers.begin(); it != m_mapAbsTimers.end(); ++it)
	{
		if ((*it).second->hWaitableTimer == hTimer)
		{
			(*it).second->pTimer->TimeOut((*it).second->sKey);
			break;
		}
	}
	return 0;
}

int CAbsTimerMgrWin32::ThreadEntry()
{
	try
	{
		while (!m_bEndThread)
		{
			int nCount = WaitObjs();
			DWORD dwRslt = WaitForMultipleObjects(nCount, m_WaitObj, FALSE, INFINITE);
			if (WAIT_FAILED == dwRslt)
			{
				CRLog(E_ERROR, "WAIT_FAILED %u",dwRslt);
				break;
			}
			else if (WAIT_ABANDONED_0 <= dwRslt && dwRslt < WAIT_ABANDONED_0 + nCount)
			{
				CRLog(E_ERROR, "WAIT_ABANDONED_%u",dwRslt);
				break;
			}
			else if (WAIT_TIMEOUT == dwRslt)
			{
				continue;
			}

			if (WAIT_OBJECT_0 == dwRslt)
			{
				HandleCancel();
				HandleCreate();
				continue;
			}

			TimeOut(m_WaitObj[dwRslt-WAIT_OBJECT_0]);
		}
		return 0;
	}
	catch(...)
	{
		CRLog(E_ERROR,"%s","Unknow Exception TimerMgr ThreadEntry");
		return -1;
	}
}

int CAbsTimerMgrWin32::End() 
{
	SetEvent(m_hEvt);
	Wait();
	return 0;
}


int CAbsTimerMgrWin32::CreateDayTimer(CGessAbsTimer* p, CGessTime& oTime, const string& sKey)
{
	if (0 == p)
		return -1;

	// Create a waitable timer.
	HANDLE hWaitableTimer = ::CreateWaitableTimer(NULL, FALSE, NULL);
    if (NULL == hWaitableTimer)
    {
        CRLog(E_ERROR,"CreateWaitableTimer failed (%d)", GetLastError());
        return -1;
    }

	try
	{
		T_DATE_TIMER* t = new T_DATE_TIMER;
		t->hWaitableTimer = hWaitableTimer;
		t->eType = E_TIMER_DAY;
		t->pTimer = p;
		t->sKey = sKey;
		t->oTime = oTime;
		
		return CreateTimer(p, t, sKey);
	}
	catch(...)
	{
		CRLog(E_ERROR,"%s","Unknow Exception CreateTimer");
	}
	return 0;
}

int CAbsTimerMgrWin32::DestroyDayTimer(CGessAbsTimer* p,const string& sKey)
{
	return DestroyTimer(p, sKey, E_TIMER_DAY);
}

int CAbsTimerMgrWin32::CreateWeekTimer(CGessAbsTimer* p, unsigned int uiWeekDay, CGessTime& oTime,const string& sKey) 
{
	if (0 == p)
		return -1;

	// Create a waitable timer.
	HANDLE hWaitableTimer = ::CreateWaitableTimer(NULL, FALSE, NULL);
    if (NULL == hWaitableTimer)
    {
        CRLog(E_ERROR,"CreateWaitableTimer failed (%d)", GetLastError());
        return -1;
    }

	T_DATE_TIMER* t = new T_DATE_TIMER;
	t->hWaitableTimer = hWaitableTimer;
	t->eType = E_TIMER_WEEK_DAY;
	t->pTimer = p;
	t->sKey = sKey;
	t->nWeekDay = uiWeekDay;
	t->oTime = oTime;

	return CreateTimer(p, t, sKey);
}

int CAbsTimerMgrWin32::DestroyWeekTimer(CGessAbsTimer* p,const string& sKey) 
{
	return DestroyTimer(p, sKey, E_TIMER_WEEK_DAY);
}

int CAbsTimerMgrWin32::CreateTimer(CGessAbsTimer* p, T_DATE_TIMER* t , const string& sKey) 
{
	try
	{	
		if (0 == t)
			return -1;

		typedef multimap<CGessAbsTimer*,T_DATE_TIMER*> MMAP_TM;
		typedef MMAP_TM::iterator MMAP_IT;
		typedef pair<MMAP_IT,MMAP_IT> RANGE_TM;
		MMAP_IT it;

		CMutexGuard oGuard(m_csAbsTimes);
		RANGE_TM range = m_mapAbsTimers.equal_range(p);
		for (it = range.first; it != range.second; )
		{
			if ((*it).second->sKey == sKey && t->eType == (*it).second->eType)
			{
				CRLog(E_SYSINFO,"重复创建定时器:%s",sKey.c_str());
				CloseHandle(t->hWaitableTimer);
				delete t;
				return -1;
			}
		}

		m_deqCreate.push_back(t);
		SetEvent(m_hEvt);
	}
	catch(...)
	{
		CRLog(E_ERROR,"%s","Unknow Exception CreateTimer");
	}
	return 0;
}


int CAbsTimerMgrWin32::DestroyTimer(CGessAbsTimer* p,const string& sKey, E_TIMER_DAY_TYPE eType) 
{
	typedef multimap<CGessAbsTimer*,T_DATE_TIMER*> MMAP_TM;
	typedef MMAP_TM::iterator MMAP_IT;
	typedef pair<MMAP_IT,MMAP_IT> RANGE_TM;
	MMAP_IT it;

	try
	{
		CMutexGuard oGuard(m_csAbsTimes);
		RANGE_TM range = m_mapAbsTimers.equal_range(p);
		for (it = range.first; it != range.second; )
		{
			if ((*it).second->sKey == sKey  && eType == (*it).second->eType)
			{
				m_deqCancel.push_back((*it).second);
				m_mapAbsTimers.erase(it++);

				SetEvent(m_hEvt);
				break;
			}
			else
			{
				++it;
			}
		}
	}
	catch(...)
	{
		CRLog(E_ERROR,"%s","Unknow Exception DestroyTimer");
	}
	return 0;
}

