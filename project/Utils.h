#ifndef __UTILS_H__
#define __UTILS_H__

#include "Hardware.h"

#include <stdint.h>
#include <stdbool.h>



//
// DS helper macros and function
//

#define ATTR_ITCM __attribute__((section(".itcm"),long_call))
#define ATTR_DTCM __attribute__((section(".dtcm")))

static inline int MakeRGB15(int r,int g,int b) { return 0x8000|(b<<10)|(g<<5)|r; }

int MakeHSV(int h,int s,int v);



//
// DS hardware state handling function
//

typedef struct DisplayRegisters
{
	uint16_t a[32],b[32];
} DisplayRegisters;

void SaveDisplayRegisters(DisplayRegisters *regs);
void RestoreDisplayRegisters(DisplayRegisters *regs);

typedef struct Palettes
{
	uint16_t a[256],b[256];
} Palettes;

void SavePalettes(Palettes *pals);
void RestorePalettes(Palettes *pals);

uint32_t SaveAndSetMemoryBanks(int bank_a,int bank_b,int bank_c,int bank_d);
void RestoreMemoryBanks(uint32_t savedbanks);

//
// DS hardware tricks
//

void SetupEngineBSpriteScreen();


//
// 20.12 fixed-point operations
//

static inline int32_t FloatToFixed(float val) { return val*4096.0f; }
static inline int32_t IntToFixed(int val) { return val<<12; }
static inline int32_t IntToFixedPlusHalf(int val) { return (val<<12)+0x800; }

static inline int FixedToInt(int32_t val) { return val>>12; }
static inline int FixedToRoundedInt(int32_t val) { return (val+0x800)>>12; }

#define F(x) ((int32_t)((x)*4096))

//static inline int32_t FixedMul(int32_t a,int32_t b) { return ((int64_t)a*(int64_t)b)>>16; }

static inline int imin(int a,int b) { return a<b?a:b; }
static inline int imax(int a,int b) { return a>b?a:b; }
static inline int iabs(int a) { return a<0?-a:a; }
static inline int isign(int a) { return a>0?1:a<0?-1:0; }

static inline int32_t imul(int32_t a,int32_t b) { return ((int64_t)a*(int64_t)b)>>12; }
static inline int32_t imul3(int32_t a,int32_t b,int32_t c) { return imul(imul(a,b),c); }
static inline int32_t imul4(int32_t a,int32_t b,int32_t c,int32_t d) { return imul(imul(imul(a,b),c),d); }

static inline int64_t imul64(int64_t a,int64_t b) { return (a*b)>>12; }

static inline int32_t idiv(int32_t num,int32_t den)
{
	DIVCNT=DIVCNT_MODE_64_32;
	DIV_NUMER_64=((int64_t)num)<<12;
	DIV_DENOM_32=den;

	while(DIVCNT&DIVCNT_BUSY);

	return DIV_RESULT_32;
}

static inline int64_t idiv64(int64_t num,int64_t den)
{
	DIVCNT=DIVCNT_MODE_64_64;
	DIV_NUMER_64=((int64_t)num)<<12;
	DIV_DENOM_64=den;

	while(DIVCNT&DIVCNT_BUSY);

	return DIV_RESULT_64;
}

static inline int32_t isqrt(int32_t val)
{
	SQRTCNT=SQRTCNT_MODE_64;
	SQRT_PARAM_64=((int64_t)val)<<12;

	while(SQRTCNT&SQRTCNT_BUSY);

	return SQRT_RESULT;
}

static inline int64_t isqrt64(int64_t val)
{
	SQRTCNT=SQRTCNT_MODE_64;
	SQRT_PARAM_64=val<<12;

	while(SQRTCNT&SQRTCNT_BUSY);

	return SQRT_RESULT;
}

static inline int32_t ifloor(int a) { return a&~0xfff; }
static inline int32_t ifrac(int a) { return a&0xfff; }

