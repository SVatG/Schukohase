// AO Cubes

#include <nds.h>

#include "DS3D/Utils.h"
#include "DS3D/DS3D.h"
#include "VoxelBlock.h"
#include "Hardware.h"
#include "Loader.h"
#include "RainbowTable.h"

volatile uint8_t colpos = 0;
volatile uint8_t copypos = 0;
void hblank() {	
// 	dmaCopyHalfWords( 0, &rainbowTable[(colpos%256)], PALRAM_A+1, 2 );
	dmaCopyHalfWords( 0, &rainbowTable[((64+colpos)%256)], PALRAM_A+2, 2 );
	dmaCopyHalfWords( 0, &rainbowTable[((128+colpos)%256)], PALRAM_A+3, 2 );
	dmaCopyHalfWords( 0, &rainbowTable[((192+colpos)%256)], PALRAM_A+4, 2 );
	dmaCopyHalfWords( 0, &rainbowTable[((colpos)%256)], PALRAM_A+5, 2 );
	
	colpos++;
// 	copypos+=9;
}

uint8_t flip = 0;

// Cap/flip
void capflip() {	 
	 if( flip ) {
		vramSetBankB( VRAMCNT_B_BG_VRAM_A_OFFS_128K );
		vramSetBankC( VRAM_C_LCD );
		REG_DISPCAPCNT =
			DCAP_BANK( 2 ) |
			DCAP_SIZE( 3 ) |
			DCAP_SRC( 0 ) |
			DCAP_MODE( 0 ) |
			DCAP_ENABLE;
	}
	else {
		vramSetBankB( VRAM_B_LCD );
		vramSetBankC( VRAMCNT_C_BG_VRAM_A_OFFS_128K );
		REG_DISPCAPCNT =
			DCAP_BANK( 1 ) |
			DCAP_SIZE( 3 ) |
			DCAP_SRC( 0 ) |
			DCAP_MODE( 0 ) |
			DCAP_ENABLE;
	}
	flip^=1;
}

void palflip_init() {

	irqSet( IRQ_HBLANK, hblank );
	irqEnable( IRQ_HBLANK );
	
	DISPCNT_A=DISPCNT_MODE_5|DISPCNT_3D|DISPCNT_BG2_ON|DISPCNT_BG3_ON|DISPCNT_ON;

	// Background
	VRAMCNT_A = VRAMCNT_B_BG_VRAM_A_OFFS_0K;
	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_128K;
	VRAMCNT_C = VRAMCNT_C_LCDC;


	BG2PA_A = 252;
	BG2PB_A = 0;
	BG2PC_A = 0;
	BG2PD_A = 252;
	BG2X_A = 0;
	BG2Y_A = 0;
	
	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	
	BG2CNT_A = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_128K;
	BG2CNT_A = (BG2CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	
	load8bVRAMIndirect( "nitro:/gfx/allstars.img.bin", VRAM_A_OFFS_0K,256*192*2);
}

uint8_t palflip_update( uint32_t t ) {
	capflip();

	uint16_t* master_bright = (uint16_t*)(0x400006C);
	if(t % 16 > 14) {
		memset( master_bright, (1<<7) | (16), 2 );
	}
	else {
		memset( master_bright, (1<<7) | (0), 2 );
	}
	
	int dx = icos(isin(t*10)/5.0)/5.5;
	int dy = isin(isin(t*10)/5.0)/5.5;

	BG3PA_A=dx;
	BG3PB_A=dy;
	BG3PC_A=-dy;
	BG3PD_A=dx;
	BG3X_A=-128*dx-92*dy+(128<<8);
	BG3Y_A=+128*dy-92*dx+(92<<8);
	BG3X_A-=t*50;
	
	return 0;
}


void palflip_destroy() {
	irqDisable( IRQ_HBLANK );
}

