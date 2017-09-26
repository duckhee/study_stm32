#define CLOCK_LOCAL

#include "Ap_Clock.h"

extern __IO uint32_t StartUpCounter;

CLOCK_DEF void System_Information()
{
    RCC_ClocksTypeDef  rcc_clocks;

    printf("StartUpCounter : %d\n", StartUpCounter);

    RCC_GetClocksFreq(&rcc_clocks);

    printf("SYSCLK_Frequency = %d\n",rcc_clocks.SYSCLK_Frequency );
    printf("HCLK_Frequency = %d\n",rcc_clocks.HCLK_Frequency );
    printf("PCLK1_Frequency = %d\n",rcc_clocks.PCLK1_Frequency );
    printf("PCLK2_Frequency = %d\n",rcc_clocks.PCLK2_Frequency );
    printf("ADCCLK_Frequency = %d\n",rcc_clocks.ADCCLK_Frequency );
    
}
