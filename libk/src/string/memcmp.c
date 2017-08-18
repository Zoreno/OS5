/**
 * @file    memcmp.c
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   Implementation of standard function memcmp
 */

#include <string.h>
#include <stdint.h>

int memcmp(const void *str1, const void *str2, size_t n)
{
    const uint8_t *a = (const uint8_t *) str1;
    const uint8_t *b = (const uint8_t *) str2;

    size_t bytes = n;

    for(size_t i = 0; i < bytes; ++i)
    {
        if(a[i] != b[i])
        {
            return (a[i] < b[i]) ? (-1) : (1);
        }
    }

    return 0;
}
