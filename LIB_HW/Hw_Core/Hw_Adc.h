#ifndef __HW_ADC_H__
#define __HW_ADC_H__

#include "Hw.h"

#ifdef ADC_LOCAL
#define ADC_DEF
#else
#define ADC_DEF            extern
#endif


ADC_DEF void ADC_Init();




#endif