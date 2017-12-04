#define RCC_LOCAL

#include "Hw_Rcc.h"

__IO uint32_t StartUpCouter = 0;

RCC_DEF void HSI_Init(void)
{
    __IO uint32_t HSIStatus = 0;
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCouter++;
    }while((HSIStatus == 0) && (StartUpCouter != HSIStartUp_TimeOut));

    /* Flash 2 wait State */
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
    /* HCLK = SYSTICK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
    /* PLL configuration : PLLCLK = HSE * 6 = 72MHz */
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL6);
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;
    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
        ;
    }
    /* seleect PLL as system clock source */
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
    /* Wailt til PLL is used as system clock source */
    while((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
        ;
    }
    
}

RCC_DEF void HSE_Init(void)
{
    __IO uint32_t HSEStatus = 0;
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCouter++;

    }while((HSEStatus == 0) && (StartUpCouter != HSEStartUp_TimeOut));

    /* Flash 2 wait State */
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
    /* HCLK = SYSTICK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
    /* PLL configuration : PLLCLK = HSE * 6 = 72MHz */
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL6);
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;
    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
        ;
    }
    /* seleect PLL as system clock source */
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
    /* Wailt til PLL is used as system clock source */
    while((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
        ;
    }

}
