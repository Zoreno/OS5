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
