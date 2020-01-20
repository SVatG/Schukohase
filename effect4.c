#include <nds.h>

#include "Utils.h"
#include "RainbowTable.h"
#include "Loader.h"

u16* unicorna;
int showmode = 0;
void effect4_init() {

	DISPCNT_A = DISPCNT_MODE_5 | DISPCNT_BG3_ON | DISPCNT_OBJ_ON | DISPCNT_ON;
	VRAMCNT_D = VRAMCNT_D_BG_VRAM_A_OFFS_128K;
	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_0K;

	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	BG3PA_A = (1 << 8);
	BG3PB_A = 0;
	BG3PC_A = 0;
	BG3PD_A = (1 << 8);
	BG3X_A = 0;
	BG3Y_A = 0;

	if( showmode == 1 ) {
		loadImage( "nitro:/gfx/eis.img.bin", VRAM_A_OFFS_0K,256*192*2);
		loadVRAMIndirect( "nitro:/gfx/eis.img.bin", VRAM_A_OFFS_128K,256*192*2);

		VRAMCNT_A = VRAMCNT_A_OBJ_VRAM_A;

		oamInit(&oamMain, SpriteMapping_1D_128, false);
		loadVRAMIndirect("nitro:/gfx/unicorn.pal.bin", SPRITE_PALETTE, 512);
		unicorna = loadSpriteA( "nitro:/gfx/unicorn.img.bin" );
	}
	else {
		loadImage( "nitro:/gfx/kirsche.img.bin", VRAM_A_OFFS_0K,256*192*2);
		loadVRAMIndirect( "nitro:/gfx/kirsche.img.bin", VRAM_A_OFFS_128K,256*192*2);

		VRAMCNT_A = VRAMCNT_A_OBJ_VRAM_A;

		oamInit(&oamMain, SpriteMapping_1D_128, false);
		loadVRAMIndirect("nitro:/gfx/unicorn.pal.bin", SPRITE_PALETTE, 512);
		unicorna = loadSpriteA( "nitro:/gfx/unicorn.img.bin" );
	}
}

u8 effect4_update( u32 t ) {
	int swoop = (t<<13)/50;
	if( showmode == 1 ) {
		oamSet(
			&oamMain, 1,
			120, 25,
			1, 0,
			SpriteSize_64x64,
			SpriteColorFormat_256Color,
			unicorna,
			1, true, false, false, false, false
		);

		oamRotateScale(
			&oamMain,
			1,
			isin(swoop)>>3,
			165-(isin(swoop)>>7),
			165-(isin(swoop)>>7)
		);
	}
	else {
		oamSet(
			&oamMain, 1,
			10, 25,
			1, 0,
			SpriteSize_64x64,
			SpriteColorFormat_256Color,
			unicorna,
			1, true, false, false, false, false
		);

		oamRotateScale(
			&oamMain,
			1,
			isin(swoop)>>3,
			-165+(isin(swoop)>>7),
			165-(isin(swoop)>>7)
		);
	}
	oamUpdate(&oamMain);
	
	return( 0 );
}


void effect4_destroy() {
	irqDisable( IRQ_HBLANK );
}
