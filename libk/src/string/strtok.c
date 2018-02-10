/* strtok.c --- 
 * 
 * Filename: strtok.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:18:45 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:24:12 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 4
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

#include <string.h>

char *strtok(char *str, const char *delim)
{
    static char *p = 0;

    if (str)
    {
        p = str;
    }
    else if(!p)
    {
        return 0;
    }

    str = p + strspn(p, delim);
    p = str + strcspn(str, delim);

    if (p == str)
    {
        return p = 0;
    }

    p = *p ? *p = 0, p + 1 : 0;

    return str;
}

/* strtok.c ends here */
