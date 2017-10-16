#define KEY_LOCAL

#include "Hw_Key.h"


KEY_DEF void Key_Test(void)
{
    uint32_t i = 0;
    Led_All_Off();

    while(1)
    {
        Hw_1_second();

        if((i++ & 0x1) == 0x0)
        {
            Led_Blue_On();
        }
        else
        {
            Led_Blue_Off();
        }

        if(GPIO_ReadInputDataBit(GPIO_KEY, GPIO_KEY1_PIN) == Bit_SET)
        {
            Led_Red_On();
        }
        else
        {
            RedLed_Red_Off_Off();
        }
        if(GPIO_ReadInputDataBit(GPIO_KEY, GPIO_KEY2_PIN) == Bit_SET)
        {
            Led_Yellow_On();
        }
        else
        {
            Led_Yellow_Off();
        }
    }
}