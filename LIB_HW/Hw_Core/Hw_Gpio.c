#define GPIO_LOCAL

#include "Hw_Gpio.h"

#include "Ld_Printf.h"

GPIO_DEF void Gpio_A_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE)
{
    RCC->APB2ENR |= RCC_APB2Periph_GPIOA;
    uint32_t tmpVal = modeE << 2 | speedValE;
    uint32_t pinpos = 0x00;
    if((pinNum & 0xFF) != 0)
    {
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos*4;
                GPIOA->CRL &= ~(0xF << pinpos);
                GPIOA->CRL |= tmpVal << pinpos;
                break;
            }
        }
    }
    else
    {
        pinNum = pinNum >> 8;
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos * 4;
                GPIOA->CRH &= ~(0xF << pinpos);
                GPIOA->CRH |= tmpVal << pinpos;
                break;
            }
        }
    }
}
GPIO_DEF void Gpio_B_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE)
{
    RCC->APB2ENR |= RCC_APB2Periph_GPIOB;
    uint32_t tmpVal = modeE << 2 | speedValE;
    uint32_t pinpos = 0x00;
    if((pinNum & 0xFF) != 0)
    {
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos*4;
                GPIOB->CRL &= ~(0xF << pinpos);
                GPIOB->CRL |= tmpVal << pinpos;
                break;
            }
        }
    }
    else
    {
        pinNum = pinNum >> 8;
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos * 4;
                GPIOB->CRH &= ~(0xF << pinpos);
                GPIOB->CRH |= tmpVal << pinpos;
                break;
            }
        }
    }
}
GPIO_DEF void Gpio_C_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE)
{
    RCC->APB2ENR |= RCC_APB2Periph_GPIOC;
    uint32_t tmpVal = modeE << 2 | speedValE;
    uint32_t pinpos = 0x00;
    if((pinNum & 0xFF) != 0)
    {
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos*4;
                GPIOC->CRL &= ~(0xF << pinpos);
                GPIOC->CRL |= tmpVal << pinpos;
                break;
            }
        }
    }
    else
    {
        pinNum = pinNum >> 8;
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos * 4;
                GPIOC->CRH &= ~(0xF << pinpos);
                GPIOC->CRH |= tmpVal << pinpos;
                break;
            }
        }
    }
}
GPIO_DEF void Gpio_D_Init(uint16_t pinNum, GPIOSpeed_TypeDef speedValE, GPIOMode_TypeDef modeE)
{
    RCC->APB2ENR |= RCC_APB2Periph_GPIOD;
    uint32_t tmpVal = modeE << 2 | speedValE;
    uint32_t pinpos = 0x00;
    if((pinNum & 0xFF) != 0)
    {
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos*4;
                GPIOD->CRL &= ~(0xF << pinpos);
                GPIOD->CRL |= tmpVal << pinpos;
                break;
            }
        }
    }
    else
    {
        pinNum = pinNum >> 8;
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            if(pinNum == ((uint32_t)0x01) << pinpos)
            {
                pinpos = pinpos * 4;
                GPIOD->CRH &= ~(0xF << pinpos);
                GPIOD->CRH |= tmpVal << pinpos;
                break;
            }
        }
    }
}

GPIO_DEF void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  
/*---------------------------- GPIO Mode Configuration -----------------------*/
//and 연산으로 상위 비트 삭제 
currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
//자동으로 cyf 위치만 남는다.

//output mode 
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    /* Output mode */
    //gpio_speed는 설정을 하지 않는다? shift를 시키지 않고 그냥 or연산 ??? shift를 시키지 않아도 된다.
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;

  }
/*---------------------------- GPIO CRL Configuration ------------------------*/
  /* Configure the eight low port pins */
  //핀 설정 
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
/*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}

/* functions */

GPIO_DEF uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}


GPIO_DEF void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
        // UART configuration ...
    
        /* Configure USARTx_Tx as alternate function push-pull */
        GPIO_InitStructure.GPIO_Pin = GPIO_USART_Tx_Pin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIO_USART, &GPIO_InitStructure);
    
        /* Configure USARTx_Rx as input floating */
        GPIO_InitStructure.GPIO_Pin = GPIO_USART_Rx_Pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIO_USART, &GPIO_InitStructure);
    
        // Key configuration ...
    
        /* Configure gpio as input : Button Left-WKUP */
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIO_KEY, &GPIO_InitStructure);
    
        /* Configure gpio as input : Button Right-USER */
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY2_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIO_KEY, &GPIO_InitStructure);
    
        // LED configuration ...
    
        /* Configure gpio as output : LED1, LED2, LED3 */
        //output만 speed를 설정을 해주면 된다.
        GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN | GPIO_LED2_PIN | GPIO_LED3_PIN ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIO_LED, &GPIO_InitStructure);
}