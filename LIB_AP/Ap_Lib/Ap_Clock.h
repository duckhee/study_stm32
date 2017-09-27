#ifndef __AP_CLOCK_H__
#define __AP_CLOCK_H__

#include "Ap.h"

#ifdef CLOCK_LOCAL
#define CLOCK_DEF 
#else
#define CLOCK_DEF              extern
#endif

#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};


CLOCK_DEF void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

CLOCK_DEF void Ld_System_Information(void);

#endif
