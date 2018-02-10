/* fmaxf.c --- 
 * 
 * Filename: fmaxf.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:34:07 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:34:14 2018 (+0100)
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


#include <math.h>

float fmaxf(float x, float y)
{
    if(isgreater(x, y))
    {
        return x;
    }
    else if(isless(x, y))
    {
        return y;
    }
    else if(issignaling(x) || issignaling(y))
    {
        return x + y;
    }
    else
    {
        return isnan(y) ? x : y;
    }
}

/* fmaxf.c ends here */
