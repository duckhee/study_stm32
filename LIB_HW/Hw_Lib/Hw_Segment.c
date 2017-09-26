#define SEGMENT_LOCAL

#include "Hw_Segment.h"


SEG_DEF void SEG_PowerOn()
{
    GPIO_7_SEG->BRR |= GPIO_7_SEG_POWER_PIN;
}
SEG_DEF void SEG_PowerOff()
{
    GPIO_7_SEG->BSRR |= GPIO_7_SEG_POWER_PIN;
}
SEG_DEF void SEG_On_OnePin(uint16_t pinNum)
{
    GPIO_7_SEG->BRR |= pinNum;
}
SEG_DEF void SEG_Off_OnePin(uint16_t pinNum)
{
    GPIO_7_SEG->BSRR |= pinNum;
}
SEG_DEF void SEG_On_All(void)
{
    SEG_On_OnePin
    (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
     | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN
     | GPIO_7_SEG_G_PIN | GPIO_7_SEG_DP_PIN);
}

SEG_DEF void SEG_Off_All(void)
{
    SEG_Off_OnePin
    (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
     | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN
     | GPIO_7_SEG_G_PIN | GPIO_7_SEG_DP_PIN);
}

SEG_DEF void SEG_On_Number(unsigned int num)
{
    SEG_Off_All();

    switch(num)
    {
    case 0:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN);
        break;

    case 1:
            SEG_On_OnePin
            (GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN);
        break;

    case 2:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_D_PIN
            | GPIO_7_SEG_E_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 3:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 4:
            SEG_On_OnePin   
            (GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 5:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_C_PIN | GPIO_7_SEG_D_PIN
            | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 6:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_C_PIN | GPIO_7_SEG_D_PIN
            | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 7:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_F_PIN);
        break;

    case 8:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN
            | GPIO_7_SEG_G_PIN);
        break;

    case 9:
            SEG_On_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;
    }
}
