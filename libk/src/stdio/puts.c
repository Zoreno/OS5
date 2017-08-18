/**
 * @file    puts.c
 * @author  Joakim Bertils
 * @date    2017-07-27
 * @brief   Implementation of standard function puts
 */

#include <stdio.h>

int puts(const char *str)
{
    if(!stdout)
        return -1;

    return fputs(str, stdout);
}
