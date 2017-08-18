/**
 * @file    vsprintf.c
 * @author  Joakim Bertils
 * @date    2017-07-28
 * @brief   Implementation of standard function vsprintf
 */

#include <stdio.h>

#include <stdint.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_PRINTF 0

/*
  Test Usage:
  vsprintf("%i", 4); // "4"
  vsprintf("%*i", 4, 4); // "   4"
  vsprintf("%*i", 4, 12345); // "12345"
  vsprintf("%4i", 4); // "   4"
  vsprintf("%4i", 12345); // "12345"

  vsprintf("%b", 10); // 1010
  vsprintf("%#b, 10), // 0b1010
*/

// (Not as in C std lib specification. This is a subset though)
// Formal Grammar rule:
// format:  (%(flags)(width)specifier | character)*

/*
  flags:
  -:        Left-justify
  +:        Force sign
  (space):  Insert space if no sign
  #:            Print prefix
  0:            Left-pad with 0 instead of space
*/

/*
  width:
  (number): Minimum number of characters to print
  *:            Minimum number of characters to print as argument before number.
  */

/*
  specifier:
  c:            Character
  d | i:        Signed dec
  o:            Signed octal
  s:            String
  u:            Unsigned dec
  x | X:        Unsigned hex
  p:            Pointer address
  %:            '%' Character
  b | B:        Binary
*/

//==============================================================================
// Implementation types
//==============================================================================

/**
 * Flags to indicate format of command
 */
typedef struct
{
    /**
     * Minimum number of characters to print
     */
    uint32_t width;

    /**
     * Output specifier
     */
    char specifier;

    /**
     * If the output should be padded on the right.
     */
    uint8_t left_justify : 1;

    /**
     * If the sign character always should be printed
     */
    uint8_t force_sign : 1;

    /**
     * If a space should be placed if there is no sign
     */
    uint8_t space : 1;

    /**
     * Print number base prefix
     */
    uint8_t print_prefix : 1;

    /**
     * If the output should be padded with '0' instead of space.
     */
    uint8_t zero_pad : 1;

    /**
     * If the width is passed as an argument.
     */
    uint8_t width_as_arg : 1;

    /**
     * Reserved for future use.
     */
    uint8_t reserved : 2;
} flags_t;


//==============================================================================
// Implementation function forward declarations
//==============================================================================

/**
 * @brief Check if char is a valid flag.
 * @param c Character to check
 * @return True if valid
 */
int is_flag(char c);

/**
 * @brief Check if char is a valid specifier.
 * @param c Character to check
 * @return True if valid
 */
int is_specifier(char c);

/**
 * @brief Parses an output command from the format string
 * @param format Format string
 * @param flags Pointer to flags struct to store result
 * @param length Pointer to variable to store number of characters processed
 */
int parse_command(const char *format, flags_t *flags, uint32_t *length);

//==============================================================================
// Implementation private variables
//==============================================================================

/**
 * String of valid flags.
 */
static char _flags[] = "-+ #0";

/**
 * String of valid specifiers.
 */
static char _specifiers[] = "cdiosuxXp%bB";

//==============================================================================
// Implementation function definitions
//==============================================================================

int is_flag(char c)
{
    size_t flags_length = strlen(_flags);

    for(size_t p = 0; p < flags_length; ++p)
    {
        if(_flags[p] == c)
        {
            return 1;
        }
    }

    return 0;
}

int is_specifier(char c)
{
    size_t specifiers_length = strlen(_specifiers);

    for(size_t p= 0; p < specifiers_length; ++p)
    {
        if(_specifiers[p] == c)
        {
            return 1;
        }
    }

    return 0;
}

int parse_command(const char *format, flags_t *flags, uint32_t *length)
{
    // Current character to process
    char *current_char = (char *)format;

    // Check and store all flags
    while(is_flag(*current_char))
    {
        switch(*current_char)
        {
        case '-':
            flags->left_justify = 1;
            break;
        case '+':
            flags->force_sign = 1;
            break;
        case ' ':
            flags->space = 1;
            break;
        case '#':
            flags->print_prefix = 1;
            break;
        case '0':
            flags->zero_pad = 1;
            break;
        default:
            // Error
            return 1;
        }

        // Advance to next character
        ++current_char;
        ++(*length);
    }

    // Check if and how width is specified
    if(*current_char == '*')
    {
        // The width is passed as an argument
        flags->width_as_arg = 1;
        ++current_char;
        ++(*length);
    }
    else if (isdigit(*current_char))
    {
        // The width is passed directly in the format
        char buf[32] = {0};
        size_t i = 0;

        // Read all characters and store them in an array
        while(isdigit(*current_char))
        {
            buf[i++] = *(current_char++);
        }

        // IMPORTANT!
        buf[i] = '\0';

        // Convert to integer with stdlib function atoi
        flags->width = atoi(buf);

        (*length) += strlen(buf);
    }

    // Finally read the passed in specifier

    if(is_specifier(*current_char))
    {
        flags->specifier = *current_char;
        ++(*length);

        return 0;
    }

    // If we did not have a specifier now, the format is not correct

    return 1;
}

#define output_char(c) (str[loc++] = c)

#define output_string(s)    {strcpy(&str[loc], s);  \
        loc += strlen(s);}

#define PAD(width_delta, pad_char)                      \
    {for(int i_pad = 0; i_pad < width_delta; ++i_pad)   \
        {                                               \
            output_char(pad_char);                      \
        }}

//==============================================================================
// Interface functions
//==============================================================================

