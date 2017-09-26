#ifndef __HW_LED_H__
#define __HW_LED_H__

#include "Hw.h"

#ifdef LED_LOCAL
#define LED_DEF
#else
#define LED_DEF          extern
#endif

#define GPIO_LED             GPIOB

#define GPIO_LED1_PIN        GPIO_Pin_9 /* RED */
#define GPIO_LED2_PIN        GPIO_Pin_5 /* YELLOW */ 
#define GPIO_LED3_PIN        GPIO_Pin_8 /* BLUE */

LED_DEF void Led_OnAll();
LED_DEF void Led_OffAll();
LED_DEF void Red_On();
LED_DEF void Red_Off();
LED_DEF void Yellow_On();
LED_DEF void Yellow_Off();
LED_DEF void Blue_On();
LED_DEF void Blue_Off();
LED_DEF void Led_Mult(uint32_t count);
LED_DEF void Led_Test();


#endif