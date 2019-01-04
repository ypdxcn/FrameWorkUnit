#include "UvServerImp.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



char  uvLocalBuf[4096];

CUvServerImp::CUvServerImp()
{
	memset(uvLocalBuf, 0, sizeof(uvLocalBuf));


}

CUvServerImp::~CUvServerImp()
{
}

int CUvServerImp::InitServerUrl(const char *url)
{
	return 0;
}

 void CUvServerImp::closeAll()
{
}

 int  CUvServerImp::send(const  char *data, int length)
{
	return  0;
}

 int CUvServerImp::recv(const  char *data)
{
		return (int) 0;
}


