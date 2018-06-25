#ifndef _PROTOCOL_PROCESS_H
#define _PROTOCOL_PROCESS_H

#include "ProtocolComm.h"
#include "GessTimerMgrPosix.h"
#include "GessTime.h"
#include "Comm.h"
#include <algorithm>

#define MAX_PACKET_SIZE						20480

enum eProcessStaticType
{
	eProcessPktRecv,		//���յ������̱�������
	eProcessPktRecvFwd,		//���͵�ת����������
	eProcessPktSend,		//���͵����̱�������
	eProcessPktSendFwd,		//���͵�ת����������
	eProcessMaxStatic
};

enum eCommStaticType
{
	eCommBytesRecv = 0,		//�������� ��ģ���յ���ȷ���������ֽ�
	eCommBytesRecvAll,		//�������� ��ģ���յ��������ֽ�
	eCommCountRecvErr,		//�������ݴ������ ��ģ���յ��Ұ�����
	eCommBytesSend,			//�������� ��ģ�鷢�͵������ֽ�
	eCommCountSendErr,		//�������� ��ģ�鷢��ʧ�ܵĴ���
	eCommMaxStatic
};

//class CProtocolComm;

class COMM_CLASS CAppProcess:virtual public CProtocolProcess
{
private:
	class CProcessTimer: public CGessTimer
	{
	public:
		CProcessTimer():m_pParent(0){}
		virtual ~CProcessTimer(){}
		void Bind(CAppProcess* p)
		{
			m_pParent=p;
		}
		int TimeOut(const string& ulKey,unsigned long& ulTmSpan)
		{
			if (0 != m_pParent)
				return m_pParent->OnTimeout(ulKey,ulTmSpan);
			return -1;
		}
		void TimerCanceled(const string& ulKey)
		{
		}
	private:
		CAppProcess* m_pParent;
	};
public:
	CAppProcess():m_pComm(0),m_sSocket(INVALID_SOCKET),m_uiOutNowStat(0),m_uiOutAveBytes(0), m_pDataWait(0)	, m_nLenWait(0)
	{
		for (int i = 0; i < eProcessMaxStatic; i++)
		{
			m_uiStatics[i] = 0;
		}

		m_oProcessTimer.Bind(this);
	}
	virtual ~CAppProcess()
	{
		if (0 != m_pDataWait)
		{
			delete[]m_pDataWait;
		}
		for (deque<DATA_BUF>::iterator it = m_deqDataBuf.begin(); it != m_deqDataBuf.end(); ++it)
		{
			delete (*it).pBuf;
		}
	}

	
	
	//��Э��ͨѶ�������󶨵�Э�����̴�����
	void Bind(CProtocolComm* p){m_pComm = p;}
	virtual int SendPacket(CPacket & Packet)
	{
		{
			int nRtn = 0;
			unsigned int  nLen = 0;
			const char* pcBuf = Packet.Encode(nLen);
			if (0 == nLen)
				return 0;

			CMutexGuard oGard(m_csStatics);
			if (m_nLenWait > 0 || m_deqDataBuf.size() > 0)
			{
				DATA_BUF stBuf;
				stBuf.pBuf = new char[nLen];
				memcpy(stBuf.pBuf, pcBuf, nLen);
				stBuf.uiLen = nLen;
				stBuf.uiUsed = nLen;
				m_deqDataBuf.push_back(stBuf);


				nRtn = -2;
			}
			else
			{
				nRtn = SendData(pcBuf, nLen);
			}
			return nRtn;
		}

	}

	//����/��ȡЭ�����̴�������Ӧ��socket
	void SocketID(tsocket_t sScoket){m_sSocket = sScoket;}
	tsocket_t  SocketID(){ return m_sSocket;}
	void SetPeerInfo(const string& sLocalIp,int nLocalPort,const string& sPeerIp,int nPeerPort)
	{
		m_sLocalIp = sLocalIp;
		m_nLocalPort = nLocalPort;
		m_sPeerIp = sPeerIp;
		m_nPeerPort = nPeerPort;
	}
	void GetPeerInfo(string& sLocalIp,int& nLocalPort,string& sPeerIp,int& nPeerPort)
	{
		sLocalIp = m_sLocalIp;
		nLocalPort = m_nLocalPort;
		sPeerIp = m_sPeerIp;
		nPeerPort = m_nPeerPort;
	}
	
