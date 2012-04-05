#include "ARM.h"

#include <math.h>

void ClaimWRAM()
{
	WRAMCNT=WRAMCNT_ARM9_ALL;
	asm volatile (
	"	mcr p15,0,%0,C6,C2,0\n" // Configure region 2 as 16 MB from 0x3000000
	"	mrc p15,0,r0,C5,C0,0\n"
	"	orr	r0,r0,#0x30\n"
	"	mcr p15,0,r0,C5,C0,0\n" // Enable data read/write for region 2
	::"r" (0x300002f):"r2");
}

void ATTR_ITCM Decay(uint16_t *screenbase,int lines)
{
/*	uint32_t *ptr=(uint32_t *)screenbase;

	for(int i=0;i<256*192/4;i++)
	{
		uint32_t val=*ptr;

//		uint32_t mask=val&0x0f0f0f0f;
//		mask|=mask<<1;
//		mask|=mask>>1;
//		mask|=mask<<2;
//		mask|=mask>>2;
//		val-=mask&0x01010101;
//		mask=mask<<4;
//		mask|=0x0f0f0f0f;
//		val&=mask;

		uint32_t mask=val;
		mask|=mask>>1;
		mask|=mask>>2;
		mask&=0x01010101;
		val-=mask;
		mask*=0xff;
		val&=mask;

//		uint32_t newval=val-0x01010101;
//		uint32_t mask=(val^newval)&0x10101010;
//		newval+=mask>>4;
//		val=newval;

		*ptr++=val;
	}
*/

	register uint32_t r0 asm("r0")=(uint32_t)screenbase;
	register uint32_t r1 asm("r1")=lines*256/4/8;
	register uint32_t r2 asm("r2")=0x01010101;

	asm volatile (
	".decayloop:					\n"
/*	"	ldr		r4,[r0]				\n"
	"	orr		r3,r4,r4,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r4,r4,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r4,r4,r3			\n"
	"	str		r4,[r0],#4			\n"*/

	"	ldm		r0,{r4-r11}			\n"

	"	orr		r3,r4,r4,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r4,r4,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r4,r4,r3			\n"

	"	orr		r3,r5,r5,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r5,r5,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r5,r5,r3			\n"

	"	orr		r3,r6,r6,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r6,r6,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r6,r6,r3			\n"

	"	orr		r3,r7,r7,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r7,r7,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r7,r7,r3			\n"

	"	orr		r3,r8,r8,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r8,r8,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r8,r8,r3			\n"

	"	orr		r3,r9,r9,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r9,r9,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r9,r9,r3			\n"

	"	orr		r3,r10,r10,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r10,r10,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r10,r10,r3			\n"

	"	orr		r3,r11,r11,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r11,r11,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r11,r11,r3			\n"

	"	stmia	r0!,{r4-r11}		\n"

	"	subs	r1,r1,#1			\n"
	"	bne		.decayloop			\n"
	:
	:"r" (r0),"r" (r1),"r" (r2)
	:"r3","r4","r5","r6","r7","r8","r9","r10","r11"
	);


/*	"	ldmia		r0!,{r5,r6,r7,r8,r9,r10,r11,r12}	\n"

	"	ldr		r4,[r2,r5,lsr #16]	\n"
	"	and		r5,r5,r3			\n"
	"	ldrh	r5,[r2,r5]			\n"
	"	orr		r5,r5,r4,lsl #16	\n"

	"	ldr		r4,[r2,r6,lsr #16]	\n"
	"	and		r6,r6,r3			\n"
	"	ldrh	r6,[r2,r6]			\n"
	"	orr		r6,r6,r4,lsl #16	\n"

	"	ldr		r4,[r2,r7,lsr #16]	\n"
	"	and		r7,r7,r3			\n"
	"	ldrh	r7,[r2,r7]			\n"
	"	orr		r7,r7,r4,lsl #16	\n"

	"	ldr		r4,[r2,r8,lsr #16]	\n"
	"	and		r8,r8,r3			\n"
	"	ldrh	r8,[r2,r8]			\n"
	"	orr		r8,r8,r4,lsl #16	\n"

	"	ldr		r4,[r2,r9,lsr #16]	\n"
	"	and		r9,r9,r3			\n"
	"	ldrh	r9,[r2,r9]			\n"
	"	orr		r9,r9,r4,lsl #16	\n"

	"	ldr		r4,[r2,r10,lsr #16]	\n"
	"	and		r10,r10,r3			\n"
	"	ldrh	r10,[r2,r10]		\n"
	"	orr		r10,r10,r4,lsl #16	\n"

	"	ldr		r4,[r2,r11,lsr #16]	\n"
	"	and		r11,r11,r3			\n"
	"	ldrh	r11,[r2,r11]		\n"
	"	orr		r11,r11,r4,lsl #16	\n"

	"	ldr		r4,[r2,r12,lsr #16]	\n"
	"	and		r12,r12,r3			\n"
	"	ldrh	r12,[r2,r12]		\n"
	"	orr		r12,r12,r4,lsl #16	\n"

	"	stmia	r1!,{r5,r6,r7,r8,r9,r10,r11,r12}		\n"

	"	subs	r14,r14,#1			\n"
	"	bne		.tunnelloop			\n"*/

}



