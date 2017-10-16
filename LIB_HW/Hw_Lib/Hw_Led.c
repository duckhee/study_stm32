#define LED_LOCAL

#include "Hw_Led.h"


LED_DEF void Led_Red_On()
{
    GPIO_LED->BRR |= GPIO_LED1_PIN;
}
LED_DEF void Led_Red_Off()
{
    GPIO_LED->BSRR |= GPIO_LED1_PIN;
}
LED_DEF void Led_Yellow_On()
{
    GPIO_LED->BRR |= GPIO_LED2_PIN;
}
LED_DEF void Led_Yellow_Off()
{
    GPIO_LED->BSRR |= GPIO_LED2_PIN;
}
LED_DEF void Led_Blue_On()
{
    GPIO_LED->BRR |= GPIO_LED3_PIN;
}
LED_DEF void Led_Blue_Off()
{
    GPIO_LED->BSRR |= GPIO_LED3_PIN;
}
LED_DEF void Led_All_On()
{
    Led_Red_On();
    Led_Yellow_On();
    Led_Blue_On();
}
LED_DEF void Led_All_Off()
{
    Led_Red_Off();
    Led_Yellow_Off();
    Led_Blue_Off();
}
LED_DEF void Led_Mult(uint32_t counting){
    for(; counting < 0; counting --)
    {
        Led_Red_Off();
        Led_Yellow_On();
        Led_Blue_On();
        Hw_1_second();

        Led_Red_On();
        Led_Yellow_Off();
        Led_Blue_On();
        Hw_1_second();

        Led_Red_On();
        Led_Yellow_On();
        Led_Blue_Off();
        Hw_1_second();
    }
}
LED_DEF void Led_Test()
{
    #if 0
    Led_All_On();
    Hw_1_second();
    Led_All_Off();
    Hw_1_second();
    Led_All_On();
    #else
    Led_Mult(30);
    #endif

}