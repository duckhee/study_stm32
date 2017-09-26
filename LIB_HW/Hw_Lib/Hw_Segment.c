#define SEGMENT_LOCAL

#include "Hw_Segment.h"


SEG_DEF void 7_SEG_PowerOn()
{
    GPIO_7_SEG->BRR |= GPIO_7_SEG_POWER_PIN;
}
SEG_DEF void 7_SEG_PowerOff()
{
    GPIO_7_SEG->BSRR |= GPIO_7_SEG_POWER_PIN;
}
SEG_DEF void 7_SEG_On_OnePin(uint16_t pinNum)
{
    GPIO_7_SEG->BRR |= pinNum;
}
SEG_DEF void 7_SEG_Off_OnePin(uint16_t pinNum)
{
    GPIO_7_SEG->BSRR |= pinNum;
}
SEG_DEF void 7_SEG_On_All(void)
{
    On_7_SEG_OnePin
    (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
     | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN
     | GPIO_7_SEG_G_PIN | GPIO_7_SEG_DP_PIN);
}
SEG_DEF void 7_SEG_Off_All(void)
{
    Off_7_SEG_OnePin
    (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
     | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN
     | GPIO_7_SEG_G_PIN | GPIO_7_SEG_DP_PIN);
}
SEG_DEF void 7_SEG_On_Number(unsigned int num)
{
    7_SEG_Off_All();

    switch(num)
    {
    case 0:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN);
        break;

    case 1:
        On_7_SEG_OnePin
            (GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN);
        break;

    case 2:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_D_PIN
            | GPIO_7_SEG_E_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 3:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 4:
        On_7_SEG_OnePin
            (GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 5:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_C_PIN | GPIO_7_SEG_D_PIN
            | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 6:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_C_PIN | GPIO_7_SEG_D_PIN
            | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;

    case 7:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_F_PIN);
        break;

    case 8:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN
            | GPIO_7_SEG_G_PIN);
        break;

    case 9:
        On_7_SEG_OnePin
            (GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN
            | GPIO_7_SEG_D_PIN | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN);
        break;
    }
}
