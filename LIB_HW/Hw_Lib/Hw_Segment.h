#ifndef __HW_SEGMENT_H__
#define __HW_SEGMENT_H__

#include "Hw.h"

#ifdef SEGMENT_LOCAL
#define SEG_DEF 
#else
#define SEG_DEF              extern
#endif

SEG_DEF void 7_SEG_PowerOn();
SEG_DEF void 7_SEG_PowerOff();
SEG_DEF void 7_SEG_On_OnePin(uint16_t pinNum);
SEG_DEF void 7_SEG_Off_OnePin(uint16_t pinNum);
SEG_DEF void 7_SEG_On_All(void);
SEG_DEF void 7_SEG_Off_All(void);
SEG_DEF void 7_SEG_On_Number(unsigned int num);



#endif
