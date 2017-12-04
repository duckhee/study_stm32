#ifndef __HW_USART_H__
#define __HW_USART_H__

#include "Hw.h"

#define GPIO_USART            GPIOA
#define GPIO_USART_Rx_Pin     GPIO_Pin_10
#define GPIO_USART_Tx_Pin     GPIO_Pin_9


/* USART OverSampling-8 Mask */
#define CR1_OVER8_Set             ((uint16_t)0x8000)  /* USART OVER8 mode Enable Mask */
#define CR1_OVER8_Reset           ((uint16_t)0x7FFF)  /* USART OVER8 mode Disable Mask */

/* USART One Bit Sampling Mask */
#define CR3_ONEBITE_Set           ((uint16_t)0x0800)  /* USART ONEBITE mode Enable Mask */
#define CR3_ONEBITE_Reset         ((uint16_t)0xF7FF)  /* USART ONEBITE mode Disable Mask */


#ifdef USART_LOCAL
#define USART_DEF 
#else
#define USART_DEF         extern
#endif

USART_DEF void USART1_Init(void);
USART_DEF void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);


#endif