#ifndef __HW_ADC_H__
#define __HW_ADC_H__

#include "stm32_reg.h"

#ifdef ADC_LOCAL
#define ADC_DEF
#else
#define ADC_DEF
#endif


ADC_DEF void ADC_Init();




#endif