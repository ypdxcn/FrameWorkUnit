/******************************************************************************
��    Ȩ:��������������ϵͳ���޹�˾.
ģ������:WorkThread.cpp
������	:��ΰ
��������:2008.07.22
��    ��:1.0				
ģ������:��װ�߳�api
��Ҫ����:BeginThread() �����߳�
         EndThread()  ��ֹ�߳�
		 ThreadEntry() ������ʵ�ֵ��躯��
�޸ļ�¼:
******************************************************************************/

#include "ThreadInterface.h"


CThreadInferface::CThreadInferface()
:m_bRunning(false)
,m_bEndThread(false)
{
}

CThreadInferface::~CThreadInferface() 
{
    //if (m_bRunning) 
    //    EndThread();

}

int CThreadInferface::BeginThread ( )
{
    if (m_bRunning) 
        return 0;

    m_bEndThread = false;
	m_bRunning = true;
	
	return pthread_create(&m_tThread, 0, InvokeThreadEntry, this);
	
}

void CThreadInferface::EndThread ()
{
    if (m_bRunning)
    {
        m_bEndThread = true;    // Notify thread to die	

		End();
        m_bRunning = false;
    }
}

void * CThreadInferface::InvokeThreadEntry(void * pArg)
{
    CThreadInferface *pWorkThread = reinterpret_cast<CThreadInferface*>(pArg);

	if( pWorkThread )
	{
		pWorkThread->OnStart();

		//�̺߳���
		int uRtn = pWorkThread->ThreadEntry();

		pWorkThread->OnStop();
	}

	return 0;
}

void CThreadInferface::Wait()
{
	pthread_t tid = pthread_self();
	if ( 0 == pthread_equal(m_tThread,tid))
		pthread_join(m_tThread, 0);
}