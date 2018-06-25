/******************************************************************************
��    Ȩ:��������������ϵͳ���޹�˾.
ģ������:GenericPacketHandler.cpp
������	:��ΰ
��������:2008.07.22
��    ��:1.0				
ģ������:��װ����TCP���Ľ��գ����ڻ���TCP��Ӧ�ò㱨�Ķ���ǧ���򻯣�������������
         ��ѡ�����������Ӧ
��Ҫ����:OnPacket(...) �麯���յ��������ĺ�ص�
		 GetPacketLength(...) ���ݱ��Ķ�������յ��Ĳ��ֱ���ͷ��������ձ��ĳ�
		 SendData(...) ���ͺ���
	     SendPacket(..) ���ͱ��Ľӿں���
�޸ļ�¼:
******************************************************************************/
#include <cassert>
#include "ProtocolProcess.h"
//#include "ProtocolComm.h"
#include "Logger.h"

//using namespace std;

//��ʼ��Ϊ4�ֽ�������ʶ����,���Ȱ�������ͷ
//PacketInfo CTcpHandler::m_PacketInfo = {4,0,ltInterger,true,0,hfNoUsed,0,tfNoUsed,0};
//bool CTcpHandler::m_blPacketInfoInited = false;

CTcpHandlerLong::CTcpHandlerLong()
:m_nIndex(0)
,m_nLength(0)
,m_uiInNowStat(0)
,m_uiInAveBytes(0)
{
	m_stRcvBuf.uiLen = MAX_PACKET_SIZE;
	m_stRcvBuf.pBuf = m_szBuf;
	m_stRcvBuf.uiUsed = 0;

	for (int i = 0; i < eCommMaxStatic; i++)
	{
		m_uiLastStatics[i] = 0;;
		m_uiStatics[i] = 0;
	}
}

CTcpHandlerLong::~CTcpHandlerLong(void)
{
}

