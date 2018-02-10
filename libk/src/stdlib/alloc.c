/* alloc.c --- 
 * 
 * Filename: alloc.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:50:48 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:51:38 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 2
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
 * @file    alloc.c
 * @author  Joakim Bertils
 * @date    2017-09-21
 * @brief   Memory allocation
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern void* kernel_malloc(size_t size);
extern void kernel_free(void* addr);

void* calloc(size_t nitems, size_t size)
{
    void* mem = kernel_malloc(nitems * size);

    if(mem)
    {
        memset(mem, 0, nitems * size);
    }

    return mem;
}

void free(void* ptr)
{
    kernel_free(ptr);
}

void* malloc(size_t size)
{
    // TODO: May include some error checks as well as some check
    // to see if the kernel is properly set up
    
    return kernel_malloc(size);
}


/* alloc.c ends here */
