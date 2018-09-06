#pragma once
#include <string>
using namespace std;

#include "reqrep.h"
#include "pubsub.h"

class CNanoServerImp
{
public:
	CNanoServerImp();
	~CNanoServerImp();

	/*CNanoServerImp *Instance()
	{
		static CNanoServerImp  imp;
		return &imp;
	}*/

	int  InitServerUrl(const char *url, int port=9090, int serverType = NN_PUB);
	int  setsockopt_impl(  int level, int option, const void *optval, size_t optlen);
	void close_impl();
	int  send_impl(  char *data);
	int  recv_impl(  char *data);
	int  RetSetSvr(  int serverType = NN_PUB);
private:

	int m_sock;
	int m_port;
	string  strUrl;

};

