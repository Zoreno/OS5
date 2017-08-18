/**
 * @file    debug_terminal.h
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   Interface of the debug terminal
 */

#ifndef _KERNEL_DEBUG_TERMINAL_H
#define _KERNEL_DEBUG_TERMINAL_H

#include <stdint.h>

/**
 * Macro expanding to the width of the terminal
 */
#define DEBUG_TERMINAL_WIDTH 80U

/**
 * Macro expanding to the height of the terminal
 */
#define DEBUG_TERMINAL_HEIGHT 25U

/**
 * Enumeration of the available terminal colors.
 */
typedef enum VGA_COLOR {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 0xA,
    VGA_COLOR_LIGHT_CYAN = 0xB,
    VGA_COLOR_LIGHT_RED = 0xC,
    VGA_COLOR_LIGHT_MAGENTA = 0xD,
    VGA_COLOR_LIGHT_BROWN = 0xE,
    VGA_COLOR_WHITE = 0xF,
} vga_color_t;

/**
 * @brief Initializes the terminal to the default values.
 */
void debug_terminal_initialize();

/**
 * @brief Restores the default colors.
 */
void debug_terminal_restore_default();

/**
 * @brief Clears the terminal and moves the cursor to the top left corner.
 */
void debug_terminal_clear();

/**
 * @brief Prints a string to the terminal
 * @param str Pointer to the null-terminated string to print
 */
void debug_terminal_print(const char* str);

/**
 * @brief Prints a character to the terminal.
 * @param c Character to print
 */
void debug_terminal_putch(char c);

/**
 * @brief Sets the text color
 * @param new_color New color to be used
 * @return Old color.
 */
vga_color_t debug_terminal_setTextColor(vga_color_t new_color);

/**
 * @brief Sets the background color
 * @param new_color New color to be used
 * @return Old color.
 */
vga_color_t debug_terminal_setBackColor(vga_color_t new_color);

/**
 * @brief Sets the cursor position
 * @param x New x position
 * @param y New y position
 */
void setCursor(uint32_t x, uint32_t y);

/**
 * @brief Gets the cursor position
 * @param x Ptr to location to store x value
 * @param y Ptr to location to store y value
 */
void getCursor(uint32_t *x, uint32_t *y);

#endif
