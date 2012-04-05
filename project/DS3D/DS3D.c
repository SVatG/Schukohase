#include "DS3D.h"

#include <string.h>




//
// Control functions, direct access only.
//

void DSInit3D()
{
	while(GXSTAT&(1<<27));

	GXSTAT|=(1<<29);
	DSResetMatrixStack();
	DSSwapBuffers(0);
	DISP3DCNT=0;
	DSClearParams(0,0,0,31,0);
	DSClearDepth(DS_MAX_DEPTH);

	TEXIMAGE_PARAM=0;
	POLYGON_ATTR=0;

	DSFreeAllTextures();
//	DSFreeAllPalettes();
}

void DSResetMatrixStack()
{
	DSMatrixMode(DS_TEXTURE);
	DSLoadIdentity();

	// make sure there are no push/pops that haven't executed yet
	while(GXSTAT&(1<<14)) GXSTAT|=1<<15; // clear push/pop errors or push/pop busy bit never clears

	DSMatrixMode(DS_PROJECTION);
	// pop the projection stack to the top; poping 0 off an empty stack causes an error... weird?
	if((GXSTAT&(1<<13))!=0) DSPopMatrix(1);
	DSLoadIdentity();

	// 31 deep modelview matrix; 32nd entry works but sets error flag
	DSMatrixMode(DS_MODELVIEW);
	DSPopMatrix((GXSTAT>>8)&0x1F);
	DSLoadIdentity();
}




//
// Implementations for functions that can either use direct access or
// be compiled to display lists.
//

void DSLookAtvImpl(ivec3_t eye,ivec3_t lookat,ivec3_t up,DSPortFunction *p)
{
	ivec3_t forward=ivec3norm(ivec3sub(eye,lookat));
	ivec3_t side=ivec3norm(ivec3cross(up,forward));
	ivec3_t newup=ivec3cross(forward,side);

	DSMultMatrix4x3Impl(imat4x3(
		   side.x,   side.y,   side.z,-ivec3dot(eye,side),
		     up.x,     up.y,     up.z,-ivec3dot(eye,up),
		forward.x,forward.y,forward.z,-ivec3dot(eye,forward)
	),p);
}




//
// Display list functions.
//

uint32_t *startoflist,*endoflist,*commandheader,*listpos;
int commandcount,paramsleft;

void DSStartList(uint32_t *list,int size)
{
	startoflist=list;
	endoflist=list+size;
	listpos=list+1;
	commandcount=4;
	paramsleft=0;
}

int DSFinishList(uint32_t *list)
{
	if(startoflist<endoflist)
	{
		if(listpos<=endoflist) *startoflist=listpos-startoflist-1;
		else *startoflist=endoflist-startoflist-1;
	}
	return listpos-startoflist;
}

void DSAppendList(const uint32_t *list)
{
	int count=*list;
	for(int i=0;i<count;i++)
	{
		if(listpos<endoflist) *listpos=list[i+1];
		listpos++;
	}
	commandcount=4;
	paramsleft=0;
}

void DSList(volatile uint32_t *port,uint32_t value)
{
	static const uint8_t paramtable[]=
	{
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 1, 0, 1, 1, 1, 0,16,12,16,12, 9, 3, 3, 0, 0, 0,
		 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
		 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 1, 0,/*0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,*/
	};

	if(paramsleft==0)
	{
		uint32_t command=(((uint32_t)port)&0x3ff)>>2;
		int params=paramtable[command];

		if(commandcount>=4 || params==0)
		{
			commandheader=listpos++;
			if(commandheader<endoflist) *commandheader=command;
			commandcount=1;
		}
		else
		{
			if(commandheader<endoflist)
			*commandheader=*commandheader|(command<<commandcount*8);
			commandcount++;
		}

		if(params==0) return;
		paramsleft=params;
	}

	if(listpos<endoflist) *listpos=value;
	listpos++;
	paramsleft--;
}

void DC_FlushRange(const void *base,uint32_t size); // kludge

// http://nocash.emubase.de/gbatek.htm#ds3dgeometrycommands
void DSCallList(const uint32_t *list)
{
	uint32_t count=*list++;

	// flush the area that we are going to DMA
	DC_FlushRange(list,count*4);

	// Don't start DMAing while anything else is being DMAed
	// because FIFO DMA is touchy as hell
	while((DMA0CNT&DMAxCNT_ENABLE)||(DMA1CNT&DMAxCNT_ENABLE)||
	(DMA2CNT&DMAxCNT_ENABLE)||(DMA3CNT&DMAxCNT_ENABLE));

	// send the packed list asynchronously via DMA to the FIFO
	DMA0SAD=list;
	DMA0DAD=&GXFIFO;
	DMA0CNT=count|DMAxCNT_ENABLE|DMAxCNT_32_BIT|DMAxCNT_SRC_INC|DMAxCNT_DEST_FIX|DMAxCNT_START_FIFO;
	while(DMA0CNT&DMAxCNT_ENABLE);
}




//
// Texture handling and allocation functions.
//

static uint32_t next_texture_block;
static uint32_t next_palette_block;

