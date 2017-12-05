#define COMMAND_SEG_LOCAL

#include "command_seg_menu.h"


COMMAND_SEG_DEF int command_seg_main(int argc, char **argv);
COMMAND_SEG_DEF int command_seg_main_menu(void);
static unsigned short flags;


COMMAND_SEG_DEF int command_seg_main(int argc, char **argv)
{
      int key;

    if(argc > 1)
    {
        if(!StrCmp(argv[0], "ch1"))
        {
            printf("testing command menu ch1\n");
        }
        else if(!StrCmp(argv[1], "ch2"))
        {
            printf("testing command menu ch2\n");
        }
        else if(!StrCmp(argv[1], "on"))
        {
            printf("\nON %s\n", argv[1]);
            if(!StrCmp(argv[2], "ch1"))
            {
                printf("\non argv[2] : %s ch1\n", argv[2]);
            }
            else if(!StrCmp(argv[2], "ch2"))
            {
                printf("\non argv[2] : %s ch2\n", argv[2]);
            }
        }
        else if(!StrCmp(argv[1], "off"))
        {
            printf("\nOFF %s\n", argv[1]);
            if(!StrCmp(argv[2], "ch1"))
            {
                printf("\noff argv[2] : %s ch1\n", argv[2]);
            }
            else if(!StrCmp(argv[2], "ch2"))
            {
                printf("\noff argv[2] : %s ch2\n", argv[2]);
            }
        }
        else if(!StrCmp(argv[1], "state"))
        {
                printf("\nSTATE %s\n", argv[1]);
            if(!StrCmp(argv[2], "ch1"))
            {
                printf("\nstate argv[2] : %s ch1\n", argv[2]);
            }
            else if(!StrCmp(argv[2], "ch2"))
            {
                printf("\nstate argv[2] : %s ch2\n", argv[2]);
            }
        }
        return 0;
    }
    while((key = command_seg_main_menu()) != 0)
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
                    Led_Test();
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



COMMAND_SEG_DEF int command_seg_main_menu(void)
{
        int key;
    
        printf("\n\n");
        printf("-------------------------------------------------\n");
        printf("                 SEG MAIN MENU\n");
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
        printf(" q. SEG Menu QUIT\n");
        printf("-------------------------------------------------\n");
        printf("\n\n");
        char a = '1';
        printf("SELECT THE COMMAND NUMBER : \n");
        key=get_byte();

        return key;
}