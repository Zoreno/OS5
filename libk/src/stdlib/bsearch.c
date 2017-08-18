/**
 * @file    bsearch.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of standard function bsearch
 */

#include <stdlib.h>

void *bsearch(
    const void *key,
    const void *base,
    size_t nitems,
    size_t size,
    int (*compar)(const void *, const void *))
{
    // Current guess
    void *guess;

    // Direction of next search
    int dir;

    while(nitems > 0)
    {
        // Guess the value in the middle
        guess = (char *)base + size*(nitems / 2);

        // Get the direction of the correct value
        dir = compar(key, guess);

        // If direction is zero, we found the element
        if(!dir)
        {
            return guess;
        }

        // If this was the last element, the element is not in the list
        else if(nitems == 1)
        {
            break;
        }

        // Split and keep left side
        else if(dir < 0)
        {
            nitems /= 2;
        }

        // Split and keep right side
        else
        {
            base = guess;
            nitems -= nitems/2;
        }
    }

    // The element was not found. Return NULL.
    return NULL;
}
