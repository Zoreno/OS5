/* extract_word.c --- 
 * 
 * Filename: extract_word.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:34:50 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:42:30 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 5
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

typedef union
{
    float x_f;
    uint32_t x_int;
} float_word;

typedef union
{
    double x_d;
    uint32_t x_int[2];
} double_word;

void extract_word(uint32_t* res, float x)
{
    float_word fw;

    fw.x_f = x;

    *res = fw.x_int;
}

void extract_words_double(uint32_t* hi, uint32_t* lo, double x)
{
    double_word dw;

    dw.x_d = x;

    *hi = dw.x_int[1];
    *lo = dw.x_int[0];
}

void extract_high_word_double(uint32_t* hi, double x)
{
    double_word dw;

    dw.x_d = x;

    *hi = dw.x_int[1];   
}

void extract_low_word_double(uint32_t* lo, double x)
{
    
    double_word dw;

    dw.x_d = x;
    
    *lo = dw.x_int[0];
}


/* extract_word.c ends here */
