#include "VoxelBlock.h"
#include "DS3D/DS3D.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>



#define PatternFlipXFlag 0x20
#define PatternFlipYFlag 0x40
#define PatternFlipDiagonalFlag 0x80
#define FullyLitPattern 0x3f
#define NoFacePattern 0x5f
#define NeedsRefreshPattern 0x7f

static uint8_t PatternTable[256]=
{
	0x3f,0x85,0xa5,0x8f,0x05,0x10,0x30,0x9c,0x45,0x50,0x70,0xdc,0x0f,0x1c,0x3c,0x1f,
	0x00,0x86,0xa7,0x91,0x06,0x10,0x32,0x9c,0x47,0xd2,0x73,0xdd,0x11,0x1c,0x3d,0x1f,
	0x20,0x87,0xa6,0xb1,0x26,0x12,0x30,0x9c,0x67,0x53,0xf2,0xfd,0x31,0x1d,0x3c,0x1f,
	0x01,0x89,0xa9,0x95,0x08,0x12,0x32,0x9c,0x4b,0xd8,0xf8,0xde,0x14,0x1d,0x3d,0x1f,
	0x40,0xc6,0xe7,0xd1,0x07,0x92,0x33,0x9d,0x46,0x50,0x72,0xdc,0x51,0x1c,0x7d,0x1f,
	0x81,0x88,0xab,0x94,0x09,0x92,0x38,0x9d,0x49,0xd2,0x78,0xdd,0x15,0x1c,0x3e,0x1f,
	0x02,0x8a,0xea,0x96,0x0a,0x17,0x33,0x9d,0x6a,0x53,0x77,0xfd,0x16,0x1d,0x7d,0x1f,
	0x03,0x8c,0xad,0x99,0x0c,0x17,0x38,0x9d,0x4d,0xd8,0x7a,0xde,0x19,0x1d,0x3e,0x1f,
	0x60,0xc7,0xe6,0xf1,0x27,0x13,0xb2,0xbd,0x66,0x52,0x70,0xdc,0x71,0x5d,0x3c,0x1f,
	0x22,0xca,0xaa,0xb6,0x2a,0x13,0x37,0xbd,0x4a,0x57,0x73,0xdd,0x36,0x5d,0x3d,0x1f,
	0xa1,0x8b,0xa8,0xb4,0x29,0x18,0xb2,0xbd,0x69,0x58,0xf2,0xfd,0x35,0x1e,0x3c,0x1f,
	0x23,0x8d,0xac,0xb9,0x2c,0x18,0x37,0xbd,0x6d,0x5a,0xf8,0xde,0x39,0x1e,0x3d,0x1f,
	0x41,0xc9,0xe9,0xd5,0x0b,0x98,0xb8,0x9e,0x48,0x52,0x72,0xdc,0x54,0x5d,0x7d,0x1f,
	0x43,0xcc,0xed,0xd9,0x0d,0x98,0x3a,0x9e,0x4c,0x57,0x78,0xdd,0x59,0x5d,0x3e,0x1f,
	0x63,0xcd,0xec,0xf9,0x2d,0x1a,0xb8,0x9e,0x6c,0x58,0x77,0xfd,0x79,0x1e,0x7d,0x1f,
	0x04,0x8e,0xae,0x9b,0x0e,0x1a,0x3a,0x9e,0x4e,0x5a,0x7a,0xde,0x1b,0x1e,0x3e,0x1f,
};




void InitVoxelBlock(VoxelBlock *self,int width,int height,int depth,uint16_t *voxels)
{
	self->width=width;
	self->height=height;
	self->depth=depth;

	self->voxels=malloc(width*height*depth*sizeof(self->voxels[0]));

	if(voxels)
	{
		for(int i=0;i<width*height*depth;i++)
		{
			self->voxels[i].colour=voxels[i];
			self->voxels[i].patterns[0]=NeedsRefreshPattern;
		}

		RefreshVoxelBlock(self);
	}
	else
	{
		for(int i=0;i<width*height*depth;i++)
		{
			self->voxels[i].colour=0;
			for(int j=0;j<6;j++) self->voxels[i].patterns[j]=NoFacePattern;
		}
	}
}

