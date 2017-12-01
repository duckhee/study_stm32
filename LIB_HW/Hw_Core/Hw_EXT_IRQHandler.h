#ifndef __HW_EXT_IRQHANDLER_H__
#define __HW_EXT_IRQHANDLER_H__

#include "Hw.h"

#ifdef HW_EXT_IRQ_LOCAL
#define HW_EXT_IRQ_DEF
#else
#define HW_EXT_IRQ_DEF                        extern
#endif

#define GPIO_PORTSOURCE_KEY        GPIO_PortSourceGPIOA
#define GPIO_PINSOURCE_KEY1        GPIO_PinSource0
#define GPIO_PINSOURCE_KEY2        GPIO_PinSource1
#define GPIO_EXTI_Line_KEY1        EXTI_Line0
#define GPIO_EXTI_Line_KEY2        EXTI_Line1
#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)



HW_EXT_IRQ_DEF void EXTI_Configuration(void);
HW_EXT_IRQ_DEF ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
HW_EXT_IRQ_DEF void EXTI_ClearITPendingBit(uint32_t EXTI_Line);
HW_EXT_IRQ_DEF void EXTI0_IRQHandler(void);
HW_EXT_IRQ_DEF void EXTI1_IRQHandler(void);
HW_EXT_IRQ_DEF void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
HW_EXT_IRQ_DEF void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);



#endif