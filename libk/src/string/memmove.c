/**
 * @file    memmove.c
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   Implementation of standard function memmove
 */

#include <string.h>
#include <stdint.h>

void *memmove(void *str1, const void *str2, size_t n)
{
    uint8_t *destPtr = (uint8_t *)str1;
    const uint8_t *srcPtr = (const uint8_t *)str2;
    size_t bytes = n;

    if(destPtr < srcPtr)
    {
        for(size_t i = 0; i < n; ++i)
        {
            destPtr[i] = srcPtr[i];
        }
    }
    else
    {
        for(size_t i = bytes; i != 0; --i)
        {
            destPtr[i - 1] = srcPtr[i - 1];
        }
    }

    return destPtr;
}
