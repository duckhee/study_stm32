#define HW_EXIT_LOCAL

#include "Hw_EXTI.h"


HW_EXT_DEF void EXTI_Configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Configure gpio as input : Button Left-WKUP */
    /* Connect EXTI Line to gpio pin */
    GPIO_EXTILineConfig(GPIO_PORTSOURCE_KEY, GPIO_PINSOURCE_KEY1);
    /* Configure EXTI Line to generate an interrupt */
    EXTI_InitStructure.EXTI_Line    = GPIO_EXTI_Line_KEY1;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    /* Configure gpio as input : Button Right-USER */
    /* Connect EXTI Line to gpio pin */
    GPIO_EXTILineConfig(GPIO_PORTSOURCE_KEY, GPIO_PINSOURCE_KEY2);
    /* Configure EXTI Line to generate an interrupt */  
    EXTI_InitStructure.EXTI_Line    = GPIO_EXTI_Line_KEY2;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
}

HW_EXT_DEF ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  enablestatus =  EXTI->IMR & EXTI_Line;
  if (((EXTI->PR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

HW_EXT_DEF void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  EXTI->PR = EXTI_Line;
}

HW_EXT_DEF void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;

  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));

}

HW_EXT_DEF void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  tmp = (uint32_t)EXTI_BASE;

  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;

    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* Clear Rising Falling edge configuration */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;

    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;
      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;
    /* Disable the selected external lines */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }

}


HW_EXT_DEF void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(GPIO_EXTI_Line_KEY1) != RESET) {
        EXTI_ClearITPendingBit(GPIO_EXTI_Line_KEY1);
        printf("Left-WKUP Button Press\n");
    }
}

HW_EXT_DEF void EXTI1_IRQHandler(void)
{
   if(EXTI_GetITStatus(GPIO_EXTI_Line_KEY2) != RESET) {
        EXTI_ClearITPendingBit(GPIO_EXTI_Line_KEY2);
        printf("Right-USER Button Press\n");
    }
}


// uint16_t capture = 0;
// extern __IO uint16_t CCR1_Val;
// extern __IO uint16_t CCR2_Val;
// extern __IO uint16_t CCR3_Val;
// extern __IO uint16_t CCR4_Val;

// HW_EXT_DEF void TIM4_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
//     {
//         TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);

//         /* Pin PB.06 toggling with frequency = 73.24 Hz */
//         GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_6)));
// #if 1
//         capture = TIM_GetCapture1(TIM4);
//         TIM_SetCompare1(TIM4, capture + CCR1_Val);
// #else
//         printf("\nTIM4->CNT: %X, TIM4->CCR1: %X\n", TIM4->CNT, TIM4->CCR1);
//         capture = TIM_GetCapture1(TIM4);
//         printf("capture: %X, CCR1_Val: %X\n", capture, CCR1_Val);
//         printf("capture + CCR1_Val: %X\n", (uint32_t)(capture) + (uint32_t)CCR1_Val);
//         TIM_SetCompare1(TIM4, capture + CCR1_Val);
//         printf("TIM_GetCapture1(): %X\n", TIM_GetCapture1(TIM4));
// #endif
//     }
//     else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
//     {
//         TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);

//         /* Pin PB.07 toggling with frequency = 109.8 Hz */
//         GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_7)));
//         capture = TIM_GetCapture2(TIM4);
//         TIM_SetCompare2(TIM4, capture + CCR2_Val);
//     }
//     else if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
//     {
//         TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);

//         /* Pin PB.08 toggling with frequency = 219.7 Hz */
//         GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8)));
//         capture = TIM_GetCapture3(TIM4);
//         TIM_SetCompare3(TIM4, capture + CCR3_Val);
//     }
//     else
//     {
//         TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);

//         /* Pin PB.09 toggling with frequency = 439.4 Hz */
//         GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_9)));
//         capture = TIM_GetCapture4(TIM4);
//         TIM_SetCompare4(TIM4, capture + CCR4_Val);
//     }
// }