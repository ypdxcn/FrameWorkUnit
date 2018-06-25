#include "GessTimerWin32.h"
#include "Logger.h"
#include "strutils.h"

using namespace std;

CGessTimerMgrWin32::CGessTimerMgrWin32()
:m_ulSpanNow(1)
,m_ulMin(1)
,m_nCancel(0)
,m_lWakeMs(10000)
{
}

CGessTimerMgrWin32::~CGessTimerMgrWin32()
{

}

int CGessTimerMgrWin32::Init(unsigned long ulTmSpan)
{
    m_hWaitTimer = CreateWaitableTimer(NULL,FALSE,NULL);
	if (NULL == m_hWaitTimer)
		return -1;

	m_ulMin = 1;
	m_ulSpanNow = max(ulTmSpan,m_ulMin);
	m_clkLastWait = clock();
	return 0;
}

void CGessTimerMgrWin32::Finish()
{
	if (NULL != m_hWaitTimer)
		 CloseHandle(m_hWaitTimer);

	 m_mapTimers.clear();
}

int CGessTimerMgrWin32::Start()
{
	return BeginThread();
}

void CGessTimerMgrWin32::Stop()
{
	m_nCancel = 1;
	EndThread();	

}

int CGessTimerMgrWin32::End()
{
	Wait();
	return 0;
}

int CGessTimerMgrWin32::ThreadEntry()
{
	try
	{
		LARGE_INTEGER liDueTime;
		long lPeriod = m_ulSpanNow*1000;
		long lDur = -m_lWakeMs * 2;
		liDueTime.QuadPart = lDur;
		SetWaitableTimer(m_hWaitTimer,&liDueTime, lPeriod, TimerAPCProc, this, FALSE);

		while (!m_bEndThread)
		{
			if (0 == m_nCancel)
				SleepEx(INFINITE, TRUE );
			else
				Sleep(1);
		}

		CancelWaitableTimer(m_hWaitTimer);
		CloseHandle(m_hWaitTimer);
		m_hWaitTimer = NULL;
		return 0;
	}
	catch(...)
	{
		CRLog(E_ERROR,"%s","Unknow Exception TimerMgr ThreadEntry");
		return -1;
	}
}

//检测是否需要触发各个定时器
void CGessTimerMgrWin32::OnTimeout()
{
	multimap<CGessTimer*,T_TIMER>::iterator it;

	try
	{
		m_csTimes.Lock();
		for (it = m_mapTimers.begin(); it != m_mapTimers.end(); )
		{
			if ((*it).second.ulLeft >= m_ulSpanNow)
			{
			   (*it).second.ulLeft -= m_ulSpanNow; 
			   ++it;
			}
			else if ((*it).second.ulLeft > 0)
			{
			   (*it).second.ulLeft = m_ulSpanNow;
			   ++it;
			}
			else
			{
				//(*it).second.pTrigger->Fire((*it).second);
				//(*it).second.ulLeft = (*it).second.ulSpan;
				//++it;
				(*it).second.ulLeft = (*it).second.ulSpan - m_ulSpanNow;
				unsigned long ulTmp = (*it).second.ulSpan;
				int nRtn = (*it).second.pTimer->TimeOut((*it).second.sKey,ulTmp);
				if (0 != nRtn)
				{
					m_mapTimers.erase(it++);//++it;
				}
				else
				{
					if (ulTmp != (*it).second.ulSpan)
					{
						(*it).second.ulSpan = max(m_ulSpanNow,ulTmp);
						(*it).second.ulLeft = (*it).second.ulSpan - m_ulSpanNow;
					}
					++it;
				}
			}
		}
		m_clkLastWait = clock();
		m_csTimes.Unlock();
	}
	catch(...)
	{
		m_csTimes.Unlock();
		CRLog(E_ERROR,"%s","Unknow Exception OnTimeout");
	}
}

