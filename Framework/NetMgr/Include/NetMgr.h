#ifndef _NET_MGR_H
#define _NET_MGR_H

#include "Nmo.h"
#include "Condition.h"
#include "Singleton.h"
#include "Nm.h"
#include "GessTimerMgrPosix.h"
#include <deque>
#include <vector>
#include <map>


using namespace std;


//�������ýӿ� �����ܷ���ʹ����ʵ��,�ṩ���MIB��̬������Ϣ�ͽ���MIB��̬��Ϣ
class NM_CLASS CNmConfigIf
{
public:
	//OIDע��֪ͨ
	virtual void OnItemRegister(const string& sOid,const string& sOidIns) = 0;
	//OIDע��֪ͨ
	virtual void OnItemUnRegister(const string& sOid,const string& sOidIns) = 0;
};

//����֪ͨ�ص��ӿ� �����ܷ���ʹ����ʵ��
class NM_CLASS CNmNotifyIf
{
public:
	//ʵʱ����֪ͨ
	virtual int OnDataChange(const CNMO& oNmo) = 0;
	//�澯֪ͨ
	virtual int OnAlmNotify(const CAlarm& alm) = 0;
	//�¼�֪ͨ
	virtual int OnEvtNotify(const CEventSimple& evt) = 0;
};


//���ܱ��ܽӿ�,�ɱ�����ģ��ʵ��
class NM_CLASS CNmoModule
{
public:
	//������ѯ�ӿ�
	virtual int Query(CNMO& vNmo) const = 0;
	//������ѯ�ӿ�
	virtual int Query(vector< CNMO > & vNmo) const = 0;	
	//���ƽӿ�
	virtual int Operate(const string &sOid, int nflag, const string &sDstValue, const string &sParamer) = 0;
};

//���ܷ���ӿ�
class NM_CLASS  CNetMgrIf
{
public:
	CNetMgrIf(){}
	virtual ~CNetMgrIf(){}
public://���½ӿں����ṩ��������ģ���������ע��/ע��/�����ϱ�/�¼��ϱ�
	//�����ϱ��ӿ�
	virtual int Report(const CNMO &oNmo) = 0;
	//�����ϱ��ӿ�
	virtual int Report(const vector<CNMO> &vNmo) = 0;
	//����ע��ӿ� pNmoModule����ģ��ӿ� �����OID��OIDʵ����
	virtual int Register(CNmoModule* pNmoModule,const string& sOid,const string& sOidIns) = 0;
	//����ע��ӿ�
	virtual int Register(CNmoModule* pNmoModule , const vector<pair<string,string> >&vpOid) = 0;
	//ע��OID�ӿ�
	virtual int UnRegisterNmo(CNmoModule* pNmo, const string& sOidIns) = 0;
	//����ע��OID�ӿ�
	virtual int UnRegisterNmo(CNmoModule* pNmo, const vector<string>& vOidIns) = 0;
	//ע������ģ��ӿ�
	virtual int UnRegisterModule(CNmoModule* pNmo) = 0;
	//�ϱ��¼�
	virtual int OnEvtNotify(const CEventSimple& evt) = 0;	
public://���½ӿں����ṩ�����ܷ���ʹ���߼�Ӧ�ò��ѯ�Ϳ��Ƶ���
	//��ѯʵʱ���ݽӿ�
	virtual int QueryItem(CNMO& vNmo) const = 0;
	virtual int QueryItem(vector<CNMO> &vtCnmo, const string& sRwFlag, const string& sItemType) const = 0;

	//���ƽӿ�
	virtual int OperateItem(const string &sOid, int nflag, const string &sDstValue, const string &sParamer) = 0;
	
	//��ѯ�¼��ӿ�
	virtual int QueryEvtSimple(vector<CEventSimple>& vEvt) const = 0;
	//��ѯ�¼��ӿ�
	virtual int QueryEvtTrack(vector<CEventTrack>& vEvt) const = 0;
	//��ѯ�澯�ӿ�
	virtual int QueryAlarm(vector<CAlarm>& vAlm) const = 0;

	//���ݼ����OID��ѯ��ӦOIDʵ��
	virtual int QueryItemCfg(const string& sOid, vector<string>& vOidIns) const = 0;
public://�����Ƕ��Ľӿ�
	virtual int Subscribe(CNmNotifyIf* p) = 0;
	virtual int UnSubscribe(CNmNotifyIf* p) = 0;
public://���½ӿں����ṩ��Ӧ�ò��ʼ����������� ��ʼ���ӿڱ�����ʹ���������нӿ�֮ǰ����
	virtual int NmInit(CNmConfigIf* pNmCfgIf,const string& sTblFilePrefix) = 0;
	//���ܽ�������
	virtual void NmFinish() = 0;
};

//
class NM_CLASS CNetMgr: public CNetMgrIf,public CSingleton< CNetMgr >
{
	friend class CSingleton< CNetMgr >;
private:
	class CAlmInterfaceImp: public CConditionCallBack
	{
	public:
		CAlmInterfaceImp():m_pParent(0){}
		virtual ~CAlmInterfaceImp(){}
		void Bind(CNetMgr* p){m_pParent=p;}
		int OnAlmNotify(const CAlarm& oAlm)
		{
			if (0 != m_pParent) 
				return m_pParent->OnAlmNotify(oAlm);		
			return 0;
		}
	private:
		CNetMgr* m_pParent;
	};

