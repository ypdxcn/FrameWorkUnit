#include <cassert>
#include "ApConstant.h"
#include "HashtableMsg.h"
#include "strutils.h"

using namespace std;


//----------------------------------------------------------------
//��������
HashtableMsg::~HashtableMsg()
{
	clear();
}

//----------------------------------------------------------------
//�޲ι��캯��
HashtableMsg::HashtableMsg()
{

}

//----------------------------------------------------------------
//���ݱ����ַ�������ʵʼ���Ĺ��캯��ѡ��Ȩ
//���������pStrMsg ��Ҫ���н������ַ���
HashtableMsg::HashtableMsg(string& sStrMsg)
{
	Parse(sStrMsg);
}

//----------------------------------------------------------------
//�������ܣ��Ա����ַ������н���
//�����������
//�� �� ֵ����
void HashtableMsg::clear()
{
	m_vFields.clear();
	m_vRecords.clear();
	m_sStrValue.clear();
}

//----------------------------------------------------------------
//�������ܣ��Ա����ַ������н���
//���������pStrMsg ��Ҫ���н������ַ���
//�� �� ֵ����������ɹ�����0�����򷵻�-1;
int HashtableMsg::Parse(string & sStrMsg)
{
	vector<string> vFldAndRecs;
	vFldAndRecs = strutils::explode(ApConst::SEPARATOR_RECORD[0],sStrMsg);

	if ( vFldAndRecs.size() == 2 )
	{
		m_vFields = strutils::explode(ApConst::SEPARATOR_RECORD[1], vFldAndRecs[0]);

		vector<string> vRecords;
		vRecords = strutils::explode(ApConst::SEPARATOR_RECORD[1], vFldAndRecs[1]);

		if ( vRecords.size() > 0 )
		{
			for ( size_t i = 0 ; i < vRecords.size() ; i++ )
			{
				vector<string> vRecValue = strutils::explode(ApConst::SEPARATOR_RECORD[2], vRecords[i]);

				if ( m_vFields.size() <= vRecValue.size() )
				{
					map<string,string> mapRec;

					for ( size_t j = 0 ; j < m_vFields.size() ; j++ )
					{						
						mapRec.insert(map<string,string>::value_type(m_vFields[j],vRecValue[j]));
					}

					m_vRecords.push_back(mapRec);
				}
				else
				{
					map<string,string> mapRec;

					size_t j = 0;
					for (;j < vRecValue.size(); j++ )
					{						
						mapRec.insert(map<string,string>::value_type(m_vFields[j],vRecValue[j]));
					}

					for (;j < m_vFields.size() ; j++)
					{
						mapRec.insert(map<string,string>::value_type(m_vFields[j],""));
					}

					m_vRecords.push_back(mapRec);
				}
			}
		
			m_sStrValue = sStrMsg;
		}
	}

	return 0;
}

//----------------------------------------------------------------
//�������ܣ���ü����еļ�¼����
//�����������
//�� �� ֵ����¼��
size_t HashtableMsg::size()
{
	return m_vRecords.size();
}

vector<string> HashtableMsg::GetFields()
{
	return m_vFields;
}

//----------------------------------------------------------------
//�������ܣ�����ǰ����ת��Ϊ�ַ���
//���������v_sOutMsg ���ڽ����ַ�����ָ��
//�� �� ֵ����
void HashtableMsg::ToString(string& v_sOutMsg)
{
	v_sOutMsg.clear();

	if ( m_vRecords.size() > 0 )
	{
		string sKey;
		for (vector<string>::iterator itKey = m_vFields.begin() ; itKey != m_vFields.end(); ++itKey)
		{
			sKey += *itKey;
			sKey += ApConst::SEPARATOR_RECORD[1];
		}
		
		v_sOutMsg += sKey;
		v_sOutMsg += ApConst::SEPARATOR_RECORD[0];

		for ( size_t i = 0 ; i < m_vRecords.size() ; i++ )
		{
			for ( size_t j = 0 ; j < m_vFields.size() ; j++ )
			{
				v_sOutMsg += m_vRecords[i].find(m_vFields[j])->second;
				v_sOutMsg += ApConst::SEPARATOR_RECORD[2];
			}
			v_sOutMsg += ApConst::SEPARATOR_RECORD[1];
		}

		v_sOutMsg += ApConst::SEPARATOR_RECORD[0];
	}
}

string HashtableMsg::ToString()
{
	m_sStrValue.clear();
	ToString(m_sStrValue);
	return m_sStrValue;
}

