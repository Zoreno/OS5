/**
 * @file    div.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of standard div functions
 */

#include <stdlib.h>

div_t div(int number, int denom)
{
    div_t ret;

    ret.quot = number / denom;
    ret.rem = number % denom;

    return ret;
}

ldiv_t ldiv(long int number, long int denom)
{
    ldiv_t ret;

    ret.quot = number / denom;
    ret.rem = number % denom;

    return ret;
}

lldiv_t lldiv(long long int number, long long int denom)
{
    lldiv_t ret;

    ret.quot = number / denom;
    ret.rem = number % denom;

    return ret;
}
