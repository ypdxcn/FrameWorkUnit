#pragma once
#include <string>
using namespace std;

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

	int  InitServerUrl(const char *url, int port=9090);
	int  setsockopt_impl(  int level, int option, const void *optval, size_t optlen);
	void close_impl();
	void send_impl(  char *data);
	int  recv_impl(  char *data);
	int  RetSetSvr();
private:

	int m_sock;
	int m_port;
	string  strUrl;

};