	//��ȡЭ�����̴���������key
	virtual  int GetNmKey(string& sKey) = 0;
protected:
	virtual int OnLogin(int nFlag) = 0;	

	//��������
	int SendData(const char* pBuf,int nSize)
	{
		assert(0 != m_pComm);
		if (0 == m_pComm)
		{
			CRLog(E_ERROR,"%s","0 Comm");
			return -1;
		}

		m_csStatics.Lock();
		int nInterval = m_oBeginStatTm.IntervalToNow();
		if (nInterval >= 5)
		{
			m_uiOutAveBytes = m_uiOutNowStat / nInterval;
			m_oBeginStatTm.ToNow();
			m_uiOutNowStat = 0;
		}
		m_uiOutNowStat += nSize;
		m_csStatics.Unlock();

		int nRtn = m_pComm->SendData(this,pBuf,nSize);
		return nRtn;
	}
	
	void ReqClose()
	{
		m_pComm->ReqClose(this);
	}

	//����Э��㱨��ͳ������
	void UpdateStatics(eProcessStaticType eType,int nCount = 1)
	{
		if (eProcessMaxStatic == eType)
			return;

		m_uiStatics[eType] += nCount;

		//do something?

		m_uiStatics[eType] += nCount;
	}

	//ȡЭ��㱨��ͳ������
	void GetProcessStatics(unsigned int	uiStatics[eProcessMaxStatic])
	{
		for (int i = 0; i < eProcessMaxStatic; i++)
		{
			uiStatics[i] = m_uiStatics[i];
		}
	}

	//ȡͨ�ų���������
	void GetOutFlowStatics(unsigned int & uiOutNowStat,unsigned int & uiOutAveBytes)
	{
		m_csStatics.Lock();
		int nInterval = m_oBeginStatTm.IntervalToNow();
		if (nInterval >= 5)
		{
			m_uiOutAveBytes = m_uiOutNowStat / nInterval;
			m_oBeginStatTm.ToNow();
			m_uiOutNowStat = 0;
		}

		uiOutAveBytes = m_uiOutAveBytes;
		uiOutNowStat = m_uiOutNowStat;
		m_csStatics.Unlock();
	}

	int CreateTimer(unsigned long& ulTmSpan){return CGessTimerMgrImp::Instance()->CreateTimer(&m_oProcessTimer,ulTmSpan,"PTimer");}
	void DestroyTimer() {CGessTimerMgrImp::Instance()->DestroyTimer(&m_oProcessTimer,"PTimer");}
	virtual int HandleTimeout(unsigned long& ulTmSpan) = 0;

	CProtocolComm* m_pComm;

	//kenny
	//�����������͵ı���
	deque<DATA_BUF>	m_deqDataBuf;
	//δ������ɵı���
	char*	m_pDataWait;
	int		m_nLenWait;

private:
	tsocket_t m_sSocket;
	string m_sLocalIp;
	int m_nLocalPort;
	string m_sPeerIp;
	int m_nPeerPort;

	//�ӿ�����״̬��ʱ��
	int OnTimeout(const string& ulKey,unsigned long& ulTmSpan){return HandleTimeout(ulTmSpan);}

	//��ʱ��
	CProcessTimer	m_oProcessTimer;

	//Э��ҵ��㱨��ͳ�ƴ���
	unsigned int	m_uiLastStatics[eProcessMaxStatic];
	unsigned int	m_uiStatics[eProcessMaxStatic];

	unsigned int	m_uiOutNowStat;
	unsigned int	m_uiOutAveBytes;
	CGessTime		m_oBeginStatTm;
	CGessMutex		m_csStatics;
};

