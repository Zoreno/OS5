/**
 * @file    fputc.c
 * @author  Joakim Bertils
 * @date    2017-07-27
 * @brief   Implementation of standard function fputc
 */

#include <stdio.h>

int fputc(char c, FILE *file)
{
    // TODO: Do this correct

    if(!file)
        return -1;

    if(!file->write)
        return -1;

    file->write(c);

    return 0;
}
