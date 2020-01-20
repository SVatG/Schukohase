#include "Utils.h"

void effect5_init() {
	uint16_t* master_bright = (uint16_t*)(0x400006C);
// 	memset( master_bright, (1<<6) | 16, 2 );

	DISPCNT_B = DISPCNT_MODE_5 | DISPCNT_BG2_ON | DISPCNT_ON;
	VRAMCNT_C = VRAMCNT_C_BG_VRAM_B;

	BG2CNT_B = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG2CNT_B = (BG2CNT_B&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG2PA_B = (1 << 8);
	BG2PB_B = 0;
	BG2PC_B = 0;
	BG2PD_B = (1 << 8);
	BG2X_B = 0;
	BG2Y_B = 0;

	DISPCNT_A = DISPCNT_MODE_5 | DISPCNT_BG2_ON | DISPCNT_ON;
	VRAMCNT_A = VRAMCNT_A_BG_VRAM_A_OFFS_0K;
	VRAMCNT_D = VRAMCNT_D_BG_VRAM_A_OFFS_128K;

	BG2CNT_A = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_BITMAP_BASE_0K;
	BG2CNT_A = (BG2CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG2PA_A = (1 << 8);
	BG2PB_A = 0;
	BG2PC_A = 0;
	BG2PD_A = (1 << 8);
	BG2X_A = 0;
	BG2Y_A = 0;

	loadImage( "nitro:/gfx/up.img.bin",VRAM_B,256*192*2);
	loadImage( "nitro:/gfx/up2.img.bin",VRAM_A,256*192*2);

}

int effect5_update( int t ) {

	return( 0 );
}


void effect5_destroy() {

}
