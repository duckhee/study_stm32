#ifndef __MIDDLE_MENU_H__
#define __MIDDLE_MENU_H__

#include "Menu.h"

#ifdef MIDDLE_MENU_LOCAL
#define MIDDLE_MENU_DEF
#else
#define MIDDLE_MENU_DEF                    extern
#endif

MIDDLE_MENU_DEF int Middle_Main(void);
MIDDLE_MENU_DEF int Middle_Main_Menu(void);


#endif