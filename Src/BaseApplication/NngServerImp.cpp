#include "NngServerImp.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//#include "utils\err.h"


char  nngLocalBuf[4096];

CNngServerImp::CNngServerImp()
{
	memset(nngLocalBuf, 0, sizeof(nngLocalBuf));
}


CNngServerImp::~CNngServerImp()
{
}

int CNngServerImp::InitServerUrl(const char *url)
{
	int rv = nng_rep0_open(&m_sock);
	if (rv != 0)
		return  -1;

	rv = nng_listen(m_sock, url, nullptr, 0);
	if (rv != 0)
		return  -1;

	strUrl = url;
	return rv;
}

int CNngServerImp::InitClientUrl(const char *url)
{
	int rv = nng_req0_open(&m_sock);
	if (rv != 0)
		return  -1;
	
	rv = nng_dial(m_sock, url, nullptr, 0);
	if (rv != 0)
		return  -1;
	
	strUrl = url;
	return rv;
}

 void CNngServerImp::closeAll()
{
	 nng_closeall();
}


 int  CNngServerImp::send(const  char *data, int length)
{
	//size_t data_len = strlen(data);
	int rc = nng_send(m_sock, (void *)data, length, 0);// NNG_FLAG_ALLOC);
	if (rc < 0) {
		/*fprintf(stderr, "Failed to send: %s [%d] (%s:%d)\n",
			nn_err_strerror(errno),
			(int)errno, file, line);*/
		abort();
	}
	if (rc != (int)length) {
		/*fprintf(stderr, "Data to send is truncated: %d != %d (%s:%d)\n",
			rc, (int)data_len,
			file, line);*/
		abort();
	}
	return  rc;
}

 


 int CNngServerImp::recv(const  char *data)
{
	 size_t data_len = 0;// strlen(data);
	/*  We allocate plus one byte so that we are sure that message received
	has correct length and not truncated  */
	memset(nngLocalBuf, 0, sizeof(nngLocalBuf));
	char *buf = nngLocalBuf;// (char *)malloc(data_len + 1);
	//alloc_assert(buf);

	int rc = nng_recv(m_sock, &buf, &data_len, 0);
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
	if (memcmp(data, buf, data_len) !=0) {
		/*  We don't print the data as it may have binary garbage  */
		/*fprintf(stderr, "Received data is wrong (%s:%d)\n", file, line);
		abort();*/
	}

	//½âÎöÊý¾Ý
	//memcpy_s(data,data_len,buf,data_len);

	return (int) data_len;
}


