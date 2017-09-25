#ifndef __HW_H__
#define __HW_H__

//stm32 register def
#include "stm32_reg.h"

//interrupt
#include "Hw_Systick.h"

//function init
#include "Hw_Gpio.h"
#include "Hw_I2c.h"
#include "Hw_Pwm.h"
#include "Hw_Adc.h"
#include "Hw_Dma.h"

//driver
#include "Hw_Led.h"

/* defines */

#define GPIO_LED             GPIOB
#define GPIO_KEY             GPIOA
#define GPIO_USART           GPIOA

#define GPIO_LED1_PIN        GPIO_Pin_9 /* RED */
#define GPIO_LED2_PIN        GPIO_Pin_5 /* YELLOW */ 
#define GPIO_LED3_PIN        GPIO_Pin_8 /* BLUE */

#define GPIO_KEY1_PIN        GPIO_Pin_0 /* LEFT_WKUP */
#define GPIO_KEY2_PIN        GPIO_Pin_1 /* RIGHT_USER */

#define GPIO_USART_Rx_Pin    GPIO_Pin_10
#define GPIO_USART_Tx_Pin    GPIO_Pin_9

#ifdef HW_LOCAL
#define HW_DEF
#else
#define HW_DEF            extern
#endif

HW_DEF void Hw_Init();



#endif