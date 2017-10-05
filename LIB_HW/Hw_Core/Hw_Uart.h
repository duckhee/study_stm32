#ifndef __HW_UART_H__
#define __HW_UART_H__

#include "Hw.h"

#ifdef UART_LOCAL
#define UART_DEF
#else
#define UART_DEF            extern
#endif

UART_DEF void Uart1_Init(void);

UART_DEF void Serial_PutString(uint8_t *s);

UART_DEF void UART_SendData(USART_TypeDef* UARTx, uint16_t Data);

UART_DEF FlagStatus UART_GetFlagStatus(USART_TypeDef* UARTx, uint16_t UART_FLAG);

UART_DEF void SerialPutChar(uint8_t c);

#endif