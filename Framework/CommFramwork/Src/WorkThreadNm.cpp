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

#include "WorkThreadNm.h"

unsigned int CWorkThreadNm::m_uiSID = 0;
CGessMutex CWorkThreadNm::m_mutexSID;

CWorkThreadNm::CWorkThreadNm()
:m_blNetManaged(false)
,m_uiKey(0)
,m_sKey("")
,m_sMibStateIns(gc_sThreadState)
{
	m_mutexSID.Lock();
	m_uiKey = ++m_uiSID;
	m_mutexSID.Unlock();
}

CWorkThreadNm::~CWorkThreadNm() 
{
    //if (m_bRunning) 
    //    EndThread();

}

int CWorkThreadNm::BeginThread ( )
{
    if (IsWorking()) 
        return 0;

	m_oWorkerNm.Bind(this);
	m_blNetManaged = IsNetManaged(m_sKey);
	if (m_blNetManaged)
		m_sMibStateIns = gc_sThreadState + "." + m_sKey + "." + ToString<unsigned int>(m_uiKey);
	
	return CThreadInferface::BeginThread();	
}

void CWorkThreadNm::OnStart()
{
	//�����Ҫ��������ע�� �ϱ� 
	if (m_blNetManaged)
	{
		CNMO oNmo;
		oNmo.m_sOid = gc_sThreadState;
		oNmo.m_sOidIns = m_sMibStateIns;
		oNmo.m_sValue = ToString<int>(gc_nThreadRun);
		oNmo.m_nQuality = gc_nQuolityGood;
		oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();

		CNetMgr::Instance()->Register(&m_oWorkerNm,oNmo.m_sOid,oNmo.m_sOidIns);
		CNetMgr::Instance()->Report(oNmo);
	}
}

void CWorkThreadNm::OnStop()
{
	//�����Ҫ���������ϱ� ע��
	if (m_blNetManaged)
	{
		CNMO oNmo;
		oNmo.m_sOid = gc_sThreadState;
		oNmo.m_sOidIns = m_sMibStateIns;
		if (!m_bEndThread)
		{//�쳣�˳�ע��ǰ�ϱ��Ҵ����澯,����ֱ��ע��
			oNmo.m_sValue = ToString<int>(gc_nThreadQuit);
			oNmo.m_nQuality = gc_nQuolityGood;
			oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
			CNetMgr::Instance()->Report(oNmo);
		}
		CNetMgr::Instance()->UnRegisterNmo(&m_oWorkerNm,oNmo.m_sOidIns);
		CNetMgr::Instance()->UnRegisterModule(&m_oWorkerNm);
	}

}

//������ѯ�ӿ�
int CWorkThreadNm::ThreadQuery(CNMO& oNmo) const
{
	if (oNmo.m_sOidIns == m_sMibStateIns)
	{
		oNmo.m_sValue = ToString<int>(!m_bEndThread?gc_nThreadRun:gc_nThreadQuit);
		oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
		oNmo.m_nQuality = gc_nQuolityGood;
	}
	return 0;
}

//������ѯ�ӿ�
int CWorkThreadNm::ThreadQuery(vector< CNMO > & vNmo) const
{
	for (vector< CNMO >::iterator it = vNmo.begin(); it != vNmo.end(); ++it)
	{
		ThreadQuery(*it);
	}
	return 0;
}