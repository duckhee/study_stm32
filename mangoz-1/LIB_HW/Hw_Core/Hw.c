
#define HW_LOCAL

#include "Hw.h"


HW_DEF void Hw_Init()
{
    HSI_Init();

    RCC->APB2ENR |= RCC_APB2Periph_GPIOA; //usart set 
    RCC->APB2ENR |= RCC_APB2Periph_GPIOB; 
    RCC->APB2ENR |= RCC_APB2Periph_USART1; //usart set
    
    GPIO_Configuration();
    USART1_Init();

    printf("\r\nHello World! Hello Cortex-M3!\r\n");

}