class COMM_CLASS CAppProcessClient:virtual public CAppProcess
{
public:
	CAppProcessClient():CAppProcess(){}
	virtual ~CAppProcessClient(){}
protected:
	//�յ�������������Ҫ����ת��
	int OnRecvPacket(CPacket& pkt){return m_pComm->OnRecvPacket(pkt);}
	
	int OnLogin(int nFlag)
	{
		CProtocolCommClient* p = dynamic_cast<CProtocolCommClient*>(m_pComm);
		if (0 == p)
			return -1;

		string sLocalIp;
		int nLocalPort;
		string sPeerIp;
		int nPeerPort;
		GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
		return p->OnLogin(sLocalIp, nLocalPort, sPeerIp, nPeerPort, nFlag);
	}

	//���ͻ������ӳɹ���ص�
	virtual int OnConnect() = 0;
};

class COMM_CLASS CAppProcessServer:virtual public CAppProcess
{
public:
	CAppProcessServer():CAppProcess(){}
	virtual ~CAppProcessServer(){m_lstKeys.clear();}

	//������˽��յ����Ӻ�ص�
	virtual int OnAccept() = 0;

	//��ȡkey�б�
	const std::list<std::string>& Keys(){return m_lstKeys;}
	//ɾ��key
	void RemoveKey(std::string sKey){m_lstKeys.remove(sKey);}
	
protected:
	
	//�յ�������������Ҫ����ת��
	int OnRecvPacket(std::string sRouteKey,CPacket& pkt)
	{
		//·����Ϣά��
		if (Is1stPacket(sRouteKey))
		{
			CProtocolCommServer* p = dynamic_cast<CProtocolCommServer*>(m_pComm);
			if (p != 0)
			{
				p->On1stPacket(this,sRouteKey);
			}
		}

		//�ϲ�ת��
		return m_pComm->OnRecvPacket(pkt);
	}

	int OnLogin(int nFlag)
	{
		CProtocolCommServer* p = dynamic_cast<CProtocolCommServer*>(m_pComm);
		if (0 == p)
			return -1;

		string sLocalIp;
		int nLocalPort;
		string sPeerIp;
		int nPeerPort;
		GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
		return p->OnLogin(sLocalIp, nLocalPort, sPeerIp, nPeerPort, nFlag);
	}
private:
	//���ݹؼ����ж��Ƿ��׸�����1��0��
	bool Is1stPacket(const std::string & sKey)
	{
		bool blRtn = false;
		std::list<std::string>::const_iterator it;
		it = find(m_lstKeys.begin(),m_lstKeys.end(),sKey);
		if (it == m_lstKeys.end())
		{
			m_lstKeys.push_back(sKey);
			blRtn = true;
		}
		return blRtn;
	}

	std::list<std::string> m_lstKeys;
};

//����ͷ��;:0 ֡���� 1Э��汾
enum HeadFlag
{
	hfFrameHeader = 0,
	hfProtocalVer = 1,
	hfNoUsed
};

//����β�Ƿ�У��
enum TailFlag
{
	tfFrameCheck = 0,
	tfNoUsed
};

//���ĳ����ֶ�����
enum LengthType
{
	ltInterger = 0,		//����
	ltCharactersDec,	//�ַ���10����
	ltCharactersHex		//�ַ���16����
};

//����ͷ��Ϣ �������ľ���Э����ͨ���ص��ṩ
typedef struct stPacketInfo
{
	size_t		nLengthBytes;		// ��Ϣ�������ֶεĳ���,Ϊ����ʱֻ֧�� 1 2 4�ֽ�
	size_t		nLengthPos;			// ��Ϣ�������ֶ��ڰ�ͷ��λ�� ��0��ʼ����
	LengthType	eLengthType;		// ��Ϣ�������ֶε�����
	int			blLenIncludeHeader;	// �����Ƿ񺬱���ͷ
	size_t		nFixHeadLen;		// �����ֶα�ʾ�ĳ���֮��Ĺ̶�����ͷ����(�������ֶα���)

	HeadFlag	eHeadFlag;			// ����ͷ��;��ʶ
	size_t		nLengthHeadFlag;	// ����ͷ��ʶռ���ֽ�
	TailFlag	eTailFlag;			// ����β��;��ʶ
	size_t		nLengthTailFlag;	// ����β��ʶռ���ֽ�
} PacketInfo,*PPacketInfo;

