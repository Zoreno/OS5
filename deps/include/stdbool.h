/**
 * @file    stdbool.h
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   LIBK stdbool.h Standard Header
 */

#ifndef _LIBK_STDBOOL_H
#define _LIBK_STDBOOL_H

#define USE_BUILT_IN_BOOL 1

#define true 1
#define false 0

#if USE_BUILT_IN_BOOL 1
#define bool _Bool
#else
#define bool int
#endif

#endif
