#ifndef __LED_MENU_H__
#define __LED_MENU_H__

#include "Menu.h"


#ifdef LED_MENU_LOCAL
#define LED_MENU_DEF
#else
#define LED_MENU_DEF                extern
#endif


LED_MENU_DEF int Led_Main(int argc, char **argv);
LED_MENU_DEF int Led_main_menu(void);

// 사용할 때 LED_MAIN()함수를 불러와서 사용한다.

#endif