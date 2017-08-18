/**
 * @file    debug_terminal.c
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   Implementation of functions to write to the standard debug terminal
 */

#include <kernel/debug_terminal.h>
#include <stdio.h>
#include <string.h>


//==============================================================================
// Implementation specific types
//==============================================================================

// Struct representing a character entry in the buffer
typedef struct {

    // Character code
    uint8_t character;

    // Text color value chosen from vga_color_t
    uint8_t text_color : 4;

    // Background color value chosen from vga_color_t
    uint8_t back_color : 4;

} __attribute__((packed)) character_entry_t;

//==============================================================================
// Implementation private function declarations
//==============================================================================

static uint32_t offset(uint32_t x, uint32_t y);

static void scroll();

//==============================================================================
// Implementation private variables
//==============================================================================

static character_entry_t *_VIDMEM = (character_entry_t *) 0xC00B8000;

static uint32_t _cursor_x = 0;
static uint32_t _cursor_y = 0;

static vga_color_t _default_text_color = VGA_COLOR_WHITE;
static vga_color_t _default_back_color = VGA_COLOR_BLACK;

static vga_color_t _text_color;
static vga_color_t _back_color;

static FILE file;

//==============================================================================
// Implementation private function definitions
//==============================================================================

uint32_t offset(uint32_t x, uint32_t y)
{
    return (x + (y * DEBUG_TERMINAL_WIDTH));
}

void scroll()
{
    if(_cursor_y >= 25)
    {
        int i;
        for(i = 0; i < (80*24); ++i)
        {
            _VIDMEM[i] = _VIDMEM[i + 80];
        }

        for(; i < (80*25); ++i)
        {
            _VIDMEM[i] = (character_entry_t){' ', _text_color, _back_color};
        }

        _cursor_y = 24;
    }
}

//==============================================================================
// Interface functions
//==============================================================================

void debug_terminal_initialize()
{
    _text_color = _default_text_color;
    _back_color = _default_back_color;

    debug_terminal_clear();

    strcpy(file.name, "debug_terminal");

    file.read = NULL;
    file.write = debug_terminal_putch;
    file.open = NULL;
    file.close = NULL;

    set_stdout(&file);
}


void debug_terminal_restore_default()
{
    _text_color = _default_text_color;
    _back_color = _default_back_color;
}

void debug_terminal_clear()
{
    for(uint32_t i = 0; i < (DEBUG_TERMINAL_WIDTH*DEBUG_TERMINAL_HEIGHT); ++i)
    {
        _VIDMEM[i] = (character_entry_t){' ', _text_color, _back_color};
    }

    _cursor_x = 0;
    _cursor_y = 0;
}

void debug_terminal_print(const char* str)
{
    while(*str)
    {
        debug_terminal_putch(*(str++));
    }
}

void debug_terminal_putch(char c)
{
    if(c == 0)
    {
        return;
    }

    if(c == '\n' || c == '\r')
    {
        _cursor_x = 0;
        ++_cursor_y;
        return;
    }

    if(_cursor_x >= DEBUG_TERMINAL_WIDTH)
    {
        _cursor_x = 0;
        ++_cursor_y;
        return;
    }

    scroll();

    _VIDMEM[offset(_cursor_x++, _cursor_y)] =
        (character_entry_t){c, _text_color, _back_color};
}

vga_color_t debug_terminal_setTextColor(vga_color_t new_color)
{
    vga_color_t old_color = _text_color;
    _text_color = new_color;
    return old_color;
}

vga_color_t debug_terminal_setBackColor(vga_color_t new_color)
{
    vga_color_t old_color = _back_color;
    _back_color = new_color;
    return old_color;
}

void setCursor(uint32_t x, uint32_t y)
{
    _cursor_x = x;
    _cursor_y = y;
}

void getCursor(uint32_t *x, uint32_t *y)
{
    *x = _cursor_x;
    *y = _cursor_y;
}

//==============================================================================
// End of file
//==============================================================================
