#ifndef __HW_UART_H__
#define __HW_UART_H__

#include "Hw.h"

#ifdef UART_LOCAL
#define UART_DEF
#else
#define UART_DEF            extern
#endif

UART_DEF void Uart1_Init(void);


#endif