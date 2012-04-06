// AO Cubes

#include <nds.h>

#include "DS3D/Utils.h"
#include "DS3D/DS3D.h"
#include "VoxelBlock.h"
#include "Hardware.h"
#include "Loader.h"
#include "RainbowTable.h"

uint8_t colpos = 0;
uint8_t copypos = 0;
void hblank() {
	dmaCopyHalfWords( 0, &rainbowTable[colpos], PALRAM_A+copypos, 5 );
	colpos++;
	copypos += 3;
}

uint8_t flip = 0;

// Cap/flip
void capflip() {	 
	 if( flip ) {
		vramSetBankA( VRAM_A_TEXTURE_SLOT2 );
		vramSetBankD( VRAM_D_LCD );
		REG_DISPCAPCNT =
			DCAP_BANK( 3 ) |
			DCAP_SIZE( 3 ) |
			DCAP_SRC( 1 ) |
			DCAP_MODE( 0 ) |
			DCAP_ENABLE;
// 		rtexture =
// 			DS_TEX_ADDRESS( VRAM_D ) |
// 			DS_TEX_SIZE_S_256 |
// 			DS_TEX_SIZE_T_256 |
// 			DS_TEX_FORMAT_RGB |
// 			DS_TEX_GEN_TEXCOORD;
	}
	else {
		vramSetBankA( VRAM_A_LCD );
		vramSetBankD( VRAM_D_TEXTURE_SLOT3 );
		REG_DISPCAPCNT =
			DCAP_BANK( 0 ) |
			DCAP_SIZE( 3 ) |
			DCAP_SRC( 1 ) |
			DCAP_MODE( 0 ) |
			DCAP_ENABLE;

// 		rtexture =
// 			DS_TEX_ADDRESS( VRAM_C ) | // It's actually VRAM A at slot 2.
// 			DS_TEX_SIZE_S_256 |
// 			DS_TEX_SIZE_T_256 |
// 			DS_TEX_FORMAT_RGB |
// 			DS_TEX_GEN_TEXCOORD;
	}
	flip^=1;
}

void palflip_init() {

	irqSet( IRQ_HBLANK, hblank );
	irqEnable( IRQ_HBLANK );
	
	DISPCNT_A=DISPCNT_MODE_5|DISPCNT_3D|DISPCNT_BG0_ON|DISPCNT_BG3_ON|DISPCNT_ON;

	VRAMCNT_A = VRAMCNT_A_LCDC;

	int dx = icos(128)/26.5;
	int dy = isin(128)/26.5;
	BG2PA_B = dx;
	BG2PB_B = dy;
	BG2PC_B = -dy;
	BG2PD_B = dx;
	BG2X_B = 4000;
	BG2Y_B = 10000;

	// Set up voxelcubes
	VRAMCNT_D=VRAMCNT_D_LCDC;
	VRAMCNT_F=VRAMCNT_F_LCDC;

	loadVRAMIndirect( "nitro:/textures.pal4", VRAM_LCDC_D,16384);

	for(int i=0;i<16;i++) VRAM_LCDC_F[i]=MakeRGB15(i+16,i+16,i+16);

	VRAMCNT_D=VRAMCNT_D_TEXTURE_OFFS_0K;
	VRAMCNT_F=VRAMCNT_F_TEXTURE_PALETTE_SLOT_0;

	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_TEXTURING|DS_ANTIALIAS);
	DSClearParams(26,26,26,0,63);

	DSSetPaletteOffset(0,DS_TEX_FORMAT_PAL4);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspectivef(100,256.0/192.0,1,1024);

	// Background
	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_0K;
	VRAMCNT_C = VRAMCNT_C_BG_VRAM_A_OFFS_128K;

	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_TRANSPARENT | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG3PA_A = (1 << 8);
	BG3PB_A = 0;
	BG3PC_A = 0;
	BG3PD_A = (1 << 8);
	BG3X_A = 0;
	BG3Y_A = 0;

	
	load8bVRAMIndirect( "nitro:/gfx/allstars.img.bin", VRAM_A_OFFS_0K,256*192*2);
// 	loadVRAMIndirect( "nitro:/gfx/alls.pal.bin", PALRAM_A,256*2);
}

void objectShow(int t) {
	static uint8_t ri = 0;
	DSMatrixMode(DS_POSITION);
	DSLoadIdentity();

	DSSwapBuffers(0);
}

uint8_t palflip_update( uint32_t t ) {
	capflip();
	
	return 0;
}


void palflip_destroy() {
	irqDisable( IRQ_HBLANK );
}

