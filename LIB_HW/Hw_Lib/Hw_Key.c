#define KEY_LOCAL

#include "Hw_Key.h"


KEY_DEF void Key_Test(void)
{
    uint32_t i = 0;
    Led_OffAll();

    while(1)
    {
        Hw_1_second();

        if((i++ & 0x1) == 0x0)
        {
            LED_On_Blue();
        }
        else
        {
            LED_Off_Blue();
        }

        if(GPIO_ReadInputDataBit(GPIO_KEY, GPIO_KEY1_PIN) == Bit_SET)
        {
            Red_On();
        }
        else
        {
            Red_Off();
        }
        if(GPIO_ReadInputDataBit(GPIO_KEY, GPIO_KEY2_PIN) == Bit_SET)
        {
            Yellow_On();
        }
        else
        {
            Yellow_Off();
        }
    }
}