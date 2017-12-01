#ifndef __UTIL_H__
#define __UTIL_H__

#include "Ap.h"

#ifdef UTIL_LOCAL
#define UTIL_DEF
#else
#define UTIL_DEF               extern
#endif

UTIL_DEF void Hw_1_second();
UTIL_DEF void Hw_second(volatile unsigned int time);

#endif