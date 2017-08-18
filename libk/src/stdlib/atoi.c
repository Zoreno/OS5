/**
 * @file    atoi.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of atoi standard function
 */

#include <stdlib.h>

int atoi(const char *str)
{
    return (int) strtol(str, NULL, 10);
}
