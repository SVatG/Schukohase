#include "Truchet.h"
#include "DS3D/DS3D.h"
#include "DS3D/Vector/VectorFixed.h"
#include "DS3D/Vector/MatrixFixed.h"
#include "DS3D/Vector/QuaternionFixed.h"

void InitWorld();
void DrawWorld(imat4x3_t cam);

static int startframe;
static iquat_t rot;
static ivec3_t pos;

int hasInit = 0;

void InitTruchet(int frame)
{
	DISPCNT_A=DISPCNT_MODE_0|DISPCNT_ON|DISPCNT_3D|DISPCNT_BG0_ON;

	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_TEXTURING|DS_ANTIALIAS|DS_FOG);
	DSClearParams(14,31,31,31,63);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspectivef(65,256.0/192.0,0.1,4);

	DSSetFogLinearf(14,31,31,31,1,3.5,0.1,4);

	startframe=frame;
	rot=iquatone;
	pos=ivec3zero;

	InitWorld();
}

int32_t fakesin(int32_t x)
{
	x=imul(x,DSf32(1.0/(2*3.141592)));
	return isin(x);
}

void Truchet(int frame)
{
	if(hasInit==0) {
		hasInit = 1;
		InitTruchet(frame);
	}
	int t=frame-startframe;

/*	rot=iquatmul(rot,iquatrotation(-40,ivec3(F(1),0,0)));
	rot=iquatmul(rot,iquatrotation(40,ivec3(0,F(1),0)));
	rot=iquatnorm(rot);
	imat3x3_t m=imat3x3quat(rot);

	pos=ivec3add(pos,ivec3mul(imat3x3_z(m),-F(0.1)));*/
//pos=ivec3(Random()%F(1),Random()%F(1),Random()%F(1));
//iprintf("%x\n",pos.x);

	int32_t sin_a=isin(t*5);
	int32_t cos_a=icos(t*5);

	ivec3_t back=ivec3(0,0,DSf32(1));
	back=ivec3(back.y,imul(back.z,cos_a)-imul(back.x,sin_a),imul(back.x,cos_a)+imul(back.z,sin_a));
	back=ivec3(back.y,imul(back.z,cos_a)-imul(back.x,sin_a),imul(back.x,cos_a)+imul(back.z,sin_a));
	back=ivec3(back.y,imul(back.z,cos_a)-imul(back.x,sin_a),imul(back.x,cos_a)+imul(back.z,sin_a));
	back=ivec3(back.y,imul(back.z,cos_a)-imul(back.x,sin_a),imul(back.x,cos_a)+imul(back.z,sin_a));

	ivec3_t up=ivec3(0,DSf32(1),0);
	up=ivec3(up.y,imul(up.z,cos_a)-imul(up.x,sin_a),imul(up.x,cos_a)+imul(up.z,sin_a));
	up=ivec3(up.y,imul(up.z,cos_a)-imul(up.x,sin_a),imul(up.x,cos_a)+imul(up.z,sin_a));
	up=ivec3(up.y,imul(up.z,cos_a)-imul(up.x,sin_a),imul(up.x,cos_a)+imul(up.z,sin_a));
	up=ivec3(up.y,imul(up.z,cos_a)-imul(up.x,sin_a),imul(up.x,cos_a)+imul(up.z,sin_a));

	imat3x3_t m=imat3x3vec3(ivec3cross(up,back),up,back);

//	float tt=t/40;
	int32_t tt=idiv(DSf32(t),DSf32(80));
	ivec3_t pos=/*fract(*/ivec3(
		2*(fakesin(tt+fakesin(2*tt)/2)/2+DSf32(0.5)),
		2*(fakesin(tt-fakesin(2*tt)/2-DSf32(3.141592/2.0))/2+DSf32(0.5)),
		2*(idiv(-2*(tt-fakesin(4*tt)/4),DSf32(3.141592))+DSf32(0.5)+DSf32(0.5))
//		DSf32(2*(sinf(tt+sinf(2.0*tt)/2.0)/2.0+0.5)),
//		DSf32(2*(sinf(tt-sinf(2.0*tt)/2.0-3.141592/2.0)/2.0+0.5)),
//		DSf32(2*(-2.0*(tt-sinf(4.0*tt)/4.0)/3.141592+0.5+0.5))
	);

	DrawWorld(imat4x3vec3(imat3x3_x(m),imat3x3_y(m),imat3x3_z(m),pos));

	t++;

	DSSwapBuffers(0);
}





