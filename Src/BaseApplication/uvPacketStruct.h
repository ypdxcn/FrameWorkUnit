#pragma once

/***************************************
* @file     net_base.h
* @brief    �����������ܺ���
* @details  ��С���ж�
32&64λϵͳ�ж�
ntohll��htonl��ʵ��
int32��int64����/�����л�Ϊchar[4],char[8]
���ݰ�ͷ�ṹ����
��winƽ̨���Թ���linuxƽ̨δ����
* @author   phata, wqvbjhc@gmail.com
* @date     2014-5-16
* @mod      2014-5-21 phata ����������˰�ͷ��β�汾��У��λ��Ϣ
****************************************/
#ifndef UV_PACKETSTRUCT_H
#define UV_PACKETSTRUCT_H


#include <stdint.h>
#if defined (WIN32) || defined (_WIN32)
#include <WinSock2.h>
#include <stdlib.h>
#ifdef _MSC_VER
#pragma comment(lib,"Ws2_32.lib")
#endif //_MSC_VER
#else
#include <sys/types.h>
#include <netinet/in.h>
#endif


// һ�����ݰ����ڴ�ṹ
//���Ӱ�ͷ���β���ݣ����ڼ����������ԡ�����ֵ���ڼ�������ȫ�ԡ�
//|-----head----|--------------------------pack header-------------------|--------------------pack data------------|-----tail----|
//|--��ͷ1�ֽ�--|--[version][head][tail][check][type][datalen][reserve]--|--datalen���ȵ��ڴ�����(����typeȥ����)--|--��β1�ֽ�--|
#pragma pack(1)//����ǰ�ֽڶ���ֵ��Ϊ1

#define NET_PACKAGE_VERSION 0x01
typedef struct _NetPacket {//�����Զ������ݰ�ͷ�ṹ
	int32_t version;        //����İ汾�ţ���ͬ�汾���Ķ�����ܲ�ͬ  :0-3
	unsigned char header;   //��ͷ-���Զ��壬����0x02                 :4
	unsigned char tail;     //��β-���Զ��壬����0x03                 :5
	unsigned char check[16];//pack dataУ��ֵ-16�ֽڵ�md5����������   :6-21
	int32_t type;           //�����ݵ�����                            :22-25
	int32_t datalen;        //�����ݵ����ݳ���-�������˰��ṹ�Ͱ�ͷβ :26-29
	int32_t reserve;        //�����ݱ����ֶ�-��ʱ��ʹ��               :30-33
}NetPacket;
#define NET_PACKAGE_HEADLEN sizeof(NetPacket)//��ͷ���ȣ�Ϊ�̶���С34�ֽ�

#pragma pack()//����ǰ�ֽڶ���ֵ��ΪĬ��ֵ(ͨ����4)



//�ж��Ƿ�С���ֽ����Ƿ���true
inline bool  IsLittleendian()
{
	int i = 0x1;
	return *(char *)&i == 0x1;
}

//�ж��Ƿ�32λϵͳ���Ƿ���true
inline bool IsSystem32()
{
	/*
	unsigned short x64 = 0;
#if defined(_MSC_VER)
	__asm mov x64, gs  // vs
#else
	asm("mov %%gs, %0" : "=r"(x64)); // gcc
#endif
	return x64 == 0;
	*/
	return  false;
}

namespace Phata
{
	//htonll��ntohll win8��֧�֣�linux֧��Ҳ��ȫ�������Լ�ʵ��
	inline uint64_t htonll(uint64_t num)
	{
		int i = 0x1;
		uint64_t retval;
		if (*(char *)&i == 0x1) {
#if defined (WIN32) || defined (_WIN32)
			retval = _byteswap_uint64(num);//��htonl��
#elif defined(__linux__ )
			retval = __builtin_bswap64(num);
#else
			retval = ((uint64_t)htonl(num & 0x00000000ffffffffULL)) << 32;
			retval |= htonl((num & 0xffffffff00000000ULL) >> 32);
#endif
		}
		else {
			return num;
		}
		return retval;
	}

