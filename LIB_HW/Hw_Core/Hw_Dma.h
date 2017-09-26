#ifndef __HW_DMA_H_
#define __HW_DMA_H_

#include "Hw.h"

#ifdef DMA_LOCAL
#define DMA_DEF
#else
#define DMA_DEF         extern
#endif

DMA_DEF void Dma_Init(void);

#endif