
#include "Hw.h"

/* Private typedef -----------------------------------------------------------*/
typedef void( *const intfunc )( void );

/* init value for the stack pointer. defined in linker script */
//extern unsigned long _estack;
//extern unsigned long _ld_stack_address;

extern unsigned long _ld_ram_start;

extern unsigned long _ld_data_start;

extern unsigned long _ld_data_end;

extern unsigned long _ld_bss_start;

extern unsigned long _ld_bss_end;

extern unsigned long _ld_stack_address;

/* Private function prototypes -----------------------------------------------*/
void Reset_Handler(void) __attribute__((__interrupt__));

__attribute__ ((section(".isr_vectorsflash")))    //linker scriptorø°º≠ ªÁøÎµ 
/* vector table*/
void (* g_pfnVectors[])(void) =
{
//    (intfunc)((unsigned long)&_estack), /* The stack pointer after relocation */
    (intfunc)((unsigned long)&_ld_stack_address), /* The stack pointer after relocation */
//    (intfunc)((unsigned long)0x20000000 + 0x1000), /* The stack pointer after relocation */
    Reset_Handler,                      /* Reset Handler */
};

void __Init_Data(void);
void Default_Handler(void);

//인터럽트 1 - 벡터를 위한 RAM 영역 공간 활당
//-- 인터럽트 벡터는 Offset은 128 word 단위로 정렬되어야함( 512 bytes 단위 ) 4byte
volatile unsigned long Hw_ISR_VectorTable[100] __attribute__((aligned(512)));
extern void Systick_Handler(void);

int a=1;
int b;

extern int main();

void __Init_Data();

