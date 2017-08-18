/**
 * @file    itoa.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of itoa family functions
 */

#include <stdlib.h>

// Valid chars to output
static char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void itoa(int i, int base, char *buf)
{
    // We do not handle bases larger than 16
    if(base > 16)
    {
        return;
    }

    // Check for negative number
    if(i < 0)
    {
        // Output '-' character
        *buf++ = '-';

        // Negate number
        i *= -1;
    }

    // Handle as an unsigned number
    uitoa((unsigned int)i, base, buf);
}

void ltoa(long int i, int base, char *buf)
{
    // We do not handle bases larger than 16
    if(base > 16)
    {
        return;
    }

    // Check for negative number
    if(i < 0)
    {
        // Output '-' character
        *buf++ = '-';

        // Negate number
        i *= -1;
    }

    // Handle as an unsigned number
    ultoa((unsigned long)i, base, buf);
}

#if 0

void lltoa(long long int i, int base, char *buf)
{
    // We do not handle bases larger than 16
    if(base > 16)
    {
        return;
    }

    // Check for negative number
    if(i < 0)
    {
        // Output '-' character
        *buf++ = '-';

        // Negate number
        i *= -1;
    }

    // Handle as an unsigned number
    ulltoa((unsigned long long)i, base, buf);
}

#endif

void uitoa(unsigned int i, int base, char *buf)
{
    int pos = 0;
    int opos = 0;
    int top = 0;

    // Allocate a temporary buffer
    char tbuf[64] = {0};

    // Check for zero or base larger than 16
    if((!i) || (base > 16))
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while(i != 0)
    {
        // Output character to temporary buffer
        tbuf[pos] = bchars[i % base];

        // Advance
        ++pos;

        // Remove last digit
        i /= base;
    }

    // Save position of last digit
    top = pos--;

    // Output all characters from the temporary buffer.
    // Remember that tbuf stores the digits in reverse
    // order.
    for(opos = 0; opos < top; pos--, opos++)
    {
        buf[opos] = tbuf[pos];
    }

    // Output null terminating character
    buf[opos] = 0;
}

void ultoa(unsigned long int i, int base, char *buf)
{
    int pos = 0;
    int opos = 0;
    int top = 0;

    // Allocate a temporary buffer
    char tbuf[64] = {0};

    // Check for zero or base larger than 16
    if((!i) || (base > 16))
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while(i != 0)
    {
        // Output character to temporary buffer
        tbuf[pos] = bchars[(unsigned int)(i % base)];

        // Advance
        ++pos;

        // Remove last digit
        i /= base;
    }

    // Save position of last digit
    top = pos--;

    // Output all characters from the temporary buffer.
    // Remember that tbuf stores the digits in reverse
    // order.
    for(opos = 0; opos < top; pos--, opos++)
    {
        buf[opos] = tbuf[pos];
    }

    // Output null terminating character
    buf[opos] = 0;
}

#if 0
void ulltoa(unsigned long long int i, int base, char *buf)
{
    int pos = 0;
    int opos = 0;
    int top = 0;

    // Allocate a temporary buffer
    char tbuf[64] = {0};

    // Check for zero or base larger than 16
    if((!i) || (base > 16))
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while(i != 0)
    {
        // Output character to temporary buffer
        tbuf[pos] = bchars[(size_t)(i % base)];

        // Advance
        ++pos;

        // Remove last digit
        i /= base;
    }

    // Save position of last digit
    top = pos--;

    // Output all characters from the temporary buffer.
    // Remember that tbuf stores the digits in reverse
    // order.
    for(opos = 0; opos < top; pos--, opos++)
    {
        buf[opos] = tbuf[pos];
    }

    // Output null terminating character
    buf[opos] = 0;
}

#endif
