//======================================================================================
//
//	DC Motor Control by PWM
//
//										 by GroundZero   2014. 1. 22.
//
//======================================================================================
#include "stm32md_reg.c"
#include "_printf.c"
#include "_delay.c"

#define MAX 400
#define MIN 260

void init_TIM2(void)
{								// CNF[1:0]=10(AF output), MODE[1:0]=11(Max output 50MHz) 1011
	GPIOA_CRL	|= ( 0xb<<0)	// set PA0 as AF output (0xb = 1011)	TIM2_CH1
				|  ( 0xb<<4)	// set PA1 as AF output (0xb = 1011)	TIM2_CH2
				|  ( 0xb<<8)	// set PA2 as AF output (0xb = 1011)	TIM2_CH2
				|  ( 0xb<<12);	// set PA3 as AF output (0xb = 1011)	TIM2_CH2
	

//	RCC_APB1ENR	|= ( 0x1<< 0);	// bit0 - TIM2 Clock Enable bit
	
	TIM2_PSC	 = 8;			// 72000000 / (8+1) = 8000000 =  8MHz, T = 1/8000000 = 0.000000125 = 0.125us
							
	TIM2_ARR	 = 400-1;		// 0.000000125 * 400 = 0.00005, F = 1 / 0.00005 = 20000Hz = 20KHz
	
	TIM2_CR1	|= ( 0x1<< 4);	// set DIR (Direction - down count)
				
	TIM2_CCMR1	|= ( 0x1<< 3)	// ch1: preload enable
				|  ( 0x6<< 4)	// ch1: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch2: preload enable
				|  ( 0x6<<12);	// ch2: OC Mode = PWM mode1 ( 110 )

	TIM2_CCMR2	|= ( 0x1<< 3)	// ch3: compare fast & preload enable(11)
				|  ( 0x6<< 4)	// ch3: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch4: compare fast & preload enable(11)
				|  ( 0x6<<12);	// ch4: OC Mode = PWM mode1 ( 110 )

	TIM2_CCER	|= ( 0x1<< 0)	// ch1: output enable
				|  ( 0x1<< 4)	// ch2: output enable
				|  ( 0x1<< 8)	// ch3: output enable
				|  ( 0x1<<12);	// ch4: output enable
	
	TIM2_CCR1	 = (280-1);		// ch1: 65% duty
	TIM2_CCR2	 = (280-1);		// ch2: 65% duty
	TIM2_CCR3	 = (280-1);		// ch3: 65% duty
	TIM2_CCR4	 = (280-1);		// ch3: 65% duty
	
	TIM2_CR1	|= ( 0x1<< 7)	// set APRE(Auto Reload Preload Enable)
				|  ( 0x1<< 0);	// TIM3 Counter Enable
}

void init_TIM3(void)
{								// CNF[1:0]=10(AF output), MODE[1:0]=11(Max output 50MHz) 1011
	GPIOA_CRL	|= ( 0xb<<24)	// set PA6 as AF output (0xb = 1011)	TIM3_CH1
				|  ( 0xb<<28);	// set PA7 as AF output (0xb = 1011)	TIM3_CH2
	
	GPIOB_CRL	|= ( 0xb<< 0)	// set PB0 as AF output (0xb = 1011)	TIM3_CH3
				|  ( 0xb<< 4);	// set PB1 as AF output (0xb = 1011)	TIM3_CH4

//	RCC_APB1ENR	|= ( 0x1<< 1);	// bit1 - TIM3 Clock Enable bit
	
	TIM3_PSC	 = 8;			// 72000000 / (8+1) = 8000000 =  8MHz, T = 1/8000000 = 0.000000125 = 0.125us
							
	TIM3_ARR	 = 400-1;		// 0.000000125 * 400 = 0.00005, F = 1 / 0.00005 = 20000Hz = 20KHz
	
	TIM3_CR1	|= ( 0x1<< 4);	// set DIR (Direction - down count)
				
	TIM3_CCMR1	|= ( 0x1<< 3)	// ch1: preload enable
				|  ( 0x6<< 4)	// ch1: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch2: preload enable
				|  ( 0x6<<12);	// ch2: OC Mode = PWM mode1 ( 110 )

	TIM3_CCMR2	|= ( 0x1<< 3)	// ch3: compare fast & preload enable(11)
				|  ( 0x6<< 4)	// ch3: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch4: compare fast & preload enable(11)
				|  ( 0x6<<12);	// ch4: OC Mode = PWM mode1 ( 110 )

	TIM3_CCER	|= ( 0x1<< 0)	// ch1: output enable
				|  ( 0x1<< 4)	// ch2: output enable
				|  ( 0x1<< 8)	// ch3: output enable
				|  ( 0x1<<12);	// ch4: output enable
	
	TIM3_CCR1	 = (280-1);		// ch1: 65% duty
	TIM3_CCR2	 = (280-1);		// ch2: 65% duty
	TIM3_CCR3	 = (280-1);		// ch3: 65% duty
	TIM3_CCR4	 = (280-1);		// ch3: 65% duty
	
	TIM3_CR1	|= ( 0x1<< 7)	// set APRE(Auto Reload Preload Enable)
				|  ( 0x1<< 0);	// TIM3 Counter Enable
}