static void DrawTile(int type,int x,int y,int z);
static void DrawArc(int type,int x,int y,int z);
static void MakeArcList(uint32_t *list,int listsize,int thickness);
static uint32_t Hash32(uint32_t val);
static void MakeTexture(uint16_t *vram,int r1,int g1,int b1,int r2,int g2,int b2);

#define NumberOfSegments 5

static int thickness;

static uint32_t arc[512];

static const uint8_t tilearcs[8][3]=
{
	{ 0,6,11 },
	{ 0,7,10 },
	{ 1,7,8 },
	{ 1,4,11 },
	{ 2,4,9 },
	{ 2,5,8 },
	{ 3,5,10 },
	{ 3,6,9 },
};

static const uint8_t arcconnections[12][4]=
{
	{ 1,1,0,1 },
	{ 0,0,1,1 },
	{ 1,0,0,0 },
	{ 0,1,1,0 },

	{ 2,0,0,1 },
	{ 2,0,1,1 },
	{ 2,0,0,0 },
	{ 2,0,1,0 },

	{ 2,1,0,1 },
	{ 2,1,1,1 },
	{ 2,1,0,0 },
	{ 2,1,1,0 },
};

static imat3x3_t arcmatrices[12];



void InitWorld()
{
	int32_t i=DSf32(1);

	arcmatrices[0]=imat3x3(i,0,0, 0,i,0, 0,0,i);
	arcmatrices[1]=imat3x3(0,-i,0, i,0,0, 0,0,i);
	arcmatrices[2]=imat3x3(-i,0,0, 0,-i,0, 0,0,i);
	arcmatrices[3]=imat3x3(0,i,0, -i,0,0, 0,0,i);

	arcmatrices[4]=imat3x3(i,0,0, 0,0,i, 0,-i,0);
	arcmatrices[5]=imat3x3(0,0,-i, i,0,0, 0,-i,0);
	arcmatrices[6]=imat3x3(-i,0,0, 0,0,-i, 0,-i,0);
	arcmatrices[7]=imat3x3(0,0,i, -i,0,0, 0,-i,0);

	arcmatrices[8]=imat3x3(i,0,0, 0,0,-i, 0,i,0);
	arcmatrices[9]=imat3x3(0,0,i, i,0,0, 0,i,0);
	arcmatrices[10]=imat3x3(-i,0,0, 0,0,i, 0,i,0);
	arcmatrices[11]=imat3x3(0,0,-i, -i,0,0, 0,i,0);

	thickness=DSf32(0.2);
	MakeArcList(arc,512,thickness);

	VRAMCNT_A=VRAMCNT_A_LCDC;
	VRAMCNT_B=VRAMCNT_B_LCDC;
	VRAMCNT_C=VRAMCNT_C_LCDC;
	VRAMCNT_D=VRAMCNT_D_LCDC;
	VRAMCNT_E=VRAMCNT_E_LCDC;
	VRAMCNT_F=VRAMCNT_F_LCDC;
	VRAMCNT_G=VRAMCNT_G_LCDC;
	
	static int red[6]=  { 1,1,0,0,0,1 };
	static int green[6]={ 0,1,1,1,0,0 };
	static int blue[6]= { 0,0,0,1,1,1 };

	for(int from=0;from<6;from++)
	for(int to=0;to<6;to++)
	{
		MakeTexture(&VRAM_LCDC_A[(from*6+to)*32*8],
		red[from],green[from],blue[from],red[to],green[to],blue[to]);
	}

	VRAMCNT_A=VRAMCNT_A_TEXTURE_OFFS_0K;
}

