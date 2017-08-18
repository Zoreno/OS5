/**
 * @file    string.h
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   LIBK string.h Standard Header
 */

#ifndef _LIBK_STRING_H
#define _LIBK_STRING_H

#include <_size_t.h>
#include <_null.h>

//void *memchr(const void *str, int c, size_t n);

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

/**
 * @brief Concaternates two strings
 * @param str1 Pointer to destination string
 * @param str2 Pointer to source string
 * @return Pointer to destination string
 */
char *strcat(char *str1, const char *str2);

//char *strncat(char *str1, const char *str2, size_t n);

//char *strchr(const char *str, int c);

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

//size_t strcspn(const char *str1, const char *str2);

/**
 * @brief Calculates the length of a string
 * @param str Pointer to string
 * @return Length of string
 */
size_t strlen(const char *str);

//char *strpbrk(const char *str1, const char *str2);

//char *strrchr(const char *str, int c);

//size_t strspn(const char *str1, const char *str2);

//char *strstr(const char *str1, const char *str2);

//char *strtok(char *str1, const char *str2);

#endif
