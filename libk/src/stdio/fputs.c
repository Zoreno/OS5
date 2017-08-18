/**
 * @file    fputs.c
 * @author  Joakim Bertils
 * @date    2017-07-27
 * @brief   Implementation of standard function fputs
 */

#include <stdio.h>
#include <string.h>

int fputs(const char *str, FILE *file)
{
    if(!file || !str)
        return -1;

    if(!file->write)
        return -1;

    char c;
    
    while((c = *str++) != NULL)
    {
        file->write(c);
    }

    return 0;
}
