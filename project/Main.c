/**
 * JBDS main entry point
 */

#include <nds.h>
#include <stdio.h>

#include <nds/ndstypes.h>
#include <nds/interrupts.h>
#include <string.h>

// Utilities to make development easier
#include "Utils.h"

// NitroFS access
#include "nitrofs.h"

// Effects!
#include "effects.h"
#include "Truchet.h"
#include "Radial.h"
#include "Tunnel.h"
#include "Pens.h"
#include "ARM.h"

// Sound!
#include <maxmod9.h>
#include "music.h"

volatile uint32_t t;
static void vblank();

static PenFrame pens[60*60*3];
extern int tempImage;
extern int cubemode;
extern int showmode;

uint8_t ATTR_DTCM dtcm_buffer[12288];

void fadeout(int t, int b) {
	uint16_t* master_bright = (uint16_t*)(0x400006C);
	if( t > b-16 ) {
		uint16_t val = 18-(b-t);
		memset( master_bright, (1<<7) | val, 2 );
	}
// 	else {
// 		memset( master_bright, (1<<7) | 15, 2 );
// 	}
}

void fadein(int t, int b) {
	uint16_t* master_bright = (uint16_t*)(0x400006C);
	if( t < b+16 ) {
		uint16_t val = (b+17-t);
		memset( master_bright, (1<<7) | val, 2 );
	}
	else {
		memset( master_bright, (1<<7) | 0, 2 );
	}
}


int main()
{
	// Turn on everything.
	POWCNT1 = POWCNT1_ALL_SWAP;
	irqEnable( IRQ_VBLANK );
	irqSet(IRQ_VBLANK,vblank);

//	ClaimWRAM();

	// Init NitroFS for data loading.
	nitroFSInitAdv( BINARY_NAME );

	tempImage = malloc(256*256*2);

	#ifdef DEBUG
	//consoleDemoInit();
	//iprintf( "Debug mode.\n" );
	#endif

	t = 0;
	
	uint8_t *wram=(uint8_t *)0x3000000;
//	memset(wram,0,128*96);

	mmInitDefault( "nitro:/zik/music.bin" );
	mmLoad( MOD_RAINBOWS_CLN );
	mmStart( MOD_RAINBOWS_CLN, MM_PLAY_ONCE );

	palflip_init();
	
	while( t<140*60 ) {
		scanKeys();

		if(1) {
			palflip_update(t);
		}
		else {

		}
 		swiWaitForVBlank();
	}

	// Superstitious save.
// 	SavePenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen");
// 	LoadPenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen");

	POWCNT1 = POWCNT1_ALL;

	for(;;);

	return 0;
}

static void vblank() { t++; }


