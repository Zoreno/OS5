/* stdlib.h --- 
 * 
 * Filename: stdlib.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:15:58 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Wed Feb  7 00:10:05 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 4
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
 * @file    stdlib.h
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   LIBK stdlib.h Standard Header
 */

#ifndef _LIBK_STDLIB_H
#define _LIBK_STDLIB_H

#include <_null.h>
#include <_size_t.h>

//==============================================================================
// Definitions
//==============================================================================

/**
 * Exit code returned on success
 */
#define EXIT_SUCCESS (0)

/**
 * Exit code returned on failure
 */
#define EXIT_FAILURE (1)

/**
 * Maximum value returned from rand function
 */
#define RAND_MAX (0x7FFFFFFF)

//==============================================================================
// Type Definitions
//==============================================================================

/**
 * Struct containing the return values of the div function
 */
typedef struct
{
    /**
     * Quotient of the division
     */
    int quot;

    /**
     * Remainder of the division
     */
    int rem;
} div_t;

/**
 * Struct containing the return values of the ldiv function
 */
typedef struct
{
    /**
     * Quotient of the division
     */
    long int quot;

    /**
     * Remainder of the division
     */
    long int rem;
} ldiv_t;

/**
 * Struct containing the return values of the lldiv function
 */
typedef struct
{
    /**
     * Quotient of the division
     */
    long long int quot;

    /**
     * Remainder of the division
     */
    long long int rem;
} lldiv_t;

//==============================================================================
// String converting functions
//==============================================================================

/**
 * @brief Converts a string to an integer
 * @param str String to convert
 * @return Resulting integer
 */
int atoi(const char *str);
//long int atol(const char *str);
//long long int atoll(const char *str);

/**
 * @brief Converts a string to an integer
 * @param str String to convert
 * @param endptr Where to store pointer to string after integer
 * @param base Number base to convert from
 * @return Resulting integer
 */
long int strtol(const char *str, char **endptr, int base);

/**
 * @brief Converts a string to an unsigned integer
 * @param str String to convert
 * @param endptr Where to store pointer to string after integer
 * @param base Number base to convert from
 * @return Resulting integer
 */
unsigned long int strtoul(const char *str, char **endptr, int base);
//long long int strtoll(const char *str, char **endptr, int base);
//unsigned long long int strtoull(const char *str, char **endptr, int base);

/**
 * @brief Converts an integer to string
 * @param i Number to convert
 * @param base Number base to convert to
 * @param buf Where to store result
 */
void itoa(int i, int base, char *buf);

/**
 * @brief Converts a long to string
 * @param i Number to convert
 * @param base Number base to convert to
 * @param buf Where to store result
 */
void ltoa(long int i, int base, char *buf);

/**
 * @brief Converts a long long to string
 * @param i Number to convert
 * @param base Number base to convert to
 * @param buf Where to store result
 */
void lltoa(long long int i, int base, char *buf);

/**
 * @brief Converts an unsigned integer to string
 * @param i Number to convert
 * @param base Number base to convert to
 * @param buf Where to store result
 */
void uitoa(unsigned int i, int base, char *buf);

/**
 * @brief Converts an unsigned long to string
 * @param i Number to convert
 * @param base Number base to convert to
 * @param buf Where to store result
 */
void ultoa(unsigned long int i, int base, char *buf);

/**
 * @brief Converts an unsigned long long to string
 * @param i Number to convert
 * @param base Number base to convert to
 * @param buf Where to store result
 */
void ulltoa(unsigned long long int i, int base, char *buf);

//==============================================================================
// Memory Allocation Functions
//==============================================================================

/**
 * @brief Allocates zero-initalized memory
 * @param nitems Number of elements to be allocated
 * @param size Size of each element
 * @return Pointer to allocated memory
 */
void *calloc(size_t nitems, size_t size);

/**
 * @brief Frees previously allocated memory
 * @param ptr Pointer to memory
 */
void free(void *ptr);

/**
 * @brief Allocates a chunk of memory of at least the given size.
 * @param size Requested size
 */
void *malloc(size_t size);
// void *realloc(void *ptr, size_t size);

//==============================================================================
// Math Functions
//==============================================================================

/**
 * @brief Returns the absolute value of x
 * @param x Number 
 * @return Absolute value
 */
int abs(int x);

/**
 * @brief Returns the absolute value of x
 * @param x Number 
 * @return Absolute value
 */
long int labs(long int x);

/**
 * @brief Returns the absolute value of x
 * @param x Number 
 * @return Absolute value
 */
long long int llabs(long long int x);

/**
 * @brief Performs integer division
 * @param number Numerator
 * @param denom Denominator
 * @return Result struct
 */
div_t div(int number, int denom);

/**
 * @brief Performs integer division
 * @param number Numerator
 * @param denom Denominator
 * @return Result struct
 */
ldiv_t ldiv(long int number, long int denom);

/**
 * @brief Performs integer division
 * @param number Numerator
 * @param denom Denominator
 * @return Result struct
 */
lldiv_t lldiv(long long int number, long long int denom);

/**
 * @brief Returns a random number from 0 to @RAND_MAX
 * @return Random number
 */
int rand(void);

/**
 * @brief Returns a random numwber in the range [@min, @max[
 * @param min Lower limit
 * @param max Upper limit
 * @return Random number
 */
int rand_range(int min, int max);

/**
 * @brief Seeds the random number generator
 * @param seed Seed
 */
void srand(unsigned int seed);

//==============================================================================
// Searching and Sorting functions
//==============================================================================

/**
 * @brief Performs binary search on a sorted array
 * @param key Key to search for
 * @param base Base of array
 * @param nitems Number of items in array
 * @param size Size of each item in array
 * @param compar Compare function 
 * @return Pointer to element if found, otherwise @NULL
 */
void *bsearch(
    const void *key,
    const void *base,
    size_t nitems,
    size_t size,
    int (*compar)(const void *, const void *));

/**
 * @brief Sorts the array according to the compare function
 * @param base Base address of the array.
 * @param nitems Number of items in array.
 * @param size Size of array entry.
 * @param compare Compare function.
 */
void qsort(
  void *base,
  size_t nitems,
  size_t size,
  int (*compare)(const void *, const void *));


//==============================================================================
// End of file
//==============================================================================

#endif

/* stdlib.h ends here */
