#ifndef __HW_H__
#define __HW_H__



#include <stdint.h>


#include "stm32_reg.h"

//#include "StartUp.h"


//HW SETTING
#include "Hw_Gpio.h"
#include "Hw_Usart.h"
#include "Hw_HSE.h"
#include "Hw_NVIC.h"


//HW LIB
#include "Hw_Led.h"
#include "Hw_Key.h"
#include "Hw_Segment.h"


//Library
#include "Ld_Printf.h"
#include "Util.h"



#ifdef HW_LOCAL
#define HW_DEF
#else
#define HW_DEF                 extern
#endif


HW_DEF void Hw_Init();
HW_DEF void RCC_Configuration(void);


#endif