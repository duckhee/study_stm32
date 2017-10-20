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

void Reset_Handler(void) __attribute__((__interrupt__));

__attribute__((section(".isr_vectorsflash")))
//__attribute__(()) 붙여서 해야한다.

void (*g_pfnVectors[])(void) = 
{
    (intfunc)((unsigned long)&_ld_stack_address),
    Reset_Handler,
};

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