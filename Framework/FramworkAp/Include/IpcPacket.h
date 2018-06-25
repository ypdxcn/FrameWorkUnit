#ifndef _IPC_PACKET_H
#define _IPC_PACKET_H

#include <string>
#include <vector>
#include <map>
#include "CommAp.h"
#include "PairPacket.h"

#define IPC_LENGTH_BYTES		8	//����ռ���ֽ���

class COMMAP_CLASS CIpcPacket:public CPairPacket
{
public:
	CIpcPacket();
	CIpcPacket(const string& sCmdID);
	virtual ~CIpcPacket();

public:
	//�������
	virtual const char* Encode(unsigned int & uiLength,CPairPacket & packet){return 0;}
	virtual const char* Encode(unsigned int & uiLength);
	virtual void  Decode(const char * pData, unsigned int uiLength);
	
	const string& GetCmdID();
	std::string RouteKey()
	{
		std::string sNodeID("");
		GetParameterVal("node_id",sNodeID);
		return sNodeID;
	}

private:
	std::string m_sCmdID;		//������
	std::string m_sEncode;		//�������ַ���

	//��ȡ�������к�
	static long GetSID();

	static CGessMutex	m_csSID;
	static unsigned int m_uiSID;		//ά�������к�,����������ͨѶ�౨��
};
#endif