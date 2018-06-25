#ifndef _GESS_TIMER_HANDLER_H
#define _GESS_TIMER_HANDLER_H
#include "Gess.h"

//定时器处理器
class UTIL_CLASS CTimerHandler
{
public:
	virtual int OnTimeout(const string& ulKey,unsigned long& ulTmSpan) = 0;
};

//定时器
class UTIL_CLASS CTimerImpl : public CGessTimer
{
public:
	CTimerImpl();
	virtual ~CTimerImpl();
	void Bind(CTimerHandler* p);
	int TimeOut(const string& ulKey,unsigned long& ulTmSpan);
	void TimerCanceled(const string& ulKey);
private:
	CTimerHandler* m_pParent;
};
#endif