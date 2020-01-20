#include <nds.h>
#include <nds/fifocommon.h>
#include <stdlib.h>
#include <nds/registers_alt.h>
#include "Hardware.h"

#include "DS3D.h"

volatile s16 linepos = 0;
volatile s32 ipos = 0;
volatile float rz = 1.0;
volatile float rzdir = 10.0;
void hblank2() {
	linepos = (linepos + 3) % (270*3);

	s32 xdx = (s32)( icos( (ipos + linepos << 4) >> 5 ) / rz);
	s32 xdy = (s32)(-isin( (ipos + linepos << 4) >> 5 ) / rz);
	s32 ydx = (s32)( isin( (ipos + linepos << 4) >> 5 ) / rz);
	s32 ydy = (s32)( icos( (ipos + linepos << 4) >> 5 ) / rz);

	BG2_XDX = xdx;
	BG2_XDY = xdy;
	BG2_YDX = ydx;
	BG2_YDY = ydy;

	BG3_XDX = xdx >> 3;
	BG3_XDY = xdy >> 3;
	BG3_YDX = ydx >> 3;
	BG3_YDY = ydy >> 3;
}

static inline cube(float xpos, float ypos, float zpos) {
	DSBegin(DS_QUADS);

	DSNormal3f(0,0,1);
	DSVertex3f(-0.5+xpos,-0.5+ypos,0.5+zpos);
	DSVertex3f(0.5+xpos,-0.5+ypos,0.5+zpos);
	DSVertex3f(0.5+xpos,0.5+ypos,0.5+zpos);
	DSVertex3f(-0.5+xpos,0.5+ypos,0.5+zpos);

	DSNormal3f(0,0,-1);
	DSVertex3f(0.5+xpos,-0.5+ypos,-0.5+zpos);
	DSVertex3f(-0.5+xpos,-0.5+ypos,-0.5+zpos);
	DSVertex3f(-0.5+xpos,0.5+ypos,-0.5+zpos);
	DSVertex3f(0.5+xpos,0.5+ypos,-0.5+zpos);

	DSNormal3f(1,0,0);
	DSVertex3f(0.5+xpos,-0.5+ypos,0.5+zpos);
	DSVertex3f(0.5+xpos,-0.5+ypos,-0.5+zpos);
	DSVertex3f(0.5+xpos,0.5+ypos,-0.5+zpos);
	DSVertex3f(0.5+xpos,0.5+ypos,0.5+zpos);

	DSNormal3f(-1,0,0);
	DSVertex3f(-0.5+xpos,-0.5+ypos,-0.5+zpos);
	DSVertex3f(-0.5+xpos,-0.5+ypos,0.5+zpos);
	DSVertex3f(-0.5+xpos,0.5+ypos,0.5+zpos);
	DSVertex3f(-0.5+xpos,0.5+ypos,-0.5+zpos);

	DSNormal3f(0,1,0);
	DSVertex3f(-0.5+xpos,0.5+ypos,0.5+zpos);
	DSVertex3f(0.5+xpos,0.5+ypos,0.5+zpos);
	DSVertex3f(0.5+xpos,0.5+ypos,-0.5+zpos);
	DSVertex3f(-0.5+xpos,0.5+ypos,-0.5+zpos);

	DSNormal3f(0,-1,0);
	DSVertex3f(-0.5+xpos,-0.5+ypos,-0.5+zpos);
	DSVertex3f(0.5+xpos,-0.5+ypos,-0.5+zpos);
	DSVertex3f(0.5+xpos,-0.5+ypos,0.5+zpos);
	DSVertex3f(-0.5+xpos,-0.5+ypos,0.5+zpos);

	DSEnd();
}

