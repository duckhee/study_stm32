#ifndef __COMMAND_ADC_MENU_H__
#define __COMMAND_ADC_MENU_H__

#include "Menu.h"


#ifdef ADC_MENU_LOCAL
#define ADC_MENU_DEF
#else
#define ADC_MENU_DEF               extern
#endif

ADC_MENU_DEF int command_adc_main(int argc, char **argv);
ADC_MENU_DEF int command_adc_main_menu(void);

#endif