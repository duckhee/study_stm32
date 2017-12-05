#ifndef __COMMAND_TESTING_MENU_H__
#define __COMMAND_TESTING_MENU_H__

#include "Menu.h"

#ifdef COMMAND_TESTING_LOCAL
#define COMMAND_TESING_DEF 
#else
#define COMMAND_TESTING_DEF          extern
#endif

COMMAND_TESTING_DEF int command_test_main(int argc, char **argv);
COMMAND_TESTING_DEF int command_test_main_menu(void);

#endif