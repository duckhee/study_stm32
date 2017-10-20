
#define SEG_MENU_LOCAL

#include "Segment_Menu.h"


SEG_MENU_DEF int Seg_Main(void);
SEG_MENU_DEF int Seg_main_menu(void);
static unsigned short flag;


SEG_MENU_DEF int Seg_Main(void)
{
    int key;

    while((key = Seg_main_menu()) != 0)
    {
            switch(key)
            {
                case '1':
                    printf("No.1\n");
                    printf("PowerOn_7_SEG");
                     PowerOn_7_SEG();
                break;
    
                case '2':
                    printf("No.2\n");
                    printf("PowerOff_7_SEG");
                     PowerOff_7_SEG();
                break;
                
                case '3':
                    printf("No.3\n");
                     OutPut_7_SEG_Number(1);
                break;
    
                case '4':
                    printf("No.4\n");
                     OutPut_7_SEG_Number(2);
                break;
                  
                case '5':
                    printf("No.5\n");
                     OutPut_7_SEG_Number(3);
                break;
    
                case '6':
                    printf("No.6\n");
                     OutPut_7_SEG_Number(4);
                break;
    
                case '7':
                    printf("No.7\n");
                     OutPut_7_SEG_Number(5);
                break;
    
                case '8':
                    printf("No.8\n");
                     OutPut_7_SEG_Number(6);
                break;
    
                case '9':
                    printf("No.9\n");
                     OutPut_7_SEG_Number(7);
                break;
    
                case '0':
                    printf("No.0\n");
                     OutPut_7_SEG_Number(8);
                break;
    
                case 'a':
                    printf("No.a\n");
                     OutPut_7_SEG_Number(9);
                break;
    
                case 'b':
                    printf("No.b\n");
                     OutPut_7_SEG_Number(0);
                break;
    
                case 'c':
                    printf("No.c\n");
                     On_7_SEG_AllPin();
                break;
    
                case 'd':
                    printf("No.d\n");
                     Off_7_SEG_AllPin();
                break;
    
                case 'e':
                    printf("No.e\n");
                     Seven_Segment_Test();
                break;
    
                case 'f':
                    printf("No.f\n");
                    System_Information();
                break;
    
                case 'g':
                    printf("No.g\n");
         
                break;
    
                case 'h':
                    printf("No.h\n");
           
                break;
    
                case 'i':
                    printf("No.i\n");
    
                break;
    
                case 'j':
                    printf("No.j\n");
    
                break;
    
                case 'k':
                    printf("No.k\n");
    
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
    
        printf("\n\n");
        printf("-------------------------------------------------\n");
        printf("                 SEH MAIN MENU\n");
        printf("-------------------------------------------------\n");
        printf(" 1. PowerOn_7_SEG                                         \n");
        printf(" 2. PowerOff_7_SEG                                         \n");
        printf(" 3. SEG 1                                         \n");
        printf(" 4. SEG 2                                        \n");
        printf(" 5. SEG 3                                        \n");
        printf(" 6. SEG 4                                        \n");
        printf(" 7. SEG 5                                        \n");
        printf(" 8. SEG 6                                        \n");
        printf(" 9. SEG 7                                        \n");
        printf(" 0. SEG 8                                        \n");
        printf(" a. SEG 9                                        \n");
        printf(" b. SEG 0                                        \n");
        printf(" c. On_7_SEG_AllPin                                        \n");
        printf(" d. Off_7_SEG_AllPin                                        \n");
        printf("-------------------------------------------------\n");
        printf(" q. LED Menu QUIT\n");
        printf("-------------------------------------------------\n");
        printf("\n\n");
        char a = '1';
        printf("SELECT THE COMMAND NUMBER : ");
        key=get_byte();
        printf("key %d\n", key);
        printf("key a : %d\n", a);
        return key;
}