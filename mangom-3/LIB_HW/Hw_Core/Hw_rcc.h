#ifndef __HW_RCC_H__
#define __HW_RCC_H__

#include "Hw.h"


#ifdef HW_RCC_LOCAL
#define HW_RCC_DEF
#else
#define HW_RCC_DEF           extern
#endif


HW_RCC_DEF void RCC_Configuration(void);
HW_RCC_DEF void RCC_APB1function(uint32_t RCC_APB1Periph, FunctionalState newState);
HW_RCC_DEF void RCC_APB2function(uint32_t RCC_APB2Periph, FunctionalState newState);
HW_RCC_DEF void RCC_APBfunction(uint32_t RCC_APBPeriph, FunctionalState NewState);
HW_RCC_DEF void SetSysClockTo72(void);

#endif // !__HW_RCC_H__
