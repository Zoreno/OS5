/**
 * @file    strtol.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of strtol family functions
 */

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <ctype.h>

long int strtol(const char *str, char **endptr, int base)
{
    // Pointer to the next character to process
    const char *s = str;

    // Accumulator for the value
    unsigned long acc;

    // Currently processed char
    int c;

    // Largest positive value divided by base
    unsigned long cutoff;

    // Flag to indicate a negative number
    int neg = 0;

    int any;

    // Last digit of the cutoff value
    int cutlim;

    // Read past any whitespace
    do
    {
        c = *s++;
    } while (isspace(c));

    // Check if number is negative
    if(c == '-')
    {
        neg = 1;
        c = *s++;
    }
    else if(c == '+')
    {
        c = *s++;
    }

    // If the base is either unspecified(0) or 16, allow "0x" or "0X" to
    // precede number. This will set base to 16 if it were unspecified.
    if((base == 0 || base == 16) && c == '0' && (*s == 'x'|| *s == 'X'))
    {
        c = s[1];
        s += 2;
        base = 16;
    }

    // If the base is either unspecified(0) or 2, allow "0b" or "0B" to
    // precede number. This will set base to 2 if it were unspecified.
    else if ((base == 0 || base == 2) && c == '0' && (*s == 'b'|| *s == 'B'))
    {
        c = s[1];
        s += 2;
        base = 2;
    }

    // If the base still is unspecified, assume octal if number starts with a 0,
    // else decimal
    else if(base == 0)
    {

        if(c == '0')
        {
            base = 8;
        }
        else
        {
            base = 10;
        }
    }

    // Calculate cutoff and offset
    cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
    cutlim = cutoff % (unsigned long)base;
    cutoff /= (unsigned long)base;

    for(acc = 0, any = 0;; c = *s++)
    {
        // Find numerical value of given char
        if(isdigit(c))
        {
            c -= '0';
        }
        else if(isalpha(c))
        {

            if(isupper(c))
            {

                c -= 'A' - 10;
            }
            else
            {

                c -= 'a' - 10;
            }
        }
        else
        {
            break; // Char is not number or alphabetical char.
        }

        if(c >= base)
        {
            break; // Digit is larger than base
        }

        // Check if appending the next character will result in an overflow.
        if((any < 0) || (acc > cutoff) || ((acc == cutoff) && (c > cutlim)))
        {
            any = -1;
        }
        else
        {
            any = 1;
            acc *= base;
            acc += c;
        }
    }

    // If overflow occured, set accumulator to maximum value
    if(any < 0)
    {
        acc = neg ? LONG_MIN : LONG_MAX;
    }
    else if(neg)
    {
        acc = -acc;
    }

    // If endptr point to a valid address, store terminating character there.
    if(endptr != 0)
    {
        *endptr = (char*)(any ? (s - 1) : str);
    }

    // Return the calculated value
    return (acc);
}

unsigned long int strtoul(const char *str, char **endptr, int base)
{
    // Pointer to the next character to process
    const char *s = str;

    // Accumulator for the value
    unsigned long acc;

    // Currently processed char
    int c;

    // Largest positive value divided by base
    unsigned long cutoff;

    // Flag to indicate a negative number
    int neg = 0;

    int any;

    // Last digit of the cutoff value
    int cutlim;

    // Read past any whitespace
    do
    {
        c = *s++;
    } while (isspace(c));

    // Check if number is negative
    if(c == '-')
    {
        neg = 1;
        c = *s++;
    }
    else if(c == '+')
    {
        c = *s++;
    }

    // If the base is either unspecified(0) or 16, allow "0x" or "0X" to
    // precede number. This will set base to 16 if it were unspecified.
    if((base == 0 || base == 16) && c == '0' && (*s == 'x'|| *s == 'X'))
    {
        c = s[1];
        s += 2;
        base = 16;
    }

    // If the base is either unspecified(0) or 2, allow "0b" or "0B" to
    // precede number. This will set base to 2 if it were unspecified.
    else if ((base == 0 || base == 2) && c == '0' && (*s == 'b'|| *s == 'B'))
    {
        c = s[1];
        s += 2;
        base = 2;
    }

    // If the base still is unspecified, assume octal if number starts with a 0,
    // else decimal
    else if(base == 0)
    {

        if(c == '0')
        {
            base = 8;
        }
        else
        {
            base = 10;
        }
    }

    // Calculate cutoff and offset
	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;

    for(acc = 0, any = 0;; c = *s++)
    {
        // Find numerical value of given char
        if(isdigit(c))
        {
            c -= '0';
        }
        else if(isalpha(c))
        {

            if(isupper(c))
            {

                c -= 'A' - 10;
            }
            else
            {

                c -= 'a' - 10;
            }
        }
        else
        {
            break; // Char is not number or alphabetical char.
        }

        if(c >= base)
        {
            break; // Digit is larger than base
        }

        // Check if appending the next character will result in an overflow.
        if((any < 0) || (acc > cutoff) || ((acc == cutoff) && (c > cutlim)))
        {
            any = -1;
        }
        else
        {
            any = 1;
            acc *= base;
            acc += c;
        }
    }

    // If overflow occured, set accumulator to maximum value
    if(any < 0)
    {
        acc = ULONG_MAX;
    }
    else if(neg)
    {
        acc = -acc;
    }

    // If endptr point to a valid address, store terminating character there.
    if(endptr != 0)
    {
        *endptr = (char*)(any ? (s - 1) : str);
    }

    // Return the calculated value
    return (acc);
}
