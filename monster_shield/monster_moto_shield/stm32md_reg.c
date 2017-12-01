// =============================================================
//
//	STM32F10x MD Devices Register Define
//
//								2014.  1.  5.	by GroundZero
//
// =============================================================

// SYSTICK	( System Tick Timer : Cortex-M Core Device )
#define	STK_RELOAD	*(volatile unsigned long *)0xe000e014
#define	STK_CURVAL	*(volatile unsigned long *)0xe000e018
#define	STK_CTRL	*(volatile unsigned long *)0xe000e010

// RCC		(Reset and Clock Control)
#define	RCC_CR		*(volatile unsigned long *)	0x40021000
#define	RCC_CFGR	*(volatile unsigned long *) 0x40021004
#define	RCC_AHBENR	*(volatile unsigned long *) 0x40021014
#define	RCC_APB2ENR	*(volatile unsigned long *) 0x40021018
#define	RCC_APB1ENR	*(volatile unsigned long *) 0x4002101c

// Flash memory latency
#define	FLASH_ACR	*(volatile unsigned long *) 0x40022000

// GPIO		(General Pulpose I/Os)
#define	GPIOA_CRL	*(volatile unsigned long *) 0x40010800
#define	GPIOA_CRH	*(volatile unsigned long *) 0x40010804
#define	GPIOA_IDR	*(volatile unsigned long *) 0x40010808
#define	GPIOA_ODR	*(volatile unsigned long *) 0x4001080c
#define	GPIOB_CRL	*(volatile unsigned long *) 0x40010c00
#define	GPIOB_CRH	*(volatile unsigned long *) 0x40010c04
#define	GPIOB_IDR	*(volatile unsigned long *) 0x40010c08
#define	GPIOB_ODR	*(volatile unsigned long *) 0x40010c0c
#define	GPIOC_CRL	*(volatile unsigned long *) 0x40011000
#define	GPIOC_CRH	*(volatile unsigned long *) 0x40011004
#define	GPIOC_IDR	*(volatile unsigned long *) 0x40011008
#define	GPIOC_ODR	*(volatile unsigned long *) 0x4001100c

// AFIO		(Alternate-Function I/Os)
#define	AFIO_MAPR	*(volatile unsigned long *) 0x40010004	// JTAG/SWD Remap 
															// bit26,25,24 = 1,0,0 : all free
// I2C1		(Inter-integrated Circuit 1)
#define	I2C1_CR1	*(volatile unsigned long *) 0x40005400
#define I2C1_CR2	*(volatile unsigned long *) 0x40005404
#define I2C1_OAR1	*(volatile unsigned long *) 0x40005408
#define I2C1_OAR2	*(volatile unsigned long *) 0x4000540c
#define I2C1_DR		*(volatile unsigned long *) 0x40005410
#define I2C1_SR1	*(volatile unsigned long *) 0x40005414
#define I2C1_SR2	*(volatile unsigned long *) 0x40005418
#define I2C1_CCR	*(volatile unsigned long *) 0x4000541c
#define I2C1_TRISE	*(volatile unsigned long *) 0x40005420

// I2C2		(Inter-integrated Circuit 2)
#define	I2C2_CR1	*(volatile unsigned long *) 0x40005800
#define I2C2_CR2	*(volatile unsigned long *) 0x40005804
#define I2C2_OAR1	*(volatile unsigned long *) 0x40005808
#define I2C2_OAR2	*(volatile unsigned long *) 0x4000580c
#define I2C2_DR		*(volatile unsigned long *) 0x40005810
#define I2C2_SR1	*(volatile unsigned long *) 0x40005814
#define I2C2_SR2	*(volatile unsigned long *) 0x40005818
#define I2C2_CCR	*(volatile unsigned long *) 0x4000581c
#define I2C2_TRISE	*(volatile unsigned long *) 0x40005820

// USART1	(Universial Syncronous Asyncronous Receiver Transmitter 1)
#define	USART1_BRR	*(volatile unsigned long *) 0x40013808
#define	USART1_CR1	*(volatile unsigned long *) 0x4001380C
#define	USART1_CR2	*(volatile unsigned long *) 0x40013810
#define	USART1_CR3	*(volatile unsigned long *) 0x40013814

// ADC1
#define	ADC1_SR		*(volatile unsigned long *) 0x40012400
#define	ADC1_CR1	*(volatile unsigned long *) 0x40012404
#define	ADC1_CR2	*(volatile unsigned long *) 0x40012408
#define	ADC1_SMPR1	*(volatile unsigned long *) 0x4001240c
#define	ADC1_SMPR2	*(volatile unsigned long *) 0x40012410
#define	ADC1_SQR1	*(volatile unsigned long *) 0x4001242c
#define	ADC1_SQR2	*(volatile unsigned long *) 0x40012430
#define	ADC1_SQR3	*(volatile unsigned long *) 0x40012434
#define	ADC1_DR		*(volatile unsigned long *) 0x4001244c