	inline uint64_t ntohll(uint64_t num)
	{
		int i = 0x1;
		uint64_t retval;
		if (*(char *)&i == 0x1) {
#if defined (WIN32) || defined (_WIN32)
			retval = _byteswap_uint64(num);
#elif defined(__linux__ )
			retval = __builtin_bswap64(num);
#else
			retval = ((uint64_t)ntohl(num & 0x00000000ffffffffULL)) << 32;
			retval |= ntohl((num & 0xffffffff00000000ULL) >> 32);
#endif
		}
		else {
			return num;
		}
		return retval;
	}
}
//��32λ��int������char[4]��.��תΪ�����ֽ���Ȼ��int�����λ����Ϊchar[0],���λ������char[3]
inline bool Int32ToChar(const uint32_t intnum, unsigned char* charnum)
{
	unsigned long network_byteorder = htonl(intnum);//ת��Ϊ�����ֽ���
	charnum[0] = (unsigned char)((network_byteorder & 0xff000000) >> 24);//int�����λ
	charnum[1] = (unsigned char)((network_byteorder & 0x00ff0000) >> 16);//int�Ĵθ�λ
	charnum[2] = (unsigned char)((network_byteorder & 0x0000ff00) >> 8); //int�Ĵε�λ;
	charnum[3] = (unsigned char)((network_byteorder & 0x000000ff));    //int�����λ;
	return true;
}

//��char[4]ת��Ϊ32λ��int��int�����λ����Ϊchar[0],���λ������char[3]��Ȼ��תΪ�����ֽ���
inline bool CharToInt32(const unsigned char* charnum, uint32_t& intnum)
{
	intnum = (charnum[0] << 24) + (charnum[1] << 16) + (charnum[2] << 8) + charnum[3];
	intnum = ntohl(intnum);//ת��Ϊ�����ֽ���
	return true;
}

//��64λ��int������char[8]��.��תΪ�����ֽ���Ȼ��int�����λ����Ϊchar[0],���λ������char[7]
inline bool Int64ToChar(const uint64_t intnum, unsigned char* charnum)
{
	uint64_t network_byteorder = Phata::htonll(intnum);//ת��Ϊ�����ֽ���
	charnum[0] = (unsigned char)((network_byteorder & 0xff00000000000000ULL) >> 56);//int�����λ
	charnum[1] = (unsigned char)((network_byteorder & 0x00ff000000000000ULL) >> 48);//int�Ĵθ�λ
	charnum[2] = (unsigned char)((network_byteorder & 0x0000ff0000000000ULL) >> 40);
	charnum[3] = (unsigned char)((network_byteorder & 0x000000ff00000000ULL) >> 32);
	charnum[4] = (unsigned char)((network_byteorder & 0x00000000ff000000ULL) >> 24);
	charnum[5] = (unsigned char)((network_byteorder & 0x0000000000ff0000ULL) >> 16);
	charnum[6] = (unsigned char)((network_byteorder & 0x000000000000ff00ULL) >> 8); //int�Ĵε�λ;
	charnum[7] = (unsigned char)((network_byteorder & 0x00000000000000ffULL));    //int�����λ;
	return true;
}

//��char[8]ת��Ϊ64λ��int��int�����λ����Ϊchar[0],���λ������char[7]��Ȼ��תΪ�����ֽ���
inline bool CharToInt64(const unsigned char* charnum, uint64_t& intnum)
{
	intnum = ((uint64_t)charnum[0] << 56) + ((uint64_t)charnum[1] << 48) + ((uint64_t)charnum[2] << 40) + ((uint64_t)charnum[3] << 32) +
		(charnum[4] << 24) + (charnum[5] << 16) + (charnum[6] << 8) + charnum[7];
	intnum = Phata::ntohll(intnum);//ת��Ϊ�����ֽ���
	return true;
}






//NetPackageתΪchar*���ݣ�chardata������38�ֽڵĿռ�
inline bool NetPacketToChar(const NetPacket& package, unsigned char* chardata) {
	if (!Int32ToChar((uint32_t)package.version, chardata)) {
		return false;
	}
	chardata[4] = package.header;
	chardata[5] = package.tail;
	memcpy(chardata + 6, package.check, sizeof(package.check));

	if (!Int32ToChar((uint32_t)package.type, chardata + 22)) {
		return false;
	}
	if (!Int32ToChar((uint32_t)package.datalen, chardata + 26)) {
		return false;
	}
	if (!Int32ToChar((uint32_t)package.reserve, chardata + 30)) {
		return false;
	}
	return true;
}

