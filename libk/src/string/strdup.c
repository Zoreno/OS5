/* strdup.c --- 
 * 
 * Filename: strdup.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:16:59 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:17:00 2018 (+0100)
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
 * @file    strdup.c
 * @author  Joakim Bertils
 * @date    2017-09-22
 * @brief   LIBK strdup standard function implementation.
 */

#include <string.h>
#include <stdlib.h>

char *strdup(const char *str)
{
    size_t len = strlen(str);

    char *new = malloc(len + 1);

    if(!new)
    {
        return NULL;
    }

    new[len] = '\0';

    return (char *)memcpy(new, str, len);
}

/* strdup.c ends here */
