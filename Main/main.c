#include "main.h"


int main()
{
    RCC->APB2ENR |= RCC_APB2Periph_GPIOB;
    Hw_Init();
    Led_Test();
}