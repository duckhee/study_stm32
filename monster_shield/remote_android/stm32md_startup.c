//========================================================================================================
//
//	file    :  stm32md_startup.c
//
//	author  :  GroundZero (the original file coded by smartrobot 2013. 04. 15.)
//
//	date    :  2013. 12. 08.
//
//	modify	:	change system clock source - interneal 36MHz → external 72MHz
//				locate vactor table on flash memory
//				SWD, JTAG I/Os remap to use as GPIOs
//				Use Register name(define register name & address in "stm32md_reg.c")
//
//========================================================================================================

// Include -----------------------------------------------------------------------------------------------
#include "stm32md_reg.c"

// Private typedef ---------------------------------------------------------------------------------------
typedef void( *const intfunc )( void );

// Private define ----------------------------------------------------------------------------------------
#define WEAK __attribute__ ((weak))

// Private macro -----------------------------------------------------------------------------------------
extern unsigned long _etext;

// start address for the initialization values of the .data section. defined in linker script ------------
extern unsigned long _sidata;

// start address for the .data section. defined in linker script -----------------------------------------										
extern unsigned long _sdata;

// end address for the .data section. defined in linker script -------------------------------------------
extern unsigned long _edata;

// start address for the .bss section. defined in linker script ------------------------------------------
extern unsigned long _sbss;

// end address for the .bss section. defined in linker script --------------------------------------------
extern unsigned long _ebss;

// init value for the stack pointer. defined in linker script --------------------------------------------
extern unsigned long _estack;

//--------  Private function prototypes ------------------------------------------------------------------
void Reset_Handler(void) __attribute__((__interrupt__));
extern int main(void);
void __Init_Data(void);
void Default_Handler(void);

//--------  Next declaration of the default fault handlers.  ---------------------------------------------

//	mthomas void WEAK Reset_Handler(void);
void WEAK NMI_Handler(void);					// 01
void WEAK HardFault_Handler(void);				// 02
void WEAK MemManage_Handler(void);				// 03
void WEAK BusFault_Handler(void);				// 04
void WEAK UsageFault_Handler(void);				// 05

//	mthomas void WEAK MemManage_Handler(void);
void WEAK SVC_Handler(void);					// 06
void WEAK DebugMon_Handler(void);				// 07
void WEAK PendSV_Handler(void);					// 08
void WEAK SysTick_Handler(void);				// 09

//	External Interrupts	//
void WEAK WWDG_IRQHandler(void);				// 10
void WEAK PVD_IRQHandler(void);					// 11
void WEAK TAMPER_IRQHandler(void);				// 12
void WEAK RTC_IRQHandler(void);					// 13
void WEAK FLASH_IRQHandler(void);				// 14
void WEAK RCC_IRQHandler(void);					// 15
void WEAK EXTI0_IRQHandler(void);				// 16
void WEAK EXTI1_IRQHandler(void);				// 17
void WEAK EXTI2_IRQHandler(void);				// 18
void WEAK EXTI3_IRQHandler(void);				// 19
void WEAK EXTI4_IRQHandler(void);				// 20
void WEAK DMA1_Channel1_IRQHandler(void);		// 21
void WEAK DMA1_Channel2_IRQHandler(void);		// 22
void WEAK DMA1_Channel3_IRQHandler(void);		// 23
void WEAK DMA1_Channel4_IRQHandler(void);		// 24
void WEAK DMA1_Channel5_IRQHandler(void);		// 25
void WEAK DMA1_Channel6_IRQHandler(void);		// 26
void WEAK DMA1_Channel7_IRQHandler(void);		// 27
void WEAK ADC1_2_IRQHandler(void);				// 28
void WEAK USB_HP_CAN1_TX_IRQHandler(void);		// 29
void WEAK USB_LP_CAN1_RX0_IRQHandler(void);		// 30
void WEAK CAN1_RX1_IRQHandler(void);			// 31
void WEAK CAN1_SCE_IRQHandler(void);			// 32
void WEAK EXTI9_5_IRQHandler(void);				// 33
void WEAK TIM1_BRK_IRQHandler(void);			// 34
void WEAK TIM1_UP_IRQHandler(void);				// 35
void WEAK TIM1_TRG_COM_IRQHandler(void);		// 36
void WEAK TIM1_CC_IRQHandler(void);				// 37
void WEAK TIM2_IRQHandler(void);				// 38
void WEAK TIM3_IRQHandler(void);				// 39
void WEAK TIM4_IRQHandler(void);				// 40
void WEAK I2C1_EV_IRQHandler(void);				// 41
void WEAK I2C1_ER_IRQHandler(void);				// 42
void WEAK I2C2_EV_IRQHandler(void);				// 43
void WEAK I2C2_ER_IRQHandler(void);				// 44
void WEAK SPI1_IRQHandler(void);				// 45
void WEAK SPI2_IRQHandler(void);				// 46
void WEAK USART1_IRQHandler(void);				// 47
void WEAK USART2_IRQHandler(void);				// 48
void WEAK USART3_IRQHandler(void);				// 49
void WEAK EXTI15_10_IRQHandler(void);			// 50
void WEAK RTCAlarm_IRQHandler(void);			// 51
void WEAK USBWakeUp_IRQHandler(void);			// 52

