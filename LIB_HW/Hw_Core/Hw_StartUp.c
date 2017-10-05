#include "Hw.h"


typedef void (*const intfunc)(void);

extern unsigned long _ld_stack_address;
extern unsigned long _ld_ram_start;
extern unsigned long _ld_text_start;
extern unsigned long _ld_text_end;
extern unsigned long _ld_data_start;
extern unsigned long _ld_data_end;
extern unsigned long _ld_bss_start;
extern unsigned long _ld_bss_end;

void Init_Data();

void Reset_Handler(void) __attribute__((__interrupt__));

__attribute__((section(".isr_vectorsflash")))

void (*g_pfnVectors[])(void) = 
{
    (intfunc)((unsigned)&_ld_stack_address),
    Reset_Handler,
};


extern int main();

extern void Systick_Handler(void);

volatile unsigned long Hw_ISR_VectorTable[100] __attribute__((align(512)));

void Reset_Handler(void)
{
    
    unsigned long HSEStatus = 0, StartUpCounter = 0;
    Init_Data();

    //////	FLASH Memory Latency ����(2 Wait State)
	// 0x40022000 FLASH_ACR RRRR RRRR RRRR RRRR RRRR RRRR RRxx xxxx xxxx
	*(volatile unsigned long *) 0x40022000 |=  0x10;		// xxxx xxxx xxxx xxxx xxxx xxxx xxx1 xxxx bit4 PRFTBE=1 Set.
	*(volatile unsigned long *) 0x40022000 &= ~(0x7);	// bit2,1,0 Clear
	*(volatile unsigned long *) 0x40022000 |=  0x2;		// bit2,1,0 = 0,1,0
    // flash memory latency end

    *(volatile unsigned long *)0x40021000 |= 0x1;
    
    do
    {
        HSEStatus = (0x40021000  & 0x1 << 1);
        StartUpCounter++;
    }while((HSEStatus == 0) && (StartUpCounter != 0x0500));
  
    *(volatile unsigned long *) 0x40021004 &= ~(0xF<<18 | 0x1<<17 | 0x1<<16);            
    
    *(volatile unsigned long *) 0x40021004 |= (0x7<<18);                  
    
    *(volatile unsigned long *) 0x40021000 |= 0x01 << 24;                   

    while( ((*(volatile unsigned long *) 0x40021000) & 0x01 << 25) == 0);   
    
    *(volatile unsigned long *) 0x40021004 &= ~0x3; 
    
    *(volatile unsigned long *) 0x40021004 |= 0x2; 
    
    while( ((*(volatile unsigned long *) 0x40021004) & 0xC) != 0x08); 

    *(volatile unsigned long *) 0x40021018 |= 0x1 << 14 | 0x1 << 2 | 0x1 << 0;         
    
    *(volatile unsigned long *)0x40010804 = 0x888444B4;
    *(volatile unsigned long *)0x40010004 &= ~(7<<24);
    *(volatile unsigned long *)0x40010004 |= (1<<26);

     *(volatile unsigned long *) 0x40013810 = 0x0;           
     *(volatile unsigned long *) 0x4001380C = 0x200C;        
     *(volatile unsigned long *) 0x40013814 = 0x0;           
     *(volatile unsigned long *) 0x40013808 = 19 << 4 | 8;   
     *(volatile unsigned long *) 0x4001380C |= 0x2000;       

    //인터럽트 2 - 벡터를 RAM 영역으로 이동
    *(volatile unsigned long *)0xE000ED08 = (unsigned long)Hw_ISR_VectorTable;
    
    //인터럽트 3 - SYSTEM TIMER interrupt 설정
    Hw_ISR_VectorTable[ 15 ] = Systick_Handler;
    
    main();

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