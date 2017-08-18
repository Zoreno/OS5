/**
 * @file    memset.c
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   Implementation of standard function memset.
 */

#include <string.h>
#include <stdint.h>

void *memset(void *str, unsigned char c, size_t n)
{
    uint8_t *buf = (uint8_t *)str;
    uint8_t value = (uint8_t)c;
    size_t bytes = n;

    for(size_t i = 0; i < bytes; ++i)
    {
        buf[i] = value;
    }

    return str;
}