// =======================================================================================================
//
//	mthomas: If been built with VECT_TAB_RAM this creates two tables:
//
//	(1) a minimal table (stack-pointer, reset-vector) used during startup before relocation of the 
//	    vector table using SCB_VTOR
//	(2) a full table which is copied to RAM and used after vector relocation (NVIC_SetVectorTable)
//
//	If been built without VECT_TAB_RAM the following comment from STM is valid:
//	The minimal vector table for a Cortex M3. Note that the proper constructs must be placed on this 
//	to ensure that it ends up at physical address 0x0000.0000.
//
// =======================================================================================================

// -------  isr_vactor table are located in Flash  -------------------------------------------------------

__attribute__ ((section(".isr_vectorsflash")))  		// linker scriptor에서 사용.


// next code( from "#if0" to "#endif" ) doesn't have to excute. it is for startup on RAM

#if 0	// -----------------------------------------------------------------------------------------------

// -------  isr_vactor tables are located in RAM  --------------------------------------------------------
//void (* const g_pfnVectorsStartup[])(void) =
//{
//    (intfunc)((unsigned long)&_estack),	/* The initial stack pointer during startup */
//    Reset_Handler,             			/* The reset handler during startup */
//};
//__attribute__ ((section(".isr_vectorsram")))

#endif	// -----------------------------------------------------------------------------------------------


// ------- isr vector table  -----------------------------------------------------------------------------

void (* g_pfnVectors[])(void) =
{
	(intfunc)((unsigned long)&_estack),	//  1.The stack pointer after relocation
	Reset_Handler,						//  2.Reset Handler
	NMI_Handler,						//  3.NMI Handler
	HardFault_Handler,					//  4.Hard Fault Handler
	MemManage_Handler,					//  5.MPU Fault Handler
	BusFault_Handler,					//  6.Bus Fault Handler
	UsageFault_Handler,					//  7.Usage Fault Handler
	0,									//  8.Reserved
	0,									//  9.Reserved
	0,									// 10.Reserved
	0,									// 11.Reserved
	SVC_Handler,						// 12.SVCall Handler
	DebugMon_Handler,					// 13.Debug Monitor Handler
	0,									// 14.Reserved
	PendSV_Handler,						// 15.PendSV Handler
	SysTick_Handler,					// 16.SysTick Handler
	
	// External Interrupts //
	WWDG_IRQHandler,					//  1.Window Watchdog
	PVD_IRQHandler,						//  2.PVD through EXTI Line detect
	TAMPER_IRQHandler,					//  3.Tamper
	RTC_IRQHandler,						//  4.RTC
	FLASH_IRQHandler,					//  5.Flash
	RCC_IRQHandler,						//  6.RCC
	EXTI0_IRQHandler,					//  7.EXTI Line 0
	EXTI1_IRQHandler,					//  8.EXTI Line 1
	EXTI2_IRQHandler,					//  9.EXTI Line 2
	EXTI3_IRQHandler, 					// 10.EXTI Line 3
	EXTI4_IRQHandler,					// 11.EXTI Line 4
	DMA1_Channel1_IRQHandler,			// 12.DMA1 Channel 1
	DMA1_Channel2_IRQHandler,			// 13.DMA1 Channel 2
	DMA1_Channel3_IRQHandler,			// 14.DMA1 Channel 3
	DMA1_Channel4_IRQHandler,			// 15.DMA1 Channel 4
	DMA1_Channel5_IRQHandler,			// 16.DMA1 Channel 5
	DMA1_Channel6_IRQHandler,			// 17.DMA1 Channel 6
	DMA1_Channel7_IRQHandler,			// 18.DMA1 Channel 7
	ADC1_2_IRQHandler,					// 19.ADC1 & ADC2
	USB_HP_CAN1_TX_IRQHandler,			// 20.USB High Priority or CAN1 TX
	USB_LP_CAN1_RX0_IRQHandler,			// 21.USB Low  Priority or CAN1 RX
	CAN1_RX1_IRQHandler,				// 22.CAN1 RX1
	CAN1_SCE_IRQHandler,				// 23.CAN1 SCE
	EXTI9_5_IRQHandler,					// 24.EXTI Line 9..5
	TIM1_BRK_IRQHandler,				// 25.TIM1 Break
	TIM1_UP_IRQHandler,					// 26.TIM1 Update
	TIM1_TRG_COM_IRQHandler,			// 27.TIM1 Trigger and Commutation
	TIM1_CC_IRQHandler,					// 28.TIM1 Capture Compare
	TIM2_IRQHandler,					// 29.TIM2
	TIM3_IRQHandler,					// 30.TIM3
	TIM4_IRQHandler,		 			// 31.TIM4
	I2C1_EV_IRQHandler,					// 32.I2C1 Event
	I2C1_ER_IRQHandler,					// 33.I2C1 Error
	I2C2_EV_IRQHandler,					// 34.I2C2 Event
	I2C2_ER_IRQHandler,					// 35.I2C2 Error
	SPI1_IRQHandler,					// 36.SPI1
	SPI2_IRQHandler,					// 37.SPI2
	USART1_IRQHandler,					// 38.USART1
	USART2_IRQHandler,					// 39.USART2
	USART3_IRQHandler,					// 40.USART3
	EXTI15_10_IRQHandler,				// 41.EXTI Line 15..10
	RTCAlarm_IRQHandler,				// 42.RTC Alarm through EXTI Line
	USBWakeUp_IRQHandler,				// 43.USB Wakeup from suspend
	0,0,0,0,0,0,0,						// 44.,45.,46.,47.,48.,49.

//	(intfunc)0xF108F85F					// @0x108.ThisisforbootinRAMmodeforSTM32F10xMediumDensity devices.
};


