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

	// Main loop
	InitPensOnSecondaryScreen(false);
	//InitTruchet(t);
	InitRadial();
// 	effect0_init();
// 	effect2_init();
	
	uint8_t *wram=(uint8_t *)0x3000000;
//	memset(wram,0,128*96);

	if(!LoadPenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen"))
	if(!LoadPenData(pens,sizeof(pens)/sizeof(*pens),"nitro:/rainbows.pen"))
	ClearPenData(pens,sizeof(pens)/sizeof(*pens));

	mmInitDefault( "nitro:/zik/music.bin" );
	mmLoad( MOD_RAINBOWS_CLN );
	mmStart( MOD_RAINBOWS_CLN, MM_PLAY_ONCE );
	while( t<140*60 ) {
		RunPens(pens,sizeof(pens)/sizeof(*pens),t);
		scanKeys();
// 		uint32_t keys=keysHeld();
// 		if(keys&KEY_A) {
// 			SavePenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen");
// 			LoadPenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen");
// 		}
// 		RunTunnel(t);

		if(0) {
			effect0_update(t);
		}
		else {
			
		if( t < 16*60+30 ) {
			RunRadial(t,dtcm_buffer);
			fadeout(t,16*60+30);
			if( t >= 16*60+30-2 ) {
				StopRadial();
				cubemode = 0;
				effect6_init();
			}
		}
		else if(t < 27*60) {
			effect6_update(t);
			fadein(t,16*60+30);
			fadeout(t,27*60);
			if( t >= 27*60-3 ) {
				effect6_destroy();
				effect2_init();
			}
		}
		else if( t < 37*60 ) {
			effect2_update(t);
			fadein(t,27*60);
			fadeout(t,37*60);
			if( t >= 37*60-3 ) {
				effect2_destroy();
				effect1_init();
			}
		}
		else if( t < 47*60 ) {
			effect1_update(t);
			fadein(t,37*60);
			fadeout(t,47*60);
			if( t >= 47*60-2 ) {
				cubemode = 1;
				effect1_destroy();
				effect6_init();
			}
		}
		else if( t < 57*60 ) {
			effect6_update(t);
			fadein(t,47*60-5);
			fadeout(t,57*60);
			if( t >= 57*60-4 ) {
				effect6_destroy();
				showmode = 1;
				InitTunnel();
			}
		}
		else if( t < 68*60 ) {
			RunTunnel(t);
			fadein(t,57*60-5);
			fadeout(t,68*60);
			if( t >= 68*60-2 ) {
				showmode = 1;
				effect4_init();
			}
		}
		else if( t < 73*60 ) {
			effect4_update(t);
			fadein(t,68*60-5);
			fadeout(t,73*60);
			if( t >= 73*60-2 ) {
				effect4_destroy();
				showmode = 0;
				effect4_init();
			}
		}
		else if( t < 78*60 ) {
			effect4_update(t);
			fadein(t,73*60-5);
			fadeout(t,78*60);
			if( t >= 78*60-2 ) {
				effect4_destroy();
				effect0_init();
			}
		}
		else if( t < 88*60 ) {
			effect0_update(t);
			fadein(t,78*60-5);
			fadeout(t,88*60);
			if( t >= 88*60-4 ) {
				effect0_destroy();
				effect5_init();
			}
		}
		else if( t < 108*60 ) {
			effect5_update(t);
			fadein(t,88*60);
			fadeout(t,108*60);
			if( t == 108*60-1 ) {
				effect5_destroy();
			}
		}
		else if( t < 129*60 ) {
			Truchet(t);
			fadein(t,108*60);
			if( t >= 129*60-2 ) {
				effect7_init();
			}
		}
		else {
			effect7_update(t);
		}
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


