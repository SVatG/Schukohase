#ifndef __DS3Dextra_H__
#define __DS3Dextra_H__

#include "Utils.h"
#include "Hardware.h"
#include "DS3D.h"

// static inline int32_t imul3(int32_t a,int32_t b,int32_t c) { return imul(imul(a,b),c); }

/*
static inline uint32_t DSPack16(int16_t a,int16_t b) { return (a&0xffff)|(b<<16); }
static inline uint32_t DSPack10(int16_t a,int16_t b,int16_t c) { return (a&0x3ff)|((b&0x3ff)<<10)|((c&0x3ff)<<20); }
static inline uint16_t DSPackRGB5(int r,int g,int b) { return r|(g<<5)|(b<<10); }
static inline uint16_t DSPackRGB8(int r,int g,int b) { return (r>>3)|((g>>3)<<5)|((b>>3)<<10); }

// f32: Matrix-math 20.12 fixed-point format
*/
// static inline int32_t DSinttof32(int n) { return n<<12; }
/*
static inline int32_t DSfloattof32(float n) { return (int32_t)(n*(float)(1<<12)); }
static inline int DSf32toint(int32_t n) { return n>>12; }
static inline float DSf32tofloat(int32_t n) { return ((float)n)/(float)(1<<12); }

#define DSf32(n) ((int32_t)((n)*(1<<12))) // shorthand

// v16: Vertex coordinate 4.12 fixed-point format
static inline int16_t DSf32tov16(int32_t n) { return (int16_t)n; }
static inline int16_t DSinttov16(int n) { return (int16_t)(n<<12); }
static inline int16_t DSfloattov16(float n) { return (int16_t)(n*(float)(1<<12)); }
static inline int DSv16toint(int16_t n) { return n>>12; }

#define DSv16(n) ((int16_t)((n)*(1<<12))) // shorthand

// v10: Vertex coordinate 4.6 fixed-point format
static inline int16_t DSf32tov10(int32_t n) { return (int16_t)(n>>6); }
static inline int16_t DSinttov10(int n) { return (int16_t)(n<<6); }
static inline int16_t DSfloattov10(float n) { return (int16_t)(n*(float)(1<<6)); }
static inline int DSv10toint(int16_t n) { return n>>6; }

#define DSv10(n) ((int16_t)((n)*(1<<6))) // shorthand

// t16: Texture coordinate 12.4 fixed-point format
static inline int16_t DSf32tot16(int32_t n) { return (int16_t)(n>>8); }
static inline int16_t DSinttot16(int n) { return (int16_t)(n<<4); }
static inline int16_t DSfloattot16(float n) { return (int16_t)(n*(float)(1<<4)); }
static inline int DSt16toint(int16_t n) { return n>>4; }
*/
#define DSt16(n) ((int16_t)((n)*(1<<4))) // shorthand
/*
// n10: Normal and light direction 1.9 fixed-point format
static inline int16_t DSf32ton10(int32_t n) { return (int16_t)(n>>3); }
static inline int16_t DSfloatton10(float n) { return (n>0.998)?0x1ff:((int16_t)(n*(float)(1<<9))); }
static inline int DSn10toint(int16_t n) { return n>>9; }

// d15: Depth buffer 12.3 fixed-point format
static inline int16_t DSinttod15(int n) { return (int16_t)(n<<3); }
static inline int16_t DSfloattod15(float n) { return (int16_t)(n*(float)(1<<3)); }
#define DS_MAX_DEPTH 0x7fff
*/
//typedef struct { int32_t m[9]; } Matrix3x3;
//typedef struct { int32_t m[12]; } Matrix4x3;
//typedef struct { int32_t m[16]; } Matrix4x4;
//typedef struct { int32_t x,y,z; } Vector;

static inline Vector MakeVector(int32_t x,int32_t y,int32_t z) { Vector v={x,y,z}; return v; }

static inline Vector MatrixXAxis3x3(Matrix3x3 m) { return MakeVector(m.m[0],m.m[1],m.m[2]); }
static inline Vector MatrixYAxis3x3(Matrix3x3 m) { return MakeVector(m.m[3],m.m[4],m.m[5]); }
static inline Vector MatrixZAxis3x3(Matrix3x3 m) { return MakeVector(m.m[6],m.m[7],m.m[8]); }

