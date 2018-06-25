#include "ProcessInterfaceCmd.h"
#include "LinePacket.h"
#include "Logger.h"
#include "strutils.h"

using namespace strutils;

int CProcessInterfaceCmd::m_blInited = false;

CProcessInterfaceCmd::CProcessInterfaceCmd()
{
	m_stRcvBuf.uiLen = 0;
	m_stRcvBuf.uiUsed = 0;
	m_stRcvBuf.pBuf = 0;

	m_uiInTotalStat = 0;
	m_uiInNowStat = 0;
	m_uiInAveBytes = 0;
}

CProcessInterfaceCmd::~CProcessInterfaceCmd()
{
	if (0 != m_stRcvBuf.pBuf)
		delete []m_stRcvBuf.pBuf;
}


PDATA_BUF CProcessInterfaceCmd::GetRcvBuf()
{
	if (0 == m_stRcvBuf.pBuf)
	{
		m_stRcvBuf.pBuf = new char[MAX_PACKET_SIZE];
		m_stRcvBuf.uiLen = MAX_PACKET_SIZE;
		m_stRcvBuf.uiUsed = 0;
	}
	else if (m_stRcvBuf.uiLen == m_stRcvBuf.uiUsed)
	{
		
	}
	return &m_stRcvBuf;
}

int CProcessInterfaceCmd::Init(CConfig * pCfg)
{
	if (!m_blInited)
	{
		m_blInited = true;
		
		m_pCfg = pCfg;
	}
	return 0;
}

// ������˽��յ����Ӻ�ص�
int CProcessInterfaceCmd::OnAccept()
{
	GetPeerInfo(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	CProcessInterfaceNm::OnAccept(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	

	CPacketLineRsp pkt("continue...");
	CAppProcess::SendPacket(pkt);
	return 0;
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
int CProcessInterfaceCmd::OnRecv(char* pBuf,int nSize)
{	
	return 0;
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
int CProcessInterfaceCmd::OnRecv()
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
		m_uiInNowStat += m_stRcvBuf.uiUsed;
		m_uiInTotalStat += m_stRcvBuf.uiUsed;
		m_csStatics.Unlock();

		if (m_stRcvBuf.uiUsed < 2)
		{
			return 0;
		}
	
		char * pcTmp = m_stRcvBuf.pBuf;
		for (unsigned int i = 1; i < m_stRcvBuf.uiUsed; i++)
		{
			if (m_stRcvBuf.pBuf[i-1] == '\r' && m_stRcvBuf.pBuf[i] == '\n')
			{
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				string sKey = sPeerIp + ToString(nPeerPort);

				if (i > 1)
				{
					CPacketLineReq pkt;
					pkt.Decode(pcTmp,static_cast<unsigned int>(m_stRcvBuf.pBuf+i-1-pcTmp));
					
					if (pkt.GetCmdID() == "exit")
					{
						ReqClose();
						return 0;
					}

					pkt.AddRouteKey(sKey);
					OnRecvPacket(sKey,pkt);
				}
				else
				{
					CPacketLineReq pkt("");
					pkt.AddRouteKey(sKey);
					OnRecvPacket(sKey,pkt);
				}

				pcTmp = pcTmp + i + 1;
			}
		}

		if (pcTmp > m_stRcvBuf.pBuf)
		{
			if (pcTmp < m_stRcvBuf.pBuf + m_stRcvBuf.uiUsed)
			{
				memcpy(m_stRcvBuf.pBuf,pcTmp,m_stRcvBuf.pBuf + m_stRcvBuf.uiUsed - pcTmp);
				m_stRcvBuf.uiUsed = m_stRcvBuf.pBuf + m_stRcvBuf.uiUsed - pcTmp + 1;
			}
			else
			{
				m_stRcvBuf.uiUsed = 0;
			}
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

void CProcessInterfaceCmd::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"Telnet CmdLine Long Connection Close %s %d",sPeerIp.c_str(),nPeerPort);

	CProcessInterfaceNm::OnClose(sLocalIp,nLocalPort,sPeerIp,nPeerPort,E_TCP_SERVER);
}


int CProcessInterfaceCmd::GetFlowStaticsInOut(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount)
{
	GetFlowStatics(uiInTotalStat,uiInAveBytes,uiOutTotalStat,uiOutAveBytes,uiOutBufBytes,uiOutBufPkts,uiOutBufBytesTotal,uiOutBufPktsTotal,uiOutBufCount);	
	return 0;
}

int CProcessInterfaceCmd::GetNmKey(string& sKey)
{
	sKey = "Զ��Telnet�ӿڷ��������.";
	int nSockeID = static_cast<int>( SocketID());
	if (INVALID_SOCKET != nSockeID)
	{
		sKey += ToString<int>(nSockeID);
	}
	else
	{
		srand(static_cast<unsigned int>(time(0)));
		int RANGE_MIN = 1;
		int RANGE_MAX = 99;
		int nRandom = rand() * (RANGE_MAX - RANGE_MIN) / RAND_MAX + RANGE_MIN;
		sKey += ToString<int>(nRandom);
	}

	return 0;
}