/******************************************************************************
��������:���ݱ��Ķ�������յ��Ĳ��ֱ���ͷ��������ձ��ĳ�
���ú���:�̺߳���
�������:char* pPacketData�ѽ��յ����ݻ���
����ֵ  :size_t �����ձ����ܳ���
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
#define MAX_CHARACTER_LEN	128
size_t CTcpHandler::GetPacketLength(const char* pPacketData)
{
	assert(pPacketData != 0);
	if (0 == pPacketData)
		return 0;

	size_t nLength = 0;
	if (m_PacketInfo.eLengthType == ltInterger)
	{//������ʶ����
		if (m_PacketInfo.nLengthBytes == 1)
		{
			nLength = *(pPacketData + m_PacketInfo.nLengthPos);
		}
		else if (m_PacketInfo.nLengthBytes == 2)
		{
			nLength = ntohs( *(reinterpret_cast<const unsigned short*>(pPacketData + m_PacketInfo.nLengthPos)));
		}
		else if (m_PacketInfo.nLengthBytes == 4)
		{
			nLength = ntohl( *(reinterpret_cast<const unsigned int*>(pPacketData + m_PacketInfo.nLengthPos)));
		}
		else
		{
			CRLog(E_CRITICAL, "�Ƿ��ĳ����ֶγߴ�: %d", m_PacketInfo.nLengthBytes);
			return 0;
		}
	}
	else if (m_PacketInfo.eLengthType == ltCharactersDec)
	{//10�����ַ�����ʶ����
		if (MAX_CHARACTER_LEN > m_PacketInfo.nLengthBytes)
		{
			char szLen[MAX_CHARACTER_LEN];
			memset(szLen,0x00,MAX_CHARACTER_LEN);
			memcpy(szLen, &pPacketData[m_PacketInfo.nLengthPos], m_PacketInfo.nLengthBytes);
			nLength = strtoul(szLen,0,10);
		}
		else
		{
			CRLog(E_CRITICAL, "�Ƿ��ĳ����ֶγߴ�: %d", m_PacketInfo.nLengthBytes);
			return 0;
		}
	}
	else if (m_PacketInfo.eLengthType == ltCharactersHex)
	{//16�����ַ�����ʶ����
		if (MAX_CHARACTER_LEN > m_PacketInfo.nLengthBytes)
		{
			char szLen[MAX_CHARACTER_LEN];
			memset(szLen,0x00,MAX_CHARACTER_LEN);
			memcpy(szLen, &pPacketData[m_PacketInfo.nLengthPos], m_PacketInfo.nLengthBytes);
			nLength = strtoul(szLen,0,16);
		}
		else
		{
			CRLog(E_CRITICAL, "�Ƿ��ĳ����ֶγߴ�: %d", m_PacketInfo.nLengthBytes);
			return 0;
		}
	}
	else
	{
		CRLog(E_CRITICAL, "�Ƿ��ĳ����ֶ�����: %d", m_PacketInfo.eLengthType);
		return 0;
	}
	
	//�����Ȳ���������ͷ,������ϱ���ͷ����
	if (!m_PacketInfo.blLenIncludeHeader && nLength!=0)
		nLength+=m_PacketInfo.nFixHeadLen;

	if ( nLength > MAX_PACKET_SIZE )
	{   //ʧ��
		CRLog(E_ERROR,"Bad MSG PACK m_nLength = %d!", nLength );				
		return 0;
	}

	return nLength;
}

/******************************************************************************
��������:socket�������������,�жϱ����Ƿ��������,��ͨ���ص������յ�����������
         �ϴ�
��������:GetPacketLength
�������:char* pBuf�ѽ��յ����ݻ���,nSize���泤��
����ֵ  :0��ȷ���� -1���մ���
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
int CTcpHandlerLong::OnRecvTcp(char* pBuf,int nSize)
{
	try
	{
		//ͳ��ƽ������
		m_csStatics.Lock();
		int nInterval = m_oBeginStatTm.IntervalToNow();
		if (nInterval >= 5)
		{
			m_uiInAveBytes = m_uiInNowStat / nInterval;
			m_oBeginStatTm.ToNow();
			m_uiInNowStat = 0;
		}
		m_uiInNowStat += nSize;
		m_csStatics.Unlock();

		//ͳ���ۼ�����
		UpdateStatics(eCommBytesRecvAll,nSize);

		int nLastIndex = m_nIndex;
		m_nIndex += nSize ; 
		if( m_nLength == 0 && m_nIndex < m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		{
			CRLog(E_DEBUG,"��������δ���룬nSize = %d, m_nIndex = %d m_nLength = %d !", nSize, m_nIndex , m_nLength);	
			memcpy(&m_szBuf[nLastIndex],pBuf,nSize);
			return 0;
		}

		//frame begin
		if ( m_nLength == 0 && m_nIndex >= m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		{
			m_nLength = GetPacketLength(m_szBuf);
			if ( m_nLength == 0 )
			{   //�����쳣Ϊ�Ұ����ʼ��
				//����֡ͷ������Ҫ��֡ͷͬ��...//
				CRLog(E_ERROR,"%s","�����쳣");
				UpdateStatics(eCommCountRecvErr);
				m_nIndex = m_nLength = 0;
				return -1;
			}
		}

		if ( m_nIndex <= m_nLength )
		{
			memcpy(&m_szBuf[nLastIndex],pBuf,nSize);
			if ( m_nIndex == m_nLength )
			{   //�յ�������һ������ ֱ�Ӵ�������
				//����֡ͷ������Ҫ�ȼ��...//
				//����֡β���򰴹涨�㷨У���ദ����ȥ֡β��������...//
				UpdateStatics(eCommBytesRecv,m_nLength);
				if (0 > OnPacket(m_szBuf,m_nLength))
				{
					return -1;
				}
				m_nIndex = m_nLength = 0;
			}

			return 0;
		}

		//�����Ƕ�һ���յ�����һ�����ĵĴ���
		//CRLog(E_DEBUG,"recv packet > 1: nSize = %d, m_nIndex = %d m_nLength = %d !", nSize, m_nIndex , m_nLength );
		memcpy(&m_szBuf[nLastIndex],pBuf,m_nLength - nLastIndex);
		if (0 > OnPacket(m_szBuf,m_nLength))
		{
			return -1;
		}
		UpdateStatics(eCommBytesRecv,m_nLength);

		pBuf += m_nLength - nLastIndex;
		unsigned int nLeaveByte = nSize - (m_nLength - nLastIndex);
		if( nLeaveByte < m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		{
			memcpy(m_szBuf,pBuf,nLeaveByte);
			m_nIndex = nLeaveByte;
			m_nLength = 0;
			return 0;
		}

		//frame begin
		unsigned int nLength = 0;
		if ( nLeaveByte >= m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		{
			nLength = GetPacketLength(pBuf);
			if ( m_nLength == 0 )
			{   //�����쳣Ϊ�Ұ����ʼ��
				//����֡ͷ������Ҫ��֡ͷͬ��...//
				UpdateStatics(eCommCountRecvErr);
				m_nIndex = m_nLength = 0;
				return -1;
			}
		}
		
		if ( nLeaveByte <= nLength )
		{
			if ( nLeaveByte == nLength )
			{   //�յ�������һ������ ֱ�Ӵ�������
				//����֡ͷ������Ҫ�ȼ��...//
				//����֡β���򰴹涨�㷨У���ദ����ȥ֡β��������...//
				UpdateStatics(eCommBytesRecv,nLength);
				if (0 > OnPacket(pBuf,nLength))
				{
					return -1;
				}
				m_nIndex = m_nLength = 0;
			}
			else
			{
				memcpy(m_szBuf,pBuf,nLeaveByte);
				m_nIndex = nLeaveByte;
				m_nLength = nLength;
			}
			return 0;
		}
		
		do
		{
			//��ȷ��������
			//����֡ͷ������Ҫ�ȼ��...//
			//����֡β���򰴹涨�㷨У���ദ����ȥ֡β��������...//
			UpdateStatics(eCommBytesRecv,nLength);
			if (0 > OnPacket(pBuf,nLength))
			{
				return -1;
			}
			
			nLeaveByte -= nLength;
			pBuf += nLength;
			if ( nLeaveByte >=  m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
			{
				nLength = GetPacketLength(pBuf);
				if ( nLength == 0 )
				{   //�����쳣Ϊ�Ұ����ʼ��
					//����֡ͷ������Ҫ��֡ͷͬ��...//
					//IncreaseStatics(CommUpInErr);
					m_nIndex = m_nLength = 0;
					nLeaveByte = 0;
					return -1;
				}
				if ( nLeaveByte < nLength )
				{
					break;
				}
			}
			else
			{
				m_nLength = 0;
				break;
			}
		} while ( nLeaveByte > 0 );

		if ( nLeaveByte > 0 )
		{
			memcpy( m_szBuf, pBuf, nLeaveByte );
			m_nIndex = nLeaveByte;
		}
		else
		{
			m_nIndex = 0;
		}
		return 0;		
	}
	catch(std::exception e)
	{
		CRLog(E_CRITICAL,"exception:%s", e.what());
		return -1;
	}
	catch(...)
	{
		CRLog(E_CRITICAL,"%s","Unknown exception");
		return -1;
	}
}

/******************************************************************************
��������:socket�������������,�жϱ����Ƿ��������,��ͨ���ص������յ�����������
         �ϴ�,���漰�����Ѿ�����m_szBuf,m_nIndex
��������:GetPacketLength
����ֵ  :0��ȷ���� -1���մ���
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
int CTcpHandlerLong::OnRecvTcp()
{
	try
	{
		//ͳ�ƽ���ƽ������ ������ʱÿ5�����ϼ��ͳ��һ��
		m_csStatics.Lock();
		int nInterval = m_oBeginStatTm.IntervalToNow();
		if (nInterval >= 5)
		{
			m_uiInAveBytes = m_uiInNowStat / nInterval;
			m_oBeginStatTm.ToNow();
			m_uiInNowStat = 0;
		}
		m_uiInNowStat += m_stRcvBuf.uiLen;
		m_csStatics.Unlock();

		//ͳ���ۼ�����
		UpdateStatics(eCommBytesRecvAll,m_stRcvBuf.uiLen);

		int nLastIndex = m_nIndex;
 		m_nIndex += m_stRcvBuf.uiLen; 
		if( m_nLength == 0 && m_nIndex < m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		{
			//CRLog(E_DEBUG,"��������δ���룬nSize = %d, m_nIndex = %d m_nLength = %d !", m_stRcvBuf.uiLen, m_nIndex , m_nLength);
			m_stRcvBuf.uiLen = MAX_PACKET_SIZE - m_nIndex;
			m_stRcvBuf.pBuf = m_szBuf + m_nIndex;
			return 0;
		}

		//frame begin
		if ( m_nLength == 0 && m_nIndex >= m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		{
			m_nLength = GetPacketLength(m_szBuf);
			if ( m_nLength == 0 )
			{   //�����쳣Ϊ�Ұ����ʼ��
				//����֡ͷ������Ҫ��֡ͷͬ��...//
				CRLog(E_ERROR,"%s","�����쳣");
				UpdateStatics(eCommCountRecvErr);
				m_nIndex = m_nLength = 0;
				m_stRcvBuf.uiLen = MAX_PACKET_SIZE;
				m_stRcvBuf.pBuf = m_szBuf;
				return -1;
			}
		}

		if ( m_nIndex <= m_nLength )
		{
			int nRtn = 0;
			if ( m_nIndex == m_nLength )
			{   //�յ�������һ������ ֱ�Ӵ�������
				//����֡ͷ������Ҫ�ȼ��...//
				//����֡β���򰴹涨�㷨У���ദ����ȥ֡β��������...//
				UpdateStatics(eCommBytesRecv,m_nLength);
				if (0 > OnPacket(m_szBuf,m_nLength))
				{
					return -1;
				}
				m_nIndex = m_nLength = 0;
				m_stRcvBuf.uiLen = MAX_PACKET_SIZE;
				m_stRcvBuf.pBuf = m_szBuf;
			}
			else
			{
				m_stRcvBuf.uiLen = MAX_PACKET_SIZE - m_nIndex;
				m_stRcvBuf.pBuf = m_szBuf + m_nIndex;
			}

			return nRtn;
		}

		//�����Ƕ�һ���յ�����һ�����ĵĴ���
		//CRLog(E_DEBUG,"recv packet > 1: nSize = %d, m_nIndex = %d m_nLength = %d !", nSize, m_nIndex , m_nLength );

		char* pszPos = m_szBuf;
		unsigned int nLeaveByte = m_nIndex;
		do
		{
			//��ȷ��������
			//����֡ͷ������Ҫ�ȼ��...//
			//����֡β���򰴹涨�㷨У���ദ����ȥ֡β��������...//
			UpdateStatics(eCommBytesRecv,m_nLength);
			if (0 > OnPacket(pszPos,m_nLength))
			{
				return -1;
			}
			nLeaveByte -= m_nLength;
			pszPos += m_nLength;
			if ( nLeaveByte >=  m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
			{
				m_nLength = GetPacketLength(pszPos);
				if ( m_nLength == 0 )
				{   //�����쳣Ϊ�Ұ����ʼ��
					//����֡ͷ������Ҫ��֡ͷͬ��...//
					UpdateStatics(eCommCountRecvErr);
					m_nIndex = m_nLength = 0;
					m_stRcvBuf.uiLen = MAX_PACKET_SIZE;
					m_stRcvBuf.pBuf = m_szBuf;
					nLeaveByte = 0;
					return -1;
				}
				if ( nLeaveByte < m_nLength )
				{
					break;
				}
			}
			else
			{
				m_nLength = 0;
				break;
			}
		} while ( nLeaveByte > 0 );

		if ( nLeaveByte > 0 )
		{
			memcpy( m_szBuf, pszPos, nLeaveByte );
			m_nIndex = nLeaveByte;
			m_stRcvBuf.uiLen = MAX_PACKET_SIZE - m_nIndex;
			m_stRcvBuf.pBuf = m_szBuf + m_nIndex;
		}
		else
		{
			m_nIndex = 0;
			m_stRcvBuf.uiLen = MAX_PACKET_SIZE;
			m_stRcvBuf.pBuf = m_szBuf;
		}
		return 0;
	}
	catch(std::exception e)
	{
		CRLog(E_CRITICAL,"exception:%s", e.what());
		return -1;
	}
	catch(...)
	{
		CRLog(E_CRITICAL,"%s","Unknown exception");
		return -1;
	}
}

void CTcpHandlerLong::UpdateStatics(eCommStaticType eType, int nCount)
{
	if (eCommMaxStatic == eType)
		return;

	m_uiStatics[eType] += nCount;

	//do something?

	m_uiLastStatics[eType] += nCount;
}