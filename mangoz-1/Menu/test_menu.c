#define TEST_MENU_LOCAL

#include "test_menu.h"

TEST_MENU_DEF int test_main(void);
TEST_MENU_DEF int test_main_menu(void);
static unsigned short flag;

TEST_MENU_DEF int test_main()
{
    int key;

    while((key = test_main_menu()) != 0)
    {
        switch(key)
        {
            case '1':
                printf("NO.1\n");
                System_Information();
            break;
            case '2':
                printf("NO.2\n");

            break;
            case '3':
                printf("NO.3\n");

            break;
            case '4':
                printf("NO.4\n");

            break;
            case '5':
                printf("NO.5\n");

            break;
            case '6':
                printf("NO.6\n");

            break;
            case '7':
                printf("NO.7\n");

            break;
            case '8':
                printf("NO.8\n");

            break;
            case '9':
                printf("NO.9\n");

            break;

            case 'q':
                printf("EXIT\n");
                return 0;
        }
    }
    return 0;
}

TEST_MENU_DEF int test_main_menu()
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