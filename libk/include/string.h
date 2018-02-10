/* string.h --- 
 * 
 * Filename: string.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:16:07 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 01:26:31 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 10
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
 * @file    string.h
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   LIBK string.h Standard Header
 *
 * @todo    Implement commented functions and create wchar functions.
 */

#ifndef _LIBK_STRING_H
#define _LIBK_STRING_H

#include <_size_t.h>
#include <_null.h>

/**
 * @brief Checks the first n bytes of str for the value c.
 * @param str String to check.
 * @param c Value to search for.
 * @param n Number of bytes to check.
 * @return Pointer to char if found, else nullptr.
 */
void *memchr(const void *str, int c, size_t n);

/**
 * @brief Compare two chunks of memory
 * @param str1 Pointer to first chunk
 * @param str2 Pointer to second chunks
 * @param n Bytes to compare
 * @return 0 if equal
 */
int memcmp(const void *str1, const void *str2, size_t n);

/**
 * @brief Copies a memory chunk to another chunk
 * @param str1 Pointer to destination chunk
 * @param str2 Pointer to source chunk
 * @param n Bytes to copy
 * @return Pointer to destination chunk
 */
void *memcpy(void *str1, const void *str2, size_t n);

/**
 * @brief Moves a memory chunk to another chunk
 * @param str1 Pointer to destination chunk
 * @param str2 Pointer to source chunk
 * @param n Bytes to move
 * @return Pointer to destination chunk
 */
void *memmove(void *str1, const void *str2, size_t n);

/**
 * @brief Fills a chunk of memory
 * @param str1 Pointer to destination chunk
 * @param c Byte to fill
 * @param n Bytes to fill
 * @return Pointer to destination chunk
 */
void *memset(void *str, unsigned char c, size_t n);

//void *memccpy(void *dest, const void *src, int c, size_t n);

//void *memmem(const void *haystack_start, size_t haystack_end,
//             const void *needle_start, size_t needle_end);

//void *mempcpy(void *dest, const void *src, size_t len);

//void *memrchr(const void *s, int c_in, size_t n);

/**
 * @brief Concaternates two strings
 * @param str1 Pointer to destination string
 * @param str2 Pointer to source string
 * @return Pointer to destination string
 */
char *strcat(char *str1, const char *str2);

//char *strncat(char *str1, const char *str2, size_t n);

/**
 * @brief Finds the first of occurance of a character in a string.
 * @param str String to search.
 * @param c Character to find.
 * @return 
 */
char *strchr(const char *str, int c);

/**
 * @brief Compares two strings
 * @param str1 Pointer to first string
 * @parma str2 Pointer to second string
 * @return 0 if equal
 */
int strcmp(const char *str1, const char *str2);

//int strncmp(const char *str1, const char *str2, size_t n);

/**
 * @brief Copies a string to another string
 * @param str1 Pointer to destination string
 * @param str2 Pointer to source string
 * @return Pointer to destination string
 */
char *strcpy(char *str1, const char *str2);

//char *strncpy(char *str1, const char *str2, size_t n);

/**
 * @brief Finds the longest initial segment of str1 which contains no characters from reject.
 * @param str1 String to search
 * @param reject String of reject characters.
 * @return Length of initial segment.
 */
size_t strcspn(const char *str1, const char *reject);

/**
 * @brief Calculates the length of a string
 * @param str Pointer to string
 * @return Length of string
 */
size_t strlen(const char *str);

/**
 * @brief Calculates the length of a string.
 * @param str Pointer to string.
 * @param maxlen Maximum number of characters to search.
 * @return Length of string.
 */
size_t strnlen(const char *str, size_t maxlen);

//char *strpbrk(const char *str1, const char *str2);

//char *strrchr(const char *str, int c);

/**
 * @brief Calculates number of characters from start of @s only consisting of characters in @accept.
 * @param s Input string
 * @param accept Accept string.
 * @return Number of leading characters only consisting of characters in @accept.
 */
size_t strspn(const char *s, const char *accept);

//char *strstr(const char *str1, const char *str2);

/**
 * @brief Breaks a string into tokens and null-terminates them.
 * @param str String to break.
 * @param delim Delimiters to identify tokens.
 * @return Next token if possible, else null.
 */
char *strtok(char *str, const char *delim);
//char *strtok_r(char *s, const char *delim, char **save_ptr);

//char *strsep(char **stringp, const char *delim);

//int strcasecmp(const char *s1, const char *s2);
//int strncasecmp(const char *s1, const char *s2, size_t n);
//int strcasestr(const char *haystack_start, const char *needle_start);

//char *strfry(char *string);

/**
 * @brief Duplicates a string
 * @param str String to duplicate
 * @return Pointer to new string.
 */
char *strdup(const char *str);

/**
 * @brief Duplicates the first n bytes of string.
 * @param str String to duplicate.
 * @param n Pointer to new string.
 * @return Pointer to new string.
 */
char *strndup(const char *str, size_t n);

//char *strchrnul(const char *str, int c_in);

//void bcopy(const void *src, void *dest, size_t len);
//void bzero(void *s, size_t len);

//void *memfrob(void *S, size_t n);

//int ffs(int i);
//int ffs(long int i);
//int ffsll(long long int);

//void swab(const void *bfrom, void *bto, size_t n);

#endif

/* string.h ends here */