//char*תΪNetPackage���ݣ�chardata������38�ֽڵĿռ�
inline bool CharToNetPacket(const unsigned char* chardata, NetPacket& package) {
	uint32_t tmp32;
	if (!CharToInt32(chardata, tmp32)) {
		return false;
	}
	package.version = tmp32;
	package.header = chardata[4];
	package.tail = chardata[5];
	memcpy(package.check, chardata + 6, sizeof(package.check));
	if (!CharToInt32(chardata + 22, tmp32)) {
		return false;
	}
	package.type = tmp32;
	if (!CharToInt32(chardata + 26, tmp32)) {
		return false;
	}
	package.datalen = tmp32;
	if (!CharToInt32(chardata + 30, tmp32)) {
		return false;
	}
	package.reserve = tmp32;
	return true;
}


#endif

////��������
//#include <stdio.h>
//#include "common/net/net_base.h"
//int main(int argc, char **argv)
//{
//	printf("islittleendian %d\n",IsLittleendian());
//	printf("IsSystem32 %d\n",IsSystem32());
//	uint32_t intnum = 0x1234567A;
//	unsigned char charnum[4];
//	Int32ToChar(intnum,&charnum[0]);
//	printf("Int32ToChar-int=0x%x, %d, char=%x,%x,%x,%x\n",intnum,intnum,charnum[0],charnum[1],charnum[2],charnum[3]);
//	CharToInt32(&charnum[0],intnum);
//	printf("CharToInt32-int=0x%x, %d, char=%x,%x,%x,%x\n",intnum,intnum,charnum[0],charnum[1],charnum[2],charnum[3]);
//
//	uint64_t int64num = 0x123456789ABCDEF0;
//	unsigned char char8num[8];
//	Int64ToChar(int64num,char8num);
//	printf("Int64ToChar-int=0x%I64x, %I64d, char=%x,%x,%x,%x,%x,%x,%x,%x\n",int64num,int64num,char8num[0],char8num[1],char8num[2],
//		char8num[3],char8num[4],char8num[5],char8num[6],char8num[7]);
//	CharToInt64(char8num,int64num);
//	printf("CharToInt64-int=0x%I64x, %I64d, char=%x,%x,%x,%x,%x,%x,%x,%x\n",int64num,int64num,char8num[0],char8num[1],char8num[2],
//		char8num[3],char8num[4],char8num[5],char8num[6],char8num[7]);
//
//	printf("sizeof NetPackage=%d\n",sizeof(NetPacket));
//	unsigned char packagechar[NET_PACKAGE_HEADLEN];
//	NetPacket package;
//	package.type = intnum;
//	package.reserve = intnum + 1;
//	package.datalen = int64num;
//	memset(packagechar,0,NET_PACKAGE_HEADLEN);
//	NetPacketToChar(package,packagechar);
//	printf("NetPackageToChar -- package data (type=%d,reserve=%d,datalen=%d), char=",package.type,package.reserve,package.datalen);
//	for (int i=0; i<NET_PACKAGE_HEADLEN; ++i) {
//		printf("%x,",packagechar[i]);
//	}
//	printf("\n");
//	memset(&package,0,NET_PACKAGE_HEADLEN);
//	CharToNetPacket(packagechar,package);
//	printf("CharToNetPackage -- package data (type=%d,reserve=%d,datalen=%d), char=",package.type,package.reserve,package.datalen);
//	for (int i=0; i<NET_PACKAGE_HEADLEN; ++i) {
//		printf("%x,",packagechar[i]);
//	}
//	printf("\n");
//	memset(packagechar,0,NET_PACKAGE_HEADLEN);
//	NetPacketToChar(package,packagechar);
//	printf("NetPackageToChar -- package data (type=%d,reserve=%d,datalen=%d), char=",package.type,package.reserve,package.datalen);
//	for (int i=0; i<NET_PACKAGE_HEADLEN; ++i) {
//		printf("%x,",packagechar[i]);
//	}
//	printf("\n");
//	return 0;
//}