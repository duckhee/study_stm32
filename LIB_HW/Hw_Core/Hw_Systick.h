#ifndef __HW_SYSTICK_H__
#define __HW_SYSTICK_H__


#include "Hw.h"

#ifdef SYSTICK_LOCAL
#define SYSTICK_DEF
#else
#define SYSTICK_DEF        extern
#endif

SYSTICK_DEF void Systick_Init(void);
SYSTICK_DEF void Systick_Handler(void);

#endif