/* math.h --- 
 * 
 * Filename: math.h
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Tue Feb  6 21:14:22 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:41:39 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 11
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Code: */




/**
 * @file    math.h
 * @author  Joakim Bertils
 * @date    2017-09-23
 * @brief   LIBK math.h Standard Header
 */

//TODO: Comment doxygen
//TODO: Implement all math functions
//TODO: Start with complex functions
//TODO: Start with fenv
//TODO: Start with type generic math (tgmath.h)

#ifndef _LIBK_MATH_H
#define _LIBK_MATH_H

#include <stdint.h>

//==============================================================================
// Definitions
//==============================================================================

/**
 * Set to one if the built in value of @HUGE_VAL is to be used.
 */
#define HAVE_BUILTIN_HUGE_VAL 1

/**
 * Set to one if the built in value of @HUGE_VALF is to be used.
 */
#define HAVE_BUILTIN_HUGE_VALF 1

/**
 * Set to one if the built in value of @HUGE_VALL is to be used.
 */
#define HAVE_BUILTIN_HUGE_VALL 1

/**
 * Set to one if the built in value of @INFINITY is to be used.
 */
#define HAVE_BUILTIN_INFINITY 1

/**
 * Set to one if the built in value of @NAN is to be used.
 */
#define HAVE_BUILTIN_NAN 1

/**
 * Set to one if the definitions of @SNAN, @SNANF and @SNANL is to be used.
 */
#define HAVE_BUILTIN_NANS 1

/**
 * A double number representing a huge value.
 */
#if HAVE_BUILTIN_HUGE_VAL
#define HUGE_VAL (__builtin_huge_val ())
#else
#define HUGE_VAL (1e10000)
#endif

/**
 * A float number representing a huge value.
 */
#if HAVE_BUILTIN_HUGE_VALF
#define HUGE_VALF (__builtin_huge_valf ())
#else
#define HUGE_VALF (1e10000f)
#endif

/**
 * A long double number representing a huge value.
 */
#if HAVE_BUILTIN_HUGE_VALL
#define HUGE_VALL (__builtin_huge_vall ())
#else
#define HUGE_VALL (1e10000L)
#endif

/**
 * A float number representing infinity.
 *
 * @TODO Create for double and long double.
 */
#if HAVE_BUILTIN_INFINITY
#define INFINITY (__builtin_inff ())
#else
#define INFINITY HUGE_VALF
#endif

/**
 * A float number representing nan (not a number).
 * 
 * @TODO Create for double and long double.
 */
#if HAVE_BUILTIN_NAN
#define NAN (__builtin_nanf (""))
#else
#define NAN (0.0f/0.0f)
#endif

/**
 * Macro expanding to a nan value.
 * 
 * @TODO Implement non-builtin functions.
 * @TODO Create NANS family macros.
 */
#if HAVE_BUILTIN_NANS
#define SNANF (__builtin_nansf (""))
#define SNAN (__builtin_nans (""))
#define SNANL (__builtin_nansl (""))
#else
#define SNANF (__nansf (""))
#define SNAN (__nans (""))
#define SNANL (__nansl (""))
#endif

//==============================================================================
// Evaluation mode
//==============================================================================


/**
 * Sets the current evaluation mode. This will determine how different types are
 * handled.
 */
#define FLOAT_EVAL_MODE 2

#if FLOAT_EVAL_MODE == 0

/**
 * Eval mode 0 float type.
 */
typedef float float_t;

/**
 * Eval mode 0 double type.
 */
typedef double double_t;


/**
 * Eval mode 0 long double type.
 */
typedef long double ldouble_t;

#elif FLOAT_EVAL_MODE == 1

/**
 * Eval mode 1 float type.
 */
typedef double float_t;

/**
 * Eval mode 1 double type.
 */
typedef double float_t;

/**
 * Eval mode 1 long double type.
 */
typedef long double ldouble_t;

#elif FLOAT_EVAL_MODE == 2

/**
 * Eval mode 2 float type.
 */
typedef long double float_t;

/**
 * Eval mode 2 double type.
 */
typedef long double double_t;

/**
 * Eval mode 2 long double type.
 */
typedef long double ldouble_t;

#endif

/**
 * If logb should return min on on 0
 */
#define _LOGB0_IS_MIN 0

