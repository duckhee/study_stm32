#ifndef __COMMAND_SEG_MENU_H__
#define __COMMAND_SEG_MENU_H__

#include "Menu.h"

#ifdef COMMAND_SEG_LOCAL
#define COMMAND_SEG_DEF
#else
#define COMMAND_SEG_DEF           extern
#endif

COMMAND_SEG_DEF int command_seg_main(int argc, char **argv);
COMMAND_SEG_DEF int command_seg_main_menu(void);



#endif