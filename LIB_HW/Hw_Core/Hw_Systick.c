#define SYSTICK_LOCAL

#include "Hw_Systick.h"

SYSTICK_DEF void Systick_Init()
{
    	// SysTick reLOAD value Register				ADD: 0xe000 e014, RST value: Unpredictable	(RW)
													// b31-24 Reserved, b23-b00 Reload Value
	*(volatile unsigned int *)0xe000e014 = 360000;	// RRRR RRRR xxxx xxxx xxxx xxxx xxxx xxxx
	
	// SysTick Current VAL Register					ADD: 0xe000 e018, RST value: Unpredictable	(RW)
													// b31-24 Reserved, b23-b00 Current Value
	*(volatile unsigned int *)0xe000e018 = 0;		// RRRR RRRR xxxx xxxx xxxx xxxx xxxx xxxx
	
	// SysTic CTRL Register 						ADD: 0xe000 e010, RST value: 0x0000 0000	(RW)
	// b31-17 Reserved, b16:COUNTFLAG, b15-b03 Resrved, b02:CLKSOURCE, b01:TICKINT, b00:ENABLE	
	*(volatile unsigned int *)0xe000e010 = 0x7;		// RRRR RRRR RRRR RRR0 RRRR RRRR RRRR R111
    //												// CLKSRC=1 INT=1 EN=1
    
    
}

SYSTICK_DEF void Systick_Handler(void)
{
    
}