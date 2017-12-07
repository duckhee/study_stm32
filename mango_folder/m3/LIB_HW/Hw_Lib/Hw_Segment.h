#ifndef __HW_SEGMENT_H__
#define __HW_SEGMENT_H__

#include "Hw.h"

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

#ifdef SEGMENT_LOCAL
#define SEG_DEF 
#else
#define SEG_DEF                   extern
#endif

SEG_DEF void PowerOn_7_SEG(void);
SEG_DEF void PowerOff_7_SEG(void);
SEG_DEF void On_7_SEG_OnePin(uint16_t pinNum);
SEG_DEF void Off_7_SEG_OnePin(uint16_t pinNum);
SEG_DEF void On_7_SEG_AllPin(void);
SEG_DEF void Off_7_SEG_AllPin(void);
SEG_DEF void OutPut_7_SEG_Number(unsigned int num);
SEG_DEF void Seven_Segment_Test(void);


#endif