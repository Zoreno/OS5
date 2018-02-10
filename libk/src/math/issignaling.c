/* issignaling.c --- 
 * 
 * Filename: issignaling.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:36:37 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:36:39 2018 (+0100)
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




#include <math.h>

int __issignalingf(float x)
{
    uint32_t xi;

    extract_word(&xi, x);

    return (xi & 0x7FC00000) == 0x7FC00000;
}

int __issignaling(double x)
{
    uint32_t hxi;
    uint32_t lxi;
    extract_words_double(&hxi, &lxi, x);

    return (hxi & 0x7FF80000) == (0x7FF80000);
}

/* issignaling.c ends here */
