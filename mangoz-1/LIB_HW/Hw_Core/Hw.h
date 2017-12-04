#ifndef __HW_H__
#define __HW_H__


//include stdint
#include <stdint.h>
//define register
#include "Hw_reg.h"
//include function core
#include "Hw_PLL.h"
#include "Hw_Usart.h"
#include "Hw_Rcc.h"
#include "Hw_Gpio.h"
#include "Hw_Flash.h"


//include printf 
#include "Ld_Printf.h"







#ifdef HW_LOCAL
#define HW_DEF 
#else
#define HW_DEF                    extern
#endif

HW_DEF void Hw_Init(void);



#endif