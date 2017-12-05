#define COMMAND_TESTING_LOCAL

#include "command_testing_menu.h"


COMMAND_TESTING_DEF int command_testing_main_menu(int argc, char **argv);
COMMAND_TESTING_DEF int command_testing_main(void);
static unsigned short flags;

COMMAND_TESTING_DEF int command_testing_main_menu(int argc, char **argv)
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
        while((key = command_testing_main()) != 0)
        {
            switch(key)
            {
                case '1':
                    printf("No.1\n");
    
                break;
                case '2':
                    printf("No.2\n");
    
                break;
                case '3':
                    printf("No.3\n");
    
                break;
                case '4':
                    printf("No.4\n");
    
                break;
                case '5':
                    printf("No.5\n");
    
                break;
                case '6':
                    printf("No.6\n");
    
                break;
                case '7':
                    printf("No.7\n");
    
                break;
                case '8':
                    printf("No.8\n");
    
                break;
                case '9':
                    printf("No.9\n");
    
                break;
                case '0':
                    printf("No.0\n");
    
                break;
    
                case 'q':
                    printf("EXIT\n");
                    return 0;
            }
        }
        return 0;
}

COMMAND_TESTING_DEF int command_testing_main(void)
{
    int key;
    
        printf("\n\n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("-------------------------------------TEST MAIN MENU----------------------------------------\n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf(" 1. TEST\n");
        printf(" 2. TEST\n");
        printf(" 3. TEST\n");
        printf(" 4. TEST\n");
        printf(" 5. TEST\n");
        printf(" 6. TEST\n");
        printf(" 7. TEST\n");
        printf(" 8. TEST\n");
        printf(" 9. TEST\n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("q. menu QUIT\n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("\n\n");
        printf("SELECT THE COMMAND NUMBER : ");
        key = get_byte();
    
        return key;
}
