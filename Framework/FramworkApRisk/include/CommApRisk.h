#ifndef _COMM_AP_RISK_H
#define _COMM_AP_RISK_H
#include "Config.h"

#include "Comm.h"

#ifdef _WIN32
#ifdef COMMAPRISK_EXPORT
#define COMMAPRISK_API			__declspec(dllexport)
#define COMMAPRISK_CLASS		__declspec(dllexport)
#else
#define COMMAPRISK_API			__declspec(dllimport)
#define COMMAPRISK_CLASS		__declspec(dllimport)
#endif
#else
#define COMMAPRISK_API
#define COMMAPRISK_CLASS
#endif

#endif