/**
 * @file    sprintf.c
 * @author  Joakim Bertils
 * @date    2017-07-28
 * @brief   Implementation of standard function sprintf
 */

#include <stdio.h>

int sprintf(char *buf, const char *format, ...)
{
    int ret;

    va_list ap;

    va_start(ap, format);

    ret = vsprintf(buf, format, ap);

    va_end(ap);

    return ret;
}
