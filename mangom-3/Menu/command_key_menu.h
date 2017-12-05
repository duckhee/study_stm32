#ifndef __COMMAND_KEY_MENU_H__
#define __COMMAND_KEY_MENU_H__

#include "Menu.h"

#ifdef COMMAND_KEY_LOCAL
#define COMMAND_KEY_DEF
#else
#define COMMAND_KEY_DEF         extern
#endif

COMMAND_KEY_DEF int command_key_main(int argc, char **argv);
COMMAND_KEY_DEF int command_key_main_menu(void);

#endif