// -------------------------------------------------------------------------------------------------------
//	초기화 과정에서 SP ← _estack, PC ← Reset_Handler 로 설정이 되어, Reset_Handler()가 호출된다.
// -------------------------------------------------------------------------------------------------------

void Reset_Handler(void)        // Reset_Handler() Start - 여기서부터 코드가 처음 시작되는 부분이다.
{
	#ifdef STARTUP_DELAY
  		volatile unsigned long i;
  		for (i=0;i<500000;i++) { ; }
	#endif
//////	clock 설정 - 내부클럭 or 외부클럭
	unsigned long StartUpCounter = 0, HSEStatus = 0;

	/* Initialize data and bss */
	__Init_Data();

	// Select HSI(internal clock source) or HSE(external clock source)
	// PLLSRC(phase loop lock source)
	// 8MHz/2 x 9 = 36MHz
	// 12MHz x 6 = 72MHz

	// HSI(0x1<<0) or HSE ON(0x1<<16) RCC_CR - bit01:HSION bit, bit16:HSEON
	// *(volatile unsigned long *) 0x40021000 |= 1;	//RCC_CR(0x40021000)-Set HSION bit(내부클럭선택)
	RCC_CR |= 1<<16;	// Set HSEON bit(외부클럭선택)

//////	clock 설정 확인
	do
	{
		// HSIStatus = (*(volatile unsigned long *) 0x40021000 & 0x1<<1);
		// RCC_CR(0x40021000) - HSIRDY bit set되면 HSEStatus != 0
		HSEStatus = (RCC_CR & 0x1<<17);
		// RCC_CR(0x40021000) - HSERDY bit set되면 HSEStatus != 0
		StartUpCounter++;
	}
	while((HSEStatus == 0) && (StartUpCounter != 0x0500));
	// HSEStatus != 0 이고, StartUpCounter = 500 이 될때까지 대기

//////	FLASH Memory Latency 설정(2 Wait State)
	// 0x40022000 FLASH_ACR RRRR RRRR RRRR RRRR RRRR RRRR RRxx xxxx xxxx
	FLASH_ACR |=  0x10;		// xxxx xxxx xxxx xxxx xxxx xxxx xxx1 xxxx bit4 PRFTBE=1 Set.
	FLASH_ACR &= ~(0x7);	// bit2,1,0 Clear
	FLASH_ACR |=  0x2;		// bit2,1,0 = 0,1,0
	// Set Latency 010 : 2 Wait State, when 48Mhz< SysClk <=72Mhz

//////	PLL 설정 내부 일 경우 36MHz 외부 일 경우 72Mhz로 설정함 ( 0x40021004는 RCC_CFGR의 주소)
	//*(volatile unsigned long *) 0x40021004 &= ~(0xF<<18 | 0x1<<17 | 0x1<<16);	// 0x3F0000;
	// RCC_CFGR   &= ~(0000 0000 0001 1111 1000 0000 0000 0000)
	// RCC_CFGR   &=   1111 1111 1110 0000 0111 1111 1111 1111   bit16-21 Clear
	//*(volatile unsigned long *) 0x40021004 |= (0x7<<18);	//RCC_CFGR 내부 4MHz

	// PLLSRC bit(16)=1: 외부클럭, PLLXTPRE bit(17)=0: 클럭 1/2분주 사용X, PLLMULL(18-21)=7: 외부클럭x9
	// 여기서 설정 전에 값을 Clear 해야하나?
	RCC_CFGR &= ~(0xF<<18 | 0x1<<17 | 0x1<<16);
	// 0000 0000 0011 1111 0000 0000 0000 0000
	// 1111 1111 1100 0000 1111 1111 1111 1111 PLLMUL[21:18], PLLXTRE[17], PLLSRC[16] Clear
	// Clear bit bit16-21
	RCC_CFGR |= (0x7<<18 | 0x1<<16);	// PLLMUL=0111(×9) PLLSRC=1(external 8MHz) → 8×9 = 72MHz
	//*(volatile unsigned long *) 0x40021004 |= (0x4<<18 | 0x1<<16);	//0x110000;//RCC_CFGR//12MHz

	//*(volatile unsigned long *) 0x40021000 |= 0x01 << 24;				//0x01000000 - PLLON
	RCC_CR	 |= (0x01 << 24 | 0x01<<16);	// HSEON,PLLON bit set
	while((RCC_CR & (0x1<<25)) == 0);		// Wait PLLRDY bit set

	// System Clock으로 PLL을 선택한다. System Clock Switch 설정 : RCC_CFGR bit1,0
	// Bits 1:0 SW : System clock switch
	// 00: HSI selected as system clock
	// 01: HSE selected as system clock
	// 10: PLL selected as system clock  ***
	// 11: not allowed

	RCC_CFGR &= ~0x3;	// bit 1,0 → 00 : clear
	RCC_CFGR |=  0x2;	// bit 1,0 → 10 : Set SW(System clock Switch) = 10
	
	while( (RCC_CFGR & 0xC) != 0x08);	// while((RCC_CFG & 0b1010) != 0b1000);
	// RCC_CFGR SW상태가 SWS(SW Status)에 반영되기를 기다려야한다면
	// while((RCC_CFGR & 0xC) == 0x0c); 가 맞지않을까?

////// HCLK(AHB)=72Mhz, PCLK2(APB2)=72Mhz, PCLK1(APB1)=36Mhz Clock set
	RCC_CFGR |= ( 0<< 7 | 0<<11 | 0<<10 | 0<<10 );	// HPRE 0XXX HCLK	= 72MHZ
	//xxxx xxxx xxxx xxxx xxxx xxxx 0XXX xxxx
	RCC_CFGR |= ( 0<<13 | 0<<12 | 0<<11 );			// PPRE2 0XX PCLK2	= 72MHZ
	//xxxx xxxx xxxx xxxx xx0X Xxxx xxxx xxxx
	RCC_CFGR |= ( 1<<10 | 0<< 9 | 0<< 8 );			// PPRE1 100 PCLK1	= 36MHz	
	//xxxx xxxx xxxx xxxx xxxx x100 xxxx xxxx		//(PCLK1 has to be <= 36MHz)
	

	// RCC_AHBENR(ADD:0x40021014, RST_VAl:0x00000000) AHB에 있는 DMA1,2 등 주변장치에 Clock 소스 제어
	RCC_AHBENR |= 0x1 << 0;	// DMA1 clock enable

	// RCC_APB2ENR(ADD:0x40021018, RST_VAl:0x00000000) APB2에 있는 UART 등 주변장치에 Clock 소스 제어
	// ( GPIO & Alternation Function IO has to be enable, to use USART1 )
	RCC_APB2ENR |= 0x1<<14 | 0x1<<11 | 0x1<<9 | 0x1<<4 | 0x1<<3 | 0x1<<2 | 0x1<<0;
	//              USART1 |   TIM1  |  ADC1  |  IOPC  |  IOPB  |  IOPA  |  AFIO

	// RCC_APB1ENR(ADD:0x4002101c, RST_VAl:0x00000000) APB1에 있는 TIM2-3 등 주변장치에 Clock 소스 제어
	RCC_APB1ENR |= 0x1 << 22 | 0x1 << 2| 0x1 << 1 | 0x1 << 0;
	//                I2C2   |   TIM4  |   TIM3   |   TIM2

//////	Configure the GPIO ports

	// GPIOA Base Address 0x4001 0800
	// GPIOB Base Address 0x4001 0C00
	// GPIOC Base Address 0x4001 1000

	// Port A Configuration Register Low  : GPIOA_CRL ADD offset(0x00) RST Value(0x4444 4444)
	GPIOA_CRL = 0x33333333;
	// PA_L 8bit : 0011 0011 0011 0011 0011 0011 0011 0011
	// PA00-PA07 All Set Output(Push Pull/High Spped-50Mhz)
	
	// Port A Configuration Register high : GPIOA_CRH ADD offset(0x04) RST Value(0x4444 4444)
	GPIOA_CRH = 0x333334B3;
	// PA_H 8bit : 0011 0011 0011 0011 0011 0100 1011 0011
	// PA9,10:UART, PA11,12:USB, else set output( PushPull, HighSpeed)

	// Port B Configuration Register Low  : GPIOB_CRL ADD offset(0x00) RST Value(0x4444 4444)
	GPIOB_CRL = 0x33333333;
	// PB_L 8bit : 0011 0011 0011 0011 0011 0011 0011 0011
	// PB00-PB07 All Set Output(Push Pull/High Spped-50Mhz)
	
	// Port B Configuration Register high : GPIOB_CRH ADD offset(0x04) RST Value(0x4444 4444)
	GPIOB_CRH = 0x33333333;
	// PB_H 8bit : 0011 0011 0011 0011 0011 0011 0011 0011
	// PB08-PB15 All Set Output(Push Pull/High Spped-50Mhz)

	// Port C Configuration Register Low  : GPIOC_CRL ADD offset(0x00) RST Value(0x4444 4444)
	GPIOC_CRL = 0x33333333;
	// PC_L 8bit : 0011 0011 0011 0011 0011 0011 0011 0011
	// PC00-PC07 All Set Output(Push Pull/High Spped-50Mhz)

	// Port C Configuration Register high : GPIOC_CRH ADD offset(0x04) RST Value(0x4444 4444)
	GPIOC_CRH = 0x33333333;
	// PC_H 8bit : 0011 0011 0011 0011 0011 0011 0011 0011
	// PC08-PB15 All Set Output(Push Pull/High Spped-50Mhz)

////// AFIO Set(SWJ I/O pin remap) for PA13, 14, 15, PB3, PB4 - All Free
	AFIO_MAPR &= ~( 7<<24);		// SWJ_CFG[2:0]bit Clear
	AFIO_MAPR |=  ( 1<<26);		// SWJ_CFG[2:0]bit = 1,0,0
	
////// USART1 configuration

	// USART1 configured as follow:
	//  - BaudRate = 115,200 baud
	//  - Word Length = 8 Bits
	//  - One Stop Bit
	//  - No parity
	//  - Hardware flow control disabled (RTS and CTS signals)
	//  - Receive and transmit enabled

	// UART1 Base Address   : 0x4001 3800

	// *(volatile unsigned long *) 0x40013808 = 19 << 4 | 8; // 115,200bps(ins OSC 36Mhz)
	// Baud Rate Register   : USART_BRR ADD offset(0x08) RST Value(0x0000 0000)
	USART1_BRR  = 39 << 4 | 1;	// 115,200 bps (ext OSC 72Mhz) : DIV_Mantisa=39, DIV_Fraction=1

	// Control Register1    : USART_CR1 ADD offset(0x0C) RST Value(0x0000 0000)
	USART1_CR1  = 0x200C;		// ADD Mask WakeUP,1 Start bit, 8 Data bit, Tx Enable, Rx Enable
																		
	// Control Register2    : USART_CR2 ADD offset(0x10) RST Value(0x0000 0000)
	USART1_CR2  = 0x0;			// 1 Stop Bit

	// Control Register3    : USART_CR3 ADD offset(0x14) RST Value(0x0000 0000)
	USART1_CR3  = 0x0;			// Hardware flow control disabled

	USART1_CR1 |= 0x2000;       // SET ADD Mask WakeUP Why?????

	main();
	
	while(1) { ; }
}	// Reset_Handler() End


