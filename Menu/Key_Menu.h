#ifndef __KEY_MENU_H__
#define __KEY_MENU_H__

#include "Ap.h"

#ifdef KEY_MENU_LOCAL
#define KEY_MENU_DEF
#else
#define KEY_MENU_DEF              extern
#endif

KEY_MENU_DEF int Key_Main(int argc, char **argv);
KEY_MENU_DEF int Key_Main_Menu();

#endif