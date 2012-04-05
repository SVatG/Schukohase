#include <nds.h>

#include "Utils.h"
#include "DS3D/DS3D.h"
#include "Loader.h"
#include "RainbowTable.h"

static int flip;
static uint32_t whitetexture;

uint8_t colpos = 0;
void hblank() {
	dmaCopyHalfWords( 0, &rainbowTable[colpos], PALRAM_A+4, 2 );
	colpos++;
}

u16* unicorn;
void effect2_init() {
	irqSet( IRQ_HBLANK, hblank );
	irqEnable( IRQ_HBLANK );
	
	DISPCNT_A=DISPCNT_MODE_5|DISPCNT_3D|DISPCNT_BG0_ON|DISPCNT_BG3_ON|DISPCNT_OBJ_ON|DISPCNT_ON;
	BG0CNT_A=BGxCNT_PRIORITY_1;

	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG3PA_A = (1 << 8);
	BG3PB_A = 0;
	BG3PC_A = 0;
	BG3PD_A = (1 << 8);
	BG3X_A = 0;
	BG3Y_A = 0;
	
	VRAMCNT_A=VRAMCNT_A_LCDC;
	VRAMCNT_C=VRAMCNT_C_LCDC;
	VRAMCNT_B=VRAMCNT_B_OBJ_VRAM_A;
	VRAMCNT_D=VRAMCNT_D_BG_VRAM_A_OFFS_0K;
	
	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_TEXTURING|DS_ALPHA_BLEND);
	DSClearParams(0,0,0,31,63);

	for(int i=0;i<256*256;i++)
	{
		VRAM_LCDC_A[i]=0x8000;
		VRAM_LCDC_C[i]=0x8000;
	}

//	DSCopyColorTexture(DS_TEX_ADDRESS(VRAM_LCDC_A+256*204),0x7fff);
//	DSCopyColorTexture(DS_TEX_ADDRESS(VRAM_LCDC_B+256*204),0x7fff);
	memset(VRAM_LCDC_A,0x00,256*192*2);
	memset(VRAM_LCDC_C,0x00,256*192*2);
	memset(VRAM_LCDC_A+256*204,0xff,8*8*2);
	memset(VRAM_LCDC_C+256*204,0xff,8*8*2);
	whitetexture=DS_TEX_ADDRESS(VRAM_LCDC_A+256*204);

	load8bVRAMIndirect( "nitro:/gfx/bolder1.img.bin",VRAM_A,256*192);
	loadVRAMIndirect( "nitro:/gfx/bolder1.pal.bin", PALRAM_A,256*2);
	
	flip=0;
	//whitetexture=DSMakeWhiteTexture();
//DSTranslatef32(128,96,0);
//DSScalef(100.0/4096,100.0/4096,1);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	loadVRAMIndirect("nitro:/gfx/unicorn.pal.bin", SPRITE_PALETTE, 512);
	unicorn = loadSpriteA( "nitro:/gfx/unicorn.img.bin" );
}

