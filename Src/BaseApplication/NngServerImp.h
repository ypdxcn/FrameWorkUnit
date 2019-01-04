#pragma once
#include <string>
using namespace std;

#include "nng.h"
#include "protocol/reqrep0/rep.h"
#include "protocol/reqrep0/req.h"
#include "supplemental/util/platform.h"

class CNngServerImp
{
public:
	CNngServerImp();
	~CNngServerImp();

	CNngServerImp *Instance()
	{
		static CNngServerImp  imp;
		return &imp;
	}

	//reqrepģʽ
	//server 
	int  InitServerUrl(const char *url);
	int  InitClientUrl(const char *url);
	void closeAll();
	int  send(const  char *data ,int length);
	int  recv(const  char *data);
	
	//
	

private:

	nng_socket  m_sock;
	int			m_port;
	string		strUrl;

};

