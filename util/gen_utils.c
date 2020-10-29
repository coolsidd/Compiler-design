
#include "gen_utils.h"

void assert(bool condition, char *error_string)
{
    if (!condition)
    {
        printf("ERROR: Assertion failed - %s\n", error_string);
        exit(1);
    }
}
