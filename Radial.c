#include "Radial.h"
#include "ARM.h"
#include "Hardware.h"
#include "Utils.h"

#include <math.h>
#include <string.h>

/*#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>*/

#define SAMPLES 4
#define WIDTH 128
#define HEIGHT 96

static uint32_t lookup1[HEIGHT][WIDTH][SAMPLES];
static uint32_t lookup2[HEIGHT][WIDTH][SAMPLES];
static uint32_t lookup3[HEIGHT][WIDTH][SAMPLES];
static uint32_t lookup4[HEIGHT][WIDTH][SAMPLES];

int frame;

void InitRadial()
{
	for(int y=0;y<2*HEIGHT;y++)
	for(int x=0;x<2*WIDTH;x++)
	for(int i=0;i<SAMPLES;i++)
	{
		float fx=x-WIDTH+1,fy=y-HEIGHT+1;
		float r=sqrtf(fx*fx+fy*fy);
		float dx=fx/r,dy=fy/r;
		int ix=-(float)(i+1)*dx*256;
		int iy=-(float)(i+1)*dy*256;

		int offs=(iy>>8)*128+(ix>>8);
		int xblend=(ix&0xff)>>1;
		int yblend=(iy&0xff)>>1;

		//uint32_t val=(offs&0xffff)|(xblend<<16)|(yblend<<24);
		uint32_t val=((offs&0xffff)<<16)|(xblend<<8)|(yblend<<0);

		if(y<HEIGHT)
		{
			if(x<WIDTH) lookup1[HEIGHT-1-y][WIDTH-1-x][i]=val;
			else lookup2[HEIGHT-1-y][x-WIDTH][i]=val;
		}
		else
		{
			if(x<WIDTH) lookup3[y-HEIGHT][WIDTH-1-x][i]=val;
			else lookup4[y-HEIGHT][x-WIDTH][i]=val;
		}
	}


	VRAMCNT_A=VRAMCNT_A_LCDC;
	VRAMCNT_B=VRAMCNT_B_LCDC;
	VRAMCNT_C=VRAMCNT_C_BG_VRAM_A_OFFS_0K;
	VRAMCNT_D=VRAMCNT_D_LCDC;

	DISPCNT_A=DISPCNT_MODE_4|DISPCNT_BG3_ON|DISPCNT_ON;
	BG3CNT_A=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_8
			|BGxCNT_BITMAP_SIZE_128x128;
	BG3PA_A=0x80;
	BG3PB_A=0;
	BG3PC_A=0;
	BG3PD_A=0x80;
	BG3HOFS_A=0;
	BG3VOFS_A=0;

	frame=0;
}

void StopRadial()
{
}

static char *logo=

"                                                      MMMM                              "
"                                                     MMMMM                              "
"                                                     MMMMM                              "
"      MMMMMMMMMM  MMMM       MMMMM  MMMMMMMMMMMMMMM  MMMMMMMMM   MMMMMMMMMMMMM          "
"      MMMMMMMMMMMMMMMM       MMMMM MMMMMMMMMMMMMMMMM MMMMMMMMMM MMMMMMMMMMMMMMM         "
"      MMMMM      MMMMM       MMMMM MMMMM       MMMMM MMMMM     MMMMM       MMMMM        "
"MMMMMMMMMMM      MMMMMMMMMMMMMMMMM MMMMMMMMMMMMMMMMM MMMMM      MMMMMMMMMMMMMMMM        "
"MMMMMMMMMMM      MMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMM MMMMM       MMMMMMMMMMMMMMM        "
"                                                                           MMMMM        "
"                                                                MMMMMMMMMMMMMMMM        "
"                                                               MMMMMMMMMMMMMMMM         ";

void DrawLogo(uint8_t *dtcm,int val)
{
	const int width=88;
	const int height=11;
	const int x1=(128-width)/2;
	const int y1=(96-height)/2;
	const int x2=x1+width;
	const int y2=y1+height;

	uint8_t *src=logo;
	uint8_t *dest=dtcm;

	for(int y=0;y<96;y++)
	for(int x=0;x<128;x++)
	{
		if(x>=x1&&x<x2&&y>=y1&&y<y2)
		{
			*dest++=(*src++==' ')?0:val;
		}
		else
		{
			*dest++=0;
		}
	}
}

int32_t smooth(int32_t x)
{
	if(x<0) return 0;
	if(x>F(1)) return F(1);
	return imul(imul(F(3)-2*x,x),x);
}

void RunRadial(int t,uint8_t *dtcm)
{
	uint16_t *vram;
	if(frame)
	{
		BG3CNT_A=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_8
				|BGxCNT_BITMAP_SIZE_128x128;
		vram=VRAM_A_OFFS_64K;
	}
	else
	{
		BG3CNT_A=BGxCNT_BITMAP_BASE_64K|BGxCNT_EXTENDED_BITMAP_8
				|BGxCNT_BITMAP_SIZE_128x128;
		vram=VRAM_A_OFFS_0K;
	}
	frame^=1;

	int cx,cy;

	const int len1=480;
	const int len2=180;
	const int len3=180;

	if(t<len1)
	{
		int tt=t;
		for(int i=0;i<256;i++)
		{
			int fade=tt<(len1/2)?tt:(len1/2);
			int c=(31*i*fade)/(len1/2)/255;
			PALRAM_A[i]=0x8000|MakeRGB15(c,c,c);
		}

		cx=64;
		cy=FixedToInt(88*smooth(F(t)/(len1+len2)));

		DrawLogo(dtcm,(255*tt)/len1);
	}
	else if(t<len1+len2)
	{
		int tt=t-len1;
		for(int i=0;i<256;i++)
		{
			int s=(256-i)*32*tt/len2;
			int v=i*16+i*16*tt/len2;
			if(s>4096) s=4096;
			if(v>4096) v=4096;


			PALRAM_A[i]=0x8000|MakeHSV((6*t+i*2)%360,s,v);
		}

		cx=64;
		cy=FixedToInt(88*smooth(F(t)/(len1+len2)));

		DrawLogo(dtcm,255);
	}
	else
	{
		int tt=t-len1-len2;
		for(int i=0;i<256;i++)
		{
			int s=(256-i)*32;
			int v=i*32;
			if(s>4096) s=4096;
			if(v>4096) v=4096;
			PALRAM_A[i]=0x8000|MakeHSV((6*t+i*2)%360,s,v);
		}

		int32_t r=smooth(F(tt)/len3);
		cx=64+FixedToInt(imul(r,isin(tt*50))*40);
		cy=88+FixedToInt(imul(r,icos(tt*50)-F(1))*40);

		DrawLogo(dtcm,255);
	}

//	RenderBackgroundARM(t,dtcm);

	RenderRadialARM(t,cx,cy,dtcm,vram,&lookup1[0][0][0],
	&lookup2[0][0][0],&lookup3[0][0][0],&lookup4[0][0][0]);
}