//TCP�������
class COMM_CLASS CTcpHandler
{
public:
	CTcpHandler(){}
	virtual ~CTcpHandler(){}

	//ֻ��ʼ��һ�α���ͷ��Ϣ
	int InitPacketInfo()
	{
		//if (!m_blPacketInfoInited)
			GetPacketInfo(m_PacketInfo);

		return 0;
	}
protected:
	virtual void GetPacketInfo(PacketInfo & stInfo) = 0;	// ��������ṩ�����йس��ȸ�ʽ��Ϣ
	
	//�����յ��Ĳ������ݼ��㱨�ĳ���
	virtual size_t GetPacketLength(const char* pPacketData);

	/*static*/ PacketInfo	m_PacketInfo;			//����ͷ��Ϣ
	//static bool			m_blPacketInfoInited;	//�Ƿ��ѳ�ʼ��
private:

};


class COMM_CLASS CTcpHandlerLong: virtual public CTcpHandler
{
public:
	CTcpHandlerLong();
	virtual ~CTcpHandlerLong();
	
	int OnRecvTcp(char* pBuf,int nSize);
	int OnRecvTcp();
	PDATA_BUF GetRcvBufTcp(){return &m_stRcvBuf;}

protected:
	virtual int OnPacket(char * pData, size_t nSize) = 0;	// �յ��������ĺ�ص�
	
	//ͨ�Ų㱨��ͳ�ƴ���
	void UpdateStatics(eCommStaticType eType, int nCount = 1); 
	void GetInFlowStatics(unsigned int & uiInNowStat,unsigned int & uiInAveBytes)
	{
		m_csStatics.Lock();
		int nInterval = m_oBeginStatTm.IntervalToNow();
		if (nInterval >= 5)
		{
			m_uiInAveBytes = m_uiInNowStat / nInterval;
			m_oBeginStatTm.ToNow();
			m_uiInNowStat = 0;
		}

		uiInNowStat = m_uiInNowStat;
		uiInAveBytes = m_uiInAveBytes;
		m_csStatics.Unlock();
	}
private:
	unsigned int	m_uiLastStatics[eCommMaxStatic];
	unsigned int	m_uiStatics[eCommMaxStatic];

	unsigned int	m_uiInNowStat;
	unsigned int	m_uiInAveBytes;
	CGessTime	m_oBeginStatTm;
	CGessMutex		m_csStatics;


	DATA_BUF     m_stRcvBuf;				// ���ջ���ṹ��ָ�����������ַ
	size_t m_nLength;					// �����ձ��ĳ���
	size_t m_nIndex;					// �ѽ��ձ���λ��
	char m_szBuf[MAX_PACKET_SIZE];		// ���ջ���
};

class COMM_CLASS CTcpAppProcessClient:virtual public CAppProcessClient,virtual public CTcpHandlerLong
{
public:
	CTcpAppProcessClient():CAppProcessClient(),CTcpHandler(){};
	virtual ~CTcpAppProcessClient(){};

	int OnRecv(char* pBuf,int nSize){return OnRecvTcp(pBuf,nSize);}
	int OnRecv(){return OnRecvTcp();}
	PDATA_BUF GetRcvBuf(){return GetRcvBufTcp();}

	virtual int Init(CConfig * pCfg){return InitPacketInfo();}

	//ȡ����ͳ�ƽӿ�
	void GetFlowStatics(unsigned int & uiInNowStat,unsigned int & uiInAveBytes,unsigned int & uiOutNowStat,unsigned int & uiOutAveBytes)
	{
		GetInFlowStatics(uiInNowStat,uiInAveBytes);
		GetOutFlowStatics(uiOutNowStat,uiOutAveBytes);
	}
};


