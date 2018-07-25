#include "SamplerPacket.h"

CSamplerPacket::CSamplerPacket(): CMsgBlock(1024, 4)
{
}

CSamplerPacket::CSamplerPacket(unsigned long uiCmdID): CMsgBlock(1024, 4)
{
	m_Msg.SetField(MSG_CMD_ID,uiCmdID);
	m_sCmdID = strutils::ToHexString<unsigned long>(uiCmdID);
}

CSamplerPacket::CSamplerPacket(CMessage& msg, unsigned long uiCmdID): CMsgBlock(msg,1024, 4)
{
	m_Msg.SetField(MSG_CMD_ID,uiCmdID);
	m_sCmdID = strutils::ToHexString<unsigned long>(uiCmdID);
}

CSamplerPacket::~CSamplerPacket(void)
{
}

void  CSamplerPacket::Decode(const char * pData, unsigned int nLength)
{
	//BlockDecode(pData,nLength);
	GetCmdID();
}

const char* CSamplerPacket::Encode(unsigned int & usLen)
{
	//return BlockEncode(usLen);
	return nullptr;
}

const string& CSamplerPacket::GetCmdID()
{
	unsigned long uiCmdID = 0; 
	m_Msg.GetField(MSG_CMD_ID, uiCmdID);
	m_sCmdID = strutils::ToHexString<unsigned long>(uiCmdID);
	return m_sCmdID;
}

std::string CSamplerPacket::RouteKey()
{
	unsigned long uiNodeID = 0; 
	m_Msg.GetField(MSG_NODE_ID, uiNodeID);
	return strutils::ToString<unsigned long>(uiNodeID);
}