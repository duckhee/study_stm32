#define HW_LOCAL


#include "Hw.h"


__IO uint32_t StartUpCounter = 0;
RCC_ClocksTypeDef  rcc_clocks;
__IO uint16_t ADCConvertedValue;
static volatile uint32_t TimingDelay;

void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


void DMA_Configuration(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* DMA1 channel1 configuration */
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* Enable DMA1 Channel1 */
    DMA_Enable(DMA1_Channel1, ENABLE);
}

HW_DEF void Hw_Init()
{
    
    RCC_APB2function(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2function(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2function(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APBfunction(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2function(RCC_APB2Periph_ADC1, ENABLE);
    RCC->APB2ENR |= RCC_APB2Periph_GPIOA;
    RCC->APB2ENR |= RCC_APB2Periph_GPIOB;
    RCC->APB2ENR |= RCC_APB2Periph_GPIOC;
    RCC->APB2ENR |= RCC_APB2Periph_USART1;
    GPIO_Configuration();
    System_Information();
    ADC_Print();
    printf("end\n");
    //LED, KEY, USART, SEGMENT config
}

HW_DEF void ADC_Print(void)
{
    DMA_Configuration();
    ADC_Configuration();

    float volt = 0.0;

    while (1)
    {
            if(!ADCConvertedValue)
            {
                printf("ADCConvertedValue %d\n", ADCConvertedValue);
                printf("failed...\n");
            }else
            {   
                printf("ADCConvertedValue %d\n", ADCConvertedValue);
                volt = (float) ADCConvertedValue*3.3/(float)4095;
                printf("ADCConvertedValue: 0x%x, %d, Volt: %f V\n", ADCConvertedValue, ADCConvertedValue, volt);
                Hw_1_second();
            }

    }

}