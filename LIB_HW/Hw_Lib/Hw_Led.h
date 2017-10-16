#ifndef __HW_LED_H__
#define __HW_LED_H__

#include "Hw.h"

#ifdef LED_LOCAL
#define LED_DEF
#else
#define LED_DEF           extern
#endif


#define GPIO_LED             GPIOB

#define GPIO_LED1_PIN        GPIO_Pin_9 /* RED */
#define GPIO_LED2_PIN        GPIO_Pin_5 /* YELLOW */ 
#define GPIO_LED3_PIN        GPIO_Pin_8 /* BLUE */


LED_DEF void Led_Red_On();
LED_DEF void Led_Red_Off();
LED_DEF void Led_Yellow_On();
LED_DEF void Led_Yellow_Off();
LED_DEF void Led_Blue_On();
LED_DEF void Led_Blue_Off();
LED_DEF void Led_All_On();
LED_DEF void Led_All_Off();
LED_DEF void Led_Mult(uint32_t counting);
LED_DEF void Led_Test();


#endif