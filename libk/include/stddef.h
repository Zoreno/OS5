/**
 * @file    stddef.h
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   LIBK stddef.h standard header
 */

#ifndef _LIBK_STDDEF_H
#define _LIBK_STDDEF_H

#include <_size_t.h>
#include <_ptrdiff_t.h>
#include <_null.h>

/**
 * Offset of a member in a struct in bytes
 */
#define offsetof(type, member) ((size_t)((char *)&(((type *)0)->member) - (char *)0))

#endif
