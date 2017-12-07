#ifndef __COMMAND_TESTING_MENU_H__
#define __COMMAND_TESTING_MENU_H__

#include "command.h"

#ifdef COMMAND_TESTING_LOCAL
#define COMMAND_TESTING_DEF
#else
#define COMMAND_TESTING_DEF           extern
#endif

COMMAND_TESTING_DEF int command_testing_main_menu(int argc, char **argv);
COMMAND_TESTING_DEF int command_testing_main(void);

#endif