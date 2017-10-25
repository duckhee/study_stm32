#include "Hw.h"

typedef void (*const intfunc)(void);

//link pointer get LINKERSCRIPT
extern unsigned long _ld_stack_address;
extern unsigned long _ld_ram_start;
extern unsigned long _ld_text_start;
extern unsigned long _ld_text_end;
extern unsigned long _ld_data_start;
extern unsigned long _ld_data_end;
extern unsigned long _ld_bss_start;
extern unsigned long _ld_bss_end;

void Init_Data();

extern int main();

// void WEAK NMI_Handler(void);
// void WEAK HardFault_Handler(void);
// void WEAK MemManage_Handler(void);
// void WEAK BusFault_Handler(void);
// void WEAK UsageFault_Handler(void);
// //mthomas void WEAK MemManage_Handler(void);
// void WEAK SVC_Handler(void);
// void WEAK DebugMon_Handler(void);
// void WEAK PendSV_Handler(void);
// void WEAK SysTick_Handler(void);

// /* External Interrupts */
// void WEAK WWDG_IRQHandler(void);
// void WEAK PVD_IRQHandler(void);
// void WEAK TAMPER_IRQHandler(void);
// void WEAK RTC_IRQHandler(void);
// void WEAK FLASH_IRQHandler(void);
// void WEAK RCC_IRQHandler(void);
// void WEAK EXTI0_IRQHandler(void);
// void WEAK EXTI1_IRQHandler(void);
// void WEAK EXTI2_IRQHandler(void);
// void WEAK EXTI3_IRQHandler(void);
// void WEAK EXTI4_IRQHandler(void);
// void WEAK DMA1_Channel1_IRQHandler(void);
// void WEAK DMA1_Channel2_IRQHandler(void);
// void WEAK DMA1_Channel3_IRQHandler(void);
// void WEAK DMA1_Channel4_IRQHandler(void);
// void WEAK DMA1_Channel5_IRQHandler(void);
// void WEAK DMA1_Channel6_IRQHandler(void);
// void WEAK DMA1_Channel7_IRQHandler(void);
// void WEAK ADC1_2_IRQHandler(void);
// void WEAK USB_HP_CAN1_TX_IRQHandler(void);
// void WEAK USB_LP_CAN1_RX0_IRQHandler(void);
// void WEAK CAN1_RX1_IRQHandler(void);
// void WEAK CAN1_SCE_IRQHandler(void);
// void WEAK EXTI9_5_IRQHandler(void);
// void WEAK TIM1_BRK_IRQHandler(void);
// void WEAK TIM1_UP_IRQHandler(void);
// void WEAK TIM1_TRG_COM_IRQHandler(void);
// void WEAK TIM1_CC_IRQHandler(void);
// void WEAK TIM2_IRQHandler(void);
// void WEAK TIM3_IRQHandler(void);
// void WEAK TIM4_IRQHandler(void);
// void WEAK I2C1_EV_IRQHandler(void);
// void WEAK I2C1_ER_IRQHandler(void);
// void WEAK I2C2_EV_IRQHandler(void);
// void WEAK I2C2_ER_IRQHandler(void);
// void WEAK SPI1_IRQHandler(void);
// void WEAK SPI2_IRQHandler(void);
// void WEAK USART1_IRQHandler(void);
// void WEAK USART2_IRQHandler(void);
// void WEAK USART3_IRQHandler(void);
// void WEAK EXTI15_10_IRQHandler(void);
// void WEAK RTCAlarm_IRQHandler(void);
// void WEAK USBWakeUp_IRQHandler(void);

void Reset_Handler(void) __attribute__((__interrupt__));

__attribute__((section(".isr_vectorsflash")))
//__attribute__(()) 붙여서 해야한다.