uint32_t DSTextureSize(uint32_t flags)
{
	uint32_t pixels=1<<(((flags>>20)&7)+((flags>>23)&7)+6);

	switch(flags&DS_TEX_FORMAT_MASK)
	{
		case DS_TEX_FORMAT_A3I5:
		case DS_TEX_FORMAT_PAL8:
		case DS_TEX_FORMAT_A5I3:
			return pixels;

		case DS_TEX_FORMAT_NONE:
		case DS_TEX_FORMAT_COMPRESSED:
			return 0;

		case DS_TEX_FORMAT_RGB:
			return pixels*2;

		case DS_TEX_FORMAT_PAL2:
			return pixels/4;

		case DS_TEX_FORMAT_PAL4:
			return pixels/2;
	}
	return 0;
}

uint16_t *DSTextureAddress(uint32_t texture)
{
	return (uint16_t *)(((texture&0xffff)<<3)|0x6800000);
}

static int VRAMAddressIsTextureBank(uint32_t addr)
{
	if((uint16_t *)addr<VRAM_LCDC_A) return 0;
	else if((uint16_t *)addr<VRAM_LCDC_B) return (VRAMCNT_A&3)==(VRAMCNT_A_TEXTURE&3);
	else if((uint16_t *)addr<VRAM_LCDC_C) return (VRAMCNT_B&3)==(VRAMCNT_B_TEXTURE&3);
	else if((uint16_t *)addr<VRAM_LCDC_D) return (VRAMCNT_C&3)==(VRAMCNT_C_TEXTURE&3);
	else if((uint16_t *)addr<VRAM_LCDC_E) return (VRAMCNT_D&3)==(VRAMCNT_D_TEXTURE&3);
	else return 0;
}

uint32_t DSAllocTexture(uint32_t flags)
{
	uint32_t size=DSTextureSize(flags);
	uint32_t addr=next_texture_block;

	next_texture_block+=size;

	// Bug: does not handle non-contiguous texture memory gracefully with large allocations
	while(!VRAMAddressIsTextureBank(next_texture_block-1) && next_texture_block<=(uint32_t)VRAM_LCDC_E)
	{
		addr=next_texture_block=(next_texture_block&~0x1ffff)+0x20000;
		next_texture_block+=size;
	}

	if(next_texture_block>(uint32_t)VRAM_LCDC_E) return DS_INVALID_TEXTURE;

	return flags|((addr>>3)&0xffff);
}

void DSFreeAllTextures()
{
	next_texture_block=(uint32_t)VRAM_LCDC_A;
}

void DSCopyTexture(uint32_t texture,void *data)
{
	uint32_t size=DSTextureSize(texture);
	void *dest=DSTextureAddress(texture);

	uint32_t vramtmp=SaveAndSetMemoryBanks(VRAMCNT_A_LCDC,VRAMCNT_B_LCDC,VRAMCNT_C_LCDC,VRAMCNT_D_LCDC);
	memcpy(dest,data,size); // TODO: check if this works right
	RestoreMemoryBanks(vramtmp);
}

uint32_t DSAllocAndCopyTexture(uint32_t flags,void *data)
{
	uint32_t tex=DSAllocTexture(flags);
	if(tex==DS_INVALID_TEXTURE) return DS_INVALID_TEXTURE;
	DSCopyTexture(tex,data);
	return tex;
}




//
// Fog functions.
//

void DSSetFogWithCallback(uint8_t r,uint8_t g,uint8_t b,uint8_t a,
int32_t start,int32_t end,int32_t near,int32_t far,
int32_t (*callback)(int32_t z,int32_t start,int32_t end))
{
	uint32_t control=DISP3DCNT&~0xf00;

	uint32_t startdepth=imul(0x7fff,idiv(imul(far,near-start),imul(start,near-far)));
	uint32_t enddepth=imul(0x7fff,idiv(imul(far,near-end),imul(end,near-far)));

	uint32_t diff=enddepth-startdepth-1;
	int log=0;
	while(diff>>=1) log++;

	int shift=14-log;
	if(shift>10) shift=10;

	DISP3DCNT=control|DS_FOG_SHIFT(shift);

	FOG_COLOR=((a&0x1f)<<16)|DSPackRGB5(r,g,b);
	FOG_OFFSET=startdepth;

	for(int i=0;i<32;i++)
	{
		uint32_t depth=startdepth+i*(0x400>>shift);
		if(i==0) FOG_TABLE[i]=imul(0x7f,callback(start,start,end));
		else if(depth>=enddepth) FOG_TABLE[i]=imul(0x7f,callback(end,start,end));
		else FOG_TABLE[i]=imul(0x7f,
		callback(idiv(imul(far,near),far+imul(idiv(depth,0x7fff),near-far)),
		start,end));
	}
}

static int32_t LinearZCallback(int32_t z,int32_t start,int32_t end)
{
	return idiv(z-start,end-start);
}

void DSSetFogLinearf32(uint8_t r,uint8_t g,uint8_t b,uint8_t a,int32_t start,int32_t end,int32_t near,int32_t far)
{
	DSSetFogWithCallback(r,g,b,a,start,end,near,far,LinearZCallback);
}

void DSSetFogLinearf(uint8_t r,uint8_t g,uint8_t b,uint8_t a,float start,float end,float near,float far)
{
	DSSetFogLinearf32(r,g,b,a,DSf32(start),DSf32(end),DSf32(near),DSf32(far));
}