/**
 * If logb should return min on on NAN
 */
#define _LOGBNAN_IS_MIN 0

/**
 * Word Size 
 */
#define __WORDSIZE 32

/**
 * Value returned by ilogb(0.0)
 */
#if _LOGB0_IS_MIN
#define FP_ILOGB0     (-2147483647 - 1)
#else
#define FP_ILOGB0     (-2147483647)
#endif

/**
 * Value returned by ilogb(NAN)
 */
#if _LOGBNAN_IS_MIN
#define FP_ILOGBNAN   (-2147483647 - 1)
#else
#define FP_ILOGBNAN   2147483647
#endif

/**
 * Maximum value of long
 */
#if __WORDSIZE == 32
#define __FP_LONG_MAX 0x7fffffffL
#else
#define __FP_LONG_MAX 0x7fffffffffffffffL
#endif

/**
 * Value returned by llogb(0.0)
 */
#if _LOGB0_IS_MIN
#define FP_LLOGB0     (-__FP_LONG_MAX - 1)
#else
#define FP_LLOGB0     (-__FP_LONG_MAX)
#endif

/**
 * Value returned by llogb(NAN)
 */
#if _LOGBNAN_IS_MIN
#define FP_LLOGBNAN   (-__FP_LONG_MAX - 1)
#else
#define FP_LLOGBNAN   __FP_LONG_MAX
#endif
//==============================================================================
// Number classification
//==============================================================================

/**
 * Number categories returned by fpclassify
 */
enum FP_CATEGORIES
{
    /**
     * NAN Category
     */
    FP_NAN = 0,

    /**
     * Infinite Category
     */
    FP_INFINITE = 1,

    /**
     * Zero Category
     */
    FP_ZERO = 2,

    /**
     * Subnormal Category
     */
    FP_SUBNORMAL = 3,
    
    /**
     * Normal Category
     */
    FP_NORMAL = 4
};

/**
 * @brief Categorizes a number.
 * @param x Number to categorize.
 * @return Number from @FP_CATEGORIES describing the number.
 */
#define fpclassify(x) (__builtin_fpclassify(FP_NAN,         \
                                            FP_INFINITE,    \
                                            FP_NORMAL,      \
                                            FP_SUBNORMAL,   \
                                            FP_ZERO,        \
                                            x))

/**
 * @brief Checks the sign of the number.
 * @param x Input number.
 * @return Non-zero if number is negative.
 */
#define signbit(x) (__builtin_signbit (x))

/**
 * @brief Checks if the number is finite.
 * @param x Input number.
 * @return Non-zero if number is not Inf or NaN.
 */
#define isfinite(x) (__builtin_isfinite (x))

/**
 * @brief Checks if the number is normal.
 * @param x Input number.
 * @return Zero if number is zero, subnormal, Inf or NaN.
 */
#define isnormal(x) (__builtin_isnormal (x))

/**
 * @brief Checks if number is NaN.
 * @param x Input number.
 * @return Non-zero if number is NaN.
 */
#define isnan(x) (__builtin_isnan (x))

/**
 * @brief Checks if number is infinite.
 * @param x Input number.
 * @return Non-zero if true.
 */
#define isinf(x) (__builtin_isinf_sign (x))

/**
 * @brief Checks if number is canonical.
 * @param x Input number.
 * @return Non-zero if true.
 */
#define iscanonical(x) ((void) (__typeof (x)) (x), 1)

/**
 * @brief Checks if number is signaling NaN.
 * @param x Input number.
 * @return Non-zero if true.
 */
#define issignaling(x) (sizeof (x) == sizeof(float) ? __issignalingf (x) : __issignaling (x))

/**
 * @brief Checks if number is subnormal.
 * @param x Input number.
 * @return Non-zero if true.
 */
#define issubnormal(x) (fpclassify(x) == FP_SUBNORMAL)

/**
 * @brief Checks if number is zero.
 * @param x Input number.
 * @return Non-zero if true.
 */
#define iszero(x) (fpclassify(x) == FP_ZERO)

/**
 * @brief Returns nonzero if x is greater than y
 * @param x First value
 * @param y Second value
 * @return Nonzero if true
 */
#define isgreater(x,y)       (__builtin_isgreater(x,y))

