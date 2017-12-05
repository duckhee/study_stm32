#define COMMAND_TESTING_LOCAL

#include "command_testing_menu.h"


COMMAND_TESTING_LOCAL int command_test(int argc, char **argv);
COMMAND_TESTING_LOCAL int command_test_main(void);
static unsigned short flag;

COMMAND_TESTING_LOCAL int command_test(int argc, char **argv)
{
    int key;

    if(argc > 1)
    {
        if(!StrCmp(argv[0], "ch1"))
        {
            
        }
    }
}
