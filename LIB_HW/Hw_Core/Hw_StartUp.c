
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

void (*g_pfeVectors[])(void) =
{
    (intfunc)((unsigned long)&_ld_stack_address),
    Reset_Handler,
};

extern int main();

 //volatile unsigned long Hw_ISR_VectorTable[100] __attribute__((align(512)));

void Reset_Handler(void)
{
    unsigned long HSEStatus = 0, StartUpCounter = 0;

    Init_Data();
    
    do
    {
        
        HSEStatus = (*(volatile unsigned long *) 0x40021000 & 0x1<<1);
        
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != 0x0500));
    
    
    //////	FLASH Memory Latency ����(2 Wait State)
    *(volatile unsigned long *) 0x40022000 |= 0x10; //bit4 PRETBE = 1 set
    *(volatile unsigned long *) 0x40022000 &= ~(0x7); //bit 2, 1, 0 clear 0, 0, 0
    *(volatile unsigned long *) 0x40022000 |= 0x2; //bit 2, 1, 0 = 0, 1, 0
    
    *(volatile unsigned long *) 0x40021000 |= 0x1;
    
    /////// PLL ���� ���� �� ��� 36MHz �ܺ� �� ��� 72Mhz�� ������
    *(volatile unsigned long *) 0x40021004 &= ~(0xF<<18 | 0x1<<17 | 0x1<<16);              //0x3F0000;      //RCC_CFGR
    *(volatile unsigned long *) 0x40021004 |= (0x7<<18);              //RCC_CFGR  //���� 4MHz
    //*(volatile unsigned long *) 0x40021004 |= (0x7<<18 | 0x1<<16);              //0x1D0000;       //RCC_CFGR  //8MHz
    //*(volatile unsigned long *) 0x40021004 |=  (0x4<<18 | 0x1<<16);              //0x110000;       //RCC_CFGR    //12MHz
    *(volatile unsigned long *) 0x40021000 |= 0x01 << 24/*0x1000000*/;                       //PLLON

    while( ((*(volatile unsigned long *) 0x40021000) & 0x01 << 25/*0x2000000*/) == 0);       //PLLRDY
   /////PLL�� �����Ѵ�.
    /////Bits 1:0 SW : System clock switch
    //00: HSI selected as system clock
    //01: HSE selected as system clock
    //10: PLL selected as system clock   <----------------- ���õ�
    //11: not allowed
    *(volatile unsigned long *) 0x40021004 &= ~0x3;
    *(volatile unsigned long *) 0x40021004 |= 0x2;
    while( ((*(volatile unsigned long *) 0x40021004) & 0xC) != 0x08);
    *(volatile unsigned long *) 0x40021018 |= 0x1 << 14 | 0x1 << 2 | 0x1 << 0;         // uart/ IOPA EN / AFIO EN    
    //APB2�� �ִ� UART �� �ֺ���ġ�� Clock �ҽ� ��������
    //UART�� ���۵Ǳ� ���ؼ��� GPIO�� Alternation Function IO�� ���ۻ��¿� �־�� ��
//    *(volatile unsigned long *) 0x40021018 |= 0x1 << 14 | 0x1 << 3  | 0x1 << 2 | 0x1 << 0;    // uart(14)/IOPB EN(3)/IOPA EN(2)/AFIO EN(0)
//    *(volatile unsigned long *) 0x40021018 |= 0x1 << 11 | 0x1 << 9;                           // TIM1(11), ADC1 EN(9)
    //APB1 Clock �ҽ� ��������
    //TIM2 Bit 0, TIM3 Bit 1, TIM4 Bit 2, TIM5 Bit 3
    //*(volatile unsigned long *) 0x4002101C |= 0x1 << 1;                                     // TIM3(1)

    //APB2 peripheral reset register (RCC_APB2RSTR)
    //*(volatile unsigned long *) 0x4002100C |= 0x1 << 11;                                    // TIM1(11)

//AF remap and debug I/O configuration register (AFIO_MAPR)
//Address offset: 0x04
//Bits 7:6 TIM1_REMAP[1:0]: TIM1 remapping
//These bits are set and cleared by software. 
//They control the mapping of TIM1 channels 1 to 4, 1N to 3N, external trigger (ETR) and Break input (BKIN) on the GPIO ports.
//00: No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
//01: Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
//10: not used
//11: Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/

    *(volatile unsigned long *)0x40010804 = 0x888444B4;
    // *(volatile unsigned long *)0x40010004 &= ~(7<<24);
    // *(volatile unsigned long *)0x40010004 |= (1<<26);

     *(volatile unsigned long *) 0x40013810 = 0x0;           
     *(volatile unsigned long *) 0x4001380C = 0x200C;        
     *(volatile unsigned long *) 0x40013814 = 0x0;           
     *(volatile unsigned long *) 0x40013808 = 19 << 4 | 8;   
     *(volatile unsigned long *) 0x4001380C |= 0x2000;       


        //인터럽트 2 - 벡터를 RAM 영역으로 이동
   //     *(volatile unsigned long *)0xE000ED08 = (unsigned long)Hw_ISR_VectorTable;
        
        //인터럽트 3 - SYSTEM TIMER interrupt 설정
//        Hw_ISR_VectorTable[ 15 ] = Systick_Handler;
        
        main();

        #if 0

        printf("failed  upload ...");

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