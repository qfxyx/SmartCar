/*****************************************************

   math.h - ANSI-C library: mathematical functions
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_MATH_
#define _H_MATH_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NO_MATH_PROTOTYPES__
/*****************************************************************************/
/* near functions                                                            */
/*****************************************************************************/

#ifdef __XGATE__	 /* IEEE32 only */

extern double frexp   (double x,int *exp);
  /* Split x into mantissa (return value) and exponent. The mantissa always is in the
     interval 0.5 > m <= 1.0, except if x == 0.0: in this case, m = 0.0 and the expon-
     ent exp = 0. */

extern double ldexp   (double x, int exp);
  /* Calculate x * (2**exp) */

extern double modf    (double x, double *int_part);
  /* Split x into integral and fractional part (return value). */

#define frexpf  frexp
#define ldexpf  ldexp
#define modff   modf

#else

#include "push.sgm"
#include "non_bank.sgm"

extern double NEAR frexp   (double x,int *exp);
  /* Split x into mantissa (return value) and exponent. The mantissa always is in the
     interval 0.5 > m <= 1.0, except if x == 0.0: in this case, m = 0.0 and the expon-
     ent exp = 0. */

extern double NEAR ldexp   (double x, int exp);
  /* Calculate x * (2**exp) */

extern double NEAR modf    (double x, double *int_part);
  /* Split x into integral and fractional part (return value). */

extern float NEAR frexpf   (float x,int *exp);
  /* Split x into mantissa (return value) and exponent. The mantissa always is in the
     interval 0.5 > m <= 1.0, except if x == 0.0: in this case, m = 0.0 and the expon-
     ent exp = 0. */

extern float NEAR ldexpf   (float x, int exp);
  /* Calculate x * (2**exp) */

extern float NEAR modff    (float x, float *int_part);
  /* Split x into integral and fractional part (return value). */
  
#endif  

/*****************************************************************************/
/* far functions                                                             */
/*****************************************************************************/

#include "default.sgm"
#include "pop.sgm"
#endif

#ifndef __DOUBLE_IS_DSP__
  #include <ieeemath.h>
#ifdef __XGATE__
  #define HUGE_VAL  x_infinity.f
#else  
  #define HUGE_VAL  infinity.f
#endif  
  #define HUGE_VALF infinityf.f
#else
  #define HUGE_VAL  0.9999695E+9863
  #define HUGE_VALF 0.9999695E+9863
#endif

/* Constants */
#define _M_PI      3.14159265358979323846   /* pi         */
#define _M_1PI     0.31830988618379067154   /* 1 / pi     */
#define _M_2PI     6.28318530717958647692   /* 2 * pi     */
#define _M_PI2     1.57079632679489661923   /* pi / 2     */
#define _M_S1_2    0.70710678118654752440   /* sqrt (0.5) */
#define _M_LOGE    0.43429448190325182765   /* log10 (e)  */

#define _M_EPS     1.053671213e-8
#define _M_EXP_MAX 709.7877

#ifndef __NO_MATH_PROTOTYPES__

/**** Trigonometric functions */

extern double cos     (double x);
extern double cosh    (double x);
extern double sin     (double x);
extern double sinh    (double x);
extern double tan     (double x);
extern double tanh    (double x);

/**** Inverse trigonometric functions */

extern double asin(double x);
extern double acos(double x);

extern double atan    (double x);
extern double atan2   (double y,double x);  /* atan (y/x) */

/**** Exponential and logarithmic functions */

extern double log10   (double x);           /* logarithm of base 10       */

extern double exp     (double x);           /* e**x */
extern double log     (double x);           /* natural logarithm (base e) */

/**** Square root */

extern double pow     (double x, double y);   /* x**y */
extern double sqrt    (double x);

/**** Other functions */

extern double ceil    (double x);             /* smallest integral number >= x */
extern double floor   (double x);             /* largest integral number <= x  */

extern double fabs    (double x);             /* absolute value of x */
extern double fmod   (double x, double y);
   /* doubleing point remainder */

/**** System internal functions */

extern double sincos  (double x, int sgn, int flg);
extern double sncsh   (double y, int flg);
extern double sqrt_r (double x);
extern double pow_i  (double x, int y);
extern double exp_r  (double x);
extern double log_r  (double x);

/*****************************************************************************/
/* float routines                                                            */
/*****************************************************************************/

/**** Trigonometric functions */

extern float cosf     (float x);
extern float coshf    (float x);
extern float sinf     (float x);
extern float sinhf    (float x);
extern float tanf     (float x);
extern float tanhf    (float x);

/**** Inverse trigonometric functions */

extern float asinf(float x);
extern float acosf(float x);

extern float atanf    (float x);
extern float atan2f   (float y,float x);    /* atan (y/x) */

/**** Exponential and logarithmic functions */

extern float log10f   (float x);           /* logarithm of base 10       */

extern float expf     (float x);           /* e**x */
extern float logf     (float x);           /* natural logarithm (base e) */

/**** Square root */

extern float powf     (float x, float y);   /* x**y */
extern float sqrtf    (float x);

/**** Other functions */

extern float ceilf    (float x);             /* smallest integral number >= x */
extern float floorf   (float x);             /* largest integral number <= x  */

extern float fabsf    (float x);             /* absolute value of x */
extern float fmodf    (float x, float y);
   /* floating point remainder */

/**** System internal functions */

extern float sincosf  (float x, int sgn, int flg);
extern float sncshf   (float y, int flg);
extern float sqrtf_r (float x);
extern float powf_i  (float x, long y);
extern float expf_r  (float x);
extern float logf_r  (float x);

#endif

#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end math.h */
