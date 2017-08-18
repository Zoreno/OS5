/**
 * @file    strcat.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of standard function strcpy
 */

#include <string.h>
#include <stdint.h>

char *strcpy(char *str1, const char *str2)
{
    char* str1_ptr = str1;

    while(*str2)
    {
        *str1++ = *str2++;
    }

    return str1_ptr;
}
