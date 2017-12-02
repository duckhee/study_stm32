#ifndef __HW_NVIC_H__
#define __HW_NVIC_H__

#include "Hw.h"

#define SCS_BASE            (0xE000E000)                              /*!< System Control Space Base Address    */
#define NVIC_BASE           (SCS_BASE +  0x0100)                      /*!< NVIC Base Address                    */
#define SCB_BASE            (SCS_BASE +  0x0D00)                      /*!< System Control Block Base Address    */
#define SCB                 ((SCB_Type *)           SCB_BASE)         /*!< SCB configuration struct             */
#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)



#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)

#ifdef NVIC_LOCAL
#define NVIC_DEF
#else
#define NVIC_DEF               extern
#endif


NVIC_DEF void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
NVIC_DEF void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
NVIC_DEF void NVIC_Configuration(void);
NVIC_DEF void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority);
NVIC_DEF void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
NVIC_DEF void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);



#endif