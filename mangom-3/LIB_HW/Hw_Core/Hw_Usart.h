#ifndef __HW_USART_H__
#define __HW_USART_H__

#include "Hw.h"


#define GPIO_USART           GPIOA

#define GPIO_USART_Rx_Pin    GPIO_Pin_10
#define GPIO_USART_Tx_Pin    GPIO_Pin_9


#ifdef USART_LOCAL
#define USART_DEF
#else
#define USART_DEF                 extern
#endif


USART_DEF void USART1_Init(void);
USART_DEF void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);

#endif