void Reset_Handler(void)
{
  
    unsigned long StartUpCounter = 0, HSEStatus = 0;

    __Init_Data();

    //////	FLASH Memory Latency ����(2 Wait State)
	// 0x40022000 FLASH_ACR RRRR RRRR RRRR RRRR RRRR RRRR RRxx xxxx xxxx
	*(volatile unsigned long *) 0x40022000 |=  0x10;		// xxxx xxxx xxxx xxxx xxxx xxxx xxx1 xxxx bit4 PRFTBE=1 Set.
	*(volatile unsigned long *) 0x40022000 &= ~(0x7);	// bit2,1,0 Clear
	*(volatile unsigned long *) 0x40022000 |=  0x2;		// bit2,1,0 = 0,1,0

    // HSI or HSE º±≈√
    // PLLSRC
    // 8MHz/2 x 18 = 72MHz
    // 12MHz x 6 = 72MHz
    
    
    ////HSI(0x1) or HSE ON(0x1<<16)
    //*(volatile unsigned long *) 0x40021000 |= 0x1;            //RCC_CR - HSION    Set HSION bit   1
    *(volatile unsigned long *) 0x40021000 |= 0x1<<16;        //RCC_CR  CR_HSEON_Set

    // º≥¡§µ» clock ¿Ã º≥¡§ µ«æ˙¥¬¡ˆ »Æ¿Œ
    do
    {
       HSEStatus = (*(volatile unsigned long *) 0x40021000 & 0x1<<17);             // HSE ¿Œ∞ÊøÏ     2
    //   HSEStatus = (*(volatile unsigned long *) 0x40021000 & 0x1<<1);             // HSI ¿Œ∞ÊøÏ
       StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != 0x0500));
  
    /////// PLL º≥¡§ ≥ª∫Œ ¿œ ∞ÊøÏ 36MHz ø‹∫Œ ¿œ ∞ÊøÏ 72Mhz∑Œ º≥¡§«‘
    *(volatile unsigned long *) 0x40021004 &= ~(0xF<<18 | 0x1<<17 | 0x1<<16);              //0x3F0000;      //RCC_CFGR
    //*(volatile unsigned long *) 0x40021004 |= (0x7<<18);              //RCC_CFGR  //≥ª∫Œ 4MHz      3
    //*(volatile unsigned long *) 0x40021004 |= (0x7<<18 | 0x1<<16);              //0x1D0000;       //RCC_CFGR  //8MHz
    *(volatile unsigned long *) 0x40021004 |=  (0x4<<18 | 0x1<<16);              //0x110000;       //RCC_CFGR    //12MHz
    *(volatile unsigned long *) 0x40021000 |= 0x01 << 24/*0x1000000*/;                       //PLLON
    while( ((*(volatile unsigned long *) 0x40021000) & 0x01 << 25/*0x2000000*/) == 0);       //PLLRDY
    
    /////PLL¿ª º±≈√«—¥Ÿ.
    /////Bits 1:0 SW : System clock switch
    //00: HSI selected as system clock
    //01: HSE selected as system clock
    //10: PLL selected as system clock   <----------------- º±≈√µ 
    //11: not allowed
    *(volatile unsigned long *) 0x40021004 &= ~0x3;
    *(volatile unsigned long *) 0x40021004 |= 0x2;
    while( ((*(volatile unsigned long *) 0x40021004) & 0xC) != 0x08);

    //APB2ø° ¿÷¥¬ UART µÓ ¡÷∫Ø¿Âƒ°ø° Clock º“Ω∫ µø¿€¡¶æÓ
    //UART∞° µø¿€µ«±‚ ¿ß«ÿº≠¥¬ GPIOøÕ Alternation Function IO∞° µø¿€ªÛ≈¬ø° ¿÷æÓæﬂ «‘
    *(volatile unsigned long *) 0x40021018 |= 0x1 << 14 | 0x1 << 2 | 0x1 << 0;         // uart/ IOPA EN / AFIO EN RCC_APB2ENR
    //RCC_APB2ENR |= 0x1 << 14 | 0x1 << 2 | 0x1 << 0;

    	/* Configure the GPIO ports */
    //*(volatile unsigned long *) 0x40010804 = 0x888444B4;//PORTA_CRH
    *(volatile unsigned long *) 0x40010804 = 0x888444B4;
    //*(volatile unsigned long *) 0x40011C00 = 0x33444444;//PORTF_CRL
    //*(volatile unsigned long *) 0x40011C04 = 0x44444433;//PORTF_CRH
    
    	/* USART1 configuration ------------------------------------------------------*/
    	/* USART1 configured as follow:
    	 - BaudRate = 19200 baud
    	 - Word Length = 8 Bits
    	 - One Stop Bit
    	 - No parity
    	 - Hardware flow control disabled (RTS and CTS signals)
    	 - Receive and transmit enabled
    	*/
        // USART1_CR2 = 0x0;
        // USART1_CR1 = 0x200C;
        // USART1_CR3 = 0x0;
        // USART1_BRR = 19 << 4 | 8;
        // USART1_CR1 |= 0x2000;
     *(volatile unsigned long *) 0x40013810 = 0x0;           // 1 stop bit USART1_CR2
     *(volatile unsigned long *) 0x4001380C = 0x200C;        // 8bit no parity USART1_CR1
     *(volatile unsigned long *) 0x40013814 = 0x0;           //USART1_CR3
     //*(volatile unsigned long *) 0x40013808 = 19 << 4 | 8;   // use inside clock OSC 32Mhz USART1_BRR
     *(volatile unsigned long *) 0x40013808 = 39 << 4 | 1;   // use extern clock OSC 32Mhz 115200bps USART1_BRR     
     *(volatile unsigned long *) 0x4001380C |= 0x2000;       //USART1_CR1


    //인터럽트 2 - 벡터를 RAM 영역으로 이동
    *(volatile unsigned long *)0xE000ED08 = (unsigned long)Hw_ISR_VectorTable;
    
        //인터럽트 3 - SYSTEM TIMER interrupt 설정
    Hw_ISR_VectorTable[ 15 ] = Systick_Handler;
    
    main();
    
}


    /*__Init_Data();*/

	/* Copy the data segment initializers from flash to SRAM */
void __Init_Data()    
{
    unsigned long *pulSrc, *pulDest;
    
    pulSrc  = &_ld_data_start;
    pulDest = &_ld_ram_start;
    if ( pulSrc != pulDest )
    {
        for(; pulDest < &_ld_data_end; )
        {
            *(pulDest++) = *(pulSrc++);
        }
    }
   /* Zero fill the bss segment. */
    for(pulDest = &_ld_bss_start; pulDest < &_ld_bss_end; )
    {
        *(pulDest++) = 0;
    }
}
//SRam move code end