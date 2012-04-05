#include <nds.h>

#include "Loader.h"
#include "Utils.h"
#include <nds/registers_alt.h>

#include "RainbowTable.h"

// Cap/flip
int line = 0;
void capflip2() {
	int capsrc;
	static int flip = 0;
	capsrc=DISPCAPCNT_SRC_A_SCREEN;

	if(flip)
	{
		VRAMCNT_A=VRAMCNT_A_BG_VRAM_A_OFFS_0K;
		VRAMCNT_B=VRAMCNT_B_LCDC;
		DISPCAPCNT=DISPCAPCNT_WRITE_VRAM_B|DISPCAPCNT_SIZE_256x192
		|capsrc|DISPCAPCNT_SRC_A|DISPCAPCNT_ENABLE;
	}
	else
	{
		VRAMCNT_A=VRAMCNT_A_LCDC;
		VRAMCNT_B=VRAMCNT_B_BG_VRAM_A_OFFS_0K;
		DISPCAPCNT=DISPCAPCNT_WRITE_VRAM_A|DISPCAPCNT_SIZE_256x192
		|capsrc|DISPCAPCNT_SRC_A|DISPCAPCNT_ENABLE;
	}
	flip^=1;
	s16* bg = (u16*)(VRAM_A_OFFS_0K);
	u16 r;
	u16 b;
	u16 g;
	int start = line*256*12;
	int end = line*256*12+256*12;
	for( int i = start; i < end; i++ ) {
		b = (bg[i] & 0x7C00) >> 10;
		g = (bg[i] & 0x03E0) >> 5;
		r = bg[i] & 0x001F;
		b = (b == 0) ? 0 : b - 1;
		g = (g == 0) ? 0 : g - 1;
		r = (r == 0) ? 0 : r - 1;
		bg[i] =  0x8000 | (b<<10) | (g<<5) | r;
	}
	line+=1;
	line = line % 16;
}

void effect0_init() {
	DISPCNT_B = DISPCNT_MODE_5 | DISPCNT_BG2_ON | DISPCNT_ON;

	BG2CNT_B = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG2CNT_B = (BG2CNT_B&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG2PA_B = (1 << 8);
	BG2PB_B = 0;
	BG2PC_B = 0;
	BG2PD_B = (1 << 8);
	BG2X_B = 0;
	BG2Y_B = 0;

	DISPCNT_A = DISPCNT_MODE_5 | DISPCNT_BG2_ON | DISPCNT_BG3_ON | DISPCNT_ON;
	VRAMCNT_A = VRAMCNT_A_BG_VRAM_A_OFFS_0K;
	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_0K;
	VRAMCNT_C = VRAMCNT_C_BG_VRAM_A_OFFS_128K;
	
	BG2CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_128K;
	BG2CNT_A = (BG2CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG2PA_A = (1 << 10);
	BG2PB_A = 0;
	BG2PC_A = 0;
	BG2PD_A = (1 << 10);
	BG2X_A = 0;
	BG2Y_A = 0;

	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	BG3PA_A = (1 << 8);
	BG3PB_A = 0;
	BG3PC_A = 0;
	BG3PD_A = (1 << 8);
	BG3X_A= 0;
	BG3Y_A= 0;
	

	load8bVRAMIndirect( "nitro:/gfx/stars.img.bin", VRAM_A+256*128*2,256*256);
	loadVRAMIndirect( "nitro:/gfx/stars.pal.bin", PALRAM_A,256*2);

}

s16 colpos_eff0 = 0;
void updatecol() {
	dmaCopyHalfWords( 0, rainbowTable + colpos_eff0, PALRAM_A+1, 2 );
	dmaCopyHalfWords( 0, rainbowTable + ((colpos_eff0 + 128)%256), PALRAM_A+2, 2 );
	colpos_eff0 = (colpos_eff0 + 1) % 256;
}

u8 effect0_update( u32 t ) {

	capflip2();

	int dx = icos(t*4)>>2;
	int dy = isin(t*4)>>2;
	BG2PA_A = dx;
	BG2PB_A = dy;
	BG2PC_A = -dy;
	BG2PD_A = dx;
	BG2X_A = t * 1000 + dx * 100;
	BG2X_A = t * 1000;

	BG3X_A = 100;
	
	updatecol();
	updatecol();
	
	return( 0 );
}


void effect0_destroy() {
// 	BLEND_CR = BLEND_NONE;
// 	SUB_BLEND_CR = BLEND_NONE;
// 	irqDisable( IRQ_HBLANK );
}
