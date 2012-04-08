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
volatile int unts = 0;
volatile int unts_proc = 0;

uint32_t effect = 1;
uint32_t last_effect = 1;
mm_word myEventHandler( mm_word msg, mm_word param )
{
    switch( msg )
    {
	case MMCB_SONGMESSAGE:
		if(param != 3) {
			unts = param;
			unts_proc = 0;
		}
		else {
			effect++;
		}
	break;
    }
}


void fadeout(int t, int b) {
	uint16_t* master_bright = (uint16_t*)(0x400006C);
	uint16_t* master_bright_sub = (u16*)(0x400106C);
	if( t > b-16 ) {
		uint16_t val = 18-(b-t);
		memset( master_bright, (1<<7) | val, 2 );
		memset( master_bright_sub, (1<<7) | val, 2 );		
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


int32_t fadet = 0;
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
// 	consoleDemoInit();
// 	iprintf( "Debug mode.\n" );
	#endif

	t = 0;
	
	uint8_t *wram=(uint8_t *)0x3000000;
//	memset(wram,0,128*96);

	mmInitDefault( "nitro:/zik/music.bin" );
	mmLoad( MOD_MUSIC );
	mmStart( MOD_MUSIC, MM_PLAY_ONCE );
	mmSetEventHandler( myEventHandler );
	
// 	palflip_init();
	effect1_init();
// 	effect6_init();
// 	effect7_init();
// 	effect5_init();
// 	effect1_init();

// 	t = 1340;
	while( 1 ) {
		if(unts != 0 && unts_proc == 1) {
			unts = 0;
		}
		if(0) {
// 			effect7_update(t);
// 			effect6_update(t);
// 			effect1_update(t);
// 			palflip_update(t);
		}
		else {
			if(effect == 0) {
				effect1_update(t);
			}
			if(effect == 1 && last_effect == 0) {
				last_effect++;
				effect1_destroy();
				effect7_init();
			}
			if(effect == 1) {
				effect7_update(t);
			}
			if(effect == 2 && last_effect == 1) {
				last_effect++;				
				effect7_destroy();
				effect5_init();
			}
			if(effect == 2) {
				effect5_update(t);
			}
			if(effect == 3 && last_effect == 2) {
				last_effect++;				
				effect5_destroy();
				effect6_init();
			}
			if(effect == 3) {
				effect6_update(t);
			}
			if(effect == 4 && last_effect == 3) {
				last_effect++;		
				effect6_destroy();
				palflip_init();
			}
			if(effect == 4) {
				palflip_update(t);
			}
			if(effect == 5 && last_effect == 4) {
				last_effect++;
				fadet = t;
			}
			if(fadet > 0 && t <= fadet + 16) {
				fadeout(t,fadet + 16);
			}
			if(effect == 6 && t > fadet + 16 ) {
				swiWaitForVBlank();
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


