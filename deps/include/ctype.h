/**
 * @file    ctype.h
 * @author  Joakim Bertils
 * @date    2017-07-31
 * @brief   LIBK standard header ctype.h
 */

#ifndef _LIBK_CTYPE_H
#define _LIBK_CTYPE_H

// TODO: Switch to function calls and move to separate files

//==============================================================================
// Character classification
//==============================================================================

#define isalnum(c) (isalpha(c) || isdigit(c))

#define isalpha(c) (isupper(c) || islower(c))

#define iscntrl(c) (((c) < (0x20)) || (c == 0x7f))

#define isgraph(c) (((c) - 0x21) < (0x5e))

#define isdigit(c) ((c) >= '0' && (c) <= '9')

#define islower(c) ((c) >= 'a' && (c) <= 'z')

#define isprint(c) ((c) >= ' ' && (c) <= '~')

#define ispunct(c) (isgraph(c) && !(isalnum(c)))

#define isspace(c) ((c) == ' ' || ((c) >= '\t' && (c) <= '\r'))

#define isupper(c) ((c) >= 'A' && (c) <= 'Z')

#define isxdigit(c) (isdigit(c)                    \
                     || ((c) >= 'A' && (c) <= 'F') \
                     || ((c) >= 'a' && (c) <= 'f'))

//==============================================================================
// Character conversion
//==============================================================================

#define tolower(c) ((c) + 0x20 * (((c) >= 'A') && ((c) <= 'Z')))

#define toupper(c) ((c) - 0x20 * (((c) >= 'a') && ((c) <= 'z')))

//==============================================================================
// Extra
//==============================================================================

#define isascii(c) ((unsigned)(c) <= 0x7F)

#define toascii(c) ((unsigned)(c) & 0x7F)

#endif
