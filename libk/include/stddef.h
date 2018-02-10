/* stddef.h --- 
 * 
 * Filename: stddef.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:15:36 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb  6 21:15:37 2018 (+0100)
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
 * @file    stddef.h
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   LIBK stddef.h standard header
 */

#ifndef _LIBK_STDDEF_H
#define _LIBK_STDDEF_H

#include <_size_t.h>
#include <_ptrdiff_t.h>
#include <_null.h>

/**
 * Offset of a member in a struct in bytes
 */
#define offsetof(type, member) ((size_t)((char *)&(((type *)0)->member) - (char *)0))

#endif

/* stddef.h ends here */