static inline Vector MatrixXAxis4x3(Matrix4x3 m) { return MakeVector(m.m[0],m.m[1],m.m[2]); }
static inline Vector MatrixYAxis4x3(Matrix4x3 m) { return MakeVector(m.m[3],m.m[4],m.m[5]); }
static inline Vector MatrixZAxis4x3(Matrix4x3 m) { return MakeVector(m.m[6],m.m[7],m.m[8]); }
static inline Vector MatrixOffset4x3(Matrix4x3 m) { return MakeVector(m.m[9],m.m[10],m.m[11]); }

static inline Vector MatrixXAxis4x4(Matrix4x4 m) { return MakeVector(m.m[0],m.m[1],m.m[2]); }
static inline Vector MatrixYAxis4x4(Matrix4x4 m) { return MakeVector(m.m[4],m.m[5],m.m[6]); }
static inline Vector MatrixZAxis4x4(Matrix4x4 m) { return MakeVector(m.m[8],m.m[9],m.m[10]); }
static inline Vector MatrixOffset4x4(Matrix4x4 m) { return MakeVector(m.m[12],m.m[13],m.m[14]); }

static inline Matrix3x3 Matrix4x4To3x3(Matrix4x4 m)
{
	Matrix3x3 res={ m.m[0],m.m[1],m.m[2],m.m[4],m.m[5],m.m[6],m.m[8],m.m[9],m.m[10] };
	return res;
}

static inline Matrix4x3 Matrix4x4To4x3(Matrix4x4 m)
{
	Matrix4x3 res={ m.m[0],m.m[1],m.m[2],m.m[4],m.m[5],m.m[6],m.m[8],m.m[9],m.m[10],m.m[12],m.m[13],m.m[14] };
	return res;
}

Vector TransformVector3x3(Matrix3x3 m,Vector v);
Vector TransformVector4x3(Matrix4x3 m,Vector v);
Vector TransformVector4x4(Matrix4x4 m,Vector v);

Matrix3x3 MatrixInverse3x3(Matrix3x3 m);
Matrix4x3 MatrixInverse4x3(Matrix4x3 m);
Matrix4x4 FastMatrixInverse4x4(Matrix4x4 m);

