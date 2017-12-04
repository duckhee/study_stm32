#ifndef __HW_RCC_H__
#define __HW_RCC_H__

#include "Hw.h"

#ifdef RCC_LOCAL
#define RCC_DEF
#else
#define RCC_DEF              extern
#endif

RCC_DEF void HSE_Init(void);
RCC_DEF void HSI_Init(void);


#endif