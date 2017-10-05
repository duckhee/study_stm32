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
        USART1_Init(USART1, &USART_InitStructure);
    
        /* Enable the USART1 */
        USART1->CR1 |= CR1_UE_Set;
}

UART_DEF void Serial_PutString(uint8_t *s)
{
    while(*s != '\0')
    {
        SerialPutChar(*s);
        s++;
    }
}

UART_DEF void UART_SendData(USART_TypeDef* UARTx, uint16_t Data)
{
    UARTx->DR = (Data & (uint16_t)0x01FF);
}

UART_DEF FlagStatus UART_GetFlagStatus(USART_TypeDef* UARTx, uint16_t UART_FLAG)
{
    FlagStatus bitstatus = RESET;

    if((UARTx->SR & UART_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

UART_DEF void SerialPutChar(uint8_t c)
{
    UART_SendData(USART1, c);
    while(UART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

