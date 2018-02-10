/* stdbool.h --- 
 * 
 * Filename: stdbool.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:15:28 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb  6 21:15:29 2018 (+0100)
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
 * @file    stdbool.h
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   LIBK stdbool.h Standard Header
 */

#ifndef _LIBK_STDBOOL_H
#define _LIBK_STDBOOL_H

#define USE_BUILT_IN_BOOL 1

#define true 1
#define false 0

#if USE_BUILT_IN_BOOL 1
#define bool _Bool
#else
#define bool int
#endif

#endif

/* stdbool.h ends here */
