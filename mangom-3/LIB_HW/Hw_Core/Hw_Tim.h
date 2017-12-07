#ifndef __HW_TIM_H__
#define __HW_TIM_H__

#include "Hw.h"

#ifdef HW_TIM_LOCAL
#define TIM_DEF
#else
#define TIM_DEF                    extern
#endif


TIM_DEF void Tim_Init(void);


#endif