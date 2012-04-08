// AO Cubes

#include <nds.h>

#include "DS3D/Utils.h"
#include "DS3D/DS3D.h"
#include "VoxelBlock.h"
#include "Hardware.h"
#include "Loader.h"
#include "RainbowTable.h"

int cubemode = 0;

VoxelBlock block;
VoxelBlock block2;
u16 aocubepal[512];

greets_len = 848;
char* greets =
 "###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
"###### " \
"    #  " \
"   #   " \
"  #    " \
" #     " \
"###### " \
"       " \
"  ###  " \
" #   # " \
"#     #" \
"#     #" \
"       " \
" #   # " \
"#  #  #" \
"#  #  #" \
"#  #  #" \
"#  #  #" \
"#  #  #" \
" ## ## " \
"       " \
"#     #" \
"#     #" \
" #   # " \
"  ###  " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"       " \
"       " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" #  #  " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"#    # " \
"##   # " \
"# #  # " \
"#  # # " \
"#   ## " \
"#    # " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"    #  " \
"   #   " \
"   #   " \
"    #  " \
"###### " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"###### " \
"   #   " \
"   #   " \
"   #   " \
"   #   " \
"###### " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"       " \
"       " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" #  #  " \
"       " \
" ##### " \
"#      " \
"#      " \
"#      " \
"#      " \
" ##### " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"     # " \
"    #  " \
"####   " \
"    #  " \
"     # " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"   #   " \
"   #   " \
"  ##   " \
" #  #  " \
"#    # " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"# #  # " \
"# #  # " \
" ## #  " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"###### " \
"    #  " \
"   #   " \
"  #    " \
" #     " \
"###### " \
"       " \
"###### " \
"   #   " \
"   #   " \
"  ##   " \
" #  #  " \
"#    # " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"       " \
"###### " \
"    #  " \
"   #   " \
"  #    " \
" #     " \
"###### " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"   #   " \
"   #   " \
"  ##   " \
" #  #  " \
"#    # " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ## #  " \
"       " \
" ##### " \
"#      " \
"#      " \
"#      " \
"#      " \
" ##### " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
" #  #  " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ##    " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
"  #  # " \
"   ##  " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"###### " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" #  #  " \
"       " \
"###### " \
"   #   " \
"   #   " \
"   #   " \
"   #   " \
"###### " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"# #  # " \
"# #  # " \
" ## #  " \
"       " \
" ##### " \
"#      " \
"#      " \
"#      " \
"#      " \
" ##### " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"###### " \
"   #   " \
"   #   " \
"  ##   " \
" #  #  " \
"#    # " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ## #  " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
" ##### " \
"#      " \
"#      " \
"#      " \
"#      " \
" ##### " \
"       " \
" #  #  " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ##    " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" #  #  " \
"       " \
"###### " \
"   #   " \
"   #   " \
"   #   " \
"   #   " \
"###### " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"# #  # " \
"# #  # " \
" ## #  " \
"       " \
"###### " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"       " \
"       " \
"       " \
" #  #  " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ##    " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" ####  " \
"       " \
"###### " \
"   # # " \
"   # # " \
"   # # " \
"   # # " \
"     # " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"###### " \
" #     " \
"  #    " \
"  #    " \
" #     " \
"###### " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" ####  " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"  #### " \
" #     " \
"#      " \
"#      " \
" #     " \
"  #### " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" ####  " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
"  #  # " \
"   ##  " \
"       " \
"###### " \
"    #  " \
"   #   " \
"   #   " \
"    #  " \
"###### " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"###### " \
"    #  " \
"   #   " \
"  #    " \
" #     " \
"###### " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" ####  " \
"       " \
"####   " \
"  # #  " \
"  #  # " \
"  #  # " \
"  # #  " \
"####   " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"###### " \
"   #   " \
"   #   " \
"  ##   " \
" #  #  " \
"#    # " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
"###### " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"# #  # " \
"# #  # " \
" ## #  " \
"       " \
"###### " \
"   #   " \
"   #   " \
"   #   " \
"   #   " \
"###### " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ## #  " \
"       " \
"###### " \
"  #  # " \
"  #  # " \
"  #  # " \
" ##  # " \
"#  ##  " \
"       " \
"###### " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
"#    # " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
"###### " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"# #  # " \
"# #  # " \
" ## #  " \
"       " \
"###### " \
"   #   " \
"   #   " \
"   #   " \
"   #   " \
"###### " \
"       " \
"     # " \
"     # " \
"###### " \
"     # " \
"     # " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ## #  " \
"       " \
"###### " \
"#      " \
"#      " \
"#      " \
"#      " \
"#      " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" ####  " \
"       " \
"###### " \
" #     " \
"  #    " \
"  #    " \
" #     " \
"###### " \
"       " \
" #     " \
"#      " \
"#      " \
"#      " \
"#      " \
" ##### " \
"       " \
" ####  " \
"#    # " \
"#    # " \
"#    # " \
"#    # " \
" ####  " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ## #  " \
"       " \
"###### " \
"#  # # " \
"#  # # " \
"#  # # " \
"#  # # " \
" ## #  " \
"       " \
"       " \
"       " \
"       ";

int placeIndex = 0;
int curGreets = 0;

extern volatile int unts;
extern volatile int unts_proc;

