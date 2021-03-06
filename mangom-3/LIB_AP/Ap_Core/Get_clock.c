#define CLOCK_LOCAL

#include "Get_clock.h"

#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)

 static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
 static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};


CLOCK_DEF void Rcc_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
CLOCK_DEF void System_Information();

CLOCK_DEF void Rcc_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

    
    
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;
  printf("tmp :::: %d\n", tmp);
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      printf("HSI_Value :::: %d\n",HSI_Value);
      break;

    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_Value;
      printf("HSE_VLAUE :::: %d\n",HSE_Value);
      break;

    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;
      printf("pllmull :::: %d\n", pllmull);
      printf("pllsource :::: %d\n", pllsource);
      pllmull = ( pllmull >> 18) + 2;
      printf("pllmull :::: %d\n", pllmull);
      if (pllsource == 0x00)
      {/* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
        printf("SYSCLK_Frequency : %d\n", (HSI_Value >> 1) * pllmull);
        
      }
      else
      {/* HSE selected as PLL clock entry */
        if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
        {/* HSE oscillator clock divided by 2 */
          RCC_Clocks->SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
          printf("SYSCLK_Frequency : %d\n", (HSE_Value >> 1) * pllmull);
        }
        else
        {
          RCC_Clocks->SYSCLK_Frequency = HSE_Value * pllmull;
          printf("SYSCLK_Frequency : %d\n", HSE_Value * pllmull);
        }
      }
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      printf("HSI_Value : %d\n", HSI_Value);
      break;
  }

  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  printf("tmp HCLK : %d\n", tmp);
  tmp = tmp >> 4;
  printf("HCLK tmp  : %d\n", tmp);
  printf("HCLK_Frequency tmp : %08x\n", tmp);
  presc = APBAHBPrescTable[tmp];
  printf("HCLK_Frequency presc : %08x\n", presc);
  printf("HCLK_Frequency presc : %d\n",presc);
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  printf(" tmp PCLK1_Frequency : %d\n", tmp);
  tmp = tmp >> 8;
  printf("PCLK1_Frequency tmp  : %d\n", tmp);
  presc = APBAHBPrescTable[tmp];
  printf("PCLK1_Frequency presc : %08x\n", presc);
  printf("PCLK1_Frequency presc : %d\n", presc);
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  

  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  printf(" tmp PCLK1_Frequency : %\d\n", tmp);
  tmp = tmp >> 11;
  printf("PCLK1_Frequency tmp  : %\d\n", tmp);
  presc = APBAHBPrescTable[tmp];
  printf("PCLK2_Frequency presc : %08x\n", presc);
  printf("PCLK2_Frequency presc : %d\n", presc);
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  

  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  printf(" tmp ADCCLK_Frequency : %d\n", tmp);
  tmp = tmp >> 14;
  printf("ADCCLK_Frequency tmp : %d\n", tmp);
  presc = ADCPrescTable[tmp];
  printf("ADCCLK_Frequency presc : %08x\n", presc);
  printf("ADCCLK_Frequency presc : %d\n", presc);
  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
  
}

extern __IO uint32_t StartUpCouter;

CLOCK_DEF void System_Information()
{

    RCC_ClocksTypeDef rcc_clock;
    printf("StartupCounter : %d\n", StartUpCouter);
    Rcc_GetClocksFreq(&rcc_clock);
    printf("System clock frequency = %d\n", rcc_clock.SYSCLK_Frequency);
    printf("HCLK_Freqeuncy : %d\n", rcc_clock.HCLK_Frequency);
    printf("PCLK1_Frequency : %d\n", rcc_clock.PCLK1_Frequency);
    printf("PCLK2_Frequency : %d\n", rcc_clock.PCLK2_Frequency);
    printf("ADCCLK_Frequency : %d\n", rcc_clock.ADCCLK_Frequency);
}