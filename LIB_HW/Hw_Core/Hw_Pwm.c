#define PWM_LOCAL

// #define	TIM1_CR1		*(volatile unsigned long *) 0x40012c00
// #define	TIM1_CR2		*(volatile unsigned long *) 0x40012c04
// #define	TIM1_SMCR 	*(volatile unsigned long *) 0x40012c08   //
// #define	TIM1_DIER		*(volatile unsigned long *) 0x40012c0c   //
// #define	TIM1_SR 		*(volatile unsigned long *) 0x40012c10   //
// #define	TIM1_EGR		*(volatile unsigned long *) 0x40012c14   //
// #define	TIM1_CCMR1	*(volatile unsigned long *) 0x40012c18
// #define	TIM1_CCMR2	*(volatile unsigned long *) 0x40012c1c
// #define	TIM1_CCER		*(volatile unsigned long *) 0x40012c20
// #define	TIM1_CNT		*(volatile unsigned long *) 0x40012c24   //
// #define	TIM1_PSC	  *(volatile unsigned long *) 0x40012c28
// #define	TIM1_ARR	  *(volatile unsigned long *) 0x40012c2c
// #define	TIM1_RCR	  *(volatile unsigned long *) 0x40012c30   //
// #define	TIM1_CCR1		*(volatile unsigned long *) 0x40012c34
// #define	TIM1_CCR2		*(volatile unsigned long *) 0x40012c38
// #define	TIM1_CCR3		*(volatile unsigned long *) 0x40012c3c
// #define	TIM1_CCR4		*(volatile unsigned long *) 0x40012c40
// #define	TIM1_BDTR		*(volatile unsigned long *) 0x40012c44   //
// #define	TIM1_DCR		*(volatile unsigned long *) 0x40012c48   //
// #define	TIM1_DMAR		*(volatile unsigned long *) 0x40012c4c   //


#include "Hw_Pwm.h"

unsigned short g_duty = 0;
unsigned short g_period = 0;

PWM_DEF void Pwm_Init()
{
    uint16_t tmpcr = 0;
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
    uint16_t tmpccmr1 = 0;

    *(volatile unsigned long *) 0x40012c2c = (g_period - 1);//auto reload reigster setting

    *(volatile unsigned long *) 0x40012c28 = 0;//prescaler setting

    *(volatile unsigned long *) 0x40012c30 = 0;//Set the Repetition Counter value

    *(volatile unsigned long *) 0x40012c14 = 0x0001;
    //Generate an update event to reload the Prescaler and the Repetition counter values immediately
    *(volatile unsigned long *) 0x40012c18 |= (0x2<< 2)              // ch1: compare fast & preload enable(11)
                                           | (0x6<< 4);             // ch1: OC Mode = PWM mode1 ( 110 )

    *(volatile unsigned long *) 0x40012c20 |= (0x1 << 0)            // ch1 : output enable, polarity
                                           | (0x1 << 2);            // ch1N: output enable, polarity

    *(volatile unsigned long *) 0x40012c04 |= 0x01 << 8;

        /* Set the Capture Compare Register value */
    *(volatile unsigned long *) 0x40012c34 = g_duty-1/*TIM_OCInitStruct->TIM_Pulse*/;    //<----------------------------------------
        //    TIM1_CCR2    = g_duty-1;      // ch2: 50% duty
        //    TIM1_CCR3    = g_duty-1;      // ch3: 50% duty
        //    TIM1_CCR4    = g_duty-1;      // ch3: 50% duty
            
    *(volatile unsigned long *) 0x40012c00 |= ( 0x1<< 4) | ( 0x1<< 0);      /* TIM_CR1_ARPE : Set the ARR Preload Bit */
                                                      // set DIR (Direction - down)
                                                      /* TIM_CR1_CEN : Enable the TIM Counter */
    *(volatile unsigned long *) 0x40012c44 |= 0x01<<15;                      /* TIM_BDTR_MOE : Enable the TIM Main Output */


}

PWM_DEF void Pwm_Duty(unsigned short change_duty)
{
    *(volatile unsigned long *) 0x40012c34 = change_duty - 1;
}

