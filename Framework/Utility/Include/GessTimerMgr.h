#ifndef _GESS_TIMER_MGR_H_
#define _GESS_TIMER_MGR_H_ 

#include "WorkThread.h"
#include "Gess.h"

using namespace std;

class CTriggerWorker;
typedef struct tagTimer
{
	CGessTimer* pTimer;
	unsigned long ulSpan;
	unsigned long ulLeft;
	string sKey;
	CTriggerWorker* pTrigger;
} T_TIMER;

class UTIL_CLASS CGessTimerMgr: public CGessTimerMgrIf,public CWorkThread
{
	friend class CTriggerWorker;
public:
	CGessTimerMgr();
	virtual ~CGessTimerMgr();

    virtual int Init(unsigned long ulTmSpan);
	virtual int Start();
	virtual void Stop();
	virtual void Finish();
    
    virtual int CreateTimer(CGessTimer* p, unsigned long ulTmSpan,const string& sKey);
    virtual int DestroyTimer(CGessTimer* p,const string& sKey);
	
	string ToString();
protected:
	//��ǰ���ȼ��
	unsigned long m_ulSpanNow;

	//��ȡ������
    virtual unsigned long Min() = 0;
	//��ʱ��λ���
	virtual int TimerWait(unsigned long ulSpanNow) = 0;
    void OnTimeout();
private:
	int ThreadEntry();
	void UpdateInterval(CGessTimer* pTimer,const string& sKey, unsigned long ulSpan);
private:
	//����
    unsigned long m_ulMin;    

	//�����ʱ���ȿ�ʼʱ��
	clock_t		m_clkLastWait;
	//�ۼ����
	clock_t		m_clkTotalDiff;

	//��ʱ��
	multimap<CGessTimer*,T_TIMER> m_mapTimers;
	CGessMutex					m_csTimes;
};


class UTIL_CLASS CTriggerWorker:public CWorkThread
{
public:
	CTriggerWorker(CGessTimerMgr* p)
	{
		m_Parent = p;
		memset(&m_stTimer,0x00,sizeof(T_TIMER));
	}
	~CTriggerWorker(){}
	void Fire(T_TIMER & stTimer)
	{
		m_stTimer = stTimer;
		BeginThread();
	}
	
	int ThreadEntry()
	{
		if (0 != m_stTimer.pTimer)
		{
			unsigned long ulTmp = m_stTimer.ulSpan;
			int nRtn = m_stTimer.pTimer->TimeOut(m_stTimer.sKey,m_stTimer.ulSpan);
			if (0 != m_Parent)
			{
				if (0 != nRtn)
				{
					//m_Parent->DestroyTimer(m_stTimer.pTimer,m_stTimer.sKey);
				}
				else if (ulTmp != m_stTimer.ulSpan)
				{
					m_Parent->UpdateInterval(m_stTimer.pTimer,m_stTimer.sKey, m_stTimer.ulSpan);
				}
			}
		}

		EndThread();
		return 0;
	}
	int End() {return 0;}
private:
	T_TIMER m_stTimer;
	CGessTimerMgr* m_Parent;
};

#endif