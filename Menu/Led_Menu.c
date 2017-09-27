#define LED_MNEU_LOCAL

#include "Led_Menu.h"


LED_MENU_DEF int Led_Main(int argc, char **argv);
LED_MENU_DEF int Led_main_menu(void);
static unsigned short flag;


LED_MENU_DEF int xxx_main(int argc, char **argv)
{

    int key;

    while((key=xxx_main_menu()) != 0)
    {
        switch(key)
        {
            case '1':
                Ld_printf("No.1\n");
             
            break;

            case '2':
                Ld_printf("No.2\n");
               
            break;
            
            case '3':
                Ld_printf("No.3\n");
                
            break;

            case '4':
                Ld_printf("No.4\n");

            break;
              
            case '5':
                Ld_printf("No.5\n");
                
            break;

            case '6':
                Ld_printf("No.6\n");
               
            break;

            case '7':
                Ld_printf("No.7\n");
                
            break;

            case '8':
                Ld_printf("No.8\n");
              
            break;

            case '9':
                Ld_printf("No.9\n");
                
            break;

            case '0':
                Ld_printf("No.0\n");
             
            break;

            case 'a':
                Ld_printf("No.a\n");
            
            break;

            case 'b':
                Ld_printf("No.b\n");
              
            break;

            case 'c':
                Ld_printf("No.c\n");
            
            break;

            case 'd':
                Ld_printf("No.d\n");
        
            break;

            case 'e':
                Ld_printf("No.e\n");
     
            break;

            case 'f':
                Ld_printf("No.f\n");

            break;

            case 'g':
                Ld_printf("No.g\n");
     
            break;

            case 'h':
                Ld_printf("No.h\n");
       
            break;

            case 'i':
                Ld_printf("No.i\n");

            break;

            case 'j':
                Ld_printf("No.j\n");

            break;

            case 'k':
                Ld_printf("No.k\n");

            break;

            case 'q':
                return 0;
        }
    }
    return 0;
}


LED_MENU_DEF int Led_main_menu(void)
{
    int key;

    Ld_printf("\n\n");
    Ld_printf("-------------------------------------------------\n");
    Ld_printf("                 LED MAIN MENU\n");
    Ld_printf("-------------------------------------------------\n");
    Ld_printf(" 1. Test                                         \n");
    Ld_printf(" 2. Test                                         \n");
    Ld_printf(" 3. Test                                         \n");
    Ld_printf(" 4. Test                                         \n");
    Ld_printf(" 5. Test                                         \n");
    Ld_printf(" 6. Test                                         \n");
    Ld_printf(" 7. Test                                         \n");
    Ld_printf(" 8. Test                                         \n");
    Ld_printf(" 9. Test                                         \n");
    Ld_printf(" 0. Test                                         \n");
    Ld_printf("-------------------------------------------------\n");
    Ld_printf(" q. LED Menu QUIT\n");
    Ld_printf("-------------------------------------------------\n");
    Ld_printf("\n\n");

    Ld_printf("SELECT THE COMMAND NUMBER : ");
    key=get_byte();

    return key;
}