	class CAlmConfirmTimer : public CGessTimer
	{
	public:
		CAlmConfirmTimer(){}
		virtual ~CAlmConfirmTimer(){}
		void Bind(CNetMgr* p)
		{
			m_pParent=p;
		}
		int TimeOut(const string& ulKey,unsigned long& ulTmSpan)
		{
			if (0 != m_pParent)
				return m_pParent->OnAlmConfirmTimeout();
			return -1;
		}
		void TimerCanceled(const string& ulKey)
		{
		}
	private:
		CNetMgr* m_pParent;
	};
protected:
	CNetMgr();
	virtual ~CNetMgr();
public://���½ӿں����ṩ��Ӧ�ò��ʼ����������� ��ʼ���ӿڱ�����ʹ���������нӿ�֮ǰ����
	int NmInit(CNmConfigIf* pNmCfgIf,const string& sTblFilePrefix);
	//���ܽ�������
	void NmFinish();	
public://���½ӿں����ṩ��������ģ��ע��/ע��/�ϱ�����	
	//�����ϱ��ӿ�
	int Report(const vector<CNMO> &vNmo);
	//�����ϱ��ӿ�
	int Report(const CNMO &oNmo);
	//����ע��ӿ�
	int Register(CNmoModule* pNmoModule, const vector<pair<string,string> >&vpOid);
	//����ע��ӿ�
	int Register(CNmoModule* pNmoModule,const string& sOid,const string& sOidIns);
	//ע��OID�ӿ�
	int UnRegisterNmo(CNmoModule* pNmo, const string& sOidIns);
	//����ע��OID�ӿ�
	int UnRegisterNmo(CNmoModule* pNmoModule, const vector<string> &vOid);
	//ע������ģ��ӿ�
	int UnRegisterModule(CNmoModule* pNmoModule);
	//�ϱ��¼�
	virtual int OnEvtNotify(const CEventSimple& evt);
public://���½ӿں����ṩ��Ӧ�ò��ѯ�Ϳ��Ƶ���
	//��ѯʵʱ���ݽӿ�
	int QueryItem(CNMO& vNmo) const;
	int QueryItem(vector<CNMO> &vtCnmo, const string& sRwFlag, const string& sItemType) const;

	//���ƽӿ�
	int OperateItem(const string &sOidIns, int nflag, const string &sDstValue, const string &sParamer);

	//��ѯ�¼��ӿ�
	int QueryEvtSimple(vector<CEventSimple>& vEvt) const;
	//��ѯ�¼��ӿ�
	int QueryEvtTrack(vector<CEventTrack>& vEvt) const;
	//��ѯ�澯�ӿ�
	int QueryAlarm(vector<CAlarm>& vAlm) const;

	//��ѯ�����ʵ����ӦOID/OIDʵ����
	int QueryItemCfg(const string& sOid, vector<string>& vOidIns) const;
public:
	int Subscribe(CNmNotifyIf* p);
	int UnSubscribe(CNmNotifyIf* p);
protected:
	virtual int OnAlmNotify(const CAlarm& oAlm);
private:
	CAlmInterfaceImp m_oAlmIf;
	CAlmConfirmTimer m_oTimer;
private:
	void CondInsComb(vector< vector<CItemIf*> >::iterator itPos,vector< vector<CItemIf*> >::iterator itEnd,vector< vector<CItemIf*> >& vResult);
	void CreateCondition();
	void CreateCondIns(int nCondID,vector<CSubCondCfg>& vSubCondCfg);
	int UnRegOidCond(CNmoModule* pNmo, const string& sOidIns);

	//��ʱ���ص��ӿ�
	int OnAlmConfirmTimeout();
protected:
	//MIB���ڵ��ϵ��
	map<string,CMibTreeNode> m_mapMibTree;
	//��������ñ�
	map<string,CItemCfg> m_mapMibItemCfg;
	//ģ���ͼ�������ñ�
	map<string,CItemAnalogCfg> m_mapMibItemAnalogCfg;
	//�������ͼ�������ñ�
	map<string,vector< CItemDigitalCfg> > m_mapMibItemDigitalCfg;
	//���������ڴ�ṹ
	map<int,CConditionCfg > m_mapCondCfg;
	//����/�����������ڴ�ṹ
	map<int,vector< CSubCondCfg > > m_mapSubCondCfg;

	//OIDʵ����Ӧ������ KEYΪʵ��OID
	//1.1.1.1.0    CCondition1
	//             CCondition2
	//1.1.1.1.1    CCondition2
	//........................
	map<string,vector<CCondition*> > m_mapSrc2Cond;

	//����ʵ��ӳ��� ����ʵ��KEY(CondID+OIDʵ����),����ʵ��
	//1:1.1.1.1.0,1.1.1.2.0    CCondition1
	map<string,CCondition*> m_mapCond;
	
	class CNmoInf
	{
	public:
		CItemIf* m_pItem;			//�����ʵ��
		CNmoModule* m_pNmoModule;	//������ģ��
	};

	//������ģ�鼯��
	vector<CNmoModule*> m_vNmoModule;
	//OIDʵ���������ӳ���
	map<string,CNmoInf> m_mapItems;

	//��ȷ�ϵĸ澯
	map<string, CAlarm>	m_mapAlmNoConfirm;
	//δ�����ĸ澯��
	vector<CAlarm> m_vAlarmTbl;
	//���¼���
	vector<CEventSimple> m_vEvtSimpleTbl;
	//�ɸ������¼���
	vector<CEventTrack> m_vEvtTrackTbl;
private:
	mutable CGessMutex  m_mutexNetMgr;

	//�������ýӿ�
	CNmConfigIf* m_pNmCfgIf;

	//���Ľӿ�
	vector<CNmNotifyIf*> m_vNotify;
	CGessMutex  m_MutexSubscrib;
};



#endif
