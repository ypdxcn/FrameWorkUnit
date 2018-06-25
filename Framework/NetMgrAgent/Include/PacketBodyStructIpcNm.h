#ifndef _PACKET_BODY_STRUCT_IPC_NMAGENT_H
#define _PACKET_BODY_STRUCT_IPC_NMAGENT_H
#include <string>
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

namespace nmagent
{
//----------------------------------------------���Ľӿ� [Hello] ����

// �ṹ����:Hello
typedef struct tagHello
{
	int          node_id              ; //Դ�ڵ��    
	unsigned int proc_id              ; //����ID    
	string       cmd_id               ; //������    
}Hello,*PHello;



//----------------------------------------------���Ľӿ� [QuitNotify] ����

// �ṹ����:QuitNotify
typedef struct tagQuitNotify
{
	int          node_id              ; //Ŀ��ڵ��    
	string       cmd_id               ; //������    
	string       time_delay           ; //�ӳ�ʱ��    
}QuitNotify,*PQuitNotify;

}

#endif
