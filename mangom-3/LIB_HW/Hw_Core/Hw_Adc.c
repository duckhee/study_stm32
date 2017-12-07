#define ADC_LOCAL

#include "Hw_ADC.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

ADC_DEF void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructur);
ADC_DEF void ADC_Configuration(void);
ADC_DEF void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
ADC_DEF void ADC_Enable(ADC_TypeDef* ADCx, FunctionalState NewState);
ADC_DEF void ADC_DMA_Eable(ADC_TypeDef* ADCx, FunctionalState NewState);
ADC_DEF void ADC_ResetCalibration(ADC_TypeDef* ADCx);
ADC_DEF FlagStatus ADC_ResetStatus(ADC_TypeDef* ADCx);
ADC_DEF void ADC_StartCalibration(ADC_TypeDef* ADCx);
ADC_DEF FlagStatus ADC_GetStatus(ADC_TypeDef* ADCx);
ADC_DEF void ADC_SoftStartConv(ADC_TypeDef* ADCx, FunctionalState NewState);




ADC_DEF void ADC_Configuration(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    /* ADC1 regular channel14 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);

    /* Enable ADC1 DMA */
    ADC_DMA_Eable(ADC1, ENABLE);

    /* Enable ADC1 */
    ADC_Enable(ADC1, ENABLE);

    /* Enable ADC1 reset calibaration register */   
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_ResetStatus(ADC1));

    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_GetStatus(ADC1));

    /* Start ADC1 Software Conversion */ 
    ADC_SoftStartConv(ADC1, ENABLE);
    printf("ADC test !\n");
}

ADC_DEF void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructur)
{
    uint32_t tmpreg1 = 0;
    uint8_t tmpreg2 = 0;
    /*---------- ADC CR1 register config --------------*/
    tmpreg1 = ADCx->CR1;
    //CR1의 register 값 얻어오기 
    tmpreg1 &= CR1_CLEAR_Mask;
    //scan mode and dual mode reset 
    tmpreg1 |= (uint32_t)(ADC_InitStructur->ADC_Mode | ((uint32_t)ADC_InitStructur->ADC_ScanConvMode << 8));
    ADCx->CR1 = tmpreg1;

    /*---------- ADC CR2 register config --------------*/
    tmpreg1 = ADCx->CR2;
    //CR2의 register 값 얻어오기 
    tmpreg1 &= CR2_CLEAR_Mask;
    /* Clear CONT, ALIGN and EXTSEL bits */
    tmpreg1 |= (uint32_t)(ADC_InitStructur->ADC_DataAlign | ADC_InitStructur->ADC_ExternalTrigConv | ((uint32_t)ADC_InitStructur->ADC_ContinuousConvMode << 1));
    ADCx->CR2 = tmpreg1;
    /*---------------------------- ADCx SQR1 Configuration -----------------*/
      /* Get the ADCx SQR1 value */
    tmpreg1 = ADCx->SQR1;
    /* Clear L bits */
    tmpreg1 &= SQR1_CLEAR_Mask;
    /* Configure ADCx: regular channel sequence length */
    /* Set L bits according to ADC_NbrOfChannel value */
    tmpreg2 |= (uint8_t) (ADC_InitStructur->ADC_NbrOfChannel - (uint8_t)1);
    tmpreg1 |= (uint32_t)tmpreg2 << 20;
    /* Write to ADCx SQR1 */
    ADCx->SQR1 = tmpreg1;

}

//adc regular mode setup function
ADC_DEF void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tmpreg1 = 0, tmpreg2 = 0;
    if(ADC_Channel > ADC_Channel_9)
    {
        tmpreg1 = ADCx->SMPR1;
        tmpreg2 = SMPR1_SMP_Set << (3 * (ADC_Channel - 10));
        tmpreg1 &= ~tmpreg2;
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 *  (ADC_Channel - 10));
        tmpreg1 |= tmpreg2;
        ADCx->SMPR1 = tmpreg1;
    }
    else
    {
        tmpreg1 = ADCx->SMPR2;
        tmpreg2 = SMPR1_SMP_Set << (3 * ADC_Channel);
        tmpreg1 &= ~tmpreg2;
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        tmpreg1 |= tmpreg2;
        ADCx->SMPR2 = tmpreg1;
    }
      /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR3;
    /* Calculate the mask to clear */
    tmpreg2 = SQR3_SQ_Set << (5 * (Rank - 1));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR2;
    /* Calculate the mask to clear */
    tmpreg2 = SQR2_SQ_Set << (5 * (Rank - 7));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR1;
    /* Calculate the mask to clear */
    tmpreg2 = SQR1_SQ_Set << (5 * (Rank - 13));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR1 = tmpreg1;
  }
}

ADC_DEF void ADC_Enable(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        ADCx->CR2 |= CR2_ADON_Set;
    }
    else
    {
        ADCx->CR2 &= CR2_ADON_Reset;
    }
}

ADC_DEF void ADC_DMA_Eable(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        ADCx->CR2 |= CR2_DMA_Set;
    }
    else
    {
        ADCx->CR2 &= CR2_DMA_Reset;
    }
}

ADC_DEF void ADC_ResetCalibration(ADC_TypeDef* ADCx)
{
    ADCx->CR2 |= CR2_RSTCAL_Set;
}

ADC_DEF FlagStatus ADC_ResetStatus(ADC_TypeDef* ADCx)
{
    FlagStatus bitstatus = RESET;
    if((ADCx->CR2 & CR2_RSTCAL_Set) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

ADC_DEF void ADC_StartCalibration(ADC_TypeDef* ADCx)
{
    ADCx->CR2 |= CR2_CAL_Set;
}

ADC_DEF FlagStatus ADC_GetStatus(ADC_TypeDef* ADCx)
{
    FlagStatus bitstatus = RESET;
    if((ADCx->CR2 & CR2_CAL_Set) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

ADC_DEF void ADC_SoftStartConv(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        ADCx->CR2 |= CR2_EXTTRIG_SWSTART_Set;
    }
    else
    {
        ADCx->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
    }
}