#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__

#include "Hw.h"

#ifdef GPIO_LOCAL
#define GPIO_DEF 
#else
#define GPIO_DEF            extern
#endif

GPIO_DEF void Gpio_Init(void);

GPIO_DEF void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
GPIO_DEF void Gpio_Output_Init();

GPIO_DEF void Gpio_A_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE);
GPIO_DEF void Gpio_B_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE);
GPIO_DEF void Gpio_C_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE);
GPIO_DEF void Gpio_D_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE);

GPIO_DEF uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
GPIO_DEF void GPIO_Configuration(void);

#endif