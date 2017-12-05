#ifndef __COMMAND_H__
#define __COMMAND_H__


#include "menu.h"


#ifdef COMMAND_LOCAL
#define COMMAND_DEF
#else
#define COMMAND_DEF                extern
#endif

COMMAND_DEF void command_main(void);


#endif