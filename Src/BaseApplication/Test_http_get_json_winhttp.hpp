#pragma once

// TestDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
//#include "jsonparser.h"
#include <string>
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")

#include <iostream>
using namespace std;


int test_winhttp_get_json()
{
	HINTERNET hSession = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hRequest = NULL;

	//1. ��ʼ��һ��WinHTTP-session���������1Ϊ�˾��������
	hSession = WinHttpOpen(L"csdn@elaine_bao", NULL, NULL, NULL, NULL);
	if (hSession == NULL) {
		cout << "Error:Open session failed: " << GetLastError() << endl;
		return -1;
	}

	//http://101.37.161.45:1009/api/PushNodeServerApi/QueryNodes
	//http://101.37.161.45:1009/api/QuoteQueryProduct/QueryPlateByProduct_PageDatas?pagesize=20&pageindex=1&product=1
	//http://10.81.173.18:1009/api/QuoteQueryProduct/QueryALLProduct
	 //2. ͨ������������ӵ�����������Ҫָ��������IP�Ͷ˿ںš������ӳɹ������ص�hConnect�����ΪNULL
	hConnect = WinHttpConnect(hSession, L"101.37.161.45", (INTERNET_PORT)1009, 0);
	if (hConnect == NULL) {
		cout << "Error:Connect failed: " << GetLastError() << endl;
		return -1;
	}

	//3. ͨ��hConnect�������һ��hRequest��������ڷ����������ȡ�ӷ��������ص����ݡ�
	hRequest = WinHttpOpenRequest(hConnect, L"Get", L"api/QuoteQueryProduct/QueryPlateByProduct_PageDatas?pagesize=20&pageindex=1&product=1", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	//���в���2��ʾ����ʽ���˴�ΪPost������3:����Post�ľ����ַ��������ľ����ַΪhttp://192.168.50.112/getServiceInfo
	if (hRequest == NULL) {
		cout << "Error:OpenRequest failed: " << GetLastError() << endl;
		return -1;
	}

	//4-1. �����������post����
	//(1) ָ�����͵���������
	string data = "This is my data to be sent";
	const void *ss = (const char *)data.c_str();

	//(2) ��������
	BOOL bResults;
	bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, const_cast<void*>(ss), data.length(), data.length(), 0);
	if (!bResults) {
		cout << "Error:SendRequest failed: " << GetLastError() << endl;
		return -1;
	}
	else {
		//��3�� ��������ɹ���׼�����ܷ�������response��ע�⣺��ʹ�� WinHttpQueryDataAvailable��WinHttpReadDataǰ����ʹ��WinHttpReceiveResponse����access���������ص�����
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}

	//4-2. ��ȡ�������������ݵ�header��Ϣ����һ����������ȡ�������ݵ��������͡�
	LPVOID lpHeaderBuffer = NULL;
	DWORD dwSize = 0;
	if (bResults)
	{
		//(1) ��ȡheader�ĳ���
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF,
			WINHTTP_HEADER_NAME_BY_INDEX, NULL,
			&dwSize, WINHTTP_NO_HEADER_INDEX);

		//(2) ����header�ĳ���Ϊbuffer�����ڴ�ռ�
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			lpHeaderBuffer = new WCHAR[dwSize / sizeof(WCHAR)];

			//(3) ʹ��WinHttpQueryHeaders��ȡheader��Ϣ
			bResults = WinHttpQueryHeaders(hRequest,
				WINHTTP_QUERY_RAW_HEADERS_CRLF,
				WINHTTP_HEADER_NAME_BY_INDEX,
				lpHeaderBuffer, &dwSize,
				WINHTTP_NO_HEADER_INDEX);
		}
	}
	printf("Header contents: \n%S", lpHeaderBuffer);

	//��������header��Ϣ�ᷢ�ַ������������ݵ�charsetΪuft-8������ζ�ź�����Ҫ�Ի�ȡ����raw data���п��ַ�ת����һ��ʼ����û����ʶ����Ҫ����ת�����Եõ������ݶ������롣
	//���������ԭ���ǣ�HTTP�ڴ���������Ƕ�ֵ�ģ�����û��text������unicode�ĸ��HTTPʹ��7bit��ASCII����ΪHTTP headers����������������Ķ�ֵ���ݣ���Ҫ����header��ָ���ı��뷽ʽ����������ͨ����Content-Type header��.
	//��˵�����յ�ԭʼ��HTTP����ʱ���Ƚ��䱣�浽char[] buffer�У�Ȼ������WinHttpQueryHearders()��ȡHTTPͷ���õ����ݵ�Content-Type,�������֪�����ݵ�����ɶ���͵��ˣ���ASCII����Unicode����������
	//һ����֪���˾���ı��뷽ʽ����Ϳ���ͨ��MultiByteToWideChar()����ת���ɺ��ʱ�����ַ�������wchar_t[]�С�
	//��������Ľ�������뿴4-4

	//4-3. ��ȡ��������������
	LPSTR pszOutBuffer = NULL;
	DWORD dwDownloaded = 0;         //ʵ����ȡ���ַ���
	wchar_t *pwText = NULL;
	if (bResults)
	{
		do
		{
			//(1) ��ȡ�������ݵĴ�С�����ֽ�Ϊ��λ��
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
				cout << "Error��WinHttpQueryDataAvailable failed��" << GetLastError() << endl;
				break;
			}
			if (!dwSize)    break;  //���ݴ�СΪ0                

									//(2) ���ݷ������ݵĳ���Ϊbuffer�����ڴ�ռ�
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer) {
				cout << "Out of memory." << endl;
				break;
			}
			ZeroMemory(pszOutBuffer, dwSize + 1);       //��buffer��0

														//(3) ͨ��WinHttpReadData��ȡ�������ķ�������
			if (!WinHttpReadData(hRequest, pszOutBuffer, dwSize, &dwDownloaded)) {
				cout << "Error��WinHttpQueryDataAvailable failed��" << GetLastError() << endl;
			}
			if (!dwDownloaded)
				break;

		} while (dwSize > 0);

		//4-4. ����������ת����UTF8
		DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, pszOutBuffer, -1, NULL, 0);    //����ԭʼASCII����ַ���Ŀ       
		pwText = new wchar_t[dwNum+1];                                              //����ASCII����ַ�������UTF8�Ŀռ�
		MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, pwText, dwNum);           //��ASCII��ת����UTF8
		printf("Received contents: \n%S", pwText);
	}


	//5. ���ιر�request��connect��session���
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);


	return 0;
}

