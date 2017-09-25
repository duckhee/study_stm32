#ifndef __HW_PWM_H__
#define __HW_PWM_H__

#ifdef PWM_LOCAL
#define PWM_DEF
#else
#define PWM_DEF           extern
#endif

PWM_DEF void Pwm_Init(void);


#endif