/*
//http://nocash.emubase.de/gbatek.htm#ds3ddisplaycontrol
#define DS_TEXTURING 0x01
#define DS_TOON_SHADING 0x02
#define DS_ALPHA_TEST 0x04
#define DS_ALPHA_BLEND 0x08
#define DS_ANTIALIAS 0x10
#define DS_OUTLINE 0x20
#define DS_FOG_ALPHA_ONLY 0x40
#define DS_FOG 0x80
#define DS_FOG_SHIFT(n) ((n)<<8)
#define DS_COLOR_UNDERFLOW 0x1000
#define DS_POLY_OVERFLOW 0x2000
#define DS_CLEAR_BITMAP 0x4000

// http://nocash.emubase.de/gbatek.htm#ds3ddisplaycontrol
#define DS_SWAP_NO_SORTING 0x01
#define DS_SWAP_WBUFFERING 0x02


// http://nocash.emubase.de/gbatek.htm#ds3dpolygonattributes
#define DS_POLY_LIGHT0 0x0001
#define DS_POLY_LIGHT1 0x0002
#define DS_POLY_LIGHT2 0x0004
#define DS_POLY_LIGHT3 0x0008
#define DS_POLY_MODE_MODULATION 0x0000
#define DS_POLY_MODE_DECAL 0x0010
#define DS_POLY_MODE_TOON 0x0020
#define DS_POLY_MODE_SHADOW 0x0030
#define DS_POLY_CULL_ALL 0x0000
#define DS_POLY_CULL_FRONT 0x0040
#define DS_POLY_CULL_BACK 0x0080
#define DS_POLY_CULL_NONE 0x00c0
#define DS_POLY_SET_TRANS_DEPTH 0x0800
#define DS_POLY_CLIP_FAR 0x1000
#define DS_POLY_RENDER_1DOT 0x2000
#define DS_POLY_DEPTH_TEST_LESS 0x0000
#define DS_POLY_DEPTH_TEST_EQUAL 0x4000
#define DS_POLY_FOG 0x8000
#define DS_POLY_ALPHA(n) (((n)&0x1f)<<16)
#define DS_POLY_ID(n) (((n)&0x3f)<<24)

// http://nocash.emubase.de/gbatek.htm#ds3dtextureattributes
#define DS_TEX_ADDRESS(addr) ((((uint32_t)(addr))>>3)&0xffff)
#define DS_TEX_WRAP_S 0x10000
#define DS_TEX_WRAP_T 0x20000
#define DS_TEX_FLIP_S 0x40000
#define DS_TEX_FLIP_T 0x80000
#define DS_TEX_SIZE_S(n) ((n)<<20)
#define DS_TEX_SIZE_S_8 (0<<20)
#define DS_TEX_SIZE_S_16 (1<<20)
#define DS_TEX_SIZE_S_32 (2<<20)
#define DS_TEX_SIZE_S_64 (3<<20)
#define DS_TEX_SIZE_S_128 (4<<20)
#define DS_TEX_SIZE_S_256 (5<<20)
#define DS_TEX_SIZE_S_512 (6<<20)
#define DS_TEX_SIZE_S_1024 (7<<20)
#define DS_TEX_SIZE_T(n) ((n)<<23)
#define DS_TEX_SIZE_T_8 (0<<23)
#define DS_TEX_SIZE_T_16 (1<<23)
#define DS_TEX_SIZE_T_32 (2<<23)
#define DS_TEX_SIZE_T_64 (3<<23)
#define DS_TEX_SIZE_T_128 (4<<23)
#define DS_TEX_SIZE_T_256 (5<<23)
#define DS_TEX_SIZE_T_512 (6<<23)
#define DS_TEX_SIZE_T_1024 (7<<23)
#define DS_TEX_FORMAT_NONE (0<<26)
#define DS_TEX_FORMAT_A3P5 (1<<26)
#define DS_TEX_FORMAT_PAL2 (2<<26)
#define DS_TEX_FORMAT_PAL4 (3<<26)
#define DS_TEX_FORMAT_PAL8 (4<<26)
#define DS_TEX_FORMAT_COMPRESSED (5<<26)
#define DS_TEX_FORMAT_A5P3 (6<<26)
#define DS_TEX_FORMAT_RGB (7<<26)
#define DS_TEX_FORMAT_MASK (7<<26)
#define DS_TEX_COLOR0_TRANS 0x20000000
#define DS_TEX_GEN_OFF 0x00000000
#define DS_TEX_GEN_TEXCOORD 0x40000000
#define DS_TEX_GEN_NORMAL 0x80000000
#define DS_TEX_GEN_POSITION 0xc0000000
#define DS_INVALID_TEXTURE 0xffffffff

// http://nocash.emubase.de/gbatek.htm#ds3dpolygondefinitionsbyvertices
#define DS_TRIANGLES 0
#define DS_QUADS 1
#define DS_TRIANGLE_STRIP 2
#define DS_QUAD_STRIP 3

// http://nocash.emubase.de/gbatek.htm#ds3dmatrixloadmultiply
#define DS_PROJECTION 0
#define DS_POSITION 1
#define DS_POSITION_AND_VECTOR 2
#define DS_TEXTURE 3

#define DS_MODELVIEW DS_POSITION_AND_VECTOR

/*#define FIFO_COMMAND_PACK(c1,c2,c3,c4) (((c4)<<24)|((c3)<<16)|((c2)<<8)|(c1))

#define REG2ID(r) (uint8_t)((((uint32_t)(&(r)))-0x04000400)>>2)

#define FIFO_NOP REG2ID(GFX_FIFO)
#define FIFO_STATUS REG2ID(GFX_STATUS)
#define FIFO_COLOR REG2ID(GFX_COLOR)

#define FIFO_VERTEX16 REG2ID(GFX_VERTEX16)
#define FIFO_TEX_COORD REG2ID(GFX_TEX_COORD)
#define FIFO_TEX_FORMAT REG2ID(GFX_TEX_FORMAT)
#define FIFO_PAL_FORMAT REG2ID(GFX_PAL_FORMAT)

#define FIFO_CLEAR_COLOR REG2ID(GFX_CLEAR_COLOR)
#define FIFO_CLEAR_DEPTH REG2ID(GFX_CLEAR_DEPTH)

#define FIFO_LIGHT_VECTOR REG2ID(GFX_LIGHT_VECTOR)
#define FIFO_LIGHT_COLOR REG2ID(GFX_LIGHT_COLOR)
#define FIFO_NORMAL REG2ID(GFX_NORMAL)

#define FIFO_DIFFUSE_AMBIENT REG2ID(GFX_DIFFUSE_AMBIENT)
#define FIFO_SPECULAR_EMISSION REG2ID(GFX_SPECULAR_EMISSION)
#define FIFO_SHININESS REG2ID(GFX_SHININESS)

#define FIFO_POLY_FORMAT REG2ID(GFX_POLY_FORMAT)

#define FIFO_BEGIN REG2ID(GFX_BEGIN)
#define FIFO_END REG2ID(GFX_END)
#define FIFO_FLUSH REG2ID(GFX_FLUSH)
#define FIFO_VIEWPORT REG2ID(GFX_VIEWPORT)* /

#ifdef __cplusplus
extern "C" {
#endif

void DSInit3D();
void DSRotatef32i(int angle,int32_t x,int32_t y,int32_t z);

uint32_t DSTextureSize(uint32_t flags);
uint16_t *DSTextureAddress(uint32_t texture);

uint32_t DSAllocTexture(uint32_t flags);
void DSFreeAllTextures();
void DSCopyTexture(uint32_t texture,void *data);
uint32_t DSAllocAndCopyTexture(uint32_t flags,void *data);

void DSSetFogWithCallback(uint8_t r,uint8_t g,uint8_t b,uint8_t a,
int32_t start,int32_t end,int32_t near,int32_t far,
int32_t (*callback)(int32_t z,int32_t start,int32_t end));
void DSSetFogLinearf32(uint8_t r,uint8_t g,uint8_t b,uint8_t a,int32_t start,int32_t end,int32_t near,int32_t far);
void DSSetFogLinearf(uint8_t r,uint8_t g,uint8_t b,uint8_t a,float start,float end,float near,float far);

#ifdef __cplusplus
}
#endif



// http://nocash.emubase.de/gbatek.htm#ds3ddisplaycontrol
static inline void DSSetControl(int control) { DISP3DCNT=control; }
static inline void DSSwapBuffers(uint32_t mode) { SWAP_BUFFERS=mode; }
static inline void DSViewport(uint8_t left,uint8_t bottom,uint8_t right,uint8_t top) { VIEWPORT=(left)|(bottom<<8)|(right<<16)|(top<<24); }

static inline void DSAlphaThreshold(int alphathreshold) { ALPHA_TEST_REF=alphathreshold; }
static inline void DSCutoffDepth(uint16_t wval) { DISP_1DOT_DEPTH=wval; }

static inline void DSClearParams(uint8_t r,uint8_t g,uint8_t b,uint8_t a,uint8_t id)
{ CLEAR_COLOR=((id&0x3f)<<24)|((a&0x1f)<<16)|DSPackRGB5(r,g,b); }

//http://nocash.emubase.de/gbatek.htm#ds3drearplane
static inline void DSClearDepth(uint16_t depth) { CLEAR_DEPTH=depth; }
static inline void DSMaxClearDepth() { CLEAR_DEPTH=DS_MAX_DEPTH; }

// http://nocash.emubase.de/gbatek.htm#ds3dpolygonattributes
static inline void DSPolygonAttributes(uint32_t format) { POLYGON_ATTR=format; }

// http://nocash.emubase.de/gbatek.htm#ds3dtextureattributes
static inline void DSSetTexture(uint32_t texture) { while(GXSTAT&(1<<27)); TEXIMAGE_PARAM=texture; }
static inline void DSSetPaletteOffset(uint32_t offs,uint32_t format)
{ PLTT_BASE=(offs>>((format&DS_TEX_FORMAT_MASK)==DS_TEX_FORMAT_PAL2?3:4))&0x1fff; }
static inline void DSSetPalette(void *ptr,uint32_t format) { DSSetPaletteOffset((uint32_t)ptr,format); }


// http://nocash.emubase.de/gbatek.htm#ds3dpolygondefinitionsbyvertices
static inline void DSBegin(int mode) { BEGIN_VTXS=mode; }
static inline void DSEnd() { END_VTXS=0; }

static inline void DSVertex(uint32_t xy,uint32_t z) { VTX_16=xy; VTX_16=z; }
static inline void DSVertex3v16(int16_t x,int16_t y,int16_t z) { DSVertex(DSPack16(x,y),z); }
static inline void DSVertex3f(float x,float y,float z) { DSVertex3v16(DSfloattov16(x),DSfloattov16(y),DSfloattov16(z)); }
static inline void DSVertex3v(const Vector v) { DSVertex3v16(v.x,v.y,v.z); }

static inline void DSVertexXY(uint32_t xy) { VTX_XY=xy; }
static inline void DSVertexXYv16(int16_t x,int16_t y) { DSVertexXY(DSPack16(x,y)); }
static inline void DSVertexXYf(float x,float y) { DSVertexXYv16(DSfloattov16(x),DSfloattov16(y)); }
static inline void DSVertex2f(float x,float y) { DSVertexXYf(x,y); }

static inline void DSVertexXZ(uint32_t xz) { VTX_XZ=xz; }
static inline void DSVertexXZv16(int16_t x,int16_t z) { DSVertexXZ(DSPack16(x,z)); }
static inline void DSVertexXZf(float x,float z) { DSVertexXZv16(DSfloattov16(x),DSfloattov16(z)); }

static inline void DSVertexYZ(uint32_t yz) { VTX_YZ=yz; }
static inline void DSVertexYZv16(int16_t y,int16_t z) { DSVertexYZ(DSPack16(y,z)); }
static inline void DSVertexYZf(float y,float z) { DSVertexYZv16(DSfloattov16(y),DSfloattov16(z)); }

static inline void DSVertex10(uint32_t xyz) { VTX_10=xyz; }
static inline void DSVertex103f(float x,float y,float z) { DSVertex10(DSPack10(DSfloattov16(x),DSfloattov16(y),DSfloattov16(z))); }

static inline void DSVertexDiff(uint32_t xyz) { VTX_DIFF=xyz; }
static inline void DSVertexDiff3n10(int16_t x,int16_t y,int16_t z) { DSVertexDiff(DSPack10(x,y,z)); }
static inline void DSVertexDiff3f(float x,float y,float z) { DSVertexDiff3n10(DSfloatton10(x*8),DSfloatton10(y*8),DSfloatton10(z*8)); }

// http://nocash.emubase.de/gbatek.htm#ds3dpolygonattributes
static inline void DSColor(uint16_t color) { COLOR=color; }
static inline void DSColor3b(uint8_t r,uint8_t g,uint8_t b) { DSColor(DSPackRGB5(r,g,b)); }
static inline void DSColor3f(float r,float g,float b) { DSColor3b(r*31,g*31,b*31); }

// http://nocash.emubase.de/gbatek.htm#ds3dpolygonlightparameters
static inline void DSNormal(uint32_t normal) { NORMAL=normal; }
static inline void DSNormal3n10(int16_t x,int16_t y,int16_t z) { DSNormal(DSPack10(x,y,z)); }
static inline void DSNormal3f(float x,float y,float z) { DSNormal3n10(DSfloatton10(x),DSfloatton10(y),DSfloatton10(z)); }

// http://nocash.emubase.de/gbatek.htm#ds3dtextureattributes
static inline void DSTexCoord(uint32_t coords) { TEXCOORD=coords; }
static inline void DSTexCoord2t16(uint16_t u,uint16_t v) { DSTexCoord(DSPack16(u,v)); }
static inline void DSTexCoord2f(float u,float v) { DSTexCoord2t16(DSfloattot16(u),DSfloattot16(v)); }




// http://nocash.emubase.de/gbatek.htm#ds3dmatrixstack
static inline void DSPushMatrix() { MTX_PUSH=0; }
static inline void DSPopMatrix(int num) { MTX_POP=num; }
static inline void DSRestoreMatrix(int index) { MTX_RESTORE=index; }
static inline void DSStoreMatrix(int index) { MTX_STORE=index; }

// http://nocash.emubase.de/gbatek.htm#ds3dmatrixloadmultiply
static inline void DSMatrixMode(int mode) { MTX_MODE=mode; }
static inline void DSLoadIdentity() { MTX_IDENTITY=0; }

static inline void DSLoadMatrix4x4(const Matrix4x4 m) { for(int i=0;i<16;i++) MTX_LOAD_4x4=m.m[i]; }
static inline void DSLoadMatrix4x3(const Matrix4x3 m) { for(int i=0;i<12;i++) MTX_LOAD_4x3=m.m[i]; }
static inline void DSMultMatrix4x4(const Matrix4x4 m) { for(int i=0;i<16;i++) MTX_MULT_4x4=m.m[i]; }
static inline void DSMultMatrix4x3(const Matrix4x3 m) { for(int i=0;i<12;i++) MTX_MULT_4x3=m.m[i]; }
static inline void DSMultMatrix3x3(const Matrix3x3 m) { for(int i=0;i<9;i++) MTX_MULT_3x3=m.m[i]; }

static inline void DSScalef32(int32_t x,int32_t y,int32_t z)
{
	MTX_SCALE=x;
	MTX_SCALE=y;
	MTX_SCALE=z;
}
static inline void DSScalev(const Vector v) { DSScalef32(v.x,v.y,v.z); }
static inline void DSScalef(float x,float y,float z) { DSScalef32(DSf32(x),DSf32(y),DSf32(z)); }
static inline void DSScaleUniformf32(int32_t factor) { DSScalef32(factor,factor,factor); }
static inline void DSScaleUniformf(float factor) { DSScaleUniformf32(DSf32(factor)); }

static inline void DSTranslatef32(int32_t x,int32_t y,int32_t z)
{
	MTX_TRANS=x;
	MTX_TRANS=y;
	MTX_TRANS=z;
}
static inline void DSTranslatev(const Vector v) { DSTranslatef32(v.x,v.y,v.z); }
static inline void DSTranslatef(float x,float y,float z) { DSTranslatef32(DSf32(x),DSf32(y),DSf32(z)); }

static inline void DSRotateXi(int angle)
{
	int32_t sine=isin(angle);
	int32_t cosine=icos(angle);
	
	MTX_MULT_3x3=DSf32(1); MTX_MULT_3x3=0; MTX_MULT_3x3=0;
	MTX_MULT_3x3=0; MTX_MULT_3x3=cosine; MTX_MULT_3x3=sine;
	MTX_MULT_3x3=0; MTX_MULT_3x3=-sine; MTX_MULT_3x3=cosine;
}

static inline void DSRotateYi(int angle)
{
	int32_t sine=isin(angle);
	int32_t cosine=icos(angle);
	
	MTX_MULT_3x3=cosine; MTX_MULT_3x3=0; MTX_MULT_3x3=-sine;
	MTX_MULT_3x3=0; MTX_MULT_3x3=DSf32(1); MTX_MULT_3x3=0;
	MTX_MULT_3x3=sine; MTX_MULT_3x3=0; MTX_MULT_3x3=cosine;
}

static inline void DSRotateZi(int angle)
{
	int32_t sine=isin(angle);
	int32_t cosine=icos(angle);
	
	MTX_MULT_3x3=cosine; MTX_MULT_3x3=sine; MTX_MULT_3x3=0;
	MTX_MULT_3x3=-sine; MTX_MULT_3x3=cosine; MTX_MULT_3x3=0;
	MTX_MULT_3x3=0; MTX_MULT_3x3=0; MTX_MULT_3x3=DSf32(1);
}

static inline void DSRotateXf(float angle) { DSRotateXi(iangle(angle)); }
static inline void DSRotateYf(float angle) { DSRotateYi(iangle(angle)); }
static inline void DSRotateZf(float angle) { DSRotateZi(iangle(angle)); }
static inline void DSRotatef32(float angle,int32_t x,int32_t y,int32_t z) { DSRotatef32i(iangle(angle),x,y,z); }
static inline void DSRotatef(float angle,float x,float y,float z) { DSRotatef32(angle,DSf32(x),DSf32(y),DSf32(z)); }

static inline void DSOrthof32(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far)
{
	MTX_MULT_4x4=idiv(DSf32(2),right-left); MTX_MULT_4x4=0; MTX_MULT_4x4=0; MTX_MULT_4x4=0;
	MTX_MULT_4x4=0; MTX_MULT_4x4=idiv(DSf32(2),top-bottom); MTX_MULT_4x4=0; MTX_MULT_4x4=0;
	MTX_MULT_4x4=0; MTX_MULT_4x4=0; MTX_MULT_4x4=idiv(DSf32(-2),far-near); MTX_MULT_4x4=0;

	MTX_MULT_4x4=-idiv(right+left,right-left);  
	MTX_MULT_4x4=-idiv(top+bottom,top-bottom);  
	MTX_MULT_4x4=-idiv(far+near,far-near);  
	MTX_MULT_4x4=DSf32(1);
}
static inline void DSOrtho(float left,float right,float bottom,float top,float near, float far)
{ DSOrthof32(DSf32(left),DSf32(right),DSf32(bottom),DSf32(top),DSf32(near),DSf32(far)); }

static inline void DS2DProjection(int fractionbits)
{
	DSOrthof32(0,(256<<fractionbits),(192<<fractionbits),0,DSf32(-1),DSf32(1));
}

void DSLookAtf32(int32_t eyex,int32_t eyey,int32_t eyez,int32_t lookatx,int32_t lookaty,
int32_t lookatz,int32_t upx,int32_t upy,int32_t upz);

static inline void DSLookAt(float eyex,float eyey,float eyez,float lookatx,float lookaty,
float lookatz,float upx,float upy,float upz)
{ DSLookAtf32(DSf32(eyex),DSf32(eyey),DSf32(eyez),DSf32(lookatx),
DSf32(lookaty),DSf32(lookatz),DSf32(upx),DSf32(upy),DSf32(upz)); }

static inline void DSFrustumf32(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far)
{
	MTX_MULT_4x4=idiv(2*near,right-left); MTX_MULT_4x4=0; MTX_MULT_4x4=0; MTX_MULT_4x4=0;
 	MTX_MULT_4x4=0; MTX_MULT_4x4=idiv(2*near,top-bottom); MTX_MULT_4x4=0; MTX_MULT_4x4=0;
	MTX_MULT_4x4=idiv(right + left, right - left);
	MTX_MULT_4x4=idiv(top + bottom, top - bottom);
	MTX_MULT_4x4=-idiv(far + near, far - near);
	MTX_MULT_4x4=DSf32(-1);
	MTX_MULT_4x4=0; MTX_MULT_4x4=0; MTX_MULT_4x4=-idiv(2*imul(far,near),far-near); MTX_MULT_4x4=0;
}
static inline void DSFrustum(float left,float right,float bottom,float top,float near,float far) { DSFrustumf32(DSf32(left),DSf32(right),DSf32(bottom),DSf32(top),DSf32(near),DSf32(far)); }

static inline void DSPerspectivef32(int fovy,int32_t aspect,int32_t near,int32_t far)
{
	int32_t ymax=imul(near,itan(fovy>>1));
	int32_t ymin=-ymax;
	int32_t xmin=imul(ymin,aspect);
	int32_t xmax=imul(ymax,aspect);

	DSFrustumf32(xmin,xmax,ymin,ymax,near,far);
}
static inline void DSPerspective(float fovy,float aspect,float near,float far) { DSPerspectivef32(iangle(fovy),DSf32(aspect),DSf32(near),DSf32(far)); }

/* Utility function which generates a picking matrix for selection
 x 2D x of center  (touch x normally)
 y 2D y of center  (touch y normally)
 width width in pixels of the window (3 or 4 is a good number)
 height height in pixels of the window (3 or 4 is a good number)
 viewport the current viewport (normaly {0, 0, 255, 191}) * /
static inline void DSPickMatrix(int x,int y,int width,int height,const int viewport[4])
{
	MTX_MULT_4x4=DSf32(viewport[2])/width; MTX_MULT_4x4=0; MTX_MULT_4x4=0; MTX_MULT_4x4=0;
	MTX_MULT_4x4=0; MTX_MULT_4x4=DSf32(viewport[3]) / height; MTX_MULT_4x4=0; MTX_MULT_4x4=0;
	MTX_MULT_4x4=0; MTX_MULT_4x4=0; MTX_MULT_4x4=DSf32(1); MTX_MULT_4x4=0;
	MTX_MULT_4x4=DSf32(viewport[2]+((viewport[0]-x)<<1))/width;
	MTX_MULT_4x4=DSf32(viewport[3]+((viewport[1]-y)<<1))/height;
	MTX_MULT_4x4=0;
	MTX_MULT_4x4=DSf32(1);
}

static inline void DSResetMatrixStack()
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



// http://nocash.emubase.de/gbatek.htm#ds3dpolygonlightparameters
static inline void DSLight(int n,uint16_t color,uint32_t dir)
{
	uint32_t nummask=(n&3)<<30;
	LIGHT_VECTOR=nummask|dir;
	LIGHT_COLOR=nummask|color;
}
static inline void DSLight3n10(int n,uint16_t color,int16_t x,int16_t y,int16_t z) { DSLight(n,color,DSPack10(x,y,z)); }
static inline void DSLight3f(int id,uint16_t color,float x,float y,float z) { DSLight3n10(id,color,DSfloatton10(x),DSfloatton10(y),DSfloatton10(z)); }
static inline void DSLight3b3f(int id,uint8_t r,uint8_t g,uint8_t b,float x,float y,float z) { DSLight3f(id,DSPackRGB5(r,g,b),x,y,z); }

static inline void DSMaterialDiffuseAndAmbient(uint16_t diffuse,uint16_t ambient) { DIF_AMB=DSPack16(diffuse,ambient); }
static inline void DSMaterialDiffuseAndAmbient6b(uint8_t dr,uint8_t dg,uint8_t db,uint8_t ar,uint8_t ag,uint8_t ab) { DSMaterialDiffuseAndAmbient(DSPackRGB5(dr,dg,db),DSPackRGB5(ar,ag,ab)); }
static inline void DSMaterialDiffuseAndAmbient3b(uint8_t r,uint8_t g,uint8_t b) { DSMaterialDiffuseAndAmbient(DSPackRGB5(r,g,b),DSPackRGB5(r,g,b)); }
static inline void DSMaterialSpecularAndEmission(uint8_t shiny,uint16_t specular,uint16_t emission) { SPE_EMI=DSPack16(specular,emission)|(shiny?0x8000:0); }
static inline void DSMaterialSpecularAndEmission6b(uint8_t shiny,uint8_t sr,uint8_t sg,uint8_t sb,uint8_t er,uint8_t eg,uint8_t eb) { DSMaterialSpecularAndEmission(shiny,DSPackRGB5(sr,sg,sb),DSPackRGB5(er,eg,eb)); }

static inline void DSMaterialShinyness()
{
	for(int i=0;i<32;i++) SHININESS=(i*8)|((i*8+2)<<8)|((i*8+4)<<8)|((i*8+6)<<8);
}

// http://nocash.emubase.de/gbatek.htm#ds3dtoonedgefog
static inline void DSSetOutlineColor(int id,uint16_t color) { EDGE_COLOR[id]=color; }
static inline void DSSetOutlineColor3b(int id,uint8_t r,uint8_t g,uint8_t b) { EDGE_COLOR[id]=DSPackRGB5(r,g,b); }

static inline void DSSetToonTable(const uint16_t *table) { for(int i=0;i<32;i++) TOON_TABLE[i]=table[i]; }
static inline void DSSetToonTableRange(int start,int end,uint16_t color) { for(int i=start;i<=end;i++) TOON_TABLE[i]=color; }
static inline void DSSetToonTableRange3b(int start,int end,uint8_t r,uint8_t g,uint8_t b) { DSSetToonTableRange(start,end,DSPackRGB5(r,g,b)); }





void DC_FlushRange(const void *base,uint32_t size); // kludge

// http://nocash.emubase.de/gbatek.htm#ds3dgeometrycommands
static inline void DSCallList(const uint32_t *list)
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





*/
#define SARRAY32(addr) ((int32_t *)(addr))
#define ARM9_SARRAY32(addr) SARRAY32(addr)
#define CLIPMTX_RESULT ARM9_SARRAY32(0x4000640)
#define VECMTX_RESULT ARM9_SARRAY32(0x4000680)

