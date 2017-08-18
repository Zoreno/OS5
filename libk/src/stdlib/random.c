/**
 * @file    random.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of standard random functions
 */

#include <stdlib.h>
#include <stdint.h>

static uint64_t _seed;

int rand(void)
{
    _seed = UINT64_C(6364136223846793005)*_seed + 1;

    return _seed>>33;
}

int rand_range(int min, int max)
{
    int range = max - min;

    return (rand() % range) + min;
}

void srand(unsigned int seed)
{
    _seed = seed - 1;
}
