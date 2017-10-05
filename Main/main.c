#include "main.h"

RCC_ClocksTypeDef  rcc_clocks;

int main()
{
    
    Hw_Init();
    Led_OffAll();
    RCC_GetClocksFreq(&rcc_clocks);
    Led_Main();
}