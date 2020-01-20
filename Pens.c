#include <nds.h>
#include <stdio.h>

#include "Pens.h"
#include "ARM.h"
#include "Drawing.h"
#include "DS3D/Hardware.h"
#include "DS3D/Utils.h"

static void GeneratePaletteBlock(int block,int h)
{
	for(int i=0;i<16;i++)
	{
		int col=MakeHSV(h,IntToFixed(1),IntToFixed(i)/15);
		PALRAM_B[block*16+i]=col;
	}
}

int lastframe,currpen;
bool recording,wasdown;
int pencol[MaxPens];

void InitPensOnSecondaryScreen(bool recordmode)
{
	VRAMCNT_H=VRAMCNT_H_BG_VRAM_B;
	VRAMCNT_I=VRAMCNT_I_BG_VRAM_B_OFFS_32K;
	for(int i=0;i<256*192/2;i++) VRAM_B[i]=0;

	DISPCNT_B=DISPCNT_MODE_3|DISPCNT_ON|DISPCNT_BG3_ON;
	BG3CNT_B=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_8
			|BGxCNT_BITMAP_SIZE_256x256|BGxCNT_PRIORITY_1;
	BG3PA_B=0x100;
	BG3PB_B=0;
	BG3PC_B=0;
	BG3PD_B=0x100;
	BG3HOFS_B=0;
	BG3VOFS_B=0;

	PALRAM_B[0]=0;
	GeneratePaletteBlock(1,0);
	GeneratePaletteBlock(2,30);
	GeneratePaletteBlock(3,60);
	GeneratePaletteBlock(4,90);
	GeneratePaletteBlock(5,120);
	GeneratePaletteBlock(6,150);
	GeneratePaletteBlock(7,180);
	GeneratePaletteBlock(8,210);
	GeneratePaletteBlock(9,240);
	GeneratePaletteBlock(10,270);
	GeneratePaletteBlock(11,300);
	GeneratePaletteBlock(12,330);

	lastframe=-1;
	recording=recordmode;
	wasdown=false;

	if(recording) currpen=0;
	else currpen=4;

	for(int i=0;i<MaxPens;i++) pencol[i]=0;
}

void RunPens(PenFrame *frames,int numframes,int frame)
{
	if(frame<=lastframe) return;

	scanKeys();
	uint32_t keys=keysHeld();
	touchPosition pen;
	touchRead(&pen);

	if(recording)
	{
	    if(keys&KEY_UP) currpen=0;
	    if(keys&KEY_LEFT) currpen=1;
	    if(keys&KEY_RIGHT) currpen=2;
	    if(keys&KEY_DOWN) currpen=3;
	}

	if(keys&KEY_TOUCH)
	{
		for(unsigned int t=lastframe+1;t<=frame && t<numframes;t++)
		{
			frames[t].pens[currpen].x=pen.px;
			frames[t].pens[currpen].y=pen.py;
		}
		wasdown=true;
    }
	else
	{
		if(wasdown)
		{
			int t=lastframe+1;
			if(t<numframes)
			{
				frames[t].pens[currpen].x=0xff;
				frames[t].pens[currpen].y=0xff;
			}
		}
		wasdown=false;
	}

	for(unsigned int t=lastframe+1;t<=frame;t++)
	{
		Decay(&VRAM_B_OFFS_0K[(t%16)*256/2*12],12);

		if(t==0) continue; // No drawing on the first frame.

		for(int i=0;i<MaxPens;i++)
		{
			if(frames[t-1].pens[i].y<192&&frames[t].pens[i].y<192)
			{
				int col=pencol[i];

				DrawLineWithClip(VRAM_B_OFFS_0K,
				frames[t-1].pens[i].x,frames[t-1].pens[i].y,
				frames[t].pens[i].x,frames[t].pens[i].y,
				col*16+31,true);
				DrawLineWithClip(VRAM_B_OFFS_0K,
				frames[t-1].pens[i].x-1,frames[t-1].pens[i].y,
				frames[t].pens[i].x-1,frames[t].pens[i].y,
				col*16+31,true);
				DrawLineWithClip(VRAM_B_OFFS_0K,
				frames[t-1].pens[i].x+1,frames[t-1].pens[i].y,
				frames[t].pens[i].x+1,frames[t].pens[i].y,
				col*16+31,true);
				DrawLineWithClip(VRAM_B_OFFS_0K,
				frames[t-1].pens[i].x,frames[t-1].pens[i].y-1,
				frames[t].pens[i].x,frames[t].pens[i].y-1,
				col*16+31,true);
				DrawLineWithClip(VRAM_B_OFFS_0K,
				frames[t-1].pens[i].x,frames[t-1].pens[i].y+1,
				frames[t].pens[i].x,frames[t].pens[i].y+1,
				col*16+31,true);
			}
			else if(frames[t-1].pens[i].y>=192&&frames[t].pens[i].y<192)
			{
				pencol[i]=(pencol[i]+1)%12;
			}
		}

//		Decay(VRAM_B_OFFS_0K);
	}

	lastframe=frame;
}

void ClearPenData(PenFrame *frames,int numframes)
{
	memset(frames,0xff,sizeof(PenFrame)*numframes);
}

bool LoadPenData(PenFrame *frames,int numframes,const char *filename)
{
	FILE *fh=fopen(filename,"rb");
	if(!fh) return false;

	fread(frames,numframes*sizeof(PenFrame),1,fh);
	fclose(fh);

	return true;
}

bool SavePenData(PenFrame *frames,int numframes,const char *filename)
{
	FILE *fh=fopen(filename,"wb");
	if(!fh) return false;

	fwrite(frames,numframes*sizeof(PenFrame),1,fh);
	fclose(fh);

	return true;
}

