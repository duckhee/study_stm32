#include "main.h"



int main()
{
    
    RCC_ClocksTypeDef  rcc_clocks;

    NVIC_Configuration();
    Hw_Init();

    // /* Setup SysTick Timer for 1 msec interrupts  */
    // if (SysTick_Config(rcc_clocks.SYSCLK_Frequency / 1000))
    // {   
    //     Rcc_GetClocksFreq(&rcc_clocks);
    //     printf("systick config error !!\n");
    //     /* Capture error */ 
    //     while (1);
    // }

    Seg_Main();
    
}