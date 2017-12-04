#ifndef __TEST_MENU_H__
#define __TEST_MENU_H__


#include "menu.h"


#ifdef TEST_MENU_LOCAL
#define TEST_MENU_DEF
#else
#define TEST_MENU_DEF              extern
#endif

TEST_MENU_DEF int test_main(void);
TEST_MENU_DEF int test_main_menu(void);


#endif