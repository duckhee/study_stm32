#ifndef __SEGMENT_MENU_H__
#define __SEGMENT_MENU_H__

#include "Menu.h"

#ifdef SEG_MENU_LOCAL
#define SEG_MENU_DEF
#else
#define SEG_MENU_DEF                   extern
#endif

SEG_MENU_DEF int Seg_Main(void);
SEG_MENU_DEF int Seg_main_menu(void);



#endif