#ifndef __LSTRING_H__
#define __LSTRING_H__

#include "Ap.h"

 #ifdef LDSTRING_LOCAL
 #define LDSTRING_DEF
 #else
 #define LDSTRING_DEF        extern
 #endif

 LDSTRING_DEF void Ld_printf(char* fmt, ...);
 LDSTRING_DEF char check_byte(char *key);
 LDSTRING_DEF char Ld_get_byte(void);

#endif