int flip = 1;
void RenderCube(int t)
{
	DSMatrixMode(DS_MODELVIEW);
	DSLoadIdentity();

	DSTranslatef(-0.95,0.45,-0.3);
	DSRotateYi(t*16);
	DSRotateXi(t*15);

	DSMaterialDiffuseAndAmbient6b(20,20,20,12,12,12);
	DSMaterialSpecularAndEmission6b(0,0,0,0,0,0,0);

	DSPolygonAttributes(DS_POLY_ALPHA(31)|DS_POLY_CULL_BACK|DS_POLY_LIGHT0);

	s32 white = 0xFFFFFFFF;
	if( flip ) {
		VRAMCNT_D = VRAMCNT_D_LCDC;
		VRAMCNT_A = VRAMCNT_A_BG_VRAM_A_OFFS_0K;
		for( int i = 0; i < 128; i++ ) {
			dmaCopyWordsAsynch( 0, (u16*)BG_BMP_RAM( 0 )+256*(i+1), (u16*)(BG_BMP_RAM( 0 )+(127-i)*256+128), 256 );
		}
		dmaCopyWordsAsynch( 1, (u16*)BG_BMP_RAM( 0 ), (u16*)(BG_BMP_RAM( 4 ) ), 512*128 );
		REG_DISPCAPCNT =
			DISPCAPCNT_WRITE_VRAM_D | DISPCAPCNT_SIZE_256x128 |
			DISPCAPCNT_SRC_A_SCREEN | DISPCAPCNT_SRC_A_3D | DISPCAPCNT_ENABLE;
	}
	else {
		VRAMCNT_A = VRAMCNT_A_LCDC;
		VRAMCNT_D = VRAMCNT_D_BG_VRAM_A_OFFS_0K;
		for( int i = 0; i < 128; i++ ) {
			dmaCopyWordsAsynch( 0, (u16*)BG_BMP_RAM( 0 )+256*(i+1), (u16*)(BG_BMP_RAM( 0 )+(127-i)*256+128), 256 );
		}
		dmaCopyWordsAsynch( 1, (u16*)BG_BMP_RAM( 0 ), (u16*)(BG_BMP_RAM( 4 ) ), 512*128 );
		REG_DISPCAPCNT =
			DISPCAPCNT_WRITE_VRAM_A | DISPCAPCNT_SIZE_256x128 |
			DISPCAPCNT_SRC_A_SCREEN | DISPCAPCNT_SRC_A_3D | DISPCAPCNT_ENABLE;
	}
	flip^=1;

	DSColor3f( 1, 1, 1 );

	cube(0, 0, 0.0f);

	DSRotateYi(512);
	DSRotateXi(512);
	DSRotateZi(512);
	cube(0, 0, 0.0f);

	DSRotateYi(512);
	DSRotateXi(512);
	DSRotateZi(512);
	cube(0, 0, 0.0f);

	DSSwapBuffers(0);
}