void (*g_pfnVectors[])(void) = 
{
    (intfunc)((unsigned long)&_ld_stack_address),
    Reset_Handler,              /* Reset Handler */
    // NMI_Handler,                /* NMI Handler */
    // HardFault_Handler,          /* Hard Fault Handler */
    // MemManage_Handler,          /* MPU Fault Handler */
    // BusFault_Handler,           /* Bus Fault Handler */
    // UsageFault_Handler,         /* Usage Fault Handler */
    // 0,                          /* Reserved */
    // 0,                          /* Reserved */
    // 0,                          /* Reserved */
    // 0,                          /* Reserved */
    // SVC_Handler,                /* SVCall Handler */
    // DebugMon_Handler,           /* Debug Monitor Handler */
    // 0,                          /* Reserved */
    // PendSV_Handler,             /* PendSV Handler */
    // SysTick_Handler,            /* SysTick Handler */
    // /* External Interrupts */
    // WWDG_IRQHandler,            /* Window Watchdog */
    // PVD_IRQHandler,             /* PVD through EXTI Line detect */
    // TAMPER_IRQHandler,          /* Tamper */
    // RTC_IRQHandler,             /* RTC */
    // FLASH_IRQHandler,           /* Flash */
    // RCC_IRQHandler,             /* RCC */
    // EXTI0_IRQHandler,           /* EXTI Line 0 */
    // EXTI1_IRQHandler,           /* EXTI Line 1 */
    // EXTI2_IRQHandler,           /* EXTI Line 2 */
    // EXTI3_IRQHandler,           /* EXTI Line 3 */
    // EXTI4_IRQHandler,           /* EXTI Line 4 */
    // DMA1_Channel1_IRQHandler,   /* DMA1 Channel 1 */
    // DMA1_Channel2_IRQHandler,   /* DMA1 Channel 2 */
    // DMA1_Channel3_IRQHandler,   /* DMA1 Channel 3 */
    // DMA1_Channel4_IRQHandler,   /* DMA1 Channel 4 */
    // DMA1_Channel5_IRQHandler,   /* DMA1 Channel 5 */
    // DMA1_Channel6_IRQHandler,   /* DMA1 Channel 6 */
    // DMA1_Channel7_IRQHandler,   /* DMA1 Channel 7 */
    // ADC1_2_IRQHandler,          /* ADC1 & ADC2 */
    // USB_HP_CAN1_TX_IRQHandler,  /* USB High Priority or CAN1 TX */
    // USB_LP_CAN1_RX0_IRQHandler, /* USB Low  Priority or CAN1 RX0 */
    // CAN1_RX1_IRQHandler,        /* CAN1 RX1 */
    // CAN1_SCE_IRQHandler,        /* CAN1 SCE */
    // EXTI9_5_IRQHandler,         /* EXTI Line 9..5 */
    // TIM1_BRK_IRQHandler,        /* TIM1 Break */
    // TIM1_UP_IRQHandler,         /* TIM1 Update */
    // TIM1_TRG_COM_IRQHandler,    /* TIM1 Trigger and Commutation */
    // TIM1_CC_IRQHandler,         /* TIM1 Capture Compare */
    // TIM2_IRQHandler,            /* TIM2 */
    // TIM3_IRQHandler,            /* TIM3 */
    // TIM4_IRQHandler,            /* TIM4 */
    // I2C1_EV_IRQHandler,         /* I2C1 Event */
    // I2C1_ER_IRQHandler,         /* I2C1 Error */
    // I2C2_EV_IRQHandler,         /* I2C2 Event */
    // I2C2_ER_IRQHandler,         /* I2C2 Error */
    // SPI1_IRQHandler,            /* SPI1 */
    // SPI2_IRQHandler,            /* SPI2 */
    // USART1_IRQHandler,          /* USART1 */
    // USART2_IRQHandler,          /* USART2 */
    // USART3_IRQHandler,          /* USART3 */
    // EXTI15_10_IRQHandler,       /* EXTI Line 15..10 */
    // RTCAlarm_IRQHandler,        /* RTC Alarm through EXTI Line */
    // USBWakeUp_IRQHandler,       /* USB Wakeup from suspend */
    // 0,0,0,0,0,0,0,
    // (intfunc)0xF108F85F          /* @0x108. This is for boot in RAM mode for
    //                                STM32F10x Medium Density devices. */
};

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

