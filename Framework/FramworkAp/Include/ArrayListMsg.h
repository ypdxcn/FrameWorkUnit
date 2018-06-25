#ifndef _ARRAY_LIST_MSG_H
#define _ARRAY_LIST_MSG_H

#include <cassert>
#include <string>
#include <sstream>
#include <iomanip> 
#include <vector>
#include "CommAp.h"
#include "Constant.h"

using namespace std;
using namespace Const;

///////////////////////////////////////////////////////////////////////////////
//���ݳ���»���׷��������޸�
///////////////////////////////////////////////////////////////////////////////
class COMMAP_CLASS ArrayListMsg
{
	friend std::ostream& operator<<(std::ostream&, const ArrayListMsg&);
	friend std::istream& operator>>(std::istream&, ArrayListMsg&);
private:
	typedef enum 
	{
		E_STRING,
		E_ARRAYLIST
	} eMsgType;

	typedef struct tagPosInfo
	{
		eMsgType eType;
		size_t nPos;
	} POS_INFO;

public:
	ArrayListMsg();
	~ArrayListMsg();	
	//----------------------------------------------------------------
	// �����ַ������г�ʼ�������Ĺ��캯��
	// ��������� pStrMsg  ��Ҫ���н������ַ���ָ��
	ArrayListMsg(const string& sStrMsg,int nLevel = 0);

	ArrayListMsg(const ArrayListMsg& oCopy);
	void operator=(const ArrayListMsg& oCopy);
	
	//----------------------------------------------------------------
	//�������ܣ������ַ���
	//��������� pStrMsg  ��Ҫ���н������ַ���ָ��
	//�� �� ֵ�� 0���ɹ�������ʧ��
	int Parse(const string& sStrMsg,int v_iLevel = 0);

	//----------------------------------------------------------------
	//�������ܣ���õ�ǰ�����е�Ԫ�ظ���
	//�����������
	//�� �� ֵ�������е�Ԫ�ظ���
	size_t size() const;

	//��������
	size_t Capacity() const;

	//������������
	void Reserve(size_t nSize);

	//----------------------------------------------------------------
	//�������ܣ�������ת��Ϊ�ַ���
	//������������ڽ��յ��ַ���ָ��
	//�� �� ֵ����
	void   ToString(string& v_sOutMsg) const;
	string ToString() const;

	void clear();

	//----------------------------------------------------------------
	//�������ܣ���ǰ���������ֵ
	//���������tValue ��Ҫ��ӵ��ַ���ֵ
	//�� �� ֵ����
	template <typename T>
	void AddValue(T tValue)
	{
		POS_INFO stInfo;
		stInfo.eType = E_STRING;
		stInfo.nPos = m_sStrValues.size();
		m_vecPosInfo.push_back(stInfo);

		std::stringstream ss;
		ss << setiosflags(ios::fixed) << setprecision(gc_ucPrecision) << tValue;
		m_sStrValues.push_back(ss.str());
	}

	void AddValue(ArrayListMsg& aRec);

	//----------------------------------------------------------------
	//�������ܣ�����������Ϊ v_iIndex λ�õ��ַ���Ԫ��
	//�����������Ҫ��ȡλ�õ��������
	//�� �� ֵ�����ָ������λ����ֵ���򷵻���Ӧָ�룬���򷵻�0
	template <typename T>
	T GetValue(size_t nIndex) const
	{
		assert(nIndex>=0 && nIndex < m_vecPosInfo.size() && m_vecPosInfo[nIndex].eType == E_STRING);
		assert(m_vecPosInfo[nIndex].nPos < m_sStrValues.size());

		std::stringstream ss;
		ss << m_sStrValues[m_vecPosInfo[nIndex].nPos];

		T tVal;
		ss >> tVal;
		return tVal;
	}

	ArrayListMsg GetValue(size_t nIndex) const;
	void GetValue(size_t nIndex,ArrayListMsg& aRec) const;
	//----------------------------------------------------------------
	//�������ܣ���ǰ���������ֵ
	//���������v_iIndex ��Ҫ������ӵ��Ӽ�������
	//          v_sValue ��Ҫ��ӵ��ַ���ֵ
	//�� �� ֵ����
	template <typename T>
	void AddValue(size_t nIndex,T tValue)
	{
		assert(nIndex>=0 && nIndex < m_vecPosInfo.size());
		assert(m_vecPosInfo[nIndex].eType == E_ARRAYLIST && m_vecPosInfo[nIndex].nPos < m_aListValues.size());

		std::stringstream ss;
		ss << tValue;
		m_aListValues[m_vecPosInfo[nIndex].nPos].AddValue(ss.str());
	}

	void AddValue(size_t nIndex,ArrayListMsg& aRec);
	//----------------------------------------------------------------
	//�������ܣ���ü�¼������ΪnRecIndex��Ԫ������nEleIndexλ�õ�ֵ
	//���������nRecIndex  ��¼����
	//          nEleIndex Ԫ������
	//�� �� ֵ��
	template <typename T>
	T GetValue(size_t nRecIndex,size_t nEleIndex)  const
	{
		assert(nRecIndex>=0 && nRecIndex < m_vecPosInfo.size());
		assert(m_vecPosInfo[nRecIndex].eType == E_ARRAYLIST && m_vecPosInfo[nRecIndex].nPos < m_aListValues.size());

		T tVal = m_aListValues[m_vecPosInfo[nRecIndex].nPos].GetValue<T>(nEleIndex);
		return tVal;
	}

	ArrayListMsg GetValue(size_t nRecIndex,size_t nEleIndex) const;
private:
	void ToString(string& sOutMsg,int nIndex ) const;

	//���ڱ���Ԫ��Ϊ�ַ����ļ���
	vector<string>        m_sStrValues;
	//���ڱ���Ԫ��ΪArrayListMsg����ļ���     �ر�˵���������������У�ֻ����һ��������Ԫ������
	vector<ArrayListMsg> m_aListValues;
	//�ַ�����ʽ
	string                m_sStrValue;

	int m_nLevel;
	vector<POS_INFO>	m_vecPosInfo;

};

#endif