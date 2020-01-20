#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifdef FloatToFixed
#undef FloatToFixed
#undef IntToFixed
#undef FixedToFloat
#undef FixedToInt
#endif


//
// 20.12 fixed-point operations
//

#define F(val) ((val)*4096)

#define FixSqrt2 5793
#define FixInvSqrt2 2896
#define FixSinPiDiv4 FixInvSqrt2
#define FixCosPiDiv4 FixInvSqrt2
#define FixSinPiDiv8 1567
#define FixCosPiDiv8 3784

static inline int32_t FloatToFixed(float val) { return val*4096.0f; }
static inline int32_t IntToFixed(int val) { return val<<12; }
static inline int32_t IntToFixedPlusHalf(int val) { return (val<<12)+0x800; }

static inline float FixedToFloat(int32_t val) { return (float)val/4096.0; }
static inline int32_t FixedToInt(int32_t val) { return val>>12; }
static inline int32_t FixedToRoundedInt(int32_t val) { return (val+0x800)>>12; }

static inline int32_t imin(int32_t a,int32_t b) { return a<b?a:b; }
static inline int32_t imax(int32_t a,int32_t b) { return a>b?a:b; }
static inline int32_t iabs(int32_t a) { return a<0?-a:a; }
static inline int32_t isign(int32_t a) { return a>0?1:a<0?-1:0; }

static inline int64_t imul64(int64_t a, int64_t b) { return (a*b)>>12; }
static inline int32_t imul(int32_t a, int32_t b) { return imul64(a,b); }

static inline int64_t idiv64(int64_t num,int64_t den) { return (num<<12)/den; }
static inline int32_t idiv(int32_t num,int32_t den) { return idiv64(num,den); }

static inline int64_t isq64(int64_t val) { return imul64(val,val); }
static inline int32_t isq(int32_t val) { return imul(val,val); }

static inline int64_t isqrt64(int64_t val) { return sqrt(((double)val)*4096.0); }
static inline int32_t isqrt(int32_t val) { return sqrt(((double)val)*4096.0); }

static inline int32_t ifloor(int a) { return a&~0xfff; }
static inline int32_t ifrac(int a) { return a&0xfff; }

int32_t isin(int a);
static inline int32_t icos(int a) { return isin(a+1024); }
static inline int32_t itan(int a) { return idiv(isin(a),icos(a)); } // TODO: use a table
static inline int32_t idegrees(int degrees) { return degrees*4096.0f/360.0f; }
static inline int32_t iradians(float radians) { return radians*4096.0f/2/M_PI; }

static inline int32_t ilerp(int32_t a,int32_t b,int32_t t)
{
	return a+imul(b-a,t);
}

/*static inline int32_t islerp(int32_t a,int32_t b,int32_t t)
{
	return a;
}*/

#endif
