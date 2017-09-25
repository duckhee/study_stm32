#ifndef __HW_KEY_H__
#define __HW_KEY_H__

#include "Hw.h"

#ifdef KEY_LOCAL
#define KEY_DEF 
#else
#define KEY_DEF                 extern
#endif

KEY_DEF void Key_Test(void);


#endif