void effect3_init() {
	u16* master_bright = (u16*)(0x400006C);
	memset( master_bright, (1<<6) | 16, 2 );
	u16* master_bright_sub = (u16*)(0x400106C);
	memset( master_bright_sub, (1<<7) | 16, 2 );

	irqSet( IRQ_HBLANK, hblank2 );
	irqEnable( IRQ_HBLANK );
	
	videoSetMode( MODE_5_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG2_ACTIVE );

	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_ANTIALIAS|DS_ALPHA_BLEND);
	DSClearParams(31,31,31,31,63);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspective(70,256.0/192.0,1,32);
	DSLookAt(0.0, 0.0, 1.9, //camera possition
	         0.0, 0.0, 0.0, //look at
	         0.0, 1.0, 0.0); //up

	DSLight3b3f(0,20,20,20,0.5,-0.5,-1);

	DSSetFogLinearf(0,0,0,31,2,6,1,32);
	DSMaterialShinyness();

	VRAMCNT_A = VRAMCNT_A_BG_VRAM_A_OFFS_0K;
	BG2CNT_A = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_BITMAP_BASE_0K;
	BG2CNT_A = (BG2CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	BG2_XDX = (1 << 10);
	BG2_XDY = 0;
	BG2_YDX = 0;
	BG2_YDY = (1 << 10);
	BG2_CX = 0;
	BG2_CY = 0;

	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_128K;
	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_128K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_2;
	BG3_XDX = (1 << 7);
	BG3_XDY = 0;
	BG3_YDX = 0;
	BG3_YDY = (1 << 7);
	BG3_CX = 0;
	BG3_CY = 0;

 	u16* screen = (u16*)BG_BMP_RAM( 8 );
	load8bVRAMIndirect( "nitro:/gfx/kugeln.img.bin", screen, 256*256 );
	loadVRAMIndirect( "nitro:/gfx/kugeln.pal.bin", PALRAM_A, 256 * 2 );

	BLEND_CR = BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_DST_BG3;
	BLEND_AB = 0x0E | (0x0F << 8);

	DISPCNT_B = DISPCNT_MODE_5 | DISPCNT_BG3_ON | DISPCNT_BG2_ON | DISPCNT_ON;
	VRAMCNT_C = VRAMCNT_C_BG_VRAM_B;

	BG2CNT_B = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_SCREEN_BASE(0);
	BG2CNT_B = (BG2CNT_B&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG2PA_B = (1 << 8);
	BG2PB_B = 0;
	BG2PC_B = 0;
	BG2PD_B = (1 << 8);
	BG2X_B = 0;
	BG2Y_B = 0;

	BG3CNT_B = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_64K;
	BG3CNT_B = (BG3CNT_B&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	BG3PA_B = (1 << 8);
	BG3PB_B = 0;
	BG3PC_B = 0;
	BG3PD_B = (1 << 8);
	BG3X_B = 0;
	BG3Y_B = 0;

	u16* sub_bg = (u16*)VRAM_B_OFFS_0K;
	u16* sub_hand = (u16*)VRAM_B_OFFS_64K;

	load8bVRAMIndirect( "nitro:/gfx/text.img.bin", sub_bg, 256*192 );
	load8bVRAMIndirect( "nitro:/gfx/standing.img.bin", sub_hand, 256*256 );
	loadVRAMIndirect( "nitro:/gfx/standing.pal.bin", PALRAM_B, 256 * 2 );
}

u8 effect3_update( u32 t ) {
	
	linepos = 0;
	ipos += 2;
	rz += rzdir*2;
	if( rz >= 14 ) {
		rzdir = -0.04;
	}
	if( rz <= 0.2 ) {
		rzdir = 0.04;
	}
	BG2_CX = ipos << 10;
	BG2_CY = ipos << 9;
 	BG3_CX = ipos << 7;
	BG3_CY = ipos << 6;

	float zoom = (icos( t<<4 )*0.001 + 4.1) * 5+1.5;
	s32 xdx = (s32)( icos( t<<3 ) / zoom);
	s32 xdy = (s32)( isin( t<<3 ) / zoom);
	s32 ydx = (s32)(-isin( t<<3 ) / zoom);
	s32 ydy = (s32)( icos( t<<3 ) / zoom);

	SUB_BG3_XDX = xdx >> 3;
	SUB_BG3_XDY = xdy >> 3;
	SUB_BG3_YDX = ydx >> 3;
	SUB_BG3_YDY = ydy >> 3;
	BG3X_B = 128<<8;
	BG3Y_B = 128<<8;

	BG2Y_B = -t<<11;
	
	RenderCube( t*3 );

	if( t == 720 ) {
		return( 1 );
	}

	if( t <= 16 ) {
		u16* master_bright = (u16*)(0x400006C);
		memset( master_bright, (1<<6) | (16-t), 2 );
		u16* master_bright_sub = (u16*)(0x400106C);
		memset( master_bright_sub, (1<<7) | (16-t), 2 );
	}

	if( t >= 704 ) {
		u16* master_bright = (u16*)(0x400006C);
		memset( master_bright, (1<<6) | (t-704), 2 );
	}
	
	return( 0 );
}


void effect3_destroy() {
	irqDisable( IRQ_HBLANK );
}
