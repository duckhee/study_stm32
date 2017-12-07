#ifndef __HW_DMA_H__
#define __HW_DMA_H__

#include "Hw.h"


#ifdef DMA_LOCAL
#define DMA_DEF 
#else
#define DMA_DEF                extern
#endif





DMA_DEF void DMA_Init(void);
DMA_DEF void DMA_ADC_Init(void);



#endif