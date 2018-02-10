/* _file.h --- 
 * 
 * Filename: _file.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:13:58 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb  6 21:14:00 2018 (+0100)
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


#ifndef _LIBK__FILE_H
#define _LIBK__FILE_H

#include <stdint.h>

typedef char (*read_function)(void);
typedef void (*write_function)(char);

typedef void (*open_function)(const char*);
typedef void (*close_function)(const char*);

typedef struct {
    char name[32];
    uint32_t flags;
    uint32_t fileLength;

    read_function read;
    write_function write;

    open_function open;
    close_function close;
} FILE, *PFILE;

#endif

/* _file.h ends here */
