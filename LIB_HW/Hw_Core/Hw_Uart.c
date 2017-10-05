#define UART_LOCAL

#include "Hw_Uart.h"

UART_DEF void Uart1_Init()
{
    USART_InitTypeDef USART_InitStructure;
    
        /* USARTx configuration ------------------------------------------------------*/
        /* USARTx configured as follow:
         - BaudRate = 115200 baud  
         - Word Length = 8 Bits
         - One Stop Bit
         - No parity
         - Hardware flow control disabled (RTS and CTS signals)
         - Receive and transmit enabled
         */
        USART_InitStructure.USART_BaudRate   = 115200;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits   = USART_StopBits_1;
        USART_InitStructure.USART_Parity     = USART_Parity_No ;
        USART_InitStructure.USART_HardwareFlowControl
                                             = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
    
        /* Configure the USARTx */ 
        USART_Init(USART1, &USART_InitStructure);
    
        /* Enable the USART1 */
        USART1->CR1 |= CR1_UE_Set;
}