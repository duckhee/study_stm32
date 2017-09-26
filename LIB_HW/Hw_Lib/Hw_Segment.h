#ifndef __HW_SEGMENT_H__
#define __HW_SEGMENT_H__

#include "Hw.h"

#ifdef SEGMENT_LOCAL
#define SEG_DEF 
#else
#define SEG_DEF              extern
#endif


#define GPIO_7_SEG_POWER_PIN    GPIO_Pin_8
#define GPIO_7_SEG_A_PIN        GPIO_Pin_0
#define GPIO_7_SEG_B_PIN        GPIO_Pin_1
#define GPIO_7_SEG_C_PIN        GPIO_Pin_2
#define GPIO_7_SEG_D_PIN        GPIO_Pin_3
#define GPIO_7_SEG_E_PIN        GPIO_Pin_4
#define GPIO_7_SEG_F_PIN        GPIO_Pin_5
#define GPIO_7_SEG_G_PIN        GPIO_Pin_7
#define GPIO_7_SEG_DP_PIN       GPIO_Pin_6

#define GPIO_7_SEG              GPIOC


SEG_DEF void SEG_PowerOn();
SEG_DEF void SEG_PowerOff();
SEG_DEF void SEG_On_OnePin(uint16_t pinNum);
SEG_DEF void SEG_Off_OnePin(uint16_t pinNum);
SEG_DEF void SEG_On_All(void);
SEG_DEF void SEG_Off_All(void);
SEG_DEF void SEG_On_Number(unsigned int num);



#endif