void CleanupVoxelBlock(VoxelBlock *self)
{
	free(self->voxels);
}


Voxel *VoxelStructAt(VoxelBlock *self,int x,int y,int z)
{
	static Voxel emptyvoxel={0,NoFacePattern,NoFacePattern,NoFacePattern,NoFacePattern,NoFacePattern,NoFacePattern };
	if(x<0) return &emptyvoxel;
	if(y<0) return &emptyvoxel;
	if(z<0) return &emptyvoxel;
	if(x>=self->width) return &emptyvoxel;
	if(y>=self->height) return &emptyvoxel;
	if(z>=self->depth) return &emptyvoxel;
	return &self->voxels[x+(y+z*self->height)*self->width];
}

inline void SetVoxelAt(VoxelBlock *self,int x,int y,int z,uint16_t val)
{
// 	if(x<0) return;
// 	if(y<0) return;
// 	if(z<0) return;
// 	if(x>=self->width) return;
// 	if(y>=self->height) return;
// 	if(z>=self->depth) return;

	Voxel *voxel=&self->voxels[x+(y+z*self->height)*self->width];

	voxel->colour=val;
	voxel->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x+1,y+1,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x+1,y+1,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x+1,y+1,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x+1,y,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x+1,y,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x+1,y,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x+1,y-1,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x+1,y-1,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x+1,y-1,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x,y+1,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x,y+1,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x,y+1,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x,y,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x,y,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x,y-1,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x,y-1,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x,y-1,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x-1,y+1,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x-1,y+1,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x-1,y+1,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x-1,y,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x-1,y,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x-1,y,z-1)->patterns[0]=NeedsRefreshPattern;

	VoxelStructAt(self,x-1,y-1,z+1)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x-1,y-1,z)->patterns[0]=NeedsRefreshPattern;
	VoxelStructAt(self,x-1,y-1,z-1)->patterns[0]=NeedsRefreshPattern;
}




static uint32_t LightFunction(ivec3_t lightdir,float nx,float ny,float nz);
static void DrawFace(int pattern,int fx,int fy,int fz,int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv);