u8 effect2_update( u32 t ) {
	int capsrc;

	for( int p = 0; p < 8; p++ ) {
		int dx =  isin(-(t+p*32)<<4)*0.055-30;
		int dy = -icos(-(t+p*32)<<4)*0.03+120;

		dx = dx > 256 ? 256 : dx;
		dy = dy > 192 ? 192 : dy;
		dx = dx < -64 ? 256 : dx;
		dy = dy < -64 ? 192 : dy;
		
		oamSet(
			&oamMain, p,
			dx, dy,
			0, 0,
			SpriteSize_64x64,
			SpriteColorFormat_256Color,
			unicorn,
			p, false, false, false, false, false
		);

		oamRotateScale(
			&oamMain,
			p,
			0,
			200-dx*0.15,
			200-dx*0.15
		);
	}

	oamUpdate(&oamMain);
	
/*	uint16_t *ptr;
	if(flip) ptr=VRAM_LCDC_A;
	else ptr=VRAM_LCDC_B;
	for(int i=0;i<256*10;i++)
	{
		ptr[256*192+i]=ptr[256*191+i];
	}*/
//	DISPCNT_A=DISPCNT_MODE_4|DISPCNT_3D|DISPCNT_BG0_ON|DISPCNT_BG3_ON|DISPCNT_ON;

	capsrc=DISPCAPCNT_SRC_A_3D;

	if(flip)
	{
		VRAMCNT_A=VRAMCNT_A_TEXTURE_OFFS_0K;
		VRAMCNT_C=VRAMCNT_C_LCDC;
		DISPCAPCNT=DISPCAPCNT_WRITE_VRAM_C|DISPCAPCNT_SIZE_256x192
		|capsrc|DISPCAPCNT_SRC_A|DISPCAPCNT_ENABLE;
	}
	else
	{
		VRAMCNT_A=VRAMCNT_A_LCDC;
		VRAMCNT_C=VRAMCNT_C_TEXTURE_OFFS_0K;
		if(t!=0) DISPCAPCNT=DISPCAPCNT_WRITE_VRAM_A|DISPCAPCNT_SIZE_256x192
		|capsrc|DISPCAPCNT_SRC_A|DISPCAPCNT_ENABLE;
	}
	flip^=1;

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DS2DProjection(0);

	DSMatrixMode(DS_MODELVIEW);
	DSLoadIdentity();

	DSSetTexture(0|DS_TEX_SIZE_S_256|DS_TEX_SIZE_T_256|DS_TEX_FORMAT_RGB|DS_TEX_GEN_TEXCOORD);

	DSColor(0x7fff);

	DSMatrixMode(DS_TEXTURE);
	for(int i=1;i<=2;i++)
	{
//		int rx=rand()%127-63;
//		int ry=rand()%127-63;
//		int x=(0)*16+rx,y=(96+15)*16+ry;
		DSLoadIdentity();
//		DSTranslatef(x,y,0);
//		DSScalef((1-(float)i/40),(1-(float)i/40),0);
//		DSTranslatef(-x,-y,0);

			DSTranslatef(-10*16,182*16,0);
			DSRotateZi(-8*i);
			DSTranslatef(10*16,-182	*16,0);
			

		if(i==1)
//		DSPolygonAttributes(DS_POLY_CULL_NONE|DS_POLY_ALPHA(16));
		DSPolygonAttributes(DS_POLY_CULL_NONE|DS_POLY_ALPHA(31/i));
		else
		DSPolygonAttributes(DS_POLY_MODE_DECAL|DS_POLY_CULL_NONE|DS_POLY_ALPHA(31/i)|DS_POLY_DEPTH_TEST_EQUAL);

		DSBegin(DS_QUADS);
		DSTexCoord2f(0,0); DSVertex3v16(0,0,DSf32(-1));
		DSTexCoord2f(256,0); DSVertex3v16(256,0,DSf32(-1));
		DSTexCoord2f(256,192); DSVertex3v16(256,192,DSf32(-1));
		DSTexCoord2f(0,192); DSVertex3v16(0,192,DSf32(-1));
		DSEnd();
	}

	DSLoadIdentity();

	DSPolygonAttributes(DS_POLY_MODE_DECAL|DS_POLY_CULL_NONE|DS_POLY_ALPHA(31));

	DSSetTexture(whitetexture);

	DSBegin(DS_TRIANGLES);
		for(int i=0;i<100;i++)
		{
			switch(Random()%2)
			{
				case 0: DSColor(rainbowTable[t%255]); break;
				case 1: DSColor(0xFFFF); break;
			}

			int x,y;
			if(Random()%2) { x=4; y=Random()%192; }
			else { x=Random()%256; y=4; }

			DSVertex3v16(x+Random()%9-4,y+Random()%9-4,DSf32(-0.5));
			DSVertex3v16(x+Random()%9-4,y+Random()%9-4,DSf32(-0.5));
			DSVertex3v16(x+Random()%9-4,y+Random()%9-4,DSf32(-0.5));
		}
	DSEnd();

	DSSwapBuffers(DS_SWAP_NO_SORTING);
	
	return 0;
}


void effect2_destroy() {
	DISPCAPCNT=0;
}
