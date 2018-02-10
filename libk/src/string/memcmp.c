/* memcmp.c --- 
 * 
 * Filename: memcmp.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:15:49 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:15:51 2018 (+0100)
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

/* memcmp.c ends here */
