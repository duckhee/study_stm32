/*!
  * @file    arch/main.c
  * @brief   string Control API
  */
#include <stdio.h>
#include "stm32f10x.h"
#include "Lb_Printf.h"

void __attribute__((weak)) osa_mdelay(unsigned int msec)
{
	uint32_t temp;
	SysTick->LOAD=(uint32_t)msec*(HSE_VALUE/1000);
	SysTick->VAL =0x00;		// clear Count flag
	SysTick->CTRL=0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));	// wait Count flag set
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}

void __attribute__((weak)) delay_us(unsigned int usec)
{
	uint32_t temp;
	SysTick->LOAD=(uint32_t)usec*(HSE_VALUE/1000000);
	SysTick->VAL =0x00;		// clear Count flag
	SysTick->CTRL=0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));	// wait Count flag set
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}

void print_byte(unsigned short  c)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
	USART_SendData(USART1, c);
}

int GetKey(char *pkey)
{
	int ret = 0;

	if ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		*pkey = (u8)USART_ReceiveData(USART1);
		ret = 1;
	}
	return ret;
}

void UART_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// RCC Configuration
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );

	// Port 설정
	/* J7-11 PA9 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* J7-12 PA10 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// UART Port 설정
	USART_InitStructure.USART_BaudRate    = 115200  ;
	USART_InitStructure.USART_WordLength   = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits    = USART_StopBits_1;
	USART_InitStructure.USART_Parity    = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode    = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void setup(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	// RCC Configuration
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );

	// Potentio meter  (volume control)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;

	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channels configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1 , ADC_SampleTime_55Cycles5);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */
	/* Check the end of ADC1 reset calibration register */
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));


	/* Start ADC1 calibration */
	/* Check the end of ADC1 calibration */
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	Lb_printf("Start Application : %s\r\n", "ADC Test");
}

void loop(void)
{
	char c;
	int AD_value;
	int timeout = 7200000;

	if(GetKey(&c)==1)
	{
		switch(c)
		{
		case '0':
			/* Start ADC1 Software Conversion */
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			while(ADC_GetFlagStatus(ADC1, 0x2)==RESET)
			{
				timeout--;
				if(timeout==0)
					break;
			}

			AD_value = ADC_GetConversionValue(ADC1);
			Lb_printf("ADC : %d, %d\r\n", AD_value, AD_value*100/4095);
			break;
		case '1':
			Lb_printf("pressed 1\r\n");
			break;
		default:
			Lb_printf("%c", c);
			break;
		}
	}
}

int main(void)
{
	UART_Configuration();

	setup();

	while(1)
	{
		loop();
	}
}