void init_TIM4(void)
{								// CNF[1:0]=10(AF output), MODE[1:0]=11(Max output 50MHz) 1011
	GPIOB_CRL	|= ( 0xb<<24)	// set PA6 as AF output (0xb = 1011)	TIM4_CH1
				|  ( 0xb<<28);	// set PA7 as AF output (0xb = 1011)	TIM4_CH2
	GPIOB_CRH	|= ( 0xb<< 0)	// set PB8 as AF output (0xb = 1011)	TIM4_CH3
				|  ( 0xb<< 4);	// set PB9 as AF output (0xb = 1011)	TIM4_CH4

//	RCC_APB1ENR	|= ( 0x1<< 2);	// bit2 - TIM4 Clock Enable bit
	
	TIM4_PSC	 = 8;			// 72000000 / (8+1) = 8000000 =  8MHz, T = 1/8000000 = 0.000000125 = 0.125us
	TIM4_ARR	 = 400-1;		// 0.000000125 * 400 = 0.00005, F = 1 / 0.00005 = 20000Hz = 20KHz
	TIM4_CR1	|= ( 0x1<< 4);	// set DIR (Direction - down count)

	TIM4_CCMR1	|= ( 0x1<< 3)	// ch1: preload enable
				|  ( 0x6<< 4)	// ch1: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch2: preload enable
				|  ( 0x6<<12);	// ch2: OC Mode = PWM mode1 ( 110 )

	TIM4_CCMR2	|= ( 0x1<< 3)	// ch3: compare fast & preload enable(11)
				|  ( 0x6<< 4)	// ch3: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch4: compare fast & preload enable(11)
				|  ( 0x6<<12);	// ch4: OC Mode = PWM mode1 ( 110 )

	TIM4_CCER	|= ( 0x1<< 0)	// ch1: output enable
				|  ( 0x1<< 4);	// ch2: output enable
	TIM4_CCER	|  ( 0x1<< 8)	// ch3: output enable
				|  ( 0x1<<12);	// ch4: output enable
	
	TIM4_CCR1	 = (280-1);		// ch1: 65% duty
	TIM4_CCR2	 = (280-1);		// ch2: 65% duty
	TIM4_CCR3	 = (280-1);		// ch3: 65% duty
	TIM4_CCR4	 = (280-1);		// ch4: 65% duty
	
	TIM4_CR1	|= ( 0x1<< 7)	// set APRE(Auto Reload Preload Enable)
				|  ( 0x1<< 0);	// TIM4 Counter Enable
}

void change_duty31(unsigned short duty)
{
	TIM3_CCR1	 = duty-1;		// change duty of TIM3_CH1
}

void change_duty32(unsigned short duty)
{
	TIM3_CCR2	 = duty-1;		// change duty of TIM3_CH2
}


void change_duty33(unsigned short duty)
{
	TIM3_CCR3	 = duty-1;		// change duty of TIM3_CH3
}

void change_duty34(unsigned short duty)
{
	TIM3_CCR4	 = duty-1;		// change duty of TIM3_CH4
}

int main(void)
{
	unsigned short duty = MAX;
	printf("Moror_Ctrl\n");

//	init_TIM2();
//	init_TIM3();
	init_TIM4();
while(1);
	GPIOB_ODR	|= ( 0xf << 4 );	// PA5,4,3,2 = 1111 = 0xf

	while(1)
	{
		switch(get_byte())
		{
			case'a':
				printf("turn left\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0x6 << 2 );	// PA5,4,3,2 = 1001 = 0x9
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0x6 << 4 );	// PB4,5,6,7 = 0110 = 0x6
//        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case'b':
				printf("turn right\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0x9 << 2 );	// PA5,4,3,2 = 0110 = 0x6				
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0x9 << 4 );	// PB4,5,6,7 = 1001 = 0x9
//        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case'c':
				printf("forward\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0x5 << 2 );	// PA5,4,3,2 = 0101 = 0x5
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0x3 << 4 );	// PB4,5,6,7 = 0011 = 0x3
//        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case'd':
				printf("back\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0xa << 2 );	// PA5,4,3,2 = 1010 = 0xa
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0xc << 4 );	// PB4,5,6,7 = 1100 = 0xc
//        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case('i'):
				printf("stop\n");
//				GPIOA_ODR	|= ( 0xf << 2 );	// PA5,4,3,2 = 1111 = 0xf
				GPIOC_ODR	&= ~( 0x3 << 14 );	// PC14,15
				GPIOB_ODR	|= ( 0xf << 4 );	// PB4,5,6,7 = 1111 = 0xf
				
				break;

/*			case('>'):
				if(duty <= MAX)
				{
					duty = duty + 10;
					change_duty31(duty);
					change_duty32(duty);
//					printf("increase\n");
//					printf("duty=%d\n",duty);
				}
				else
				{
					duty = MAX;
//					printf("duty=%d\n",duty);
//					printf("MAX duty!\n");
				}
				break;
				
			case('<'):
				if(duty >= MIN)
				{
					duty = duty - 10;
					change_duty31(duty);
					change_duty32(duty);
//					printf("decrease\n");
//					printf("duty=%d\n",duty);
				}
				else
				{
					duty = MIN;
//					printf("duty=%d\n",duty);
//					printf("MIN duty!\n");
				}
				break;
				
			case('x'):
				duty = MAX;
				change_duty31(duty);
				change_duty32(duty);		
				printf("duty=%d\n",duty);
				printf("MAX duty!\n");
				break;

			case('n'):
				duty = MIN;
				change_duty31(duty);
				change_duty32(duty);
				printf("duty=%d\n",duty);
				printf("MIN duty!\n");
				break;
*/
			default:
				break;
		}
	}
}