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
//void lltoa(long long int i, int base, char *buf);

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
//void ulltoa(unsigned long long int i, int base, char *buf);

//==============================================================================
// Memory Functions
//==============================================================================

// void *calloc(size_t nitems, size_t size); // Zero-initializes
// void free(void *ptr);

// void *malloc(size_t size);
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

/*
  void qsort(
  void *base,
  size_t nitems,
  size_t size,
  int (*compar)(const void *, const void *));
*/

//==============================================================================
// End of file
//==============================================================================

#endif