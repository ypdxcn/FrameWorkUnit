#ifndef _GESS_TIMER_WIN32_H_
#define _GESS_TIMER_WIN32_H_ 
#include "GessTimerMgr.h"
#include "Gess.h"
#include "Singleton.h"

using namespace std;

class UTIL_CLASS CGessTimerMgrWin32: public CGessTimerMgrIf,public CWorkThread,public CSingleton< CGessTimerMgrWin32 >
{
	friend class CSingleton< CGessTimerMgrWin32 >;
public:
	virtual int Init(unsigned long ulTmSpan = 1);
	virtual int Start();
	virtual void Stop();
	virtual void Finish();
	
	virtual int CreateTimer(CGessTimer* p, unsigned long ulTmSpan,const string& sKey);
    virtual int DestroyTimer(CGessTimer* p,const string& sKey);
	
	string ToString();
protected:
	CGessTimerMgrWin32();
	virtual ~CGessTimerMgrWin32();
    
protected:
	//当前调度间隔
	unsigned long m_ulSpanNow;
	//精度	
    unsigned long m_ulMin; 
	//最近定时调度开始时刻
	clock_t		m_clkLastWait;

	void OnTimeout();
	int End();
private:
	//定时器
	multimap<CGessTimer*,T_TIMER> m_mapTimers;
	CGessMutex					m_csTimes;

	HANDLE		m_hWaitTimer;
	int			m_nCancel;
	long  m_lWakeMs;

	int ThreadEntry();
	static void CALLBACK TimerAPCProc(LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue);
};

#endif