#pragma once


//test  libcur
#include "curl.h"

#include <iostream>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <sstream>

using namespace std;
using namespace boost::property_tree;

// on  UTF-8 转中文GB2312   换C++11的
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}


//c++11新特性,对 string 和 wstring 的转换，对 Unicode 进行了语言和库级别的支持
#include <codecvt>
#include <string>

std::wstring s2ws(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}
//专门写的新的转换版本

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	string data((const char*)ptr, (size_t)size * nmemb);
	*((stringstream*)stream) << data << endl;
	return size * nmemb;
}


static size_t write_memory(char *data, size_t size, size_t nmemb, string *write_data)
{
	unsigned long sizes = size * nmemb;
	if (write_data == nullptr) return 0;

	write_data->append(data, sizes);
	return sizes;
}

std::string wstring2utf8string(const std::wstring& str)
{
	// strcvt中的两个空字符串参数作用是在转换错误时返回空字符串
	// 如果不设置，当传入参数为非UTF-8中文时，会引起程序错误
	std::wstring_convert<std::codecvt_utf8<wchar_t>> strcvt(std::string(""), std::wstring(L""));
	return strcvt.to_bytes(str);
}


int test_Libcurl()
{
	CURL *curl;
	CURLcode res;

	wchar_t *pwText = NULL;
	std::stringstream out;

	curl = curl_easy_init();
	if (curl) {
		//curl_easy_setopt(curl, CURLOPT_URL, "http://101.37.161.45:1009/api/PushNodeServerApi/QueryNodes");
		curl_easy_setopt(curl, CURLOPT_URL, "http://101.37.161.45:1009/api/QuoteQueryProduct/QueryPlateByProduct_PageDatas?pagesize=20&pageindex=1&product=1");
		//curl_easy_setopt(curl, CURLOPT_URL, "http://101.37.161.45:1009/swagger/ui/index#!/QuoteQueryProduct/QuoteQueryProduct_QueryPlatByCenter");

		// 设置接收数据的处理函数和存放变量
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 5000);

		//执行ged操作
		res = curl_easy_perform(curl);
		if (CURLE_OK == res) {
			char *ct;
			res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

			if ((CURLE_OK == res) && ct)
				printf("We received Content-Type: %s\n", ct);
		}
		string str_json = out.str();
		//wcout.imbue(std::locale(".936"));
		//auto  str = wstring2utf8string(str_json);
		
		wstring str_ch = s2ws(str_json);

        wcout.imbue(std::locale(".936"));
        wcout << str_ch << std::endl;
		//std::wcout << str_ch << endl;
		/* always cleanup */
		curl_easy_cleanup(curl);
		wptree pt; //define property_tree object
	    //string test =  str_ch.
		std::wstringstream ss(str_ch);//str_ch
		try {
			read_json(ss, pt);        //parse json
		}
		catch (ptree_error & e) {
			string msg = e.what();
			return 1;
		}

		/*
		auto code = pt.get<string>("code");
		auto message = pt.get<string>("message");
		auto resultLine = pt.get<string>("resultLine");
		auto PageIndex = pt.get<string>("PageIndex");
		auto PageSize = pt.get<string>("PageSize");
		auto Total = pt.get<string>("Total");
		
		auto bodyMessage = pt.get_child("bodyMessage");
		*/

		//for (auto it = bodyMessage.begin(); it != bodyMessage.end(); ++it) {
		//	std::wcout << it->first;
		//	std::wcout << it->second.get<std::wstring>(L"id") << " "
		//		<< it->second.get<std::wstring>(L"temperature") << " "
		//		<< it->second.get<std::wstring>(L"humidity") << " "
		//		<< std::endl;
		//}

	}



	return  1;
}