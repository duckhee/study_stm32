#ifndef __HW_HSE_H__
#define __HW_HSE_H__

#include "Hw.h"

#ifdef HSE_LOCAL
#define HSE_DEF
#else
#define HSE_DEF              extern
#endif



HSE_DEF void HSE_Init();


#endif