#define SAMPLES 4
#define WIDTH 128
#define HEIGHT 96

static inline void ATTR_ITCM WritePixel8(uint8_t *screen,int x,int y,int c)
{
	screen[y*WIDTH+x]=c;
/*	uint16_t val=screen[y*128+(x>>1)];
	if(x&1) val=(val&0x00ff)|(c<<8);
	else val=(val&0xff00)|(c);
	screen[y*128+(x>>1)]=val;*/
}

static inline int ATTR_ITCM ReadPixel8(uint8_t *screen,int x,int y)
{
	return screen[y*WIDTH+x];
/*	uint16_t val=screen[y*128+(x>>1)];
	if(x&1) return val>>8;
	else return val&0xff;*/
}

void ATTR_ITCM RenderBackgroundARM(int t,uint8_t *screen)
{
	uint32_t *ptr=(uint32_t *)screen;
	for(int i=0;i<WIDTH*HEIGHT/4;i++) *ptr++=0;

	for(int y=0;y<8;y++)
	for(int x=0;x<8;x++)
	{
		WritePixel8(screen,x+WIDTH/3,y+HEIGHT/3,255);
		WritePixel8(screen,x+2*WIDTH/3-8,y+HEIGHT/3,255);
		WritePixel8(screen,x+WIDTH/3,y+2*HEIGHT/3-8,255);
		WritePixel8(screen,x+2*WIDTH/3-8,y+2*HEIGHT/3-8,255);
	}
}



static inline void ATTR_ITCM RenderPixel(uint8_t *pixel,uint32_t *lookup)
{
	int sum=*pixel<<2+14;
	for(int i=0;i<SAMPLES;i++)
	{
		int val=*lookup++;
//		int16_t offs=val;
//		int xblend=(val>>16)&0xff;
//		int yblend=(val>>24)&0xff;
		int16_t offs=val>>16;
		int xblend=(val>>8)&0xff;
		int yblend=(val>>0)&0xff;

		sum+=(pixel[offs]*(128-xblend)+pixel[offs+1]*xblend)*(128-yblend)
		+(pixel[offs+128]*(128-xblend)+pixel[offs+129]*xblend)*yblend;
	}
	sum>>=2+14;
	if(sum>255) sum=255;
	*pixel=sum;
}

