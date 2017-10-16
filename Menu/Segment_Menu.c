
#define SEG_MENU_LOCAL

#include "Segment_Menu.h"


SEG_MENU_DEF int Seg_Main(void);
SEG_MENU_DEF int Seg_main_menu(void);
static unsigned short flag;


SEG_MENU_DEF int Seg_Main(void)
{
int key;

    while((key = Key_Main_Menu()) != 0)
    {
            switch(key)
            {
                case '1':
                    Ld_printf("No.1\n");
                    PowerOn_7_SEG();
                break;
    
                case '2':
                    Ld_printf("No.2\n");
                    PowerOff_7_SEG();
                break;
                
                case '3':
                    Ld_printf("No.3\n");
                    OutPut_7_SEG_Number(1);
                break;
    
                case '4':
                    Ld_printf("No.4\n");
                    OutPut_7_SEG_Number(2);
                break;
                  
                case '5':
                    Ld_printf("No.5\n");
                    OutPut_7_SEG_Number(3);
                break;
    
                case '6':
                    Ld_printf("No.6\n");
                    OutPut_7_SEG_Number(4);
                break;
    
                case '7':
                    Ld_printf("No.7\n");
                    OutPut_7_SEG_Number(5);
                break;
    
                case '8':
                    Ld_printf("No.8\n");
                    OutPut_7_SEG_Number(6);
                break;
    
                case '9':
                    Ld_printf("No.9\n");
                    OutPut_7_SEG_Number(7);
                break;
    
                case '0':
                    Ld_printf("No.0\n");
                    OutPut_7_SEG_Number(8);
                break;
    
                case 'a':
                    Ld_printf("No.a\n");
                    OutPut_7_SEG_Number(9);
                break;
    
                case 'b':
                    Ld_printf("No.b\n");
                    OutPut_7_SEG_Number(0);
                break;
    
                case 'c':
                    Ld_printf("No.c\n");
                    On_7_SEG_AllPin();
                break;
    
                case 'd':
                    Ld_printf("No.d\n");
                    Off_7_SEG_AllPin();
                break;
    
                case 'e':
                    Ld_printf("No.e\n");
                    Seven_Segment_Test();
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
SEG_MENU_DEF int Seg_main_menu(void)
{
    int key;
    
        Ld_printf("\n\n");
        Ld_printf("-------------------------------------------------\n");
        Ld_printf("                 LED MAIN MENU\n");
        Ld_printf("-------------------------------------------------\n");
        Ld_printf(" 1. PowerOn_7_SEG                                         \n");
        Ld_printf(" 2. PowerOff_7_SEG                                         \n");
        Ld_printf(" 3. SEG 1                                         \n");
        Ld_printf(" 4. SEG 2                                        \n");
        Ld_printf(" 5. SEG 3                                        \n");
        Ld_printf(" 6. SEG 4                                        \n");
        Ld_printf(" 7. SEG 5                                        \n");
        Ld_printf(" 8. SEG 6                                        \n");
        Ld_printf(" 9. SEG 7                                        \n");
        Ld_printf(" 0. SEG 8                                        \n");
        Ld_printf(" a. SEG 9                                        \n");
        Ld_printf(" b. SEG 0                                        \n");
        Ld_printf(" c. On_7_SEG_AllPin                                        \n");
        Ld_printf(" d. Off_7_SEG_AllPin                                        \n");
        Ld_printf("-------------------------------------------------\n");
        Ld_printf(" q. LED Menu QUIT\n");
        Ld_printf("-------------------------------------------------\n");
        Ld_printf("\n\n");
    
        Ld_printf("SELECT THE COMMAND NUMBER : ");
        key=Ld_get_byte();
    
        return key;
}