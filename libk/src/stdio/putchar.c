/**
 * @file    putchar.c
 * @author  Joakim Bertils
 * @date    2017-07-27
 * @brief   Implementation of standard function putchar
 */

#include <stdio.h>

int putchar(char c)
{
    if(!stdout)
        return -1;

    return fputc(c, stdout);
}
