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
	//父类定义的回调函数实现
	void GetPacketInfo(PacketInfo & stInfo);//报文格式信息
private:
};
#endif