//----------------------------------------------------------------
//�������ܣ����ָ������λ�õļ�¼
//���������v_iIndex ����λ��
//�� �� ֵ��������ڣ��򷵻�ָ������λ�õļ�¼�����򷵻�0
const map<string,string>& HashtableMsg::GetMap(size_t v_iIndex)
{
	assert(v_iIndex >= 0 && v_iIndex < m_vRecords.size() );
	return m_vRecords[v_iIndex];
}


//----------------------------------------------------------------
//�������ܣ���ǰ���������ֵ
//���������v_iIndex ��Ҫ������ӵ�����λ��
//          v_sKey   ������
//          v_sValue ֵ
//�� �� ֵ����
void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,string v_sValue)
{
	assert(v_iIndex >= 0 && v_iIndex <= m_vRecords.size() );
	if ( v_iIndex == m_vRecords.size() )
	{
		map<string,string> mapRec;
		mapRec.insert(map<string,string>::value_type(v_sKey,v_sValue));
		m_vRecords.push_back(mapRec);
	}
	else
	{
		m_vRecords[v_iIndex].insert(map<string,string>::value_type(v_sKey,v_sValue));
	}
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,const char* pcVal)
{
	assert(v_iIndex >= 0 && v_iIndex <= m_vRecords.size() );
	string sValue = pcVal;

	if ( v_iIndex == m_vRecords.size() )
	{
		map<string,string> mapRec;
		mapRec.insert(map<string,string>::value_type(v_sKey,sValue));
		m_vRecords.push_back(mapRec);
	}
	else
	{
		m_vRecords[v_iIndex].insert(map<string,string>::value_type(v_sKey,sValue));
	}
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,char v_chVal)
{
	string sVal;
	sVal.append(1,v_chVal);
	AddValue(v_iIndex,v_sKey,sVal);
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,short v_sVal)
{
	AddValue(v_iIndex,v_sKey,strutils::ToString<short>(v_sVal));
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,int v_iVal)
{
	AddValue(v_iIndex,v_sKey,strutils::ToString<int>(v_iVal));
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,long v_lVal)
{
	AddValue(v_iIndex,v_sKey,strutils::ToString<long>(v_lVal));
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,unsigned char v_uchVal)
{
	string sVal;
	sVal.append(1,v_uchVal);
	AddValue(v_iIndex,v_sKey,sVal);
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,unsigned short v_usVal)
{
	AddValue(v_iIndex,v_sKey,strutils::ToString<unsigned short>(v_usVal));
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,unsigned int v_uiVal)
{
	AddValue(v_iIndex,v_sKey,strutils::ToString<unsigned int>(v_uiVal));
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,unsigned long v_ulVal)
{
	AddValue(v_iIndex,v_sKey,strutils::ToString<unsigned long>(v_ulVal));
}

void HashtableMsg::AddValue(size_t v_iIndex,string v_sKey,double v_dlVal)
{
	AddValue(v_iIndex,v_sKey,strutils::ToString<double>(v_dlVal));
}


//----------------------------------------------------------------
//�������ܣ����ָ������λ�ü�¼��ֵ
//���������v_iIndex ��Ҫ���л�ȡ������λ��
//          v_sKey   ��Ҫ��ȡֵ�ļ�����
//�� �� ֵ����Ӧ����λ�õ�ֵ
string   HashtableMsg::GetString (size_t v_iIndex,string v_sKey)
{
	assert(v_iIndex >= 0 && v_iIndex < m_vRecords.size());
	return m_vRecords[v_iIndex].find(v_sKey)->second;
}

char HashtableMsg::GetChar(size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	if ( value.size() > 0 )
		return value[0];
	else
		return '\0';
}

short  HashtableMsg::GetShort  (size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	return strutils::FromString<short>(value);
}

int HashtableMsg::GetInt(size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	return strutils::FromString<int>(value);
}

long HashtableMsg::GetLong   (size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	return strutils::FromString<long>(value);
}

unsigned char  HashtableMsg::GetUChar  (size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	if ( value.size() > 0 )
		return value[0];
	else
		return '\0';
}

unsigned short HashtableMsg::GetUShort(size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	return strutils::FromString<unsigned short>(value);
}

unsigned int   HashtableMsg::GetUInt   (size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	return strutils::FromString<unsigned int>(value);
}

unsigned long  HashtableMsg::GetULong  (size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	return strutils::FromString<unsigned long>(value);
}

double HashtableMsg::GetDouble (size_t v_iIndex,string v_sKey)
{
	string value = GetString(v_iIndex,v_sKey);
	return strutils::FromString<double>(value);
}