void DrawWorld(imat4x3_t cam)
{
	DSMatrixMode(DS_POSITION_AND_VECTOR);
	DSLoadMatrix4x3(imat4x3affineinverse(cam));

	DSLight3f(0,0x7fff,1,-1,-1);
//	DSMaterialDiffuseAndAmbient(0x3def,0x3def);
	DSMaterialDiffuseAndAmbient6b(10,10,10,21,21,21);

	ivec3_t pos=imat4x3_w(cam);
	ivec3_t zaxis=imat4x3_z(cam);
	int x0=FixedToInt(pos.x);
	int y0=FixedToInt(pos.y);
	int z0=FixedToInt(pos.z);

	DSPolygonAttributes(DS_POLY_MODE_MODULATION|DS_POLY_CULL_BACK|DS_POLY_LIGHT0|DS_POLY_FOG|DS_POLY_ALPHA(31));

	for(int z=z0-4;z<=z0+4;z++)
	for(int y=y0-4;y<=y0+4;y++)
	for(int x=x0-4;x<=x0+4;x++)
	{
		const int32_t half=DSf32(0.5);
		ivec3_t center=ivec3(DSf32(x)+half,DSf32(y)+half,DSf32(z)+half);
		ivec3_t camtocenter=ivec3sub(center,pos);
		if(ivec3dot(zaxis,camtocenter)>DSf32(0.5)) continue;

		DSPushMatrix();
		DSTranslatev(center);
		DSScalef(0.5,0.5,0.5);

		int type=Hash32(Hash32(Hash32(x)^y)^z)&7;
		DrawTile(type,x,y,z);

		DSPopMatrix(1);
	}
}

static void DrawTile(int type,int x,int y,int z)
{
	for(int i=0;i<3;i++) DrawArc(tilearcs[type][i],x,y,z);
}

static int Colour(int plane,int x,int y,int z)
{
//	return Hash32(Hash32(Hash32(Hash32(plane)^x)^y)^z)%6;

/*	switch(plane)
	{
		case 0: return (x&1)?0:3;
		case 1: return (y&1)?1:4;
		case 2: return (z&1)?2:5;
	}*/

/*	int32_t r=ivec2abs(ivec2(DSf32(x),DSf32(y)));
	return DSf32toint(2*r-DSf32(z))%6;*/

	return (z%6+6)%6;
}

#include <stdio.h>

static void DrawArc(int type,int x,int y,int z)
{
	DSPushMatrix();
	DSMultMatrix3x3(arcmatrices[type]);

	int fromplane=arcconnections[type][0];
	int fromoffs=arcconnections[type][1];
	int toplane=arcconnections[type][2];
	int tooffs=arcconnections[type][3];

	int fromx=x,fromy=y,fromz=z;
	switch(fromplane)
	{
		case 0: fromx+=fromoffs; break;
		case 1: fromy+=fromoffs; break;
		case 2: fromz+=fromoffs; break;
	}

	int tox=x,toy=y,toz=z;
	switch(toplane)
	{
		case 0: tox+=tooffs; break;
		case 1: toy+=tooffs; break;
		case 2: toz+=tooffs; break;
	}

	int from=Colour(fromplane,fromx,fromy,fromz);
	int to=Colour(toplane,tox,toy,toz);

	DSSetTexture(DS_TEX_ADDRESS((from*6+to)*32*8*2)|DS_TEX_SIZE_S_32|DS_TEX_SIZE_T_8|DS_TEX_FORMAT_RGB);
	DSCallList(arc);

	DSPopMatrix(1);
}

