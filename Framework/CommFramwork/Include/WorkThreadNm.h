#ifndef _WORKTHREAD_NM_H
#define _WORKTHREAD_NM_H

//#include <pthread.h>
#include "Comm.h"
#include "NetMgr.h"
#include "ThreadInterface.h"
#include "FramworkNmConstant.h"

using namespace FramworkNmConst;

class COMM_CLASS  CWorkThreadNm: public CThreadInferface
{
	friend class CWorkerNm;
private:
	class CWorkerNm: public CNmoModule
	{
	public:
		CWorkerNm():m_pParent(0){}
		virtual ~CWorkerNm(){}
		void Bind(CWorkThreadNm* pParent){m_pParent = pParent;}
		//������ѯ�ӿ�
		int Query(CNMO& oNmo) const
		{
			if (0 == m_pParent)
				return -1;
			return m_pParent->ThreadQuery(oNmo);
		}

		//������ѯ�ӿ�
		int Query(vector< CNMO > & vNmo) const
		{
			if (0 == m_pParent)
				return -1;
			return m_pParent->ThreadQuery(vNmo);
		}

		//���ƽӿ�
		int Operate(const string &sOid, int nflag, const string &sDstValue, const string &sParamer) {return 0;}
	private:
		CWorkThreadNm* m_pParent;
	};
protected:
	//������ѯ�ӿ�
	virtual int ThreadQuery(CNMO& oNmo) const;

	//������ѯ�ӿ�
	virtual int ThreadQuery(vector< CNMO > & vNmo) const;
public:
    CWorkThreadNm ();
    virtual ~CWorkThreadNm();
	
	int BeginThread ();
protected:
	void OnStart();
	void OnStop();

	//�������߳�״̬�Ƿ���Ҫ������
	virtual bool IsNetManaged(string& sKeyName) = 0;
	unsigned int ID(){return m_uiKey;}

private:
	int		m_blNetManaged;
	unsigned int   m_uiKey;	
	string		m_sKey;
	string		m_sMibStateIns;

	static CGessMutex m_mutexSID;
	static unsigned int m_uiSID;

	CWorkerNm m_oWorkerNm;
}; 
#endif