// BaseApplication.cpp : 定义控制台应用程序的入口点。
//

#include "Gess.h"
#include "MainCPMgr.h"

MainCPMgr  theMgr;

int main()
{
	try
	{

		char szFileName[_MAX_PATH], szFilePath[_MAX_PATH];
		char * pcName;
		::GetModuleFileName(0, szFileName, _MAX_PATH);
		::GetFullPathName(szFileName, _MAX_PATH, szFilePath, &pcName);
		char szBuf[_MAX_PATH];
		strcpy(szBuf, pcName);
		*pcName = '\0';
		SetCurrentDirectory(szFilePath);

		//winsock初始化
		WSADATA wsaData;
		int nRtn = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (nRtn != NO_ERROR)
		{
			CRLog(E_ERROR, "%s", "Error at WSAStartup()");
			return -1;
		}

		if (0 == theMgr.Init())
		{
			if (0 == theMgr.Start())
			{
				theMgr.StartMe();
				theMgr.Run();
				/*theMgr.StopMe();
				theMgr.Stop();
				theMgr.Finish();*/
			}
			else
			{
				theMgr.Stop();
				theMgr.Finish();
			}

			//退出时未作线程同步，简单sleep
			Sleep(2);
		}

		WSACleanup();

		return 0;

	}
	catch (std::exception e)
	{
		CRLog(E_CRITICAL, "exception:%s", e.what());
		return -1;
	}
	catch (...)
	{
		CRLog(E_CRITICAL, "%s", "Unknown exception");
		return -1;
	}


    return 0;
}