void ATTR_ITCM RenderRadialARM(int t,int cx,int cy,uint8_t *screen,uint16_t *vram,
uint32_t *lookup1,uint32_t *lookup2,uint32_t *lookup3,uint32_t *lookup4)
{
	#if 1

	register uint32_t r4 asm("r4"),r5 asm("r5"),r6 asm("r6");
	register uint32_t r7 asm("r7"),r8 asm("r8"),r9 asm("r9");

	// r0: sum
	// r1: val/yblend
	// r2: tmp
	// r3: xblend
	// r4: lookup
	// r5: pixel
	// r6: num_x
	// r7: num_y
	// r8: lookup_skip
	// r9: pixel_skip
	// r10: x_counter
	// r11: offspixel
	// r12: loadtmp
	// r14:

	#define ONE_LOOKUP \
	"	ldr		r1,[r4],#4			\n" \
	"	add		r11,r5,r1,asr #16	\n" \
	"	and		r3,r1,#0x00ff		\n" \
	"	and		r1,r1,#0xff00		\n" \
	"	mov		r1,r1,lsr #8		\n" \
	                                    \
	"	ldrb	r12,[r11,#129]		\n" \
	"	smulbb	r2,r12,r1			\n" \
	"	rsb		r1,r1,#128			\n" \
	"	ldrb	r12,[r11,#128]		\n" \
	"	smlabb	r2,r12,r1,r2		\n" \
	"	smlabb	r0,r2,r3,r0			\n" \
	"	rsb		r3,r3,#128			\n" \
	                                    \
	"	ldrb	r12,[r11,#0]		\n" \
	"	smulbb	r2,r12,r1			\n" \
	"	rsb		r1,r1,#128			\n" \
	"	ldrb	r12,[r11,#1]		\n" \
	"	smlabb	r2,r12,r1,r2		\n" \
	"	smlabb	r0,r2,r3,r0			\n"

	r4=(uint32_t)lookup1;
	r5=(uint32_t)&screen[cx-1+(cy-1)*128];
	r6=cx;
	r7=cy;
	r8=(WIDTH-cx)*SAMPLES*4;
	r9=-(WIDTH-cx);

	asm volatile(
	"yloop1:						\n"
	"	mov		r10,r6				\n"

	"xloop1:						\n"
	"	ldrb	r0,[r5]				\n"
	"	mov		r0,r0,lsl #16		\n"

	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP

	"	mov		r0,r0,lsr #16		\n"
	"	cmp		r0,#255				\n"
	"	movgt	r0,#255				\n"
	"	strb	r0,[r5],#-1			\n"

	"	subs	r10,r10,#1			\n"
	"	bne		xloop1				\n"

	"	add		r4,r4,r8			\n"
	"	add		r5,r5,r9			\n"
	"	subs	r7,r7,#1			\n"
	"	bne		yloop1				\n"

	:"=r" (r4),"=r" (r5),"=r" (r7)
	:"r" (r4),"r" (r5),"r" (r6),"r" (r7),"r" (r8),"r" (r9)
	:"r0","r1","r2","r3","r10","r11","r12","cc"
	);

	r4=(uint32_t)lookup2;
	r5=(uint32_t)&screen[cx+(cy-1)*128];
	r6=WIDTH-cx;
	r7=cy;
	r8=cx*SAMPLES*4;
	r9=cx-2*WIDTH;

	asm volatile(
	"yloop2:						\n"
	"	mov		r10,r6				\n"

	"xloop2:						\n"
	"	ldrb	r0,[r5]				\n"
	"	mov		r0,r0,lsl #16		\n"

	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP

	"	mov		r0,r0,lsr #16		\n"
	"	cmp		r0,#255				\n"
	"	movgt	r0,#255				\n"
	"	strb	r0,[r5],#1			\n"

	"	subs	r10,r10,#1			\n"
	"	bne		xloop2				\n"

	"	add		r4,r4,r8			\n"
	"	add		r5,r5,r9			\n"
	"	subs	r7,r7,#1			\n"
	"	bne		yloop2				\n"

	:"=r" (r4),"=r" (r5),"=r" (r7)
	:"r" (r4),"r" (r5),"r" (r6),"r" (r7),"r" (r8),"r" (r9)
	:"r0","r1","r2","r3","r10","r11","r12","cc"
	);

	r4=(uint32_t)lookup3;
	r5=(uint32_t)&screen[(cx-1)+cy*128];
	r6=cx;
	r7=HEIGHT-cy;
	r8=(WIDTH-cx)*SAMPLES*4;
	r9=cx+WIDTH;

	asm volatile(
	"yloop3:						\n"
	"	mov		r10,r6				\n"

	"xloop3:						\n"
	"	ldrb	r0,[r5]				\n"
	"	mov		r0,r0,lsl #16		\n"

	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP

	"	mov		r0,r0,lsr #16		\n"
	"	cmp		r0,#255				\n"
	"	movgt	r0,#255				\n"
	"	strb	r0,[r5],#-1			\n"

	"	subs	r10,r10,#1			\n"
	"	bne		xloop3				\n"

	"	add		r4,r4,r8			\n"
	"	add		r5,r5,r9			\n"
	"	subs	r7,r7,#1			\n"
	"	bne		yloop3				\n"

	:"=r" (r4),"=r" (r5),"=r" (r7)
	:"r" (r4),"r" (r5),"r" (r6),"r" (r7),"r" (r8),"r" (r9)
	:"r0","r1","r2","r3","r10","r11","r12","cc"
	);

	r4=(uint32_t)lookup4;
	r5=(uint32_t)&screen[cx+cy*128];
	r6=WIDTH-cx;
	r7=HEIGHT-cy;
	r8=cx*SAMPLES*4;
	r9=cx;

	asm volatile(
	"yloop4:						\n"
	"	mov		r10,r6				\n"

	"xloop4:						\n"
	"	ldrb	r0,[r5]				\n"
	"	mov		r0,r0,lsl #16		\n"

	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP
	ONE_LOOKUP

	"	mov		r0,r0,lsr #16		\n"
	"	cmp		r0,#255				\n"
	"	movgt	r0,#255				\n"
	"	strb	r0,[r5],#1			\n"

	"	subs	r10,r10,#1			\n"
	"	bne		xloop4				\n"

	"	add		r4,r4,r8			\n"
	"	add		r5,r5,r9			\n"
	"	subs	r7,r7,#1			\n"
	"	bne		yloop4				\n"

	:"=r" (r4),"=r" (r5),"=r" (r7)
	:"r" (r4),"r" (r5),"r" (r6),"r" (r7),"r" (r8),"r" (r9)
	:"r0","r1","r2","r3","r10","r11","r12","cc"
	);

	#else

	uint32_t *lookup;
	uint8_t *pixel;

	lookup=lookup1;
	pixel=&screen[cx-1+(cy-1)*128];
	for(int y=cy-1;y>=0;y--)
	{
		for(int x=cx-1;x>=0;x--)
		{
			RenderPixel(pixel,lookup);
			lookup+=SAMPLES;
			pixel--;
		}
		pixel-=WIDTH-cx;
		lookup+=(WIDTH-cx)*SAMPLES;
	}

	lookup=lookup2;
	pixel=&screen[cx+(cy-1)*128];
	for(int y=cy-1;y>=0;y--)
	{
		for(int x=cx;x<WIDTH;x++)
		{
			RenderPixel(pixel,lookup);
			lookup+=SAMPLES;
			pixel++;
		}
		pixel+=cx-2*WIDTH;
		lookup+=cx*SAMPLES;
	}

	lookup=lookup3;
	pixel=&screen[(cx-1)+cy*128];
	for(int y=cy;y<HEIGHT;y++)
	{
		for(int x=cx-1;x>=0;x--)
		{
			RenderPixel(pixel,lookup);
			lookup+=SAMPLES;
			pixel--;
		}
		pixel+=cx+WIDTH;
		lookup+=(WIDTH-cx)*SAMPLES;
	}

	lookup=lookup4;
	pixel=&screen[cx+cy*128];
	for(int y=cy;y<HEIGHT;y++)
	{
		for(int x=cx;x<WIDTH;x++)
		{
			RenderPixel(pixel,lookup);
			lookup+=SAMPLES;
			pixel++;
		}
		pixel+=cx;
		lookup+=cx*SAMPLES;
	}

	#endif

	//swiCopy(dtcm,vram,WIDTH*HEIGHT/4|COPY_MODE_WORD);

	uint32_t *src=(uint32_t *)screen;
	uint32_t *dest=(uint32_t *)vram;
	for(int i=0;i<WIDTH*HEIGHT/4;i++) *dest++=*src++;

}

