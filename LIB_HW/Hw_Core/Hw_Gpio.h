#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__

#ifdef GPIO_LOCAL
#define GPIO_DEF 
#else
#define GPIO_DEF            extern
#endif

GPIO_DEF void Gpio_Init(void);


#endif