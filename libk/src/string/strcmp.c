/* strcmp.c --- 
 * 
 * Filename: strcmp.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:16:39 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:16:40 2018 (+0100)
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
 * @file    strcat.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of standard function strcmp
 */

#include <string.h>
#include <stdint.h>

int strcmp(const char *str1, const char *str2)
{
    int res = 0;

    while(!(res = *(unsigned char *) str1 - *(unsigned char *) str2) && *str2)
    {
        ++str1;
        ++str2;
    }

    if(res < 0)
    {
        res = -1;
    }
    else if (res > 0)
    {
        res = 1;
    }

    return res;
}


/* strcmp.c ends here */
