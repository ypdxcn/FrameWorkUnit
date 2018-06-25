#ifndef _HASHTABLE_MSG_H
#define _HASHTABLE_MSG_H

#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include "CommAp.h"

using namespace std;

//----------------------------------------------------------------
//���¼���Զ����ֵ��Ӧ����Ϣ����(��ϸ˵����ο���ر��Ľӿ��ĵ�)
//�����ߣ�����» 2008.11.17
//
class COMMAP_CLASS HashtableMsg
{
private:
	//�洢�ֶμ���
	vector<string>	m_vFields;

	//�洢��¼�ļ���
	vector< map<string,string> > m_vRecords;

	//�ַ�����ʽ
	string  m_sStrValue;
public:

	//----------------------------------------------------------------
	//��������
	~HashtableMsg();

	//----------------------------------------------------------------
	//�޲ι��캯��
	HashtableMsg();

	//----------------------------------------------------------------
	//���ݱ����ַ�������ʵʼ���Ĺ��캯��ѡ��Ȩ
	//���������pStrMsg ��Ҫ���н������ַ���
	HashtableMsg(string& sStrMsg);

	//----------------------------------------------------------------
	//�������ܣ��Ա����ַ������н���
	//���������pStrMsg ��Ҫ���н������ַ���
	//�� �� ֵ����������ɹ�����0�����򷵻�-1;
	int Parse(string& sStrMsg);

	//----------------------------------------------------------------
	//�������ܣ��Ա����ַ������н���
	//�����������
	//�� �� ֵ����
	void clear();

	//----------------------------------------------------------------
	//�������ܣ���ü����еļ�¼����
	//�����������
	//�� �� ֵ����¼��
	size_t size();

	//----------------------------------------------------------------
	//�������ܣ���ü����е��ֶ����Ƽ���
	//�����������
	//�� �� ֵ���ֶ����Ƽ���
	vector<string> GetFields();

	//----------------------------------------------------------------
	//�������ܣ����ָ������λ�õļ�¼
	//���������v_iIndex ����λ��
	//�� �� ֵ��������ڣ��򷵻�ָ������λ�õļ�¼�����򷵻�0
	const map<string,string>& GetMap(size_t v_iIndex);

	//----------------------------------------------------------------
	//�������ܣ�����ǰ����ת��Ϊ�ַ���
	//���������v_sOutMsg ���ڽ����ַ�����ָ��
	//�� �� ֵ����
	void   ToString(string& v_sOutMsg);
	string ToString();

	//----------------------------------------------------------------
	//�������ܣ���ǰ���������ֵ
	//���������v_iIndex ��Ҫ������ӵ�����λ��
	//          v_sKey   ������
	//          v_sValue ֵ
	//�� �� ֵ����
	void AddValue(size_t v_iIndex,string v_sKey,string v_sValue);
	void AddValue(size_t v_iIndex,string v_sKey,const char* pcVal);
	void AddValue(size_t v_iIndex,string v_sKey,char v_chVal);
	void AddValue(size_t v_iIndex,string v_sKey,short v_nVal);
	void AddValue(size_t v_iIndex,string v_sKey,int v_nVal);
	void AddValue(size_t v_iIndex,string v_sKey,long v_lVal);
	void AddValue(size_t v_iIndex,string v_sKey,unsigned char v_uchVal);
	void AddValue(size_t v_iIndex,string v_sKey,unsigned short v_usVal);
	void AddValue(size_t v_iIndex,string v_sKey,unsigned int v_uiVal);
	void AddValue(size_t v_iIndex,string v_sKey,unsigned long v_ulVal);
	void AddValue(size_t v_iIndex,string v_sKey,double v_dlVal);

	//----------------------------------------------------------------
	//�������ܣ����ָ������λ�ü�¼��ֵ
	//���������v_iIndex ��Ҫ���л�ȡ������λ��
	//          v_sKey   ��Ҫ��ȡֵ�ļ�����
	//�� �� ֵ����Ӧ����λ�õ�ֵ
	string   GetString (size_t v_iIndex,string v_sKey);
	char           GetChar   (size_t v_iIndex,string v_sKey);
	short          GetShort  (size_t v_iIndex,string v_sKey);
	int            GetInt    (size_t v_iIndex,string v_sKey);
	long           GetLong   (size_t v_iIndex,string v_sKey);
	unsigned char  GetUChar  (size_t v_iIndex,string v_sKey);
	unsigned short GetUShort (size_t v_iIndex,string v_sKey);
	unsigned int   GetUInt   (size_t v_iIndex,string v_sKey);
	unsigned long  GetULong  (size_t v_iIndex,string v_sKey);
	double         GetDouble (size_t v_iIndex,string v_sKey);
	
};

#endif