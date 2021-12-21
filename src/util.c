#include "util.h"
#include <stdlib.h>


char *util_ch_to_str(char c)
{
    char *str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';
    return str;
}

