#ifndef __HW_NVIC_H__
#define __HW_NVIC_H__

#include "Hw.h"


#ifdef NVIC_LOCAL
#define NVIC_DEF
#else
#define NVIC_DEF               extern
#endif


NVIC_DEF void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
NVIC_DEF void NVIC_Configuration(void);


#endif