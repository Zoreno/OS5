/* memchr.c --- 
 * 
 * Filename: memchr.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:15:38 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:15:51 2018 (+0100)
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
 * @file    memchr.c
 * @author  Joakim Bertils
 * @date    2017-09-22
 * @brief   LIBK memchr standard function implementation.
 */

#include <string.h>

void *memchr(const void *str, int c, size_t n)
{
    unsigned char* ptr = (unsigned char*)str;
    unsigned char val = (unsigned char)c;
    size_t i;

    for(i = 0; i < n; ++i, ++ptr)
    {
        if(*ptr == val)
        {
            return ptr;
        }
    }

    return NULL;
}

/* memchr.c ends here */