/**
 * @brief Returns nonzero if x is greater than or equal to y
 * @param x First value
 * @param y Second value
 * @return Nonzero if true
 */
#define isgreaterequal(x, y) (__builtin_isgreaterequal(x, y))
    
/**
 * @brief Returns nonzero if x is less than y
 * @param x First value
 * @param y Second value
 * @return Nonzero if true
 */
#define isless(x, y)         (__builtin_isless(x, y))
 
/**
 * @brief Returns nonzero if x is less than or equal to y
 * @param x First value
 * @param y Second value
 * @return Nonzero if true
 */
#define islessequal(x, y)    (__builtin_islessequal(x, y))
 
/**
 * @brief Returns nonzero if x is less than or greater than y
 * @param x First value
 * @param y Second value
 * @return Nonzero if true
 */
#define islessgreater(x, y)  (__builtin_islessgreater(x, y))
 
/**
 * @brief Returns nonzero if u and v are unordered
 * @param u First value
 * @param v Second value
 * @return Nonzero if true
 */
#define isunordered(u, v)    (__builtin_isunordered(u, v))

//==============================================================================
// Mathematical constants
//==============================================================================

/**
 * Value of e.
 */
#define M_E         2.7182818284590452354   /* e */

/**
 * Value of log_2(e).
 */
#define M_LOG2E     1.4426950408889634074   /* log_2 e */

/**
 * Value of log_10(e).
 */
#define M_LOG10E    0.43429448190325182765  /* log_10 e */

/**
 * Value of log_e(2).
 */
#define M_LN2       0.69314718055994530942  /* log_e 2 */

/**
 * Value of log_e(10).
 */
#define M_LN10      2.30258509299404568402  /* log_e 10 */

/**
 * Value of pi.
 */
#define M_PI        3.14159265358979323846  /* pi */

/**
 * Value of pi/2.
 */
#define M_PI_2      1.57079632679489661923  /* pi/2 */

/**
 * Value of pi/4.
 */
#define M_PI_4      0.78539816339744830962  /* pi/4 */

/**
 * Value of 1/pi.
 */
#define M_1_PI      0.31830988618379067154  /* 1/pi */

/**
 * Value of 2/pi.
 */
#define M_2_PI      0.63661977236758134308  /* 2/pi */

/**
 * Value of 2/sqrt(pi).
 */
#define M_2_SQRTPI  1.12837916709551257390  /* 2/sqrt(pi) */

/**
 * Value of sqrt(2).
 */
#define M_SQRT2     1.41421356237309504880  /* sqrt(2) */

/**
 * Value of 1/sqrt(2).
 */
#define M_SQRT1_2   0.70710678118654752440  /* 1/sqrt(2) */

/**
 * Long double value of e.
 */
#define M_El        2.718281828459045235360287471352662498L /* e */

/**
 * Long double value of log_2(e).
 */
#define M_LOG2El    1.442695040888963407359924681001892137L /* log_2 e */

/**
 * Long double value of log_10(e).
 */
#define M_LOG10El   0.434294481903251827651128918916605082L /* log_10 e */


/**
 * Long double value of log_e(2).
 */
#define M_LN2l      0.693147180559945309417232121458176568L /* log_e 2 */

/**
 * Long double value of log_e(10).
 */
#define M_LN10l     2.302585092994045684017991454684364208L /* log_e 10 */

/**
 * Long double value of pi.
 */
#define M_PIl       3.141592653589793238462643383279502884L /* pi */

/**
 * Long double value of pi/2.
 */
#define M_PI_2l     1.570796326794896619231321691639751442L /* pi/2 */

/**
 * Long double value of pi/4.
 */
#define M_PI_4l     0.785398163397448309615660845819875721L /* pi/4 */

/**
 * Long double value of 1/pi.
 */
#define M_1_PIl     0.318309886183790671537767526745028724L /* 1/pi */

/**
 * Long double value of 2/pi.
 */
#define M_2_PIl     0.636619772367581343075535053490057448L /* 2/pi */

/**
 * Long double value of 2/sqrt(pi).
 */
#define M_2_SQRTPIl 1.128379167095512573896158903121545172L /* 2/sqrt(pi) */

/**
 * Long double value of sqrt(2).
 */