static inline Matrix4x4 DSGetPositionMatrix()
{
	Matrix4x4 res;

	DSMatrixMode(DS_PROJECTION);
	DSPushMatrix();
	DSLoadIdentity();
	while(GXSTAT&(1<<27));
	for(int i=0;i<16;i++) res.m[i]=CLIPMTX_RESULT[i];
	DSPopMatrix(1);

	return res;
}
/*
static inline Matrix4x4 DSGetProjectionMatrix()
{
	Matrix4x4 res;

	DSMatrixMode(DS_POSITION);
	DSPushMatrix();
	DSLoadIdentity();
	while(GXSTAT&(1<<27));
	for(int i=0;i<16;i++) res.m[i]=CLIPMTX_RESULT[i];
	DSPopMatrix(1);

	return res;
}

static inline Matrix3x3 DSGetVectorMatrix()
{
	Matrix3x3 res;

	while(GXSTAT&(1<<27));
	for(int i=0;i<9;i++) res.m[i]=VECMTX_RESULT[i];

	return res;
}


/*! \brief Grabs integer state variables from openGL
\param param The state variable to retrieve
\param i pointer with room to hold the requested data */
/*static inline void glGetInt(GL_GET_ENUM param, int* i) {
	switch (param) {
		case GL_GET_POLYGON_RAM_COUNT:
			*i = GFX_POLYGON_RAM_USAGE;
			break;
		case GL_GET_VERTEX_RAM_COUNT:
			*i = GFX_VERTEX_RAM_USAGE;
			break;
		case GL_GET_TEXTURE_WIDTH:
			*i = 8 << (((glGlob->textures[glGlob->activeTexture]) >> 20) & 7);
			break;
		case GL_GET_TEXTURE_HEIGHT:
			*i = 8 << (((glGlob->textures[glGlob->activeTexture]) >> 23) & 7);
			break;
		default:
			break;
	}
} * /
*/

#endif
