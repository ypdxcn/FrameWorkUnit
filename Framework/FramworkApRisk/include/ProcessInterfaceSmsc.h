#ifndef _PROCESS_INTERFACE_SMSC_H
#define _PROCESS_INTERFACE_SMSC_H

#include "CommApRisk.h"
#include "TcpShortCp.h"
#include "ProtocolProcess.h"

using namespace std;

class COMMAPRISK_CLASS CProcessInterfaceSmsc : public CTcpShortProcess
{
public:
	CProcessInterfaceSmsc(void){}
	virtual ~CProcessInterfaceSmsc(void){}

	int PreHandle(){return 0;}
protected:
	//���ඨ��Ļص�����ʵ��
	void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
private:
};
#endif
