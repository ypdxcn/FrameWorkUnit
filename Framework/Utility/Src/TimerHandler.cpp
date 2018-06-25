#include "TimerHandler.h"

CTimerImpl::CTimerImpl(void)
:m_pParent(0)
{
}

CTimerImpl::~CTimerImpl(void)
{
}

void CTimerImpl::Bind(CTimerHandler* p) 
{
	m_pParent=p;
}

int CTimerImpl::TimeOut(const string& ulKey,unsigned long& ulTmSpan)
{
	if (0 != m_pParent)
		return m_pParent->OnTimeout(ulKey,ulTmSpan);
	return -1;
}

void CTimerImpl::TimerCanceled(const string& ulKey)
{
}