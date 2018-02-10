/* bsearch.c --- 
 * 
 * Filename: bsearch.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:52:06 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:52:07 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 1
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Code: */





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

/* bsearch.c ends here */
