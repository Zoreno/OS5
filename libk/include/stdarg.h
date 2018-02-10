/* stdarg.h --- 
 * 
 * Filename: stdarg.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:15:21 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb  6 21:15:22 2018 (+0100)
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
 * @file stdarg.h
 * @author Joakim Bertils
 * @date 24 July 2017
 * @brief File containing the LIBK helper functions and definitions for variable expansion.
 */

#ifndef _LIBK_STDARG_H
#define _LIBK_STDARG_H

#include <va_list.h>

/**
 * Stack item definition
 */
#define STACKITEM int

/**
 * Returns the size on the stack of a varaible of type TYPE
 */
#define VA_SIZE(TYPE) \
    ((sizeof(TYPE) + sizeof(STACKITEM) - 1) \
     & ~(sizeof(STACKITEM) - 1))

/**
 * Begins a variable argument expansion
 */
#define va_start(AP, LASTARG) \
    (AP=((va_list)&(LASTARG) + VA_SIZE(LASTARG)))

/**
 * Ends a variable argument expansion
 */
#define va_end(AP)

/**
 * Retrieves the next variable interpreted as TYPE
 */
#define va_arg(AP, TYPE) \
    (AP += VA_SIZE(TYPE), *((TYPE *)(AP - VA_SIZE(TYPE))))

#endif

/* stdarg.h ends here */
