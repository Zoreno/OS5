/* strspn.c --- 
 * 
 * Filename: strspn.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 01:01:15 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:13:39 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 6
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

size_t strspn(const char *s, const char *accept)
{
    const char *p;
    const char *a;

    size_t count = 0;

    // Loop over each character in the input string
    for (p = s; *p != '\0'; ++p)
    {
        // Loop over each character in the accept string
        for (a = accept; *a != '\0'; ++a)
        {
            if(*p == *a)
            {
                break;
            }
        }

        // If we did not exit the accept loop early, last character
        // was not valid. Return current count.
        if (*a == '\0')
        {
            return count;
        }
        // Else we increase the count and continue the loop
        else
        {
            ++count;
        }
    }
    
    return count;
}


/* strspn.c ends here */
