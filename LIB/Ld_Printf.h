#ifndef __LSTRING_H__
#define __LSTRING_H__

#include "Hw.h"

 #ifdef LSTRING_LOCAL
 #define LSTRING_DEF
 #else
 #define LSTRING_DEF        extern
 #endif

 LSTRING_DEF void printf(char* fmt, ...);
 LSTRING_DEF char check_byte(char *key);
 LSTRING_DEF char get_byte(void);

#endif