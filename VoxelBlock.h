#ifndef __VOXELBLOCK_H__
#define __VOXELBLOCK_H__

#include "Utils.h"

typedef struct Voxel
{
		uint16_t colour;
		uint8_t patterns[6];
} Voxel;

typedef struct VoxelBlock
{
	int width,height,depth;
	Voxel *voxels;
} VoxelBlock;

void InitVoxelBlock(VoxelBlock *self,int width,int height,int depth,uint16_t *voxels);
void CleanupVoxelBlock(VoxelBlock *self);

Voxel *VoxelStructAt(VoxelBlock *self,int x,int y,int z);
void SetVoxelAt(VoxelBlock *self,int x,int y,int z,uint16_t val);

static inline uint16_t VoxelAt(VoxelBlock *self,int x,int y,int z) { return VoxelStructAt(self,x,y,z)->colour; }
static inline uint16_t MakeVoxel(int r,int g,int b) { return 0x8000|r|(g<<5)|(b<<10); }
static inline int VoxelRed(uint16_t voxel) { return voxel&0x1f; }
static inline int VoxelGreen(uint16_t voxel) { return (voxel>>5)&0x1f; }
static inline int VoxelBlue(uint16_t voxel) { return (voxel>>10)&0x1f; }
static inline bool IsVoxelFilled(uint16_t voxel) { return (voxel&0x8000)?true:false; }
static inline bool IsVoxelFilledAt(VoxelBlock *self,int x,int y,int z) { return IsVoxelFilled(VoxelAt(self,x,y,z)); }

void DrawVoxelBlock(VoxelBlock *self);
void RefreshVoxelBlock(VoxelBlock *self);

void ScrollVoxelBlockByZ(VoxelBlock *self);

#endif
