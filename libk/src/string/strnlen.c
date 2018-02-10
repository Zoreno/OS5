/* strnlen.c --- 
 * 
 * Filename: strnlen.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:17:18 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:17:19 2018 (+0100)
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
 * @file    strnlen.c
 * @author  Joakim Bertils
 * @date    2017-09-22
 * @brief   LIBK strnlen standard function implementation.
 */

#include <string.h>

size_t strnlen(const char *str, size_t maxlen)
{
    if(maxlen == 0)
    {
        return 0;
    }

    int i;
    
    for(i = 0; i < maxlen; ++i)
    {
        if(*str++ == 0)
        {
            return i;
        }
    }

    return maxlen;
}

/* strnlen.c ends here */
