#include <nds.h>

#include "Utils.h"
#include "RainbowTable.h"
#include "Loader.h"

u16* arr_a;
u16* arr_b;
u16* arr_c;
void effect1_init() {
		
	DISPCNT_A = DISPCNT_MODE_5 | DISPCNT_BG2_ON | DISPCNT_BG3_ON | DISPCNT_OBJ_ON | DISPCNT_ON;
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
	
	BG2CNT_A = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_TRANSPARENT | BGxCNT_BITMAP_BASE_128K;
	BG2CNT_A = (BG2CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	BG2PA_A = icos(-800)>>4;
	BG2PB_A = isin(-800)>>4;
	BG2PC_A = -isin(-800)>>4;
	BG2PD_A = icos(-800)>>4;
	BG2X_A = 50000;
	BG2Y_A = -30000;

	loadImage( "nitro:/gfx/clouds.img.bin", VRAM_A_OFFS_0K,256*192*2);
	loadVRAMIndirect( "nitro:/gfx/clouds.img.bin", VRAM_A_OFFS_128K,256*192*2);

	VRAMCNT_A = VRAMCNT_A_OBJ_VRAM_A;

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	loadVRAMIndirect("nitro:/gfx/unicorn.pal.bin", SPRITE_PALETTE, 512);
	arr_a = loadSpriteA( "nitro:/gfx/unicorn.img.bin" );
	arr_b = arr_a;
	arr_c = arr_a;

	DISPCNT_B = DISPCNT_MODE_5 | DISPCNT_BG2_ON | DISPCNT_ON;
	VRAMCNT_C = VRAMCNT_C_BG_VRAM_B;

	BG2CNT_B = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_SCREEN_BASE(0);
	BG2CNT_B = (BG2CNT_B&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG2PA_B = (1 << 8);
	BG2PB_B = 0;
	BG2PC_B = 0;
	BG2PD_B = (1 << 8);
	BG2X_B = 0;
	BG2Y_B = 0;

	loadImage( "nitro:/gfx/text.img.bin", VRAM_B_OFFS_0K,256*192*2);
}

int arra_m = 2;
int arrb_m = -2;
int arrc_m = 2;
int arra_s = 0;
int arrb_s = 160;
int arrc_s = 100;

void drawbars(int t) {
	u16* bg = (u16*)(VRAM_A_OFFS_0K+0x10000);

	arra_s += arra_m;
// 	arrb_s += arrb_m;
// 	arrc_s += arrc_m;

	int bnd = 128;
	
	if( arra_m == 2 ) {
		if( arra_s > 158 + Random()%98 ) {
			arra_m = -1;
		}
	}
	else {
		if( arra_s < 98 - Random()%98 ) {
			arra_m = 2;
		}
	}

	arrb_s = (isin(t<<4)>>5)+100;

	int arra_r = 0;
	int arrb_r = 0;
	int arrc_r = 0;
	
	for( int x = 0; x < 256; x++ ) {
		if( x > arra_s && x < arra_s + 10 ) {
			bg[x] = 4 | 4<<5 | 4<<10 | BIT(15);
			arra_r += 10;
		}
		else if( x > arrb_s && x < arrb_s + 10 ) {
			bg[x] = 4 | 4<<5 | 4<<10 | BIT(15);
			arrb_r += 10;
		}
		else if( x > arrc_s - (isin(t<<4)>>7) && x < arrc_s + 10 - (isin(t<<4)>>7) ) {
			bg[x] = 4 | 4<<5 | 4<<10 | BIT(15);
			arrc_r += 10;
		} else {
			bg[x] = ~BIT(15);
		}
	}

	for( int y = 192; y > 0; y-- ) {
		dmaCopy( &bg[(y-1)*256], &bg[y*256], 512 );
	}

	oamSet(
		&oamMain, 1,
		arra_s*0.45-50, 130-arra_s*0.78,
		1, 0,
		SpriteSize_64x64,
		SpriteColorFormat_256Color,
		arr_a,
		1, true, false, false, false, false
	);

	oamRotateScale(
		&oamMain,
		1,
		0,
		255,
		255
	);

	oamSet(
		&oamMain, 2,
		arrb_s*0.3-30, 159-arrb_s*0.95-(icos((t+10)<<4))/200,
		1, 0,
		SpriteSize_64x64,
		SpriteColorFormat_256Color,
		arr_a,
		0, true, false, true, false, false
	);

	oamRotateScale(
		&oamMain,
		0,
		-(icos((t+10)<<4)),
		255,
		255
	);
	
	oamSet(
		&oamMain, 3,
		-(isin(t<<4)>>9)*1.25+34, arrc_s*0.6+30+(isin(t<<4)>>7),
		0, 0,
		SpriteSize_64x64,
		SpriteColorFormat_256Color,
		arr_a,
		-1, false, false, false, false, false
	);
	
	oamUpdate(&oamMain);
}

u8 effect1_update( u32 t ) {
	BG3X_A = -t*800;

	drawbars(t);
	drawbars(t);	

	
	return( 0 );
}


void effect1_destroy() {
	irqDisable( IRQ_HBLANK );
}
