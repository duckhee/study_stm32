#ifndef __AP_CLOCK_H__
#define __AP_CLOCK_H__

#include "Ap.h"

#ifdef CLOCK_LOCAL
#define CLOCK_DEF 
#else
#define CLOCK_DEF              extern
#endif

CLOCK_DEF void System_Information(void);

#endif