#define M_SQRT2l    1.414213562373095048801688724209698079L /* sqrt(2) */

/**
 * Long double value of 1/sqrt(2).
 */
#define M_SQRT1_2l  0.707106781186547524400844362104849039L /* 1/sqrt(2) */

//==============================================================================
// Helper functions
//==============================================================================

/**
 * @brief Extracts the bytes from a float value.
 * @param res Pointer to place to store val.
 * @param x Float value to convert.
 */
void extract_word(uint32_t* res, float x);

/**
 * @brief Extracts the bytes from a double
 * @param hi Pointer to place to store high bytes of value.
 * @param lo Pointer to place to store low bytes of value.
 * @param x Double value to convert.
 */
void extract_words_double(uint32_t* hi, uint32_t* lo, double x);

/**
 * @brief Extracts only the high bytes from a double.
 * @param hi Pointer to place to store high bytes of value.
 * @param x Double value to convert.
 */
void extract_high_word_double(uint32_t* hi, double x);

/**
 * @brief Extracts only the low bytes from a double.
 * @param lo Pointer to place to store low bytes of value.
 * @param x Double value to convert.
 */
void extract_low_word_double(uint32_t* lo, double x);

/**
 * @brief Checks if value is signaling NaN.
 * @param x Value to check.
 * @return Non-zero if true.
 */
int __issignalingf(float x);

/**
 * @brief Checks if value is signaling NaN.
 * @param x Value to check.
 * @return Non-zero if true.
 */
int __issignaling(double x);
// int __issignalingl(long double x);

//==============================================================================
// Mathematical functions for double, float and long double arguments
// respectively.
//==============================================================================

//fmod
//fmodf
//fmodl

//remainder
//remainderf
//remainderl

//remquo
//remquof
//remquoln

//fma
//fmaf
//fmal

//double fmax(double x, double y);

/**
 * @brief Calculates the maximum of the arguments.
 * @param x First value.
 * @param y Second value.
 * @return The maximum of x and y.
 */
float fmaxf(float x, float y);
//long double fmaxl(long double x, long double y);

//fmin
//fminf
//fminl

//fdim
//fdimf
//fdiml

//nan
//nanf
//nanl

//exp
//expf
//expl

//exp2
//exp2f
//exp2l

//expm1
//expm1f
//expm1l

//log
//logf
//logl

//log2
//log2f
//log2l

//log10
//log10f
//log10l

//log1p
//log1pf
//log1pl

//ilog
//ilogf
//ilogl

//logb
//logbf
//logbl

//sqrt
//sqrtf
//sqrtl

//cbrt
//cbrtf
//cbrtl

//hypot
//hypotf
//hypotl

//pow
//powf
//powl

//sin
//sinf
//sinl

//cos
//cosf
//cosl

//sincos
//sincosf
//sincosl

//tan
//tanf
//tanl

//asin
//asinf
//asinl

//acos
//acosf
//acosl

//atan
//atanf
//atanl

//atan2
//atan2f
//atan2l

//sinh
//sinhf
//sinhl

//cosh
//coshf
//coshl

//tanh
//tanhf
//tanhl

//asinh
//asinhf
//asinhl

//acosh
//acoshf
//acoshl

//atanh
//atanhf
//atanhl

//erf
//erff
//erfl

//erfc
//erfcf
//erfcl

//lgamma
//lgammaf
//lgammal

//tgamma
//tgammaf
//tgammal

//ceil
//ceilf
//ceill

//floor
//floorf
//floorl

//trunc
//truncf
//truncl

//round
//roundf
//roundl

//lround
//lroundf
//lroundl

//llround
//llroundf
//llroundf

//nearbyint
//nearbyintf
//nearbyintl

//rint
//rintf
//rintl

//lrint
//lrintf
//lrintl

//llrint
//llrintf
//llrintl

//frexp
//frexpf
//frexpl

//ldexp
//ldexpf
//ldexpl

//modf
//modff
//modfl

//scalbn
//scalbnf
//scalbnl

//scalbln
//scalblnf
//scalblnl

//nextafter
//nextafterf
//nextafterl

//nexttoward
//nexttowardf
//nexttowardl

//copysign
//copysignf
//copysignl

//==============================================================================
// End of file
//==============================================================================

#endif

/* math.h ends here */
