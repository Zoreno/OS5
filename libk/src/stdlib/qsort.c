/* qsort.c --- 
 * 
 * Filename: qsort.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:52:50 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:55:39 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 3
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
 * @file    qsort.c
 * @author  Joakim Bertils
 * @date    2017-09-03
 * @brief   Implementation of standard function qsort
 */

#include <stdlib.h>

#include <stdint.h>

typedef int(*COMPARE)(const void *, const void *);

void swap(
    void *mem1,
    void *mem2,
    size_t size);

size_t partition(
    void *arr,
    int low,
    int high,
    size_t item_size,
    COMPARE compare);

void quicksort(
    void *arr,
    int low,
    int high,
    size_t item_size,
    COMPARE compare);

void swap(
    void *mem1,
    void *mem2,
    size_t size)
{
    uint8_t* b1 = (uint8_t*) mem1;
    uint8_t* b2 = (uint8_t*) mem2;

    if(b1 == b2)
        return;

    // TODO: Maybe optimize for word or dword accesses
    while(size--)
    {
        uint8_t b = *b1;
        *b1++ = *b2;
        *b2++ = b;
    }
}

size_t partition(
    void *arr,
    int low,
    int high,
    size_t item_size,
    COMPARE compare)
{
    int i = low - 1;

    uint8_t* arr_b = arr;

    for(size_t j = low; j < high; ++j)
    {
        if(compare((void*)(arr_b + j*item_size), (void*)(arr_b + high*item_size)))
        {
            ++i;
            swap(arr_b + i*item_size, arr_b + j*item_size, item_size);
        }
    }

    swap(arr_b + (i + 1)*item_size, arr_b + high*item_size, item_size);

    return i + 1;
}

void quicksort(
    void *arr,
    int low,
    int high,
    size_t item_size,
    COMPARE compare)
{
    if(low < high)
    {
        size_t partition_index = partition(arr, low, high, item_size, compare);

        quicksort(arr, low, partition_index - 1, item_size, compare);
        quicksort(arr, partition_index + 1, high, item_size, compare);
    }
}

void qsort(
    void *base,
    size_t nitems,
    size_t size,
    COMPARE compare)
{
    quicksort(base, 0, nitems - 1, size, compare);
}

/* qsort.c ends here */
