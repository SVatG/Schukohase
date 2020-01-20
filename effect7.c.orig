#include <nds.h>
#include "Utils.h"
#include "RainbowTable.h"

uint16_t hstate = 0xDEC0;
uint16_t vstate = 0xC0DE;

uint16_t hnext() {
	uint16_t next =
		((hstate & 0x08) >> 3) ^
		((hstate & 0x10) >> 4) ^
		((hstate & 0x20) >> 5) ^
		((hstate & 0x80) >> 7);
	hstate = (hstate >> 1) | (next << 15);
	return( hstate );
}

uint16_t vnext() {
	uint16_t next =
		((vstate & 0x08) >> 3) ^
		((vstate & 0x10) >> 4) ^
		((vstate & 0x20) >> 5) ^
		((vstate & 0x80) >> 7);
	vstate = (vstate >> 1) | (next << 15);
	return( vstate );
}

void effect7_init() {
	VRAMCNT_A=VRAMCNT_A_BG_VRAM_A;

	DISPCNT_A=DISPCNT_MODE_0|DISPCNT_ON|DISPCNT_BG0_ON;
	BG0CNT_A=BGxCNT_TILE_BASE_0K|BGxCNT_CHAR_BASE_64K
			|BGxCNT_TEXT_256_COLOURS|BGxCNT_TEXT_SIZE_256x256;

	for(int i=0;i<126*1024/2;i++)
	{
		VRAM_A_OFFS_64K[i]=hnext();
		vnext() & 0x01 ? hnext() : vnext();
	}

	for(int i=0;i<32*24;i++)
	{
		VRAM_A_OFFS_0K[i]=vnext()&0xc3ff;
	}

	for(int i=0;i<256;i++)
	{
		int c=(hnext())&0x1f;
		PALRAM_A[i]=0x8000|(c<<10)|(c<<5)|c;
	}

}

u8 effect7_update( u32 t ) {
	static uint8_t rind;
	static int round = 0;
	for(int i=round;i<126*1024/2;i+=16) {
		VRAM_A_OFFS_64K[i]=hnext()^vnext();
	}
	round++;
	round = round & 0xF;

	for(int i=0;i<256;i++) {
		int c=(hnext())&0x1f;
			PALRAM_A[i]=(0x8000|(c<<10)|(c<<5)|c)^rainbowTable[rind++];
	}

	return( 1 );
}


void effect7_destroy() {
	
}