void effect6_init() {
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

	InitVoxelBlock(&block,7,7,64,NULL);

	// Background
	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_0K;
	
	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_TRANSPARENT | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG3PA_A = (1 << 8);
	BG3PB_A = 0;
	BG3PC_A = 0;
	BG3PD_A = (1 << 8);
	BG3X_A = 0;
	BG3Y_A = 0;

	if( cubemode == 0 ) {
		load8bVRAMIndirect( "nitro:/gfx/aocubes.img.bin", VRAM_A_OFFS_0K,256*192*2);
		loadVRAMIndirect( "nitro:/gfx/aocubes.pal.bin", PALRAM_A,256*2);
		loadVRAMIndirect( "nitro:/gfx/aocubes.pal.bin", aocubepal,256*2);
	}
	else {
		uint16_t* bg = VRAM_A_OFFS_128K;
		for( int i = 0; i < 256*256; i++ ) {
			bg[i] = 0;
		}
		load8bVRAMIndirect( "nitro:/gfx/svatg.img.bin", VRAM_A_OFFS_128K,256*256);
		loadVRAMIndirect( "nitro:/gfx/svatg.pal.bin", PALRAM_A,256*2);
	}
	
	if( cubemode == 1 ) {
		
		// Other version.
		s16* bg = (u16*)(VRAM_A_OFFS_0K);
		for( int i = 0; i < 256*192; i++ ) {
			u16 c = ((i+1)%3) == 0 ? 5 : 0;
			c = ((i+2)%3) == 0 ? 26 : 23;
			bg[i] = 0|(int)(c*0.5)<<5|c|0x8000;
		}
				
		DISPCNT_A |= DISPCNT_BG3_ON | DISPCNT_BG2_ON;
		BG3CNT_A = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
		BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
		BG0CNT_A = (BG0CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_2;
		BG3PA_A = dx;
		BG3PB_A = dy;
		BG3PC_A = -dx;
		BG3PD_A = dy;
		BG3X_A = 0;
		BG3Y_A = 0;

		// Background
		BG2CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_128K;
		BG2CNT_A = (BG2CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
		BG2PA_A = (1 << 8);
		BG2PB_A = 0;
		BG2PC_A = 0;
		BG2PD_A = (1 << 8);
		BG2X_A = 0;
		BG2Y_A = -31500;

		int dx = icos(128)/26.5;
		int dy = isin(128)/26.5;
		BG3PA_A=dx;
		BG3PB_A=dy;
		BG3PC_A=-dy;
		BG3PD_A=dx;
		BG3X_A=-128*dx-92*dy+(128<<8)+7000;
		BG3Y_A=+128*dy-92*dx+(92<<8)+5000;
	}

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

	loadImage( "nitro:/gfx/arschgeige_3.img.bin", VRAM_B_OFFS_0K,256*192*2);
}

void voxelSpiral(int t) {
	// Kludge
	static int lt = 0;
	lt++;
	t = lt;
	
	static uint8_t ri = 0;
	DSMatrixMode(DS_POSITION);
	DSLoadIdentity();
	
	// Cross
	for( int i = 0; i < 3; i++ ) {
		SetVoxelAt(&block2,i,1,1,rainbowTable[ri]|0x8000);
		SetVoxelAt(&block2,1,i,1,rainbowTable[(ri+10)%255]|0x8000);
		SetVoxelAt(&block2,1,1,i,rainbowTable[(ri+30)%255]|0x8000);
	}
	RefreshVoxelBlock(&block2);
	
	// Move blocks
	if(t%2==0) {
		ScrollVoxelBlockByZ(&block);
		placeIndex++;
	}

	// Spiral rainbows
	for(int i = 0; i < 7; i++) {
		if(placeIndex < greets_len) {
			if(greets[placeIndex*7+i] == '#') {
				SetVoxelAt(&block,i,8,0,0xFFFF);
			}
			else {
				SetVoxelAt(&block,i,8,0,0);
			}
		}
		else {

		}
	}
	RefreshVoxelBlock(&block);

	// Move things
// 	DSTranslatef(-300,0,200);
// 	DSRotateYi(-(120<<2));
// 	DSRotateZi(120<<2);
	DSScalef(8,8,8);
	DSTranslatef32(DSf32(-5),DSf32(20),((t&2)<<10)-DSf32(15));
	DSRotateXi(-200<<2);
	DrawVoxelBlock(&block);
	DSSwapBuffers(0);
}

void objectShow(int t) {
	static uint8_t ri = 0;
	DSMatrixMode(DS_POSITION);
	DSLoadIdentity();

	DSSwapBuffers(0);
}

int bluh = 0;
int blah = 0;

uint8_t effect6_update( uint32_t t ) {
	voxelSpiral(t);


// 	if( cubemode != 1 ) {
// 		static u16 colpal[70];
// 		u16 col;
// 		for( int i = 0; i < 70; i++ ) {
// 			s16 val = unts * 5;
// 
// 			colpal[i] = col;
// 		}
// 		dmaCopyHalfWords( 0, colpal, PALRAM_A, 2*70 );
// 	}

	if(unts == 1) {
		bluh = 2;
		unts_proc = 0;
	}
	if( bluh > 0) {
		BG2PA_B = (1 << 8) * 0.9;
		BG2PD_B = (1 << 8) * 0.9;
		bluh--;
	}
	else {
		BG2PA_B = (1 << 8);
		BG2PD_B = (1 << 8);
	}

	if(unts != 0) {
		blah = 3;
		unts_proc = 1;
	}
	if(blah != 0) {
		memset(PALRAM_A,0xFFFF,512);
		blah--;
	}
	else {
		dmaCopyHalfWords( 0, aocubepal, PALRAM_A, 512 );
	}
	
	return 0;
}


void effect6_destroy() {
	CleanupVoxelBlock(&block);
}

