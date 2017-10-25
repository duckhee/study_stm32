#ifndef __HW_SYSTICK_H__
#define __HW_SYSTICK_H__

#include "Hw.h"

#define SYSTICK_ENABLE              0                                          /* Config-Bit to start or stop the SysTick Timer                         */
#define SYSTICK_TICKINT             1                                          /* Config-Bit to enable or disable the SysTick interrupt                 */
#define SYSTICK_CLKSOURCE           2                                          /* Clocksource has the offset 2 in SysTick Control and Status Register   */
#define SYSTICK_MAXCOUNT       ((1<<24) -1)                                    /* SysTick MaxCount                                                      */


#ifdef HW_SYSTICK_LOCAL
#define HW_SYSTICK_DEF
#else
#define HW_SYSTICK_DEF          extern
#endif

HW_SYSTICK_DEF uint32_t SysTick_Config(uint32_t ticks);

#endif