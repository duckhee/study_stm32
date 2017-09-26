#ifndef __HW_KEY_H__
#define __HW_KEY_H__

#include "Hw.h"

#ifdef KEY_LOCAL
#define KEY_DEF 
#else
#define KEY_DEF                 extern
#endif

#define GPIO_KEY             GPIOA

#define GPIO_KEY1_PIN        GPIO_Pin_0 /* LEFT_WKUP */
#define GPIO_KEY2_PIN        GPIO_Pin_1 /* RIGHT_USER */


KEY_DEF void Key_Test(void);


#endif