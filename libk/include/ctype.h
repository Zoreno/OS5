/* ctype.h --- 
 * 
 * Filename: ctype.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:13:35 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb  6 21:13:38 2018 (+0100)
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
 * @file    ctype.h
 * @author  Joakim Bertils
 * @date    2017-07-31
 * @brief   LIBK standard header ctype.h
 */

#ifndef _LIBK_CTYPE_H
#define _LIBK_CTYPE_H

// TODO: Switch to function calls and move to separate files

//==============================================================================
// Character classification
//==============================================================================

#define isalnum(c) (isalpha(c) || isdigit(c))

#define isalpha(c) (isupper(c) || islower(c))

#define iscntrl(c) (((c) < (0x20)) || (c == 0x7f))

#define isgraph(c) (((c) - 0x21) < (0x5e))

#define isdigit(c) ((c) >= '0' && (c) <= '9')

#define islower(c) ((c) >= 'a' && (c) <= 'z')

#define isprint(c) ((c) >= ' ' && (c) <= '~')

#define ispunct(c) (isgraph(c) && !(isalnum(c)))

#define isspace(c) ((c) == ' ' || ((c) >= '\t' && (c) <= '\r'))

#define isupper(c) ((c) >= 'A' && (c) <= 'Z')

#define isxdigit(c) (isdigit(c)                    \
                     || ((c) >= 'A' && (c) <= 'F') \
                     || ((c) >= 'a' && (c) <= 'f'))

//==============================================================================
// Character conversion
//==============================================================================

#define tolower(c) ((c) + 0x20 * (((c) >= 'A') && ((c) <= 'Z')))

#define toupper(c) ((c) - 0x20 * (((c) >= 'a') && ((c) <= 'z')))

//==============================================================================
// Extra
//==============================================================================

#define isascii(c) ((unsigned)(c) <= 0x7F)

#define toascii(c) ((unsigned)(c) & 0x7F)

#endif

/* ctype.h ends here */
