/* limits.h --- 
 * 
 * Filename: limits.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:14:09 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb  6 21:14:11 2018 (+0100)
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


#ifndef _LIBK_LIMITS_H
#define _LIBK_LIMITS_H

#define CHAR_BIT 8

#define SCHAR_MIN -127
#define SCHAR_MAX 127
#define UCHAR_MAX 255

#define CHAR_MIN 0
#define CHAR_MAX UCHAR_MAX

#define MB_LEN_MAX 1

#define SHRT_MIN -32767
#define SHRT_MAX 32767
#define USHRT_MAX 65535

#define INT_MIN -32767
#define INT_MAX 32767
#define UINT_MAX 65535

#define LONG_MIN -2147483647
#define LONG_MAX 2147483647
#define ULONG_MAX 4294967295

#endif

/* limits.h ends here */
