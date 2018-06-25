#ifndef _PACKET_STRUCT_TRANSFER_IPC_NMAGENT_H
#define _PACKET_STRUCT_TRANSFER_IPC_NMAGENT_H
#include "IpcPacket.h"
#include "PacketBodyStructIpcNm.h"
#include "NetMgrAgent.h"

namespace nmagent
{
class CPacketStructIpcNm
{
public:

	//----------------------------------------------���Ľӿ� [Hello] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    Hello
	static int Packet2Struct(Hello& stBody, CIpcPacket& pkt)
	{
		pkt.GetParameterVal("node_id"           , stBody.node_id);
		pkt.GetParameterVal("proc_id"           , stBody.proc_id);		
		pkt.GetParameterVal("cmd_id"            , stBody.cmd_id);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    Hello
	static int Struct2Packet(Hello& stBody, CIpcPacket& pkt)
	{
		pkt.AddParameter("node_id"           , stBody.node_id);
		pkt.AddParameter("proc_id"           , stBody.proc_id);		
		pkt.AddParameter("cmd_id"            , stBody.cmd_id);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [QuitNotify] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    QuitNotify
	static int Packet2Struct(QuitNotify& stBody, CIpcPacket& pkt)
	{
		pkt.GetParameterVal("node_id"           , stBody.node_id);
		pkt.GetParameterVal("cmd_id"            , stBody.cmd_id);
		pkt.GetParameterVal("time_delay"        , stBody.time_delay);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    QuitNotify
	static int Struct2Packet(QuitNotify& stBody, CIpcPacket& pkt)
	{
		pkt.AddParameter("node_id"           , stBody.node_id);
		pkt.AddParameter("cmd_id"            , stBody.cmd_id);
		pkt.AddParameter("time_delay"        , stBody.time_delay);
		return 0;
	};

};
}
#endif