// =======================================================================================================
//	initializes data and bss sections
// =======================================================================================================

void __Init_Data(void)
{
	unsigned long *pulSrc, *pulDest;

	/* Copy the data segment initializers from flash to SRAM */
	pulSrc  = &_sidata;
	pulDest = &_sdata;
	if ( pulSrc != pulDest )
	{
		for(; pulDest < &_edata; )
		{
			*(pulDest++) = *(pulSrc++);
		}
	}
	/* Zero fill the bss segment. */
	for(pulDest = &_sbss; pulDest < &_ebss; )
	{
		*(pulDest++) = 0;
	}
}


// =======================================================================================================
//	Provide weak aliases for each Exception handler to the Default_Handler.
//	As they are weak aliases, any function with the same name will override this definition.
// =======================================================================================================
#pragma weak MMI_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler
#pragma weak SysTick_Handler = Default_Handler
#pragma weak WWDG_IRQHandler = Default_Handler
#pragma weak PVD_IRQHandler = Default_Handler
#pragma weak TAMPER_IRQHandler = Default_Handler
#pragma weak RTC_IRQHandler = Default_Handler
#pragma weak FLASH_IRQHandler = Default_Handler
#pragma weak RCC_IRQHandler = Default_Handler
#pragma weak EXTI0_IRQHandler = Default_Handler
#pragma weak EXTI1_IRQHandler = Default_Handler
#pragma weak EXTI2_IRQHandler = Default_Handler
#pragma weak EXTI3_IRQHandler = Default_Handler
#pragma weak EXTI4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel1_IRQHandler = Default_Handler
#pragma weak DMA1_Channel2_IRQHandler = Default_Handler
#pragma weak DMA1_Channel3_IRQHandler = Default_Handler
#pragma weak DMA1_Channel4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel5_IRQHandler = Default_Handler
#pragma weak DMA1_Channel6_IRQHandler = Default_Handler
#pragma weak DMA1_Channel7_IRQHandler = Default_Handler
#pragma weak ADC1_2_IRQHandler = Default_Handler
#pragma weak USB_HP_CAN1_TX_IRQHandler = Default_Handler
#pragma weak USB_LP_CAN1_RX0_IRQHandler = Default_Handler
#pragma weak CAN1_RX1_IRQHandler = Default_Handler
#pragma weak CAN1_SCE_IRQHandler = Default_Handler
#pragma weak EXTI9_5_IRQHandler = Default_Handler
#pragma weak TIM1_BRK_IRQHandler = Default_Handler
#pragma weak TIM1_UP_IRQHandler = Default_Handler
#pragma weak TIM1_TRG_COM_IRQHandler = Default_Handler
#pragma weak TIM1_CC_IRQHandler = Default_Handler
#pragma weak TIM2_IRQHandler = Default_Handler
#pragma weak TIM3_IRQHandler = Default_Handler
#pragma weak TIM4_IRQHandler = Default_Handler
#pragma weak I2C1_EV_IRQHandler = Default_Handler
#pragma weak I2C1_ER_IRQHandler = Default_Handler
#pragma weak I2C2_EV_IRQHandler = Default_Handler
#pragma weak I2C2_ER_IRQHandler = Default_Handler
#pragma weak SPI1_IRQHandler = Default_Handler
#pragma weak SPI2_IRQHandler = Default_Handler
#pragma weak USART1_IRQHandler = Default_Handler
#pragma weak USART2_IRQHandler = Default_Handler
#pragma weak USART3_IRQHandler = Default_Handler
#pragma weak EXTI15_10_IRQHandler = Default_Handler
#pragma weak RTCAlarm_IRQHandler = Default_Handler
#pragma weak USBWakeUp_IRQHandler = Default_Handler


// =======================================================================================================
//	This is the code that gets called when the processor receives an unexpected interrupt. 
//	This simply enters an infinite loop, preserving the system state for examination by a debugger.
// =======================================================================================================

void Default_Handler(void)
{
	/* Go into an infinite loop. */
	while (1)
	{
	}
}

// 	--------------------------------   >>>>>  END OF FILE  <<<<<   ----------------------------------------
