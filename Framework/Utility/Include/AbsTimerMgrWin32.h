#pragma once
#include "Gess.h"
#include "GessDateTime.h"
#include "Singleton.h"
#include "WorkThread.h"

enum E_TIMER_DAY_TYPE
{
	E_TIMER_DAY,
	E_TIMER_WEEK_DAY,
	E_TIMER_MONTH_DAY,
	E_TIMER_YEAR_DAY
};

typedef struct tagDateTimer
{
	union
	{
		struct
		{
			int nYear;
			int nMonth;
			int nDay;
		} oDate;
		int nWeekDay;
	};
	CGessTime	oTime;
	E_TIMER_DAY_TYPE	eType;
	CGessAbsTimer* pTimer;
	string sKey;
	HANDLE	hWaitableTimer;
} T_DATE_TIMER;


class CGessTimerMgrWin32;
typedef struct
{
	CGessAbsTimer* pTimer;
	string sKey; 
	CGessTimerMgrWin32* pMgr;
} DAY_TIMER_CONTEX;

class UTIL_CLASS CAbsTimerMgrWin32: public CGessAbsTimerMgrIf,public CWorkThread,public CSingleton< CAbsTimerMgrWin32 >
{
	friend class CSingleton< CAbsTimerMgrWin32 >;
public:
	CAbsTimerMgrWin32(void);
	~CAbsTimerMgrWin32(void);

	virtual int Init();
	virtual int Start();
	virtual void Stop();
	virtual void Finish();

	virtual int CreateDayTimer(CGessAbsTimer* p, CGessTime& oTime, const string& sKey);
	virtual int DestroyDayTimer(CGessAbsTimer* p,const string& sKey);

	virtual int CreateWeekTimer(CGessAbsTimer* p, unsigned int uiWeekDay, CGessTime& oTime,const string& sKey);
	virtual int DestroyWeekTimer(CGessAbsTimer* p,const string& sKey);

	virtual int CreateMonthTimer(CGessAbsTimer* p, unsigned int uiMonthDay, CGessTime& oTime,const string& sKey) {return -1;}
	virtual int CreateMonthTimer(CGessAbsTimer* p, CGessDate& oDate, CGessTime& oTime,const string& sKey) {return -1;}
	virtual int CreateMonthTimer(CGessAbsTimer* p, CGessDateTime& oDateTime, const string& sKey) {return -1;}
	virtual int DestroyMonthTimer(CGessAbsTimer* p,const string& sKey) {return -1;}

	virtual int CreateYearTimer(CGessAbsTimer* p, unsigned int uiYearDay, CGessTime& oTime, const string& sKey) {return -1;}
	virtual int CreateYearTimer(CGessAbsTimer* p, unsigned int uiMonth, unsigned int uiDay, CGessTime& oTime, const string& sKey) {return -1;}
	virtual int CreateYearTimer(CGessAbsTimer* p, CGessDate& oDate, CGessTime& oTime, const string& sKey) {return -1;}
	virtual int CreateYearTimer(CGessAbsTimer* p, CGessDateTime& oDateTime, const string& sKey) {return -1;}
	virtual int DestroyYearTimer(CGessAbsTimer* p,const string& sKey) {return -1;}

private:
	int SetAbsTimer(T_DATE_TIMER* t);
	void HandleCreate();
	void CancelAbsTimer(T_DATE_TIMER* t);
	void HandleCancel();
	int WaitObjs();
	int TimeOut(HANDLE hTimer);

	int CreateTimer(CGessAbsTimer* p, T_DATE_TIMER* t , const string& sKey);
	int DestroyTimer(CGessAbsTimer* p,const string& sKey, E_TIMER_DAY_TYPE eType);
private:
	//定时器创建请求队列
	deque<T_DATE_TIMER*> m_deqCreate;
	//定时器取消请求队列
	deque<T_DATE_TIMER*> m_deqCancel;
	//已成功创建定时器
	multimap<CGessAbsTimer*,T_DATE_TIMER*> m_mapAbsTimers;
	
	HANDLE		m_hEvt;
	HANDLE		m_WaitObj[MAXIMUM_WAIT_OBJECTS];
	CGessMutex	m_csAbsTimes;
	
	int ThreadEntry();
	int End();
};