void DrawVoxelBlock(VoxelBlock *self)
{
	DSMatrixMode(DS_POSITION);
	DSStoreMatrix(0);
	DSTranslatef32(-DSf32(self->width)/2,-DSf32(self->height)/2,-DSf32(self->depth)/2);

	imat4x4_t posmtx=DSGetPositionMatrix();
	imat4x4_t inverse=imat4x4affineinverse(posmtx);
	ivec3_t viewdir=ivec4_xyz(imat4x4_w(inverse));
	ivec3_t lightdir=imat3x3transform(imat4x4_mat3x3(inverse),ivec3(DSf32(-1),DSf32(1),DSf32(2)));

//	Vector viewdir=MakeVector(DSf32(1),DSf32(1),DSf32(-1));

	uint32_t light_x_pos=LightFunction(lightdir,1,0,0);
	uint32_t light_x_neg=LightFunction(lightdir,-1,0,0);
	uint32_t light_y_pos=LightFunction(lightdir,0,1,0);
	uint32_t light_y_neg=LightFunction(lightdir,0,-1,0);
	uint32_t light_z_pos=LightFunction(lightdir,0,0,1);
	uint32_t light_z_neg=LightFunction(lightdir,0,0,-1);

	DSMatrixMode(DS_POSITION);
	DSScalef32(DSf32(4096),DSf32(4096),DSf32(4096));

	DISP3DCNT|=DS_OUTLINE;
	DSPolygonAttributes(DS_POLY_MODE_MODULATION|DS_POLY_CULL_NONE|DS_POLY_LIGHT0|DS_POLY_ALPHA(31));
	DSLight(0,0xffff,0x200);

	DSBegin(DS_QUADS);

	Voxel *voxel=self->voxels;
	for(int z=0;z<self->depth;z++)
	for(int y=0;y<self->height;y++)
	for(int x=0;x<self->width;x++)
	{
		if(IsVoxelFilled(voxel->colour))
		{
			//DSColor(voxel->colour);
			DSMaterialDiffuseAndAmbient(voxel->colour,0);
	
			if(voxel->patterns[0]!=NoFacePattern && viewdir.x<DSinttof32(x))
			{
				DSNormal(light_x_neg);
				DrawFace(voxel->patterns[0],x,y,z,0,1,0,0,0,1);
			}
			if(voxel->patterns[1]!=NoFacePattern && viewdir.x>DSinttof32(x+1))
			{
				DSNormal(light_x_pos);
				DrawFace(voxel->patterns[1],x+1,y,z,0,1,0,0,0,1);
			}
	
			if(voxel->patterns[2]!=NoFacePattern && viewdir.y<DSinttof32(y))
			{
				DSNormal(light_y_neg);
				DrawFace(voxel->patterns[2],x,y,z,0,0,1,1,0,0);
			}
			if(voxel->patterns[3]!=NoFacePattern && viewdir.y>DSinttof32(y+1))
			{
				DSNormal(light_y_pos);
				DrawFace(voxel->patterns[3],x,y+1,z,0,0,1,1,0,0);
			}
	
			if(voxel->patterns[4]!=NoFacePattern && viewdir.z<DSinttof32(z))
			{
				DSNormal(light_z_neg);
				DrawFace(voxel->patterns[4],x,y,z,1,0,0,0,1,0);
			}
			if(voxel->patterns[5]!=NoFacePattern && viewdir.z>DSinttof32(z+1))
			{
				DSNormal(light_z_pos);
				DrawFace(voxel->patterns[5],x,y,z+1,1,0,0,0,1,0);
			}
		}

		voxel++;
	}
	DSEnd();
	DSMatrixMode(DS_POSITION);
	DSRestoreMatrix(0);
}

static inline float TransformRange(float val,float oldlow,float oldhigh,float newlow,float newhigh)
{
	return (val-oldlow)/(oldhigh-oldlow)*(newhigh-newlow)+newlow;
}

static inline float ClampRange(float val,float low,float high)
{
	if(val<low) return low;
	if(val>high) return high;
	return val;
}

static uint32_t LightFunction(ivec3_t lightdir,float nx,float ny,float nz)
{
	float lx=lightdir.x;
	float ly=lightdir.y;
	float lz=lightdir.z;
	float l=sqrt(lx*lx+ly*ly+lz*lz);
	lx/=l; ly/=l; lz/=l;

	float light=ClampRange(TransformRange(lx*nx+ly*ny+lz*nz,-0.5,1,0.5,1),0.5,1);

	return ((int)(light*511))&0x3ff;
}

static void DrawFace(int pattern,int fx,int fy,int fz,int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv)
{
	if(pattern!=FullyLitPattern)
	{
		int index=pattern&0x1f;

		int16_t u1=0,v1=0,u2=DSt16(32),v2=DSt16(32);
		if(pattern&PatternFlipXFlag) { u1=DSt16(32)-u1; u2=DSt16(32)-u2; }
		if(pattern&PatternFlipYFlag) { v1=DSt16(32)-v1; v2=DSt16(32)-v2; }

		DSSetTexture(DS_TEX_ADDRESS(index*32*32/2)|DS_TEX_SIZE_S_32|DS_TEX_SIZE_T_32|DS_TEX_FORMAT_PAL4);

		if(pattern&PatternFlipDiagonalFlag)
		{
			DSTexCoord2t16(v1,u1); DSVertex3v16(fx,fy,fz);
			DSTexCoord2t16(v1,u2); DSVertex3v16(fx+dxdu,fy+dydu,fz+dzdu);
			DSTexCoord2t16(v2,u2); DSVertex3v16(fx+dxdu+dxdv,fy+dydu+dydv,fz+dzdu+dzdv);
			DSTexCoord2t16(v2,u1); DSVertex3v16(fx+dxdv,fy+dydv,fz+dzdv);
		}
		else
		{
			DSTexCoord2t16(u1,v1); DSVertex3v16(fx,fy,fz);
			DSTexCoord2t16(u2,v1); DSVertex3v16(fx+dxdu,fy+dydu,fz+dzdu);
			DSTexCoord2t16(u2,v2); DSVertex3v16(fx+dxdu+dxdv,fy+dydu+dydv,fz+dzdu+dzdv);
			DSTexCoord2t16(u1,v2); DSVertex3v16(fx+dxdv,fy+dydv,fz+dzdv);
		}
	}
	else
	{
		DSSetTexture(0);

		DSVertex3v16(fx,fy,fz);
		DSVertex3v16(fx+dxdu,fy+dydu,fz+dzdu);
		DSVertex3v16(fx+dxdu+dxdv,fy+dydu+dydv,fz+dzdu+dzdv);
		DSVertex3v16(fx+dxdv,fy+dydv,fz+dzdv);
	}
}




