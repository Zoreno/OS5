/**
 * @file    strcat.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of standard function strcmp
 */

#include <string.h>
#include <stdint.h>

int strcmp(const char *str1, const char *str2)
{
    int res = 0;

    while(!(res = *(unsigned char *) str1 - *(unsigned char *) str2) && *str2)
    {
        ++str1;
        ++str2;
    }

    if(res < 0)
    {
        res = -1;
    }
    else if (res > 0)
    {
        res = 1;
    }

    return res;
}

