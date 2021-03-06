/* fputc.c --- 
 * 
 * Filename: fputc.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:48:05 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:48:06 2018 (+0100)
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
 * @file    fputc.c
 * @author  Joakim Bertils
 * @date    2017-07-27
 * @brief   Implementation of standard function fputc
 */

#include <stdio.h>

int fputc(char c, FILE *file)
{
    // TODO: Do this correct

    if(!file)
        return -1;

    if(!file->write)
        return -1;

    file->write(c);

    return 0;
}

/* fputc.c ends here */
