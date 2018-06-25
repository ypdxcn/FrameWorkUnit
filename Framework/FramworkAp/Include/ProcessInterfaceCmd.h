#ifndef _PROCESS_INTERFACE_CMD_H
#define _PROCESS_INTERFACE_CMD_H

#include "CommAp.h"
#include "ProcessInterfaceNm.h"
#include "GessDateTime.h"

using namespace std;

class COMMAP_CLASS CProcessInterfaceCmd: public CAppProcessServer, public CProcessInterfaceNm
{
public:
	CProcessInterfaceCmd();
	~CProcessInterfaceCmd();

	int OnRecv(char* pBuf,int nSize);
	int OnRecv();
	PDATA_BUF GetRcvBuf();

	int Init(CConfig * pCfg);

	int OnAccept();					// ������˽��յ����Ӻ�ص�
	void OnClose();					// �Ͽ�����ʱ����

	//ȡ����ͳ�ƽӿ�
	void GetFlowStatics(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount)
	{
		GetInFlowStatics(uiInTotalStat,uiInAveBytes);
		GetOutFlowStatics(uiOutTotalStat,uiOutAveBytes);
	}
	int GetNmKey(string& sKey);
protected:
	
private:
	int HandleTimeout(unsigned long& ulTmSpan){return 0;}
	int GetFlowStaticsInOut(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount);

	//ͨ�Ų㱨��ͳ�ƴ���
	void UpdateStatics(eCommStaticType eType, int nCount = 1); 
	void GetInFlowStatics(unsigned int & uiInTotalStat,unsigned int & uiInAveBytes)
	{
		m_csStatics.Lock();
		int nInterval = m_oBeginStatTm.IntervalToNow();
		if (nInterval >= 5)
		{
			m_uiInAveBytes = m_uiInNowStat / nInterval;
			m_oBeginStatTm.ToNow();
			m_uiInNowStat = 0;
		}

		uiInTotalStat = m_uiInTotalStat;
		uiInAveBytes = m_uiInAveBytes;
		m_csStatics.Unlock();
	}

	DATA_BUF     m_stRcvBuf;				// ���ջ���ṹ��ָ�����������ַ

	static int	m_blInited;

	CConfig *	m_pCfg;

	unsigned int	m_uiLastStatics[eCommMaxStatic];
	unsigned int	m_uiStatics[eCommMaxStatic];

	unsigned int	m_uiInTotalStat;
	unsigned int	m_uiInNowStat;
	unsigned int	m_uiInAveBytes;
	CGessDateTime	m_oBeginStatTm;
	CGessMutex		m_csStatics;
};
#endif
