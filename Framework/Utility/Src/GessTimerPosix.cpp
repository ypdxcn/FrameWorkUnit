#include "GessTimerMgrPosix.h"


unsigned long CGessTimerMgrImp::Min(){return 1UL;}

int CGessTimerMgrImp::TimerWait(unsigned long ulSpanNow)
{
	struct timespec tInterval;
	tInterval.tv_sec = time(0) + ulSpanNow;
	tInterval.tv_nsec = 0;
	m_condTimerSignal.Lock();
	int nRtn = m_condTimerSignal.TimeWaitAbs(tInterval);
	m_condTimerSignal.Unlock();

	if (ETIMEDOUT == nRtn)
		nRtn = 0;

	return nRtn;
}

int CGessTimerMgrImp::End()
{
	//Ӧ�ò㶨ʱ�������޷�֪���Ƿ�����,�ݲ�ͬ��wait
	return 0;
}