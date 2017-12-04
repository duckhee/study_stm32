#ifndef __KEY_MENU_H__
#define __KEY_MENU_H__

#include "Menu.h"

#ifdef KEY_MENU_LOCAL
#define KEY_MENU_DEF
#else
#define KEY_MENU_DEF              extern
#endif

KEY_MENU_DEF int Key_Main(void);
KEY_MENU_DEF int Key_Main_Menu(void);

#endif