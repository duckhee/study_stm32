#define DMA_LOCAL

#include "Hw_DMA.h"

DMA_DEF void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStructur);
DMA_DEF void DMA_Enable(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
DMA_DEF void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

DMA_DEF void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStructur)
{
    uint32_t tmpreg = 0;
    //get ccr register
    tmpreg = DMAy_Channelx -> CCR;
    // clear ccr register
    tmpreg &= CCR_CLEAR_Mask;

    tmpreg |= DMA_InitStructur->DMA_DIR | DMA_InitStructur->DMA_Mode | DMA_InitStructur->DMA_PeripheralInc | DMA_InitStructur->DMA_MemoryInc | DMA_InitStructur->DMA_PeripheralDataSize | DMA_InitStructur->DMA_Priority | DMA_InitStructur->DMA_M2M;

    DMAy_Channelx->CCR = tmpreg;

    DMAy_Channelx->CNDTR = DMA_InitStructur->DMA_BufferSize;

    DMAy_Channelx->CPAR = DMA_InitStructur->DMA_PeripheralBaseAddr;

    DMAy_Channelx->CMAR = DMA_InitStructur->DMA_MemoryBaseAddr;
}

DMA_DEF void DMA_Enable(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
    if(NewState != RESET)
    {
        DMAy_Channelx->CCR |= CCR_ENABLE_Set;
    }
    else
    {
        DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
    }
}

DMA_DEF void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
     /* Disable the selected DMAy Channelx */
  DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
  /* Reset DMAy Channelx control register */
  DMAy_Channelx->CCR  = 0;
  
  /* Reset DMAy Channelx remaining bytes register */
  DMAy_Channelx->CNDTR = 0;
  
  /* Reset DMAy Channelx peripheral address register */
  DMAy_Channelx->CPAR  = 0;
  
  /* Reset DMAy Channelx memory address register */
  DMAy_Channelx->CMAR = 0;
  
  if (DMAy_Channelx == DMA1_Channel1)
  {
    /* Reset interrupt pending bits for DMA1 Channel1 */
    DMA1->IFCR |= DMA1_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel2)
  {
    /* Reset interrupt pending bits for DMA1 Channel2 */
    DMA1->IFCR |= DMA1_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel3)
  {
    /* Reset interrupt pending bits for DMA1 Channel3 */
    DMA1->IFCR |= DMA1_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel4)
  {
    /* Reset interrupt pending bits for DMA1 Channel4 */
    DMA1->IFCR |= DMA1_Channel4_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel5)
  {
    /* Reset interrupt pending bits for DMA1 Channel5 */
    DMA1->IFCR |= DMA1_Channel5_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel6)
  {
    /* Reset interrupt pending bits for DMA1 Channel6 */
    DMA1->IFCR |= DMA1_Channel6_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel7)
  {
    /* Reset interrupt pending bits for DMA1 Channel7 */
    DMA1->IFCR |= DMA1_Channel7_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel1)
  {
    /* Reset interrupt pending bits for DMA2 Channel1 */
    DMA2->IFCR |= DMA2_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel2)
  {
    /* Reset interrupt pending bits for DMA2 Channel2 */
    DMA2->IFCR |= DMA2_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel3)
  {
    /* Reset interrupt pending bits for DMA2 Channel3 */
    DMA2->IFCR |= DMA2_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel4)
  {
    /* Reset interrupt pending bits for DMA2 Channel4 */
    DMA2->IFCR |= DMA2_Channel4_IT_Mask;
  }
  else
  { 
    if (DMAy_Channelx == DMA2_Channel5)
    {
      /* Reset interrupt pending bits for DMA2 Channel5 */
      DMA2->IFCR |= DMA2_Channel5_IT_Mask;
    }
  }
}