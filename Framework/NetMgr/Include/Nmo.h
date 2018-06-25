#ifndef _CNMO_H
#define _CNMO_H

#include "Nm.h"
#include "strutils.h"
#include <vector>
#include <string>
#include <bitset>

using namespace std;
using namespace strutils;

//����ʵʱ���ݽṹ
class NM_CLASS CNMO
{
public:
	CNMO(void){}
	~CNMO(void){}
public:
	string m_sOid;			//��̬MIB��ӦOID
	string m_sOidIns;		//�����OIDʵ��
	string m_sValue;		//����ǰֵ
	int    m_nQuality;		//����ǰ��������
	string m_sTimeStamp;	//����ǰʱ���
};

//�������������Դ
typedef struct tagMibItem
{
	string sOid;				//OID
	string sParentOid;			//���ڵ�OID
	string sAlias;				//�ڵ�OID����
	string sName;				//�ڵ���
	string nRwFlag;				//��д��־
	string nItemType;			//���������
	int nValType;				//ֵ����
} MIB_ITEM_CFG,*PMIB_ITEM_CFG;

//ģ��������������Դ
typedef struct tagAnalogItemCfg
{
	string sOid;				//OID
	string  sUnit;				//��λ
	int uiPrecision;			//��ʾ����
	double  dlThreshold;		//���ݴ洢��ֵ
	int  nsTimeOut;				//���ݴ洢����
} ANALOG_ITEM_CFG,*PANALOG_ITEM_CFG;

//���ּ������������Դ
typedef struct tagDigitalItemCfg
{
	string sOid;				//OID
	string sState;				//״̬
	string sMean;				//����
} DIGITAL_ITEM_CFG,*PDIGITAL_ITEM_CFG;



//MIB���ڵ�
class CMibTreeNode
{
public:
	CMibTreeNode(){}
	virtual ~CMibTreeNode(){}

	string m_sOid;			//MIB���ڵ�OID
	string m_sParentOid;	//���ڵ�OID
	string m_sOidAlias;		//�ڵ�OID����
	int m_nNodeType;		//�ڵ�����
	string m_sName;			//�ڵ���
};

//��������÷�װ��,��MIB��Ҷ�ӽڵ�
class NM_CLASS CItemCfg
{
public:
	CItemCfg(){}
	virtual ~CItemCfg(){}

	string m_sOid;			//��Ҷ�ӽڵ�OID
	string m_sParentOid;	//���ڵ�OID
	string m_sAlias;		//��Ҷ�ӽڵ�OID����
	string m_sName;			//��Ҷ�ӽڵ���
	string m_nRwFlag;		//��д��־
	string m_nItemType;		//����,"0"������ 1ģ����
	int m_nValType;			//ֵ���� 1int�� 2double�� 3string
	bitset<32> m_bsProperty;//����
};

//ģ���ͼ�������÷�װ��
class NM_CLASS CItemAnalogCfg
{
public:
	string OID() const {return m_sOid;}
	int Precision() const {return m_uiPrecision;}
	string Unit() const {return m_sUnit;}
	double Threshold() const {return m_dlThreshold;}
	int TimeOut() const {return m_nsTimeOut;}

	string m_sOid;				//OID
	int m_uiPrecision;			//��ʾ����
	string m_sUnit;				//��λ
	double m_dlThreshold;		//���ݴ洢��ֵ
	int m_nsTimeOut;			//���ݴ洢����
};

//�����ͼ�������÷�װ��
class NM_CLASS CItemDigitalCfg
{
public:
	CItemDigitalCfg(){}
	virtual ~CItemDigitalCfg(){}

	string OID() const {return m_sOid;}
	string State() const {return m_sStateVal;}
	string StateMearning() const {return m_sStateMearn;}

	string m_sOid;				//OID
	string m_sStateVal;			//״̬
	string m_sStateMearn;		//��Ӧ״̬����
};

class NM_CLASS CItemIf
{
public:
	CItemIf(CItemCfg cfg,string sOidIns)
	:m_oItemCfg(cfg),m_sOidIns(sOidIns),m_nQuality(0),m_sTimeStamp(""){}
	virtual ~CItemIf(){}

	virtual void OnDataChange(const string& sOidIns,const string& sVal,int nQuality,const string& sTimeStamp) = 0;
	virtual void NowValue(string& sNowVal) const = 0;
	virtual void LastValue(string& sLastVal) const = 0;

	int Quality() const {return m_nQuality;}
	string TimeStamp() const {return m_sTimeStamp;}

	string Oid() const {return m_oItemCfg.m_sOid;}
	string OidIns() const {return m_sOidIns;}
	string ParentOid() const {return m_oItemCfg.m_sParentOid;}
	string Alias() const {return m_oItemCfg.m_sAlias;}
	string Name() const {return m_oItemCfg.m_sName;}
	string RwFlag() const {return m_oItemCfg.m_nRwFlag;}
	string ItemType() const {return m_oItemCfg.m_nItemType;}
	int ValueType() const {return m_oItemCfg.m_nValType;}
protected:
	CItemCfg m_oItemCfg;		//���������
	string m_sOidIns;			//�����ʵ��OID,����Ϊoid.0 ���¼�ֶ�Ϊoid.key
	int m_nQuality;				//��������
	string m_sTimeStamp;		//ʱ���
};