static int PickPattern(VoxelBlock *self,int x,int y,int z,int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv);

void RefreshVoxelBlock(VoxelBlock *self)
{
	Voxel *voxel=self->voxels;
	for(int z=0;z<self->depth;z++)
	for(int y=0;y<self->height;y++)
	for(int x=0;x<self->width;x++)
	{
		if(IsVoxelFilled(voxel->colour) && voxel->patterns[0]==NeedsRefreshPattern)
		{
			voxel->patterns[0]=PickPattern(self,x-1,y,z,0,1,0,0,0,1);
			voxel->patterns[1]=PickPattern(self,x+1,y,z,0,1,0,0,0,1);

			voxel->patterns[2]=PickPattern(self,x,y-1,z,0,0,1,1,0,0);
			voxel->patterns[3]=PickPattern(self,x,y+1,z,0,0,1,1,0,0);

			voxel->patterns[4]=PickPattern(self,x,y,z-1,1,0,0,0,1,0);
			voxel->patterns[5]=PickPattern(self,x,y,z+1,1,0,0,0,1,0);
		}
		voxel++;
	}

}

static int PickPattern(VoxelBlock *self,int x,int y,int z,
int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv)
{
	if(IsVoxelFilledAt(self,x,y,z)) return NoFacePattern;

	int pattern=0;
	if(IsVoxelFilledAt(self,x+dxdu,y+dydu,z+dzdu)) pattern|=0x01;
	if(IsVoxelFilledAt(self,x-dxdu,y-dydu,z-dzdu)) pattern|=0x02;
	if(IsVoxelFilledAt(self,x+dxdv,y+dydv,z+dzdv)) pattern|=0x04;
	if(IsVoxelFilledAt(self,x-dxdv,y-dydv,z-dzdv)) pattern|=0x08;
	if(IsVoxelFilledAt(self,x+dxdu+dxdv,y+dydu+dydv,z+dzdu+dzdv)) pattern|=0x10;
	if(IsVoxelFilledAt(self,x-dxdu+dxdv,y-dydu+dydv,z-dzdu+dzdv)) pattern|=0x20;
	if(IsVoxelFilledAt(self,x+dxdu-dxdv,y+dydu-dydv,z+dzdu-dzdv)) pattern|=0x40;
	if(IsVoxelFilledAt(self,x-dxdu-dxdv,y-dydu-dydv,z-dzdu-dzdv)) pattern|=0x80;
	return PatternTable[pattern];
}

void ScrollVoxelBlockByZ(VoxelBlock *self)
{
	memmove(&self->voxels[self->width*self->height],self->voxels,sizeof(Voxel)*self->width*self->height*(self->depth-1));

/*	for(int y=0;y<self->height;y++)
	for(int x=0;x<self->width;x++)
	{
		VoxelStructAt(self,x,y,0)->patterns[0]=NeedsRefreshPattern;
		VoxelStructAt(self,x,y,1)->patterns[0]=NeedsRefreshPattern;
	}*/
}
