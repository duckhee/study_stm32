#define LED_LOCAL

#include "Hw_Led.h"


LED_DEF void Red_On()
{
    GPIO_LED->BRR |= GPIO_LED1_PIN;
}
LED_DEF void Red_Off()
{
    GPIO_LED->BSRR |= GPIO_LED1_PIN;
}
LED_DEF void Yellow_On()
{
    GPIO_LED->BRR |= GPIO_LED2_PIN;
}
LED_DEF void Yellow_Off()
{
    GPIO_LED->BSRR |= GPIO_LED2_PIN;
}
LED_DEF void Blue_On()
{
    GPIO_LED->BRR |= GPIO_LED3_PIN;
}
LED_DEF void Blue_Off()
{
    GPIO_LED->BSRR |= GPIO_LED3_PIN;
}
LED_DEF void Led_OnAll()
{
    Red_On();
    Yellow_On();
    Blue_On();
}
LED_DEF void Led_OffAll()
{
    Red_Off();
    Yellow_Off();
    Blue_Off();
}

LED_DEF void Led_Mult(uint32_t count)
{
    for(;count>0; count--)
    {
        Red_Off();
        Yellow_On();
        Blue_On();
        Hw_1_second();

        Red_On();
        Yellow_Off();
        Blue_On();
        Hw_1_second();

        Red_On();
        Yellow_On();
        Blue_Off();
        Hw_1_second();
        
    }
}

LED_DEF void Led_Test()
{
    #if 0
        Led_OnAll();
        Hw_1_second();
        Led_OffAll();
        Hw_1_second();
        Led_OnAll();
    #else
        Led_Mult(30);
    #endif
}