void CALLBACK CGessTimerMgrWin32::TimerAPCProc(LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	CGessTimerMgrWin32* p = (CGessTimerMgrWin32*)lpArg;
	if (0 != p)
	{
		p->OnTimeout();
	}
}


//创建定时器
int CGessTimerMgrWin32::CreateTimer(CGessTimer* p, unsigned long ulTmSpan, const string& sKey)
{
	if (0 == p)
		return -1;

	typedef multimap<CGessTimer*,T_TIMER> MMAP_TM;
	typedef MMAP_TM::iterator MMAP_IT;
	typedef pair<MMAP_IT,MMAP_IT> RANGE_TM;
	MMAP_IT it;

	try
	{
		m_csTimes.Lock();
		RANGE_TM range = m_mapTimers.equal_range(p);
		for (it = range.first; it != range.second; )
		{
			if ((*it).second.sKey == sKey)
			{
				m_csTimes.Unlock();
				CRLog(E_SYSINFO,"重复创建定时器:%s",sKey.c_str());
				return -1;
			}
		}

		T_TIMER t;
		t.pTimer = p;
		t.ulSpan = max(m_ulSpanNow,ulTmSpan);
		t.sKey = sKey;

		//CTriggerWorker* pTrigger = new CTriggerWorker(this);
		t.pTrigger = 0;//pTrigger;
		clock_t clkNow = clock();
		unsigned long ulDiff = 0;
		ulDiff = (clkNow - m_clkLastWait) / CLOCKS_PER_SEC;
		ulDiff = min(ulDiff,m_ulSpanNow);
		t.ulLeft = t.ulSpan - (m_ulSpanNow - ulDiff);
		m_mapTimers.insert(make_pair(p,t));
		m_csTimes.Unlock();
	}
	catch(...)
	{
		m_csTimes.Unlock();
		CRLog(E_ERROR,"%s","Unknow Exception CreateTimer");
	}
	return 0;
}

int CGessTimerMgrWin32::DestroyTimer(CGessTimer* p,const string& sKey)
{
	typedef multimap<CGessTimer*,T_TIMER> MMAP_TM;
	typedef MMAP_TM::iterator MMAP_IT;
	typedef pair<MMAP_IT,MMAP_IT> RANGE_TM;
	MMAP_IT it;

	try
	{
		m_csTimes.Lock();
		RANGE_TM range = m_mapTimers.equal_range(p);
		for (it = range.first; it != range.second; )
		{
			//if (0 != (*it).second.pTrigger)
			//	delete (*it).second.pTrigger;

			if ((*it).second.sKey == sKey)
			{
				m_mapTimers.erase(it++);
				break;
			}
			else
			{
				++it;
			}
		}
		m_csTimes.Unlock();
	}
	catch(...)
	{
		m_csTimes.Unlock();
		CRLog(E_ERROR,"%s","Unknow Exception DestroyTimer");
	}
	return 0;
}

string CGessTimerMgrWin32::ToString()
{
	string sRtn = "\r\n";
	multimap<CGessTimer*,T_TIMER>::iterator it;	
	try
	{
		m_csTimes.Lock();
		for (it = m_mapTimers.begin(); it != m_mapTimers.end(); ++it)
		{
			sRtn += "key:";
			sRtn += (*it).second.sKey;
			sRtn += " ulSpan:";
			sRtn += strutils::ToString<unsigned long>((*it).second.ulSpan);
			sRtn += " ulLeft:";
			sRtn += strutils::ToString<unsigned long>((*it).second.ulLeft);
			sRtn += " pTimer:";
			sRtn += strutils::ToString<unsigned long>(reinterpret_cast<unsigned long>((*it).second.pTimer));
			sRtn += "\r\n";
		}
		m_csTimes.Unlock();
	}
	catch(...)
	{
		m_csTimes.Unlock();
		CRLog(E_ERROR,"%s","Unknown exception!");
	}
	return sRtn;
}