int vsprintf(char *str, const char *format, va_list arg)
{


    if(!str)
    {
        puts("[vsprintf] Output buffer null\n");

        return 0;
    }

    if(!format)
    {
        puts("[vsprintf] Format buffer null\n");

        return 0;
    }

    size_t loc = 0;

    size_t i = 0;

    const size_t format_length = strlen(format);

    while(i <= format_length)
    {
        char c = format[i++];

        if(c == '%')
        {
            flags_t flags;
            memset(&flags, 0, sizeof(flags_t));

            uint32_t length = 0;

            if(parse_command(&format[i], &flags, &length))
            {
                // Error in format

                puts("[vsprintf] Error parsing format!\n");

                return 0;
            }

            int width = 0;

            if(flags.width != 0)
            {
                width = flags.width;
            }
            else if(flags.width_as_arg)
            {
                width = va_arg(arg, int);
            }

#if DEBUG_PRINTF

            puts("[vsprintf] Format parsing successfull:\n");


            puts("[vsprintf] Found format string: ");

            char tmp_buf[32] = {0};

            memcpy(tmp_buf, &format[i], length);

            puts(tmp_buf);

            puts("\n[vsprintf] Parsed flags: ");

            if(width)
            {
                puts("width[");

                char tmp_buf[32];

                itoa(width, 10, tmp_buf);

                puts(tmp_buf);

                puts("] ");
            }

            putchar(flags.specifier);

            putchar(' ');

            if(flags.left_justify)
            {
                puts("lj ");
            }

            if(flags.force_sign)
            {
                puts("fc ");
            }

            if(flags.space)
            {
                puts("sp ");
            }

            if(flags.print_prefix)
            {
                puts("pp ");
            }

            if(flags.zero_pad)
            {
                puts("zp ");
            }

            if(flags.width_as_arg)
            {
                puts("wa ");
            }

            puts("\n");

#endif

            i += length;

            char pad_char = (flags.zero_pad) ? '0' : ' ';

            switch(flags.specifier)
            {
                //============================================================
                // Signed Decimal
                //============================================================
            case 'd':
            case 'i':
            {

                int c = va_arg(arg, int);

                char s[32] = {0};

                itoa(c, 10, s);

                int width_delta = width - strlen(s);

                if(c >= 0)
                {
                    if(flags.force_sign)
                    {
                        output_char('+');
                        width_delta -= 1;
                    }
                    else if(flags.space)
                    {
                        output_char(' ');
                        width_delta -= 1;
                    }
                }

                if(flags.left_justify)
                {
                    output_string(s);
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_string(s);
                }

                break;
            }

            //============================================================
            // Signed Octal
            //============================================================
            case 'o':
            {
                int c = va_arg(arg, int);

                char s[32] = {0};

                itoa(c, 8, s);

                int width_delta = width - strlen(s);

                if(c >= 0)
                {
                    if(flags.force_sign)
                    {
                        output_char('+');
                        width_delta -= 1;
                    }
                    else if(flags.space)
                    {
                        output_char(' ');
                        width_delta -= 1;
                    }
                }

                if(flags.print_prefix){
                    output_string("0");
                    width_delta -= 1;
                }

                if(flags.left_justify)
                {
                    output_string(s);
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_string(s);
                }

                break;
            }

            //============================================================
            // String Pointer
            //============================================================
            case 's':
            {
                int c = va_arg(arg, int);

                char s[32] = {0};

                strcpy(s, (const char *)c);

                int width_delta = width - strlen(s);

                if(flags.left_justify)
                {
                    output_string(s);
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_string(s);
                }

                break;
            }

            //============================================================
            // Unsigned decimal
            //============================================================
            case 'u':
            {
                unsigned int c = va_arg(arg, unsigned int);

                char s[32] = {0};

                uitoa(c, 10, s);

                int width_delta = width - strlen(s);

                if(flags.left_justify)
                {
                    output_string(s);
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_string(s);
                }

                break;
            }

            //============================================================
            // Unsigned hexadecimal
            //============================================================
            case 'p':
            case 'x':
            case 'X': // TODO: 'X' prints capital letters
            {
                unsigned int c = va_arg(arg, unsigned int);

                char s[32] = {0};

                uitoa(c, 16, s);

                int width_delta = width - strlen(s);

                if(flags.print_prefix){
                    output_string("0x");
                    width_delta -= 2;
                }

                if(flags.left_justify)
                {
                    output_string(s);
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_string(s);
                }

                break;
            }

            //============================================================
            // Character
            //============================================================
            case 'c':
            {
                char c = va_arg(arg, char);

                int width_delta = width - 1;

                if(flags.left_justify)
                {
                    output_char(c);
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_char(c);
                }

                break;
            }

            //============================================================
            // % Character
            //============================================================
            case '%':
            {
                int width_delta = width - 1;

                if(flags.left_justify)
                {
                    output_char('%');
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_char('%');
                }

                break;
            }

            //============================================================
            // Binary
            //============================================================

            case 'b':
            case 'B': // TODO: 'B' prints capital letters
            {
                unsigned int c = va_arg(arg, unsigned int);

                char s[64] = {0};

                uitoa(c, 2, s);

                int width_delta = width - strlen(s);

                if(flags.print_prefix){
                    output_string("0b");
                    width_delta -= 2;
                }

                if(flags.left_justify)
                {
                    output_string(s);
                    PAD(width_delta, pad_char);
                }
                else
                {
                    PAD(width_delta, pad_char);
                    output_string(s);
                }

                break;
            }

            //============================================================
            // Default case
            //============================================================
            default:
                // Error: Unhandled case

                puts("[vsprintf] Unhandled specifier case\n");

                return 0;
            }
        }
        else
        {
            output_char(c);
        }
    }

    return (int) loc;
}