template <typename T>
class NM_CLASS CItem: public CItemIf
{
public:
	CItem(CItemCfg cfg,string sOidIns)
		:CItemIf(cfg,sOidIns){}
	virtual ~CItem(){}

	//��������ݱ仯����
	//�������:sOidIns,ʵ��oid
	//         tVal,����ֵ
	//         nQuality,������������
	//         sTimeStamp,ʱ���
	virtual void OnDataChange(const string& sOidIns,const string& sVal,int nQuality,const string& sTimeStamp)
	{
		m_tLastVal = m_tValue;
		m_tValue = FromString<T>(sVal);
		m_nQuality = nQuality;
		m_sTimeStamp = sTimeStamp;
	}
	void NowValue(string& sNowVal) const {sNowVal = ToString<T>(m_tValue);}
	void LastValue(string& sLastVal) const {sLastVal = ToString<T>(m_tLastVal);}
	T NowValue() const {return m_tValue;}
	T LastValue() const {return m_tLastVal;}
protected:
	T m_tValue;					//��ǰֵ
	T m_tLastVal;				//�ϴ�ֵ
};

//ģ���ͼ����
template <typename T>
class NM_CLASS CItemAnalog: public CItem<T>
{
public:
	CItemAnalog(const CItemCfg& cfg,const string& sOidIns,const CItemAnalogCfg& oAnalogCfg)
	:CItem<T>(cfg,sOidIns),m_oItemAnalogCfg(oAnalogCfg){}
	virtual ~CItemAnalog(){}

	int Precision() const {return m_oItemAnalogCfg.Precision();}
	string Unit() const {return m_oItemAnalogCfg.Unit();}
	double Threshold() const {return m_oItemAnalogCfg.Threshold();}
	int TimeOut() const {return m_oItemAnalogCfg.TimeOut();}
protected:
	CItemAnalogCfg m_oItemAnalogCfg;
};

//ģ���Ϳ�����
template <typename T>
class NM_CLASS CItemAdjust: public CItemAnalog<T>
{
public:
	CItemAdjust(T tHi,T tLo,const CItemCfg& cfg,const string& sOidIns,const CItemAnalogCfg& oAnalogCfg)
	:m_tValHigh(tHi),m_tValLow(tLo),CItemAnalog<T>(cfg,sOidIns,oAnalogCfg){}
	virtual ~CItemAdjust(){}
	T HiVal(){return m_tValHigh;}
	T LoVal(){return m_tValLow;}
	void SetAdjustVal(T tValDest){m_tValDest = tValDest;}
	void SetPara(const string & sPara){m_sParaDest = sPara;}
private:
	T m_tValHigh;				//���ֵ
	T m_tValLow;				//��Сֵ
	T m_tValDest;				//����ֵ
	string m_sParaDest;			//����
};

//�����ͼ����
template <typename T>
class NM_CLASS CItemDigital: public CItem<T>
{
public:
	CItemDigital(const CItemCfg& cfg,const string& sOidIns,const vector<CItemDigitalCfg>& vItemDigitalCfg)
		:CItem<T>(cfg,sOidIns),m_vItemDigitalCfg(vItemDigitalCfg)
	{
		for (vector<CItemDigitalCfg>::const_iterator itv = vItemDigitalCfg.begin(); itv != vItemDigitalCfg.end(); ++itv)
		{
			T tState = FromString<T>((*itv).m_sStateVal);
			m_vStateVal.push_back(tState);
			m_mapStateMearn[tState] = (*itv).m_sStateMearn;
		}
	}
	virtual ~CItemDigital(){}
	void EnumState(vector<T>& v) const {v = m_vStateVal;}
	string StateMearning(T tVal) const 
	{
		string sRtn("");
		typename map<T,string>::iterator it = m_mapStateMearn.find(tVal);
		if (it != m_mapStateMearn.end())
			sRtn = (*it).second;
		return sRtn;
	}
protected:
	vector<CItemDigitalCfg> m_vItemDigitalCfg;
	vector<T> m_vStateVal;			//����״̬����
	map<T,string> m_mapStateMearn;	//״̬��Ӧ״̬����
};

//�����Ϳ�����
template <typename T>
class NM_CLASS CItemControl: public CItemDigital<T>
{
public:
	CItemControl(const CItemCfg& cfg,const string& sOidIns,const CItemDigitalCfg& oItemDigitalCfg)
		:CItemDigital<T>(cfg,sOidIns,oItemDigitalCfg),m_sParaDest(""){}
	virtual ~CItemControl(){}
	void SetControlState(T tDestVal){m_tStateDest = tDestVal;}
	void SetPara(const string & sPara){m_sParaDest = sPara;}
private:
	T m_tStateDest;
	string m_sParaDest;
};

//
template <typename T>
class NM_CLASS CItemConfig: public CItem<T>
{

private:
	T m_tValDest;
};


#endif