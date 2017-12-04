#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__

#include "Hw.h"

#ifdef GPIO_LOCAL
#define GPIO_DEF
#else
#define GPIO_DEF              extern
#endif


GPIO_DEF void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
GPIO_DEF uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
GPIO_DEF void GPIO_Configuration(void);



#endif
