#ifndef __HW_FLASH_H__
#define __HW_FLASH_H__

#include "Hw.h"

#ifdef FLASH_LOCAL
#define FLASH_DEF
#else
#define FLASH_DEF        extern
#endif

FLASH_DEF void Flash_Init(void);


#endif