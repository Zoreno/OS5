/**
 * @file    set_stdout.c
 * @author  Joakim Bertils
 * @date    2017-07-27
 * @brief   Sets the standard out stream
 */

#include <stdio.h>

FILE *stdout = NULL;

void set_stdout(FILE *file)
{
    // TODO: Open and close correct

    stdout = file;
}
