/* strcspn.c ---
 *
 * Filename: strcspn.c
 * Description:
 * Author: Joakim Bertils
 * Maintainer:
 * Created: Sat Feb 10 01:16:51 2018 (+0100)
 * Version:
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:17:02 2018 (+0100)
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
 * @file    strcspn.c
 * @author  Joakim Bertils
 * @date    2017-09-23
 * @brief   LIBK strcspn standard function implementation.
 */

#include <string.h>

size_t strcspn(const char *str1, const char *reject)
{

    // If the reject string is only a single character, we can use strchr
    if(reject[0] == '\0' || reject[1] == '\0')
    {
        return strchr(str1, reject[0]) - str1;
    }

    // Allocate a lookup table to store our reject list.
    unsigned char table[256];
    unsigned char *p = memset(table, 0, 64);
    memset(p + 64, 0, 64);
    memset(p + 128, 0, 64);
    memset(p + 192, 0, 64);

    unsigned char *s = (unsigned char *)reject;
    unsigned char tmp;

    // Parse the reject list to fill out the table.
    do
    {
        p[tmp = *s++] = 1;
    }
    while(tmp);
    unsigned char *str = (unsigned char *)str1;
    s = (unsigned char *) str1;

    // Go through the string and break when we find a reject character
    while(*s)
    {
        if(p[*s])
        {
            break;
        }

        ++s;
    }

    return s - str;
}

/* strcspn.c ends here */
