#ifndef __HW_I2C_H__
#define __HW_I2C_H__

#include "Hw.h"

#ifdef I2C_LOCAL
#define I2C_DEF
#else
#define I2C_DEF         extern
#endif

I2C_DEF void I2c_Init(void);


#endif