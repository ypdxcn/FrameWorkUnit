#include "NanoServerImp.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "nn.h"
//#include "utils\err.h"
#include "reqrep.h"

char  localBuf[4096];

CNanoServerImp::CNanoServerImp()
{
	memset(localBuf, 0, sizeof(localBuf));
}


CNanoServerImp::~CNanoServerImp()
{
}


int CNanoServerImp::InitServerUrl(const char *url, int port)
{
	m_sock = nn_socket(AF_SP, NN_REQ);

	if (nn_bind(m_sock, url) >= 0)
		return  0;
	else
		return  -1;//绑定失败l

	strUrl = url;
	return m_sock;
}

int CNanoServerImp::RetSetSvr()
{
	m_sock = nn_socket(AF_SP, NN_REQ);

	if (nn_bind(m_sock, strUrl.c_str()) >= 0)
		return  0;
	else
		return  -1;//绑定失败
	return m_sock;
}


 int CNanoServerImp::setsockopt_impl(int level, int option, const void *optval, size_t optlen)
{
	int rc = nn_setsockopt(m_sock, level, option, optval, optlen);
	if (rc < 0) {
		/*fprintf(stderr, "Failed set option \"%d\": %s [%d] (%s:%d)\n",
			option,
			nn_err_strerror(errno),
			(int)errno, file, line);*/
		abort();
	}
	return rc;
}
 void CNanoServerImp::close_impl()
{
	int rc = nn_close(m_sock);
	if ((rc != 0) && (errno != EBADF && errno != ETERM)) {
		/*fprintf(stderr, "Failed to close socket: %s [%d] (%s:%d)\n",
			nn_err_strerror(errno),
			(int)errno, file, line);*/
		abort();
	}

}
 void CNanoServerImp::send_impl( char *data)
{
	size_t data_len = strlen(data);
	int rc = nn_send(m_sock, data, data_len, 0);
	if (rc < 0) {
		/*fprintf(stderr, "Failed to send: %s [%d] (%s:%d)\n",
			nn_err_strerror(errno),
			(int)errno, file, line);*/
		abort();
	}
	if (rc != (int)data_len) {
		/*fprintf(stderr, "Data to send is truncated: %d != %d (%s:%d)\n",
			rc, (int)data_len,
			file, line);*/
		abort();
	}
}

 


 int CNanoServerImp::recv_impl( char *data)
{
	size_t data_len= strlen(data);
	/*  We allocate plus one byte so that we are sure that message received
	has correct length and not truncated  */
	memset(localBuf, 0, sizeof(localBuf));
	char *buf = localBuf;// (char *)malloc(data_len + 1);
	//alloc_assert(buf);

	int rc = nn_recv(m_sock, buf, data_len + 1, 0);
	if (rc < 0) {
	/*	fprintf(stderr, "Failed to recv: %s [%d] (%s:%d)\n",
			nn_err_strerror(errno),
			(int)errno, file, line);*/
		abort();
	}
	if (rc != (int)data_len) {
		/*fprintf(stderr, "Received data has wrong length: %d != %d (%s:%d)\n",
			rc, (int)data_len,
			file, line);*/
		abort();
	}
	if (memcmp(data, buf, data_len) != 0) {
		/*  We don't print the data as it may have binary garbage  */
		/*fprintf(stderr, "Received data is wrong (%s:%d)\n", file, line);
		abort();*/
	}

	//解析数据
	memcpy_s(data,data_len,buf,data_len);

	return (int) data_len;
	//free(buf);
}