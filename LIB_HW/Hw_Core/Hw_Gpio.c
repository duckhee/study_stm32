#define GPIO_LOCAL

#include "Hw_Gpio.h"


GPIO_DEF void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
    uint32_t tmpreg = 0x00, pinmask = 0x00;
    /*--------------- GPIO Mode Configuration -----------------*/
    //gpio mode 찾기 아웃풋인지 아닌지 abcd 중 ab가 모드를 결정한다. 연산시에 모드가 설정이 된다.
    //이중 포인터로 모드의 값을 참조한다.??
    currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
    //구조체에 저장된 gpio_mode가 output이면 speed를 설정을 해주어야한다.
    if((((uint32_t)GPIO_InitStruct->GPIO_Mode)&((uint32_t)0x10)) != 0x00)
    {
        //output시시에 전체 모드와 속도를 결정을 해주는 것
        currentmode |= GPIO_InitStruct->GPIO_Speed;
    }
    /*--------------- GPIO CRL Configuration -----------------*/
    if(((uint32_t)GPIO_InitStruct->GPIO_Pin &((uint32_t)0x00FF)) != 0x00)
    {
        tmpreg = GPIOx->CRL;
        for(pinpos = 0x00; pinpos < 0x08;pinpos++)
        {
            //shift연산으로 설정한 핀을 지정
            pos = ((uint32_t)0x01) << pinpos;
            /* Get the port pin position */
            currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
            if(currentpin == pos)
            {
                pos = pinpos << 2;
                /* Clear the corresponding low control register bits */
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;
                /* Write the mmode configuratuin in the corresponding bits */ 
                tmpreg |= (currentmode << pos);
                /* Reset the corresponding ODR bit */
                //Input mode set
                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx->BRR = (((uint32_t)0x01) << pinpos);
                }else
                {
                    /* Set the corresponding ODR bit */
                    if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                    {
                        GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
                    }
                }
            }
        }
        GPIOx->CRL = tmpreg;
    }
    /*--------------- GPIO CRH Configuration -----------------*/

    /* Configure the eight high port pins */
    if(GPIO_InitStruct->GPIO_Pin > 0x00FF)
    {
        tmpreg = GPIOx->CRH;
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = (((uint32_t)0x01) << (pinpos + 0x08));
            /* Get the port pins position */
            currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
            if(currentpin == pos)
            {
                pos = pinpos << 2;
                /* Clear the corresponding high control register bits */
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;
                /* Write the mode configuration in the corresponding bits */
                tmpreg |= (currentmode << pos);
                /* Reset the corresponding ODR bit */
                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
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

    //USART configuration
    //여기서 .으로 멤버를 접근을 한다. 궁금한 것은 왜 여기서는 이중 포인터를 사용하지 않고 멤버의 값을 접근을 해서 사용을 하는지 ?
    GPIO_InitStructure.GPIO_Pin = GPIO_USART_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIO_USART, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_USART_Rx_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_USART, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_KEY, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN | GPIO_LED2_PIN | GPIO_LED3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_LED, &GPIO_InitStructure);
    //led all off setting
    Led_All_Off();

    GPIO_InitStructure.GPIO_Pin
    = GPIO_7_SEG_POWER_PIN | GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN | GPIO_7_SEG_DP_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_7_SEG, &GPIO_InitStructure);
    //segment all off setting
    Off_7_SEG_AllPin();

}