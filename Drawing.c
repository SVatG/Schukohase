#include "Drawing.h"
#include "Utils.h"
#include "Hardware.h"

#include <string.h>

#define VRAM_A_ADDR VRAM_A_OFFS_80K
#define VRAM_B_ADDR VRAM_B_OFFS_80K

void DrawPixelWithClip(uint16_t *screenbase,int x,int y,int col,bool clip)
{
	if(clip)
	{
		if(x<0||x>=256) return;
		if(y<0||y>=192) return;
	}

	uint16_t val=screenbase[(x>>1)+y*128];
	
	if(x&1) screenbase[(x>>1)+y*128]=(val&0x00ff)|(col<<8);
	else screenbase[(x>>1)+y*128]=(val&0xff00)|col;
}

void DrawVerticalLineWithClip(uint16_t *screenbase,int x,int y,int h,int col,bool clip)
{
	if(clip)
	{
		if(x<0||x>=256) return;
		if(y+h<=0||y>=192) return;
		if(y<0) { h+=y; y=0; }
		if(y+h>192) h=192-y;
	}
	
	if(x&1) for(int i=0;i<h;i++)
	{
		uint16_t val=screenbase[(x>>1)+(y+i)*128];
		screenbase[(x>>1)+(y+i)*128]=(val&0x00ff)|(col<<8);
	}
	else for(int i=0;i<h;i++)
	{
		uint16_t val=screenbase[(x>>1)+(y+i)*128];
		screenbase[(x>>1)+(y+i)*128]=(val&0xff00)|col;
	}
}

void DrawHorizontalLineWithClip(uint16_t *screenbase,int x,int y,int w,int col,bool clip)
{
	if(clip)
	{
		if(x+w<=0||x>=256) return;
		if(y<0||y>=192) return;
		if(x<0) { w+=x; x=0; }
		if(x+w>256) w=256-x;
	}

	if(w==1) DrawPixelWithClip(screenbase,x,y,col,false);
	else
	{
		if(x&1)
		{
			uint16_t val=screenbase[(x>>1)+y*128];
			screenbase[(x>>1)+y*128]=(val&0x00ff)|(col<<8);
		}
		for(int i=x+1>>1;i<x+w>>1;i++)
		{
			screenbase[i+y*128]=(col<<8)+col;
		}
		if(x+w&1)
		{
			uint16_t val=screenbase[(x+w>>1)+y*128];
			screenbase[(x+w>>1)+y*128]=(val&0xff00)|col;
		}
	}
}

void DrawLineWithClip(uint16_t *screenbase,int x1,int y1,int x2,int y2,int col,bool clip)
{
	if(clip)
	{
		if(((x1|x2)&~255)==0&&y1>=0&&y1<192&&y2>=0&&y2<192) clip=false;
	}

	int x_start,y_start,x_end,y_end;
	if(y1<y2)
	{
		x_start=x1; y_start=y1;
		x_end=x2; y_end=y2;
	}
	else
	{
		x_start=x2; y_start=y2;
		x_end=x1; y_end=y1;
	}

	int dx=iabs(x_end-x_start);
	int dy=y_end-y_start;

	if(dx==0)
	{
		DrawVerticalLineWithClip(screenbase,x_start,y_start,dy+1,col,true);
	}
	else if(dy==0)
	{
		if(x_start<=x_end) DrawHorizontalLineWithClip(screenbase,x_start,y_start,dx+1,col,true);
		else DrawHorizontalLineWithClip(screenbase,x_start-dx,y_start,dx+1,col,true);
	}
	else if(dx==dy)
	{
		if(x_start<=x_end) for(int i=0;i<=dx;i++) DrawPixelWithClip(screenbase,x_start+i,y_start+i,col,true);
		else for(int i=0;i<=dx;i++) DrawPixelWithClip(screenbase,x_start-i,y_start+i,col,true);
	}
	else if(dx>dy)
	{
		int stepsize=dx/dy;
		int adj_up=(dx%dy)*2;
		int adj_down=dy*2;
		int error=adj_up/2-adj_down;
		int initial_len=stepsize/2+1;
		int final_len=initial_len;

		if(stepsize&1)
		{
			/* If there're an odd number of pixels per run, we have 1 pixel that can't
			be allocated to either the initial or last partial run, so we'll add 0.5
			to error term so this pixel will be handled by the normal full-run loop */
			error+=dy;
		}
		else
		{
			/* If the basic run length is even and there's no fractional
			advance, we have one pixel that could go to either the initial
			or last partial run, which we'll arbitrarily allocate to the
			last run */
			if(adj_up==0) initial_len-=1;
		}

		int x=x_start;

		if(x_start<=x_end) 
		{
			DrawHorizontalLineWithClip(screenbase,x,y_start,initial_len,col,true);
			x+=initial_len;

			for(int y=y_start+1;y<y_end;y++)
			{
				int len=stepsize;
				error+=adj_up;
				if(error>0) { len+=1; error-=adj_down; }
				DrawHorizontalLineWithClip(screenbase,x,y,len,col,true);
				x+=len;
			}
			DrawHorizontalLineWithClip(screenbase,x,y_end,final_len,col,true);
		}
		else
		{
			DrawHorizontalLineWithClip(screenbase,x-initial_len+1,y_start,initial_len,col,true);
			x-=initial_len;

			for(int y=y_start+1;y<y_end;y++)
			{
				int len=stepsize;
				error+=adj_up;
				if(error>0) { len+=1; error-=adj_down; }
				DrawHorizontalLineWithClip(screenbase,x-len+1,y,len,col,true);
				x-=len;
			}
			DrawHorizontalLineWithClip(screenbase,x-final_len+1,y_end,final_len,col,true);
		}
	}
	else
	{
		int stepsize=dy/dx;
		int adj_up=(dy%dx)*2;
		int adj_down=dx*2;
		int error=adj_up/2-adj_down;
		int initial_len=stepsize/2+1;
		int final_len=initial_len;

		if(stepsize&1)
		{
			/* If there're an odd number of pixels per run, we have 1 pixel that can't
			be allocated to either the initial or last partial run, so we'll add 0.5
			to error term so this pixel will be handled by the normal full-run loop */
			error+=dx;
		}
		else
		{
			/* If the basic run length is even and there's no fractional
			advance, we have one pixel that could go to either the initial
			or last partial run, which we'll arbitrarily allocate to the
			last run */
			if(adj_up==0) initial_len-=1;
		}

		int y=y_start;
		int x_step=x_start<=x_end?1:-1;

		DrawVerticalLineWithClip(screenbase,x_start,y,initial_len,col,true);
		y+=initial_len;

		for(int x=x_start+x_step;x!=x_end;x+=x_step)
		{
			int len=stepsize;
			error+=adj_up;
			if(error>0) { len+=1; error-=adj_down; }
			DrawVerticalLineWithClip(screenbase,x,y,len,col,true);
			y+=len;
		}
		DrawVerticalLineWithClip(screenbase,x_end,y,final_len,col,true);
	}
}

