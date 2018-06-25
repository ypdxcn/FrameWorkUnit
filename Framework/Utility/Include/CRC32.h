#ifndef _GESS_CRC_32_H_
#define _GESS_CRC_32_H_
#include "GESS.h"


// CRC32 Class
class UTIL_CLASS CCRC32
{
private:
	static unsigned int crc_32_tab[256];
    static unsigned int UPDC32(unsigned char octet, unsigned int crc);
public:
    static unsigned int crc32_loader(unsigned char *sp,unsigned int len);
};
#endif