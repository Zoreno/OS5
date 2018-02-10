/* stdint.h --- 
 * 
 * Filename: stdint.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:15:43 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb  6 21:15:44 2018 (+0100)
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
 * @file stdint.h
 * @author Joakim Bertils
 * @date 23 July 2017
 * @brief File containing the LIBK type definitons for integer types.
 */

#ifndef _LIBK_STDINT_H
#define _LIBK_STDINT_H

#include <_size_t.h>

#define ARCH_I686

#define STDINT_PROVIDE_64

#ifdef ARCH_I686

//==============================================================================
// Exact Width Integer types
//==============================================================================

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#ifdef STDINT_PROVIDE_64
typedef unsigned long long uint64_t;
#endif

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
#ifdef STDINT_PROVIDE_64
typedef signed long long int64_t;
#endif

#define INT8_MIN -128
#define INT8_MAX 127
#define UINT8_MAX 255

#define INT16_MIN -32768
#define INT16_MAX 32767
#define UINT16_MAX 65635

#define INT32_MIN -2147483648L
#define INT32_MAX 2147483647L
#define UINT32_MAX 4294967295UL

#ifdef STDINT_PROVIDE_64
#define INT64_MIN -9223372036858775808LL
#define INT64_MAX 9223372036858775807LL
#define UINT64_MAX 18446744073709551615ULL
#endif

//==============================================================================
// Minimum Width Integer types
//==============================================================================

typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;

#ifdef STDINT_PROVIDE_64
typedef unsigned long long uint_least64_t;
#endif

typedef signed char int_least8_t;
typedef signed short int_least16_t;
typedef signed int int_least32_t;

#ifdef STDINT_PROVIDE_64
typedef signed long long int_least64_t;
#endif

#define INT_LEAST8_MIN -128
#define INT_LEAST8_MAX 127
#define UINT_LEAST8_MAX 255

#define INT_LEAST16_MIN -32768
#define INT_LEAST16_MAX 32767
#define UINT_LEAST16_MAX 65635

#define INT_LEAST32_MIN -2147483648L
#define INT_LEAST32_MAX 2147483647L
#define UINT_LEAST32_MAX 4294967295UL

#ifdef STDINT_PROVIDE_64
#define INT_LEAST64_MIN -9223372036858775808LL
#define INT_LEAST64_MAX 9223372036858775807LL
#define UINT_LEAST64_MAX 18446744073709551615ULL
#endif

#define INT8_C(value) (value)
#define UINT8_C(value) (value)

#define INT16_C(value) (value)
#define UINT16_C(value) (value)

#define INT32_C(value) (value ## L)
#define UINT32_C(value) (value ## UL)

#ifdef STDINT_PROVIDE_64
#define INT64_C(value) (value ## LL)
#define UINT64_C(value) (value ## ULL)
#endif

//==============================================================================
// Fastest Minimum Width Integer Types
//==============================================================================

typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef unsigned int uint_fast32_t;

#ifdef STDINT_PROVIDE_64
typedef unsigned long long uint_fast64_t;
#endif

typedef signed char int_fast8_t;
typedef signed short int_fast16_t;
typedef signed int int_fast32_t;

#ifdef STDINT_PROVIDE_64
typedef signed long long int_fast64_t;
#endif

#define INT_FAST8_MIN -128
#define INT_FAST8_MAX 127
#define UINT_FAST8_MAX 255

#define INT_FAST16_MIN -32768
#define INT_FAST16_MAX 32767
#define UINT_FAST16_MAX 65635

#define INT_FAST32_MIN -2147483648L
#define INT_FAST32_MAX 2147483647L
#define UINT_FAST32_MAX 4294967295UL

#ifdef STDINT_PROVIDE_64
#define INT_FAST64_MIN -9223372036858775808LL
#define INT_FAST64_MAX 9223372036858775807LL
#define UINT_FAST64_MAX 18446744073709551615ULL
#endif

//==============================================================================
// Pointer Types
//==============================================================================

typedef long intptr_t;
typedef unsigned long uintptr_t;

#define INTPTR_MIN (-2147483647L-1)
#define INTPTR_MAX (2147483647L)
#define UINTPTR_MAX (4294967295UL)

//==============================================================================
// Greatest Width Integer types
//==============================================================================

#ifdef STDINT_PROVIDE_64

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define INTMAX_C(value) (INT64_C(value))
#define UINTMAX_C(value) (UINT64_C(value))

#else

typedef int32_t intmax_t;
typedef uint32_t uintmax_t;

#define INTMAX_MIN INT32_MIN
#define INTMAX_MAX INT32_MAX
#define UINTMAX_MAX UINT32_MAX

#define INTMAX_C(value) (INT32_C(value))
#define UINTMAX_C(value) (UINT32_C(value))

#endif // STDINT_PROVIDE_64

//==============================================================================
// Other Types
//==============================================================================

#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX

#define SIZE_MAX UINT32_MAX


#endif // ARCH_I686

#endif // _LIBK_STDINT_H

/* stdint.h ends here */