class COMM_CLASS CTcpAppProcessServer:virtual public CAppProcessServer,virtual public CTcpHandlerLong
{
public:
		CTcpAppProcessServer():CAppProcessServer(),CTcpHandler(){};
		virtual ~CTcpAppProcessServer(){};

		int OnRecv(char* pBuf,int nSize){return OnRecvTcp(pBuf,nSize);}
		int OnRecv(){return OnRecvTcp();}
		PDATA_BUF GetRcvBuf(){return GetRcvBufTcp();}

		virtual int Init(CConfig * pCfg){return InitPacketInfo();}

		//ȡ����ͳ�ƽӿ�
		void GetFlowStatics(unsigned int & uiInNowStat,unsigned int & uiInAveBytes,unsigned int & uiOutNowStat,unsigned int & uiOutAveBytes)
		{
			GetInFlowStatics(uiInNowStat,uiInAveBytes);
			GetOutFlowStatics(uiOutNowStat,uiOutAveBytes);
		}
protected:
	
};


#define MAX_TCP_SHORT_PACKET_SIZE			4096
//��װTCP������Э������
class COMM_CLASS CTcpShortProcess: virtual public CTcpHandler
{
public:
	CTcpShortProcess(){}
	virtual ~CTcpShortProcess(){}
	//��ʼ��
	virtual int Init(CConfig* pCfg){m_pCfg = pCfg; return InitPacketInfo();}
	//���ͱ����ر�Ĵ��� PreSendHandle���崦������Ǽ���,ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�ʵ�ʷ��͵��ֽ���
	virtual int PreSendHandle(CPacket &sndPacket) = 0;
	//���������ر�Ĵ��� SufRecvHandle���崦������ǽ���,��ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�1 
	virtual int SufRecvHandle(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket) = 0;
	//���ͱ���
	virtual int SendPacket(CPacket &sndPacket,CPacket &rcvPacket,unsigned int uiTimeout)
	{
		assert(0 != m_pComm);
		if (0 == m_pComm)
			return -1;

		int nRtn = PreSendHandle(sndPacket);

        // modified by Jerry Lee, 2011-5-12, ����Ԥ����ɹ����޷����ձ��ĵ�bug
        /*
		if (0 > nRtn)
		{
			return -1;
		}
		else if (0 < nRtn)
		{
			return 0;
		}
		else
		{
			//����������
			unsigned int  nLen = 0;
			const char* pcBuf = sndPacket.Encode(nLen);
			nRtn = m_pComm->SendData(pcBuf,nLen);
			if (-1 == nRtn)
			{
				CRLog(E_ERROR,"%s","SendData err");
				return -1;
			}
		}
        */

        //
        if (0 > nRtn)
        {
            return -1;
        }
        else if (0 < nRtn)
        {
            // ����ִ���Խ��ձ���
        }
        else
        {
            //����������
            unsigned int  nLen = 0;
            const char* pcBuf = sndPacket.Encode(nLen);
            nRtn = m_pComm->SendData(pcBuf,nLen);
            if (-1 == nRtn)
            {
                CRLog(E_ERROR,"%s","SendData err");
                return -1;
            }
        }
	
		//����Ӧ����
		nRtn = -1;
		time_t tmLast,tmNow;
		time(&tmLast); 
		unsigned int nTimeLeft = uiTimeout;
		size_t nPktLen = 0;
		
		std::list<RCV_BUF*> lstBuf;
		RCV_BUF * pBufNow = new RCV_BUF;
		pBufNow->pBuf = new char[MAX_TCP_SHORT_PACKET_SIZE];
		pBufNow->uiLen = MAX_TCP_SHORT_PACKET_SIZE;
		pBufNow->uiUsed = 0;
		lstBuf.push_back(pBufNow);

		char* pBuf = pBufNow->pBuf;
		int nLenLeft = pBufNow->uiLen;
		size_t nReadTotal = 0;

		CRLog(E_DEBUG,"%s","Begin Recv Data");
		do
		{
			//modify by zhangwei 2010.04.20 �����ļ�����ʱ������socket���ر�����Զ�ȴ�����
			//int nRecv = m_pComm->RecvData(pBuf,nLenLeft,uiTimeout);

			//����socket�������ݳ�ʱʱ��
// 			unsigned int uiTimeoutRcv = 30;
			int nRecv = m_pComm->RecvData(pBuf,nLenLeft, uiTimeout);
			if (-1 == nRecv)
			{
				break;
			}

			time(&tmNow);
			nTimeLeft = uiTimeout - static_cast<int>(difftime(tmNow,tmLast));
			if ( nTimeLeft <= 0 )
			{

				break;
			}

			CRLog(E_DEBUG,"Recv Bytes:%d,Total:%d,Left time:%d ",nRecv,nReadTotal,nTimeLeft);

			pBuf += nRecv;
			nReadTotal += nRecv;
			pBufNow->uiUsed += nRecv;
			nLenLeft -= nRecv;
			if (nLenLeft <= 0)
			{				
				pBufNow = new RCV_BUF;
				pBufNow->pBuf = new char[MAX_TCP_SHORT_PACKET_SIZE];
				pBufNow->uiLen = MAX_TCP_SHORT_PACKET_SIZE;
				pBufNow->uiUsed = 0;
				lstBuf.push_back(pBufNow);

				pBuf = pBufNow->pBuf;
				nLenLeft = pBufNow->uiLen;
			}

			if (nReadTotal < m_PacketInfo.nLengthBytes)
			{//��Ҫ�յ����ٱ��ĳ��Ȳ����ֽ�
				continue;
			}

			if (0 == nPktLen)
			{//�����յ������ݲ���ȷ������
				char * pLenBuf = new char[m_PacketInfo.nLengthBytes];
				char * pTmp = pLenBuf;
				unsigned int nCopyLeft = m_PacketInfo.nLengthBytes;

				std::list<RCV_BUF*>::iterator it;				
				for (it = lstBuf.begin(); it != lstBuf.end();++it)
				{
					if ((*it)->uiUsed >= nCopyLeft)
					{
						memcpy(pTmp,(*it)->pBuf,nCopyLeft);
						pTmp += nCopyLeft;
						nCopyLeft = 0;
						break;
					}
					else
					{
						memcpy(pTmp,(*it)->pBuf,(*it)->uiUsed);
						pTmp += (*it)->uiUsed;
						nCopyLeft -= (*it)->uiUsed;

						if (nCopyLeft <= 0)
						{
							break;
						}
					}
				}

				nPktLen = GetPacketLength(pLenBuf);
				delete []pLenBuf;
				if (0 == nPktLen)
				{
					break;
				}
			}

			if (nReadTotal >= nPktLen)
			{				
				break;
			}
		} while (true);

		CRLog(E_DEBUG,"Recv Bytes Total:%d",nReadTotal);

		char * pBufTotal = new char[nReadTotal];
		char * pTmp = pBufTotal;
		std::list<RCV_BUF*>::iterator it;				
		for (it = lstBuf.begin(); it != lstBuf.end();)
		{
			if ((*it)->uiUsed > 0)
			{
				memcpy(pTmp,(*it)->pBuf,(*it)->uiUsed);
				pTmp += (*it)->uiUsed;
			}
			
			delete []((*it)->pBuf);
			delete (*it);
			lstBuf.erase(it++);
		}

		if (nReadTotal > 0)
		{
			nRtn = SufRecvHandle(pBufTotal,nReadTotal,rcvPacket);
			if (0 > nRtn)
			{
				nRtn = -1;
			}
			else if (0 < nRtn)
			{
				nRtn = 0;
			}
			else
			{
				rcvPacket.Decode(pBufTotal,nReadTotal);
				nRtn = 0;
			}
		}
		delete []pBufTotal;
		return nRtn;
	}
	void Bind(CTcpShortComm* pComm){m_pComm=pComm;}
protected:
	int SendData(const char* pcBuf, int nLen) {return m_pComm->SendData(pcBuf,nLen);}
	CConfig* m_pCfg;
private:
	CTcpShortComm*	m_pComm;

};

#endif