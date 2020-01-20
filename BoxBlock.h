#ifndef __BOXBLOCK_H__
#define __BOXBLOCK_H__

#include "Utils.h"

typedef struct Box
{
		uint16_t colour;
		uint8_t size;
} Box;

typedef struct BoxBlock
{
	int width,height,depth;
	Box *boxes;
} BoxBlock;

void InitBoxBlock(BoxBlock *self,int width,int height,int depth);
void CleanupBoxBlock(BoxBlock *self);
void SetBoxAt(BoxBlock *self,int x,int y,int z,uint16_t val,uint8_t size);
void DrawBoxBlock(BoxBlock *self);
static inline bool IsBoxFilled(uint16_t voxel) { return (voxel&0x8000)?true:false; }

#endif
