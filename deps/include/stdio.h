/**
 * @file    stdio.h
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   LIBK stdio.h Standard Header
 */

#ifndef _LIBK_STDIO_H
#define _LIBK_STDIO_H

#include <_size_t.h>
#include <_null.h>

#include <_file.h>

#include <stdarg.h>

/**
 * Pointer to file stdout.
 */
extern FILE *stdout;

/**
 * Sets the stdout pointer to a new file.
 */
void set_stdout(FILE *file);

//==============================================================================
// File Functions
//==============================================================================

//==============================================================================
// File IO
//==============================================================================

/**
 * @brief Outputs a character to a file
 * @param c Character to output 
 * @param file Pointer to file
 * @return Non-zero if successfull
 */
int fputc(char c, FILE *file);

/**
 * @brief Outputs a string to a file
 * @param str String to output 
 * @param file Pointer to file
 * @return Non-zero if successfull
 */
int fputs(const char *str, FILE *file);

//==============================================================================
// Print to stdout
//==============================================================================

/**
 * @brief Outputs a character to stdout
 * @param c Character to output 
 * @return Non-zero if successfull
 */
int putchar(char c);

/**
 * @brief Outputs a string to stdout
 * @param str String to output 
 * @return Non-zero if successfull
 */
int puts(const char *str);

//==============================================================================
// Formatted output
//==============================================================================

/**
 * @brief Outputs a formatted string to a file
 * @param file Pointer to file
 * @param format Format string
 * @return Number of characters outputted
 */
int fprintf(FILE *file, const char *format, ...);

/**
 * @brief Outputs a formatted string to stdout
 * @param format Format string
 * @return Number of characters outputted
 */
int printf(const char *format, ...);

/**
 * @brief Outputs a formatted string to a buffer
 * @param buf Pointer to buffer
 * @param format Format string
 * @return Number of characters outputted
 */
int sprintf(char *buf, const char *format, ...);

/**
 * @brief Outputs a formatted string to a buffer
 * @param str Output buffer
 * @param format Format string
 * @param Variable argument list
 * @return Number of characters outputted
 */
int vsprintf(char *str, const char *format, va_list arg);

#endif
