#ifndef __HW_LED_H__
#define __HW_LED_H__

#include "Hw.h"

#ifdef LED_LOCAL
#define LED_DEF
#else
#define LED_DEF          extern
#endif

LED_DEF void Led_OnAll();
LED_DEF void Led_OffAll();
LED_DEF void Led_Mult();
LED_DEF void Red_On();
LED_DEF void Red_Off();
LED_DEF void Yellow_On();
LED_DEF void Yellow_Off();
LED_DEF void Blue_On();
LED_DEF void Blue_Off();


#endif