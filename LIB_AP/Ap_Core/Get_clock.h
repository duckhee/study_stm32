#ifndef __GET_CLOCK_H__
#define __GET_CLOCK_H__

#include "Ap.h"


#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)





#ifdef CLOCK_LOCAL
#define CLOCK_DEF
#else
#define CLOCK_DEF                 extern
#endif


CLOCK_DEF void Rcc_GetClocksFreq(RCC_ClocksTypeDef* RCC_Cloks);
CLOCK_DEF void System_Information(void);



#endif