int32_t isin(int a);
static inline int32_t icos(int a) { return isin(a+1024); }
static inline int32_t itan(int a) { return idiv(isin(a),icos(a)); } // TODO: use a table
static inline int32_t iangle(int degrees) { return degrees*4096.0f/360.0f; }

static inline void icross(int32_t *a,int32_t *b,int32_t *res)
{
	res[0]=imul(a[1],b[2])-imul(b[1],a[2]);
	res[1]=imul(a[2],b[0])-imul(b[2],a[0]);
	res[2]=imul(a[0],b[1])-imul(b[0],a[1]);
}

static inline int32_t idot(int32_t *a,int32_t *b)
{
	return imul(a[0],b[0])+imul(a[1],b[1])+imul(a[2],b[2]);
}

static inline int32_t imag2(int32_t *v) { return imul(v[0],v[0])+imul(v[1],v[1])+imul(v[2],v[2]); }

static inline int32_t imag(int32_t *v) { return isqrt(imag2(v)); }

static inline void inormalize(int32_t *v)
{
	int32_t mag=imag(v);

	v[0]=idiv(v[0],mag);
	v[1]=idiv(v[1],mag);
	v[2]=idiv(v[2],mag);
}




//
// Bitwise operations
//

static inline int CountBits32(uint32_t val)
{
	val=(val&0x55555555)+((val&0xaaaaaaaa)>>1);
	val=(val&0x33333333)+((val&0xcccccccc)>>2);
	val=(val&0x0f0f0f0f)+((val&0xf0f0f0f0)>>4);
	val=(val&0x00ff00ff)+((val&0xff00ff00)>>8);
	val=(val&0x0000ffff)+((val&0xffff0000)>>16);
	return val;
}

static inline int CountBits16(uint16_t val)
{
	val=(val&0x5555)+((val&0xaaaa)>>1);
	val=(val&0x3333)+((val&0xcccc)>>2);
	val=(val&0x0f0f)+((val&0xf0f0)>>4);
	val=(val&0x00ff)+((val&0xff00)>>8);
	return val;
}

static inline int CountBits8(uint8_t val)
{
	val=(val&0x55)+((val&0xaa)>>1);
	val=(val&0x33)+((val&0xcc)>>2);
	val=(val&0x0f)+((val&0xf0)>>4);
	return val;
}

static inline uint32_t ReverseBits32(uint32_t val)
{
	val=((val>>1)&0x55555555)|((val<<1)&0xaaaaaaaa);
	val=((val>>2)&0x33333333)|((val<<2)&0xcccccccc);
	val=((val>>4)&0x0f0f0f0f)|((val<<4)&0xf0f0f0f0);
	val=((val>>8)&0x00ff00ff)|((val<<8)&0xff00ff00);
	val=((val>>16)&0x0000ffff)|((val<<16)&0xffff0000);
	return val;
}

static inline uint16_t ReverseBits16(uint16_t val)
{
	val=((val>>1)&0x5555)|((val<<1)&0xaaaa);
	val=((val>>2)&0x3333)|((val<<2)&0xcccc);
	val=((val>>4)&0x0f0f)|((val<<4)&0xf0f0);
	val=((val>>8)&0x00ff)|((val<<8)&0xff00);
	return val;
}

static inline uint8_t ReverseBits8(uint8_t val)
{
	val=((val>>1)&0x55)|((val<<1)&0xaa);
	val=((val>>2)&0x33)|((val<<2)&0xcc);
	val=((val>>4)&0x0f)|((val<<4)&0xf0);
	return val;
}

static int LowestBitSet32(uint32_t val)
{
	if(val==0) return -1;
	return CountBits32(val^val-1)-1;
}

static int LowestBitSet16(uint16_t val)
{
	if(val==0) return -1;
	return CountBits16(val^val-1)-1;
}

static int LowestBitSet8(uint8_t val)
{
	if(val==0) return -1;
	return CountBits8(val^val-1)-1;
}



//
// Random numbers
//

uint32_t Random();

#endif