// TIM1

// TIM2
#define	TIM2_CR1	*(volatile unsigned long *) 0x40000000
#define	TIM2_CR2	*(volatile unsigned long *) 0x40000004
#define	TIM2_SMCR	*(volatile unsigned long *) 0x40000008
#define	TIM2_DIER	*(volatile unsigned long *) 0x4000000c
#define	TIM2_SR		*(volatile unsigned long *) 0x40000010
#define	TIM2_EGR	*(volatile unsigned long *) 0x40000014
#define	TIM2_CCMR1	*(volatile unsigned long *) 0x40000018
#define	TIM2_CCMR2	*(volatile unsigned long *) 0x4000001c
#define	TIM2_CCER	*(volatile unsigned long *) 0x40000020
#define	TIM2_CNT	*(volatile unsigned long *) 0x40000024
#define	TIM2_PSC	*(volatile unsigned long *) 0x40000028
#define	TIM2_ARR	*(volatile unsigned long *) 0x4000002c
#define	TIM2_CCR1	*(volatile unsigned long *) 0x40000034
#define	TIM2_CCR2	*(volatile unsigned long *) 0x40000038
#define	TIM2_CCR3	*(volatile unsigned long *) 0x4000003c
#define	TIM2_CCR4	*(volatile unsigned long *) 0x40000030
#define	TIM2_DCR	*(volatile unsigned long *) 0x40000044
#define	TIM2_DMAR	*(volatile unsigned long *) 0x40000048

// TIM3
#define	TIM3_CR1	*(volatile unsigned long *) 0x40000400
#define	TIM3_CR2	*(volatile unsigned long *) 0x40000404
#define	TIM3_SMCR	*(volatile unsigned long *) 0x40000408
#define	TIM3_DIER	*(volatile unsigned long *) 0x4000040c
#define	TIM3_SR		*(volatile unsigned long *) 0x40000410
#define	TIM3_EGR	*(volatile unsigned long *) 0x40000414
#define	TIM3_CCMR1	*(volatile unsigned long *) 0x40000418
#define	TIM3_CCMR2	*(volatile unsigned long *) 0x4000041c
#define	TIM3_CCER	*(volatile unsigned long *) 0x40000420
#define	TIM3_CNT	*(volatile unsigned long *) 0x40000424
#define	TIM3_PSC	*(volatile unsigned long *) 0x40000428
#define	TIM3_ARR	*(volatile unsigned long *) 0x4000042c
#define	TIM3_CCR1	*(volatile unsigned long *) 0x40000434
#define	TIM3_CCR2	*(volatile unsigned long *) 0x40000438
#define	TIM3_CCR3	*(volatile unsigned long *) 0x4000043c
#define	TIM3_CCR4	*(volatile unsigned long *) 0x40000440
#define	TIM3_DCR	*(volatile unsigned long *) 0x40000448
#define	TIM3_DMAR	*(volatile unsigned long *) 0x4000044c

// TIM4
#define	TIM4_CR1	*(volatile unsigned long *) 0x40000800
#define	TIM4_CR2	*(volatile unsigned long *) 0x40000804
#define	TIM4_SMCR	*(volatile unsigned long *) 0x40000808
#define	TIM4_DIER	*(volatile unsigned long *) 0x4000080c
#define	TIM4_SR		*(volatile unsigned long *) 0x40000810
#define	TIM4_EGR	*(volatile unsigned long *) 0x40000814
#define	TIM4_CCMR1	*(volatile unsigned long *) 0x40000818
#define	TIM4_CCMR2	*(volatile unsigned long *) 0x4000081c
#define	TIM4_CCER	*(volatile unsigned long *) 0x40000820
#define	TIM4_CNT	*(volatile unsigned long *) 0x40000824
#define	TIM4_PSC	*(volatile unsigned long *) 0x40000828
#define	TIM4_ARR	*(volatile unsigned long *) 0x4000082c
#define	TIM4_CCR1	*(volatile unsigned long *) 0x40000834
#define	TIM4_CCR2	*(volatile unsigned long *) 0x40000838
#define	TIM4_CCR3	*(volatile unsigned long *) 0x4000083c
#define	TIM4_CCR4	*(volatile unsigned long *) 0x40000830
#define	TIM4_DCR	*(volatile unsigned long *) 0x40000844
#define	TIM4_DMAR	*(volatile unsigned long *) 0x40000848






