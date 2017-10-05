#ifndef __HW_PWM_H__
#define __HW_PWM_H__

#include "Hw.h"

#ifdef PWM_LOCAL
#define PWM_DEF
#else
#define PWM_DEF           extern
#endif

PWM_DEF void Pwm_Init(void);

PWM_DEF void Pwm_Duty(unsigned short change_duty);

#endif