// Metaballs

#include <nds.h>

#include "Utils.h"
#include "DS3D/DS3D.h"
#include "BoxBlock.h"
#include "Hardware.h"
#include "Loader.h"
#include "RainbowTable.h"

typedef struct ball {
	int x;
	int y;
	int z;
	int c;
} ball;

BoxBlock balls;
ball ballp[3];

void effect5_init() {

	DISPCNT_A=DISPCNT_MODE_5|DISPCNT_3D|DISPCNT_BG0_ON|DISPCNT_BG3_ON|DISPCNT_ON;

	// Set up voxelcubes
	DSInit3D();
	DSViewport(0,0,255,191);
	
	DSSetControl(DS_ALPHA_BLEND|DS_ANTIALIAS);
	DSClearParams(26,26,26,0,63);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspectivef(45,256.0/192.0,1,1024);

	InitBoxBlock(&balls,20,24,20);

	// Background
	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_0K;
	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	BG0CNT_A = (BG0CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG3PA_A = (1 << 9);
	BG3PB_A = 0;
	BG3PC_A = 0;
	BG3PD_A = (1 << 9);
	BG3X_A = 0;
	BG3Y_A = 0;

	load8bVRAMIndirect( "nitro:/gfx/metaballs.img.bin", VRAM_A_OFFS_0K,256*192*2);
	loadVRAMIndirect( "nitro:/gfx/metaballs.pal.bin", PALRAM_A,256*2);
}

int ballRound = 0;
void MetaBallsA(int t) {
	loadVRAMIndirect( "nitro:/gfx/metaballs.pal.bin", PALRAM_A,256*2);
	static uint8_t ri = 0;
	ri++;
	uint8_t tti = 0;
	uint8_t inti = 0;
	DSMatrixMode(DS_POSITION);
	DSLoadIdentity();

	#define BALLMULT 8
	
	ballp[0].x = -14*BALLMULT+(isin(t<<3))/90;
	ballp[0].y = -12*BALLMULT+(icos(t<<3))/110;
	ballp[0].z = -10*BALLMULT;
	ballp[0].c = 1;
	ballp[1].x = -14*BALLMULT;
	ballp[1].y = -12*BALLMULT+(icos(t<<3))/80;
	ballp[1].z = -10*BALLMULT+(isin(t<<4))/100;
	ballp[1].c = 1;
	ballp[2].x = -12*BALLMULT+(icos(t<<3))/130;;
	ballp[2].y = -14*BALLMULT;
	ballp[2].z = -10*BALLMULT+(isin(t<<4))/100;
	ballp[2].c = 1;
	
	uint32_t det = 0;
	uint32_t dett = 0;
	for( int x = 0; x < 20; x++ ) {
		for( int y = ballRound; y < ballRound+8; y++ ) {
			for( int z = 0; z < 20; z++ ) {
				det = 0;
				for( int i = 0; i < 3; i++ ) {
					int dx = ballp[i].x+x*BALLMULT;
					int dy = ballp[i].y+y*BALLMULT;
					int dz = ballp[i].z+z*BALLMULT;
					dett = dx*dx+dy*dy+dz*dz;
					if( dett > BALLMULT*BALLMULT ) {
						dett = (BALLMULT*BALLMULT*BALLMULT)/dett;
						det += dett;
					}
				}
				if(det > 0 ) {
					inti = tti++ + ri;
					uint16_t cc = rainbowTable[inti]|0x8000;
					SetBoxAt(&balls,x,y,z,cc,det);
				}
				else {
					SetBoxAt(&balls,x,y,z,0,0);
				}
			}
		}
	}
	ballRound += 8;
	if(ballRound == 24 ) {
		ballRound = 0;
	}

	// Move things
	DSTranslatef(0,0,-15);
	DSRotateXi(t);
	DSRotateZi(-t<<2);
	DSRotateYi(t>>3);
	DrawBoxBlock(&balls);
	DSSwapBuffers(0);
}

uint8_t effect5_update( uint32_t t ) {

	int dx=icos(t*8)>>4;
	int dy=isin(t*8)>>4;
	BG3X_A=-128*dx-92*dy+(128<<8)+t<<2;
	BG3Y_A=+128*dy-92*dx+(92<<8)+t<<1;
	BG3PA_A=dx;
	BG3PB_A=dy;
	BG3PC_A=-dy;
	BG3PD_A=dx;
	
	MetaBallsA(t);
	
	return 0;
}


void effect5_destroy() {
	CleanupBoxBlock(&balls);
}

