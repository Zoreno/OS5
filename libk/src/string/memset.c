/* memset.c --- 
 * 
 * Filename: memset.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:16:17 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:16:18 2018 (+0100)
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

/* memset.c ends here */