void DrawRectWithClip(uint16_t *screenbase,int x,int y,int w,int h,int col,bool clip)
{
	if(w<=0||h<=0) return;
	DrawHorizontalLineWithClip(screenbase,x,y,w,col,true);
	DrawHorizontalLineWithClip(screenbase,x,y+h-1,w,col,true);
	if(h>2)
	{
		DrawVerticalLineWithClip(screenbase,x,y+1,h-2,col,true);
		DrawVerticalLineWithClip(screenbase,x+w-1,y+1,h-2,col,true);
	}
}

void FillRectWithClip(uint16_t *screenbase,int x,int y,int w,int h,int col,bool clip)
{
	if(w<=0) return;
	for(int i=0;i<h;i++) DrawHorizontalLineWithClip(screenbase,x,y+i,w,col,true);
}

void ClearScreen(uint16_t *screenbase,int col)
{
	memset(screenbase,col,256*192);
}


void DrawPixel(int x,int y,int col)
{
	if(y<192) DrawPixelWithClip(VRAM_A_ADDR,x,y,col,true);
	else DrawPixelWithClip(VRAM_B_ADDR,x,y-192,col,true);
}

void DrawVerticalLine(int x,int y,int h,int col)
{
	if(y<192) DrawVerticalLineWithClip(VRAM_A_ADDR,x,y,h,col,true);
	if(y+h>192) DrawVerticalLineWithClip(VRAM_B_ADDR,x,y-192,h,col,true);
}

void DrawHorizontalLine(int x,int y,int w,int col)
{
	if(y<192) DrawHorizontalLineWithClip(VRAM_A_ADDR,x,y,w,col,true);
	else DrawHorizontalLineWithClip(VRAM_B_ADDR,x,y-192,w,col,true);
}

void DrawLine(int x1,int y1,int x2,int y2,int col)
{
	if(y1<192||y2<192) DrawLineWithClip(VRAM_A_ADDR,x1,y1,x2,y2,col,true);
	if(y1>=192||y2>=192) DrawLineWithClip(VRAM_B_ADDR,x1,y1-192,x2,y2-192,col,true);
}

void DrawRect(int x,int y,int w,int h,int col)
{
	if(y<192) DrawRectWithClip(VRAM_A_ADDR,x,y,w,h,col,true);
	if(y+h>192) DrawRectWithClip(VRAM_B_ADDR,x,y-192,w,h,col,true);
}

void FillRect(int x,int y,int w,int h,int col)
{
	if(y<192) FillRectWithClip(VRAM_A_ADDR,x,y,w,h,col,true);
	if(y+h>192) FillRectWithClip(VRAM_B_ADDR,x,y-192,w,h,col,true);
}


static bool ClipTest(int n,int d,int *n1,int *d1,int *n2,int *d2)
{
	if(d<0)
	{
		if(n*(*d2)<(*n2)*d) return false; // r>u2
		if(n*(*d1)<(*n1)*d) { *n1=-n; *d1=-d; } //r>u1
	}
	else if(d>0)
	{
		if(n*(*d1)<(*n1)*d) return false; // r<u1
		if(n*(*d2)<(*n2)*d) { *n2=n; *d2=d; } // r<u2
	}
	else
	{
		if(n<0) return false;
	}
	return true;
}

bool ClipLine(int *x1,int *y1,int *x2,int *y2,int left,int top,int right,int bottom)
{
	int n1=0,d1=1;
	int n2=1,d2=1;

	int dx=*x2-*x1;
	int dy=*y2-*y1;

	if(ClipTest(*x1-left,-dx,&n1,&d1,&n2,&d2))
	if(ClipTest(right-*x1,dx,&n1,&d1,&n2,&d2))
	if(ClipTest(*y1-top,-dy,&n1,&d1,&n2,&d2))
	if(ClipTest(bottom-*y1,dy,&n1,&d1,&n2,&d2))
	{
		if(n2<d2)
		{
			*x2=*x1+(n2*dx+isign(dx)*d2/2)/d2;
			*y2=*y1+(n2*dy+isign(dy)*d2/2)/d2;
		}
		if(n1>0)
		{
			*x1=*x1+(n1*dx+isign(dx)*d1/2)/d1;
			*y1=*y1+(n1*dy+isign(dy)*d1/2)/d1;
		}

		return true;
	}

	return false;
}