void Reset_Handler(void)
{
    unsigned long HSIStatus = 0, StartUpCounter = 0;
    //unsigned long HSEStatus = 0, StartUpCounter = 0;
    Init_Data();
    
    //HSI On 
    *(volatile unsigned long *)0x40021000 |= 0x1 << 0; 
    //HSE ON
    //*(volatile unsigned long *)0x40021000 |= 0x1 << 16;
    
    //check HSI Or HSE READY
    do
    {
        //HSI check
        HSIStatus = (*(volatile unsigned long *)0x40021000 & 0x1 << 1); //HSI RDY check bit
        //HSE check
        //HSEStatus = (*(volatile unsigned long *)0x40021000 & 0x1 << 17); //HSE RDY check bit
        StartUpCounter++;
    }while((HSIStatus == 0) && (StartUpCounter != 0x0500));
    
    ///////////////// FLASH Memory Latency move code RAM sections ////////////////////////////////////
    *(volatile unsigned long *)0x40022000 |= 0x10; //bit PRETBE = 1 Set
    *(volatile unsigned long *)0x40022000 &= ~(0x7); //bit 2, 1, 0 clear 0, 0, 0
    *(volatile unsigned long *)0x40022000 |= 0x2; //bit 2, 1, 0 = 0, 1, 0
    //////////////////////////////////////////////////////////////////////////////////////////////////
    
    // reset setting PLL 
    *(volatile unsigned long *)0x40021004 &= ~(0xF << 18 | 0x1 << 17 | 0x1 << 16); //18 bit set 0, 17 bit set 0, 16 bit set 0

    *(volatile unsigned long *)0x40021004 |= (0x7 << 18); //0111: PLL input clock x 9 4MHz ?? HSI = 8MHz
    // *(volatile unsigned long *)0x40021004 |= (0x7 << 18 | 0x1 << 16); //0111 : PLL input clock x 9 HSE Set 8MHz ??
    // *(volatile unsigned long *)0x40021004 |= (0x4 << 18 | 0x1 << 16); //0x100 : PLL input clock x 6 HSE set 12MHz
    
    *(volatile unsigned long *) 0x40021000 |= 0x01 << 24/*0x1000000*/;                       //PLLON
    while( ((*(volatile unsigned long *) 0x40021000) & 0x01 << 25/*0x2000000*/) == 0);       //PLLRDY
    /////////// PLL Seting System clock ///////////////////////////////
    /*
        Bit 1:0 SW : System Clock
        00: HSI selected as system clock(PLL)
        01: HSE selected as system clock(PLL)
        10: PLL selected as system clock <------------- use this
        11: not allowed (not use system clock PLL)
    */
    *(volatile unsigned long *)0x40021004 &= ~(0x3); //reset PLL 
    *(volatile unsigned long *)0x40021004 |= 0x2; //set system clcok PLL
    while(((*(volatile unsigned long *)0x40021004) & 0xC) != 0x08); // ??? 알아보기 
    *(volatile unsigned long *) 0x40021018 |= 0x1 << 14 | 0x1 << 2 | 0x1 << 0;            // uart/ IOPA EN / AFIO EN    APB2ENR
    *(volatile unsigned long *)0x40010804 = 0x888444B4; //GPIO A CRH bit

   
    	/* USART1 configuration ------------------------------------------------------*/
    	/* USART1 configured as follow:
    	 - BaudRate = 19200 baud
    	 - Word Length = 8 Bits
    	 - One Stop Bit
    	 - No parity
    	 - Hardware flow control disabled (RTS and CTS signals)
    	 - Receive and transmit enabled
    	*/
    *(volatile unsigned long *) 0x40013810 = 0x0;           // 1 stop bit
    *(volatile unsigned long *) 0x4001380C = 0x200C;        // 8bit no parity
    *(volatile unsigned long *) 0x40013814 = 0x0;
    *(volatile unsigned long *) 0x40013808 = 19 << 4 | 8; //OSC 32MHz 115200bps Setting
    //*(volatile unsigned long *)0x40013808 = 39 << 4 | 1; //OSC 72MHz 115200bps Setting
    *(volatile unsigned long *) 0x4001380C |= 0x2000;

    main(); //jump main function

    #if 0

        printf("failed load ..");

    #endif

}


void Init_Data()
{
    unsigned long *pulSrc, *pulDest;

    pulSrc = &_ld_data_start;
    pulDest = &_ld_ram_start;

    if(pulSrc != pulDest)
    {
        for(;pulDest < &_ld_data_end; )
        {
            *(pulDest++) = *(pulSrc++);

        }
    }

    for(pulDest = &_ld_bss_start; pulDest <  &_ld_bss_end; )
    {
        *(pulDest++) = 0;
    }
}
//code move ram section 


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
#pragma weak SPI3_IRQHandler = Default_Handler


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
