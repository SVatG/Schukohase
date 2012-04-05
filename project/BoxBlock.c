#include "VoxelBlock.h"
#include "BoxBlock.h"
#include "DS3D/DS3D.h"

#include <stdlib.h>
#include <math.h>

void InitBoxBlock(BoxBlock *self,int width,int height,int depth)
{
	self->width=width;
	self->height=height;
	self->depth=depth;

	self->boxes=malloc(width*height*depth*sizeof(self->boxes[0]));

	for(int i=0;i<width*height*depth;i++) {
		self->boxes[i].colour=0;
		self->boxes[i].size=0;
	}
}

void CleanupBoxBlock(BoxBlock *self) {
	free(self->boxes);
}


inline void SetBoxAt(BoxBlock *self,int x,int y,int z,uint16_t val,uint8_t size) {
	Box *box=&self->boxes[x+(y+z*self->height)*self->width];

	box->colour=val;
	box->size=size;
}

static void DrawBoxFace(int fx,int fy,int fz,int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv);

void DrawBoxBlock(BoxBlock *self) {
	DSMatrixMode(DS_POSITION);
	DSStoreMatrix(0);
	DSTranslatef32(-DSf32(self->width)/2,-DSf32(self->height)/2,-DSf32(self->depth)/2);

	DSMatrixMode(DS_POSITION);
	DSScalef32(DSf32(512),DSf32(512),DSf32(512));

	DISP3DCNT|=DS_OUTLINE;
	DSPolygonAttributes(DS_POLY_CULL_NONE|DS_POLY_LIGHT0|DS_POLY_ALPHA(31));
	DSLight3f(0,0xDDDD,-1,-10,-1);

	DSBegin(DS_QUADS);

	int boxsize = 0;
	int boxspace = 8;
	Box *box=self->boxes;
	for(int z=0;z<self->depth*boxspace;z+=boxspace)
	for(int y=0;y<self->height*boxspace;y+=boxspace)
	for(int x=0;x<self->width*boxspace;x+=boxspace)
	{
		if(IsBoxFilled(box->colour)) {
			boxsize = box->size;
			DSMaterialDiffuseAndAmbient(box->colour,box->colour);
			DSNormal3f(-1,0,0);
			DrawBoxFace(x-boxsize/2,y-boxsize/2,z-boxsize/2,0,boxsize,0,0,0,boxsize);
			DSNormal3f(1,0,0);
			DrawBoxFace(x+boxsize/2,y-boxsize/2,z-boxsize/2,0,boxsize,0,0,0,boxsize);
			DSNormal3f(0,-1,0);
			DrawBoxFace(x-boxsize/2,y-boxsize/2,z-boxsize/2,0,0,boxsize,boxsize,0,0);
			DSNormal3f(0,1,0);
			DrawBoxFace(x-boxsize/2,y+boxsize/2,z-boxsize/2,0,0,boxsize,boxsize,0,0);
			DSNormal3f(0,0,-1);
			DrawBoxFace(x-boxsize/2,y-boxsize/2,z-boxsize/2,boxsize,0,0,0,boxsize,0);
			DSNormal3f(0,0,1);
			DrawBoxFace(x-boxsize/2,y-boxsize/2,z+boxsize/2,boxsize,0,0,0,boxsize,0);
		}

		box++;
	}
	DSEnd();
	DSMatrixMode(DS_POSITION);
	DSRestoreMatrix(0);
}

static void DrawBoxFace(int fx,int fy,int fz,int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv) {
	DSSetTexture(0);

	DSVertex3v16(fx,fy,fz);
	DSVertex3v16(fx+dxdu,fy+dydu,fz+dzdu);
	DSVertex3v16(fx+dxdu+dxdv,fy+dydu+dydv,fz+dzdu+dzdv);
	DSVertex3v16(fx+dxdv,fy+dydv,fz+dzdv);
}