static void MakeArcList(uint32_t *list,int listsize,int thickness)
{
	int one=DSf32(1);
	int r1=DSf32(1)-thickness;
	int r2=DSf32(1)+thickness;
	static int16_t arc[NumberOfSegments][3][2];

	for(int i=0;i<NumberOfSegments;i++)
	{
		int a=(i*1024)/(NumberOfSegments-1);
		arc[i][0][0]=imul(r1,icos(a));
		arc[i][0][1]=imul(r1,isin(a));
		arc[i][1][0]=imul(r2,icos(a));
		arc[i][1][1]=imul(r2,isin(a));
		arc[i][2][0]=DSf32ton10(icos(a));
		arc[i][2][1]=DSf32ton10(isin(a));
	}
	arc[0][0][1]-=F(0.01);
	arc[0][1][1]-=F(0.01);
	arc[NumberOfSegments-1][0][0]-=F(0.01);
	arc[NumberOfSegments-1][1][0]-=F(0.01);

	DSStartList(list,listsize);

	DSListBegin(DS_QUAD_STRIP);
	DSListNormal3f(0,0,1);
	for(int i=0;i<NumberOfSegments;i++)
	{
		DSListTexCoord2t16(DSinttot16(32*i)/(NumberOfSegments-1),0);
		DSListVertex3v16(one-arc[i][0][0],one-arc[i][0][1],thickness);
		DSListVertex3v16(one-arc[i][1][0],one-arc[i][1][1],thickness);
	}
	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	DSListNormal3f(0,0,-1);
	for(int i=0;i<NumberOfSegments;i++)
	{
		DSListTexCoord2t16(DSinttot16(32*i)/(NumberOfSegments-1),0);
		DSListVertex3v16(one-arc[i][1][0],one-arc[i][1][1],-thickness);
		DSListVertex3v16(one-arc[i][0][0],one-arc[i][0][1],-thickness);
	}
	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	for(int i=0;i<NumberOfSegments;i++)
	{
		DSListNormal3n10(-arc[i][2][0],-arc[i][2][1],0);
		DSListTexCoord2t16(DSinttot16(32*i)/(NumberOfSegments-1),0);
		DSListVertex3v16(one-arc[i][1][0],one-arc[i][1][1],thickness);
		DSListVertex3v16(one-arc[i][1][0],one-arc[i][1][1],-thickness);
	}
	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	for(int i=0;i<NumberOfSegments;i++)
	{
		DSListNormal3n10(arc[i][2][0],arc[i][2][1],0);
		DSListTexCoord2t16(DSinttot16(32*i)/(NumberOfSegments-1),0);
		DSListVertex3v16(one-arc[i][0][0],one-arc[i][0][1],-thickness);
		DSListVertex3v16(one-arc[i][0][0],one-arc[i][0][1],thickness);
	}
	DSListEnd();

	int size=DSFinishList();
	//iprintf("Size: %d\n",size);
}

static void MakeTexture(uint16_t *vram,int r1,int g1,int b1,int r2,int g2,int b2)
{
/*uint16_t colours[32]=
{
	DSPackRGB5(31,0,0),
	DSPackRGB5(31,6,0),
	DSPackRGB5(31,12,0),
	DSPackRGB5(31,19,0),
	DSPackRGB5(31,25,0),
	DSPackRGB5(31,31,0),
	DSPackRGB5(25,31,0),
	DSPackRGB5(19,31,0),
	DSPackRGB5(12,31,0),
	DSPackRGB5(6,31,0),
	DSPackRGB5(0,31,0),
	DSPackRGB5(0,31,6),
	DSPackRGB5(0,31,12),
	DSPackRGB5(0,31,19),
	DSPackRGB5(0,31,25),
	DSPackRGB5(0,31,31),
	DSPackRGB5(0,31,31),
	DSPackRGB5(0,25,31),
	DSPackRGB5(0,19,31),
	DSPackRGB5(0,12,31),
	DSPackRGB5(0,6,31),
	DSPackRGB5(0,0,31),
	DSPackRGB5(6,0,31),
	DSPackRGB5(12,0,31),
	DSPackRGB5(19,0,31),
	DSPackRGB5(25,0,31),
	DSPackRGB5(31,0,31),
	DSPackRGB5(31,0,25),
	DSPackRGB5(31,0,19),
	DSPackRGB5(31,0,12),
	DSPackRGB5(31,0,6),
	DSPackRGB5(31,0,0),
};*/

	for(int t=0;t<8;t++)
	for(int s=0;s<32;s++)
	{
		*vram++=DSPackRGB5((31-s)*r1+s*r2,(31-s)*g1+s*g2,(31-s)*b1+s*b2)|0x8000;
//		*vram++=colours[s]|0x8000;
	}
}

static uint32_t Hash32(uint32_t val)
{
	val^=val>>16;
	val^=61;
	val+=val<<3;
	val^=val>>4;
	val*=0x27d4eb2d;
	val^=val>>15;
	return val;
}

