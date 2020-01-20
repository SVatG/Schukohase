#ifndef __DS3D_H__
#define __DS3D_H__

#include "Utils.h"
#include "Vector/VectorFixed.h"
#include "Vector/MatrixFixed.h"
#include "Hardware.h"



//
// Register bit definitions.
//

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
#define DS_TEX_FORMAT_A3I5 (1<<26)
#define DS_TEX_FORMAT_PAL2 (2<<26)
#define DS_TEX_FORMAT_PAL4 (3<<26)
#define DS_TEX_FORMAT_PAL8 (4<<26)
#define DS_TEX_FORMAT_COMPRESSED (5<<26)
#define DS_TEX_FORMAT_A5I3 (6<<26)
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



//
// Fixed-point type convesions.
//

static inline uint32_t DSPack16(int16_t a,int16_t b) { return (a&0xffff)|(b<<16); }
static inline uint32_t DSPack10(int16_t a,int16_t b,int16_t c) { return (a&0x3ff)|((b&0x3ff)<<10)|((c&0x3ff)<<20); }
static inline uint16_t DSPackRGB5(int r,int g,int b) { return r|(g<<5)|(b<<10); }
static inline uint16_t DSPackRGB8(int r,int g,int b) { return (r>>3)|((g>>3)<<5)|((b>>3)<<10); }

// f32: Matrix-math 20.12 fixed-point format
static inline int32_t DSinttof32(int n) { return n<<12; }
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

#define DSt16(n) ((int16_t)((n)*(1<<4))) // shorthand

// n10: Normal and light direction 1.9 fixed-point format
static inline int16_t DSf32ton10(int32_t n) { return (n>0xfff)?0x1ff:(int16_t)(n>>3); }
static inline int16_t DSfloatton10(float n) { return (n>0.998)?0x1ff:((int16_t)(n*(float)(1<<9))); }
static inline int DSn10toint(int16_t n) { return n>>9; }

// d15: Depth buffer 12.3 fixed-point format
static inline int16_t DSinttod15(int n) { return (int16_t)(n<<3); }
static inline int16_t DSfloattod15(float n) { return (int16_t)(n*(float)(1<<3)); }
#define DS_MAX_DEPTH 0x7fff



//
// Control functions, direct access only.
// (Some do use FIFO ports but are not very useful in display lists.)
//

void DSInit3D();
void DSResetMatrixStack();

// http://nocash.emubase.de/gbatek.htm#ds3ddisplaycontrol
static inline void DSSetControl(int control) { DISP3DCNT=control; }
static inline void DSSwapBuffers(uint32_t mode) { SWAP_BUFFERS=mode; }
static inline void DSViewport(uint8_t left,uint8_t bottom,uint8_t right,uint8_t top) { VIEWPORT=(left)|(bottom<<8)|(right<<16)|(top<<24); }

static inline void DSAlphaThreshold(int alphathreshold) { ALPHA_TEST_REF=alphathreshold; }
static inline void DSCutoffDepth(uint16_t wval) { DISP_1DOT_DEPTH=wval; }

//http://nocash.emubase.de/gbatek.htm#ds3drearplane
static inline void DSClearParams(uint8_t r,uint8_t g,uint8_t b,uint8_t a,uint8_t id) { CLEAR_COLOR=((id&0x3f)<<24)|((a&0x1f)<<16)|DSPackRGB5(r,g,b); }
static inline void DSClearDepth(uint16_t depth) { CLEAR_DEPTH=depth; }
static inline void DSMaxClearDepth() { CLEAR_DEPTH=DS_MAX_DEPTH; }

static inline void DSWaitUntilEngineNotBusy() { while(GXSTAT&(1<<27)); }



//
// Implementations for functions that can either use direct access or
// be compiled to display lists.
//

typedef void DSPortFunction(volatile uint32_t *port,uint32_t value);

// http://nocash.emubase.de/gbatek.htm#ds3dpolygonattributes
static inline void DSPolygonAttributesImpl(uint32_t format,DSPortFunction *p) { p(&POLYGON_ATTR,format); }

// http://nocash.emubase.de/gbatek.htm#ds3dtextureattributes
static inline void DSSetTextureImpl(uint32_t texture,DSPortFunction *p) { p(&TEXIMAGE_PARAM,texture); }
static inline void DSSetPaletteOffsetImpl(uint32_t offs,uint32_t format,DSPortFunction *p)
{
	if((format&DS_TEX_FORMAT_MASK)==DS_TEX_FORMAT_PAL2) p(&PLTT_BASE,(offs>>3)&0x1fff);
	else p(&PLTT_BASE,(offs>>4)&0x1fff);
}
static inline void DSSetPaletteImpl(void *ptr,uint32_t format,DSPortFunction *p) { DSSetPaletteOffsetImpl((uint32_t)ptr,format,p); }

// http://nocash.emubase.de/gbatek.htm#ds3dpolygondefinitionsbyvertices
static inline void DSBeginImpl(int mode,DSPortFunction *p) { p(&BEGIN_VTXS,mode); }
static inline void DSEndImpl(DSPortFunction *p) { p(&END_VTXS,0); }

static inline void DSVertexImpl(uint32_t xy,uint32_t z,DSPortFunction *p) { p(&VTX_16,xy); p(&VTX_16,z); }
static inline void DSVertex3v16Impl(int16_t x,int16_t y,int16_t z,DSPortFunction *p) { DSVertexImpl(DSPack16(x,y),z,p); }
static inline void DSVertex3fImpl(float x,float y,float z,DSPortFunction *p) { DSVertex3v16Impl(DSfloattov16(x),DSfloattov16(y),DSfloattov16(z),p); }
static inline void DSVertex3vImpl(const ivec3_t v,DSPortFunction *p) { DSVertex3v16Impl(v.x,v.y,v.z,p); }

static inline void DSVertexXYImpl(uint32_t xy,DSPortFunction *p) { p(&VTX_XY,xy); }
static inline void DSVertexXYv16Impl(int16_t x,int16_t y,DSPortFunction *p) { DSVertexXYImpl(DSPack16(x,y),p); }
static inline void DSVertexXYfImpl(float x,float y,DSPortFunction *p) { DSVertexXYv16Impl(DSfloattov16(x),DSfloattov16(y),p); }
static inline void DSVertex2fImpl(float x,float y,DSPortFunction *p) { DSVertexXYfImpl(x,y,p); }

static inline void DSVertexXZImpl(uint32_t xz,DSPortFunction *p) { p(&VTX_XZ,xz); }
static inline void DSVertexXZv16Impl(int16_t x,int16_t z,DSPortFunction *p) { DSVertexXZImpl(DSPack16(x,z),p); }
static inline void DSVertexXZfImpl(float x,float z,DSPortFunction *p) { DSVertexXZv16Impl(DSfloattov16(x),DSfloattov16(z),p); }

static inline void DSVertexYZImpl(uint32_t yz,DSPortFunction *p) { p(&VTX_YZ,yz); }
static inline void DSVertexYZv16Impl(int16_t y,int16_t z,DSPortFunction *p) { DSVertexYZImpl(DSPack16(y,z),p); }
static inline void DSVertexYZfImpl(float y,float z,DSPortFunction *p) { DSVertexYZv16Impl(DSfloattov16(y),DSfloattov16(z),p); }

static inline void DSVertex10Impl(uint32_t xyz,DSPortFunction *p) { p(&VTX_10,xyz); }
static inline void DSVertex103fImpl(float x,float y,float z,DSPortFunction *p) { DSVertex10Impl(DSPack10(DSfloattov16(x),DSfloattov16(y),DSfloattov16(z)),p); }

static inline void DSVertexDiffImpl(uint32_t xyz,DSPortFunction *p) { p(&VTX_DIFF,xyz); }
static inline void DSVertexDiff3n10Impl(int16_t x,int16_t y,int16_t z,DSPortFunction *p) { DSVertexDiffImpl(DSPack10(x,y,z),p); }
static inline void DSVertexDiff3fImpl(float x,float y,float z,DSPortFunction *p) { DSVertexDiff3n10Impl(DSfloatton10(x*8),DSfloatton10(y*8),DSfloatton10(z*8),p); }

// http://nocash.emubase.de/gbatek.htm#ds3dpolygonattributes
static inline void DSColorImpl(uint16_t color,DSPortFunction *p) { p(&COLOR,color); }
static inline void DSColor3bImpl(uint8_t r,uint8_t g,uint8_t b,DSPortFunction *p) { DSColorImpl(DSPackRGB5(r,g,b),p); }
static inline void DSColor3fImpl(float r,float g,float b,DSPortFunction *p) { DSColor3bImpl(r*31,g*31,b*31,p); }

// http://nocash.emubase.de/gbatek.htm#ds3dpolygonlightparameters
static inline void DSNormalImpl(uint32_t normal,DSPortFunction *p) { p(&NORMAL,normal); }
static inline void DSNormal3n10Impl(int16_t x,int16_t y,int16_t z,DSPortFunction *p) { DSNormalImpl(DSPack10(x,y,z),p); }
static inline void DSNormal3fImpl(float x,float y,float z,DSPortFunction *p) { DSNormal3n10Impl(DSfloatton10(x),DSfloatton10(y),DSfloatton10(z),p); }

// http://nocash.emubase.de/gbatek.htm#ds3dtextureattributes
static inline void DSTexCoordImpl(uint32_t coords,DSPortFunction *p) { p(&TEXCOORD,coords); }
static inline void DSTexCoord2t16Impl(uint16_t u,uint16_t v,DSPortFunction *p) { DSTexCoordImpl(DSPack16(u,v),p); }
static inline void DSTexCoord2fImpl(float u,float v,DSPortFunction *p) { DSTexCoord2t16Impl(DSfloattot16(u),DSfloattot16(v),p); }

// http://nocash.emubase.de/gbatek.htm#ds3dmatrixstack
static inline void DSPushMatrixImpl(DSPortFunction *p) { p(&MTX_PUSH,0); }
static inline void DSPopMatrixImpl(int num,DSPortFunction *p) { p(&MTX_POP,num); }
static inline void DSRestoreMatrixImpl(int index,DSPortFunction *p) { p(&MTX_RESTORE,index); }
static inline void DSStoreMatrixImpl(int index,DSPortFunction *p) { p(&MTX_STORE,index); }

// http://nocash.emubase.de/gbatek.htm#ds3dmatrixloadmultiply
static inline void DSMatrixModeImpl(int mode,DSPortFunction *p) { p(&MTX_MODE,mode); }
static inline void DSLoadIdentityImpl(DSPortFunction *p) { p(&MTX_IDENTITY,0); }

static inline void DSLoadMatrix4x3Impl(const imat4x3_t m,DSPortFunction *p) { for(int i=0;i<12;i++) p(&MTX_LOAD_4x3,m.m[i]); }
static inline void DSLoadMatrix4x4Impl(const imat4x4_t m,DSPortFunction *p) { for(int i=0;i<16;i++) p(&MTX_LOAD_4x4,m.m[i]); }
static inline void DSMultMatrix3x3Impl(const imat3x3_t m,DSPortFunction *p) { for(int i=0;i<9;i++) p(&MTX_MULT_3x3,m.m[i]); }
static inline void DSMultMatrix4x3Impl(const imat4x3_t m,DSPortFunction *p) { for(int i=0;i<12;i++) p(&MTX_MULT_4x3,m.m[i]); }
static inline void DSMultMatrix4x4Impl(const imat4x4_t m,DSPortFunction *p) { for(int i=0;i<16;i++) p(&MTX_LOAD_4x4,m.m[i]); }

static inline void DSScalef32Impl(int32_t x,int32_t y,int32_t z,DSPortFunction *p) { p(&MTX_SCALE,x); p(&MTX_SCALE,y); p(&MTX_SCALE,z); }
static inline void DSScalefImpl(float x,float y,float z,DSPortFunction *p) { DSScalef32Impl(DSf32(x),DSf32(y),DSf32(z),p); }
static inline void DSScaleUniformf32Impl(int32_t factor,DSPortFunction *p) { DSScalef32Impl(factor,factor,factor,p); }
static inline void DSScaleUniformfImpl(float factor,DSPortFunction *p) { DSScaleUniformf32Impl(DSf32(factor),p); }

static inline void DSTranslatef32Impl(int32_t x,int32_t y,int32_t z,DSPortFunction *p) { p(&MTX_TRANS,x); p(&MTX_TRANS,y); p(&MTX_TRANS,z); }
static inline void DSTranslatevImpl(const ivec3_t v,DSPortFunction *p) { DSTranslatef32Impl(v.x,v.y,v.z,p); }
static inline void DSTranslatefImpl(float x,float y,float z,DSPortFunction *p) { DSTranslatef32Impl(DSf32(x),DSf32(y),DSf32(z),p); }

static inline void DSRotateXiImpl(int angle,DSPortFunction *p) { DSMultMatrix3x3Impl(imat3x3rotatex(angle),p); }
static inline void DSRotateYiImpl(int angle,DSPortFunction *p) { DSMultMatrix3x3Impl(imat3x3rotatey(angle),p); }
static inline void DSRotateZiImpl(int angle,DSPortFunction *p) { DSMultMatrix3x3Impl(imat3x3rotatez(angle),p); }
static inline void DSRotateXfImpl(float angle,DSPortFunction *p) { DSRotateXiImpl(iangle(angle),p); }
static inline void DSRotateYfImpl(float angle,DSPortFunction *p) { DSRotateYiImpl(iangle(angle),p); }
static inline void DSRotateZfImpl(float angle,DSPortFunction *p) { DSRotateZiImpl(iangle(angle),p); }

static inline void DSRotatevImpl(int angle,ivec3_t axis,DSPortFunction *p) { DSMultMatrix3x3Impl(imat3x3rotate(angle,axis),p); }
static inline void DSRotatef32iImpl(int angle,int32_t x,int32_t y,int32_t z,DSPortFunction *p) { DSRotatevImpl(angle,ivec3(x,y,z),p); }
static inline void DSRotatef32fImpl(float angle,int32_t x,int32_t y,int32_t z,DSPortFunction *p) { DSRotatef32iImpl(iangle(angle),x,y,z,p); }
static inline void DSRotatefImpl(float angle,float x,float y,float z,DSPortFunction *p) { DSRotatef32fImpl(angle,DSf32(x),DSf32(y),DSf32(z),p); }

static inline void DSOrthof32Impl(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far,DSPortFunction *p)
{
	DSMultMatrix4x4Impl(imat4x4(
		idiv(DSf32(2),right-left),0,0,-idiv(right+left,right-left),
		0,idiv(DSf32(2),top-bottom),0,-idiv(top+bottom,top-bottom),
		0,0,idiv(DSf32(-2),far-near), -idiv(far+near,far-near),
		0,0,0,                        DSf32(1)
	),p);
}
static inline void DSOrthofImpl(float left,float right,float bottom,float top,float near, float far,DSPortFunction *p) { DSOrthof32Impl(DSf32(left),DSf32(right),DSf32(bottom),DSf32(top),DSf32(near),DSf32(far),p); }
static inline void DS2DProjectionImpl(int fractionbits,DSPortFunction *p) { DSOrthof32Impl(0,(256<<fractionbits),(192<<fractionbits),0,DSf32(-1),DSf32(1),p); }

void DSLookAtvImpl(ivec3_t eye,ivec3_t lookat,ivec3_t up,DSPortFunction *p);
static inline void DSLookAtf32Impl(int32_t eyex,int32_t eyey,int32_t eyez,int32_t lookatx,int32_t lookaty,int32_t lookatz,int32_t upx,int32_t upy,int32_t upz,DSPortFunction *p) { DSLookAtvImpl(ivec3(eyex,eyey,eyez),ivec3(lookatx,lookaty,lookatz),ivec3(upx,upy,upz),p); }
static inline void DSLookAtfImpl(float eyex,float eyey,float eyez,float lookatx,float lookaty, float lookatz,float upx,float upy,float upz,DSPortFunction *p) { DSLookAtf32Impl(DSf32(eyex),DSf32(eyey),DSf32(eyez),DSf32(lookatx),DSf32(lookaty),DSf32(lookatz),DSf32(upx),DSf32(upy),DSf32(upz),p); }

static inline void DSFrustumf32Impl(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far,DSPortFunction *p)
{
	DSMultMatrix4x4Impl(imat4x4(
		idiv(2*near,right-left),0,idiv(right+left,right-left),0,
		0,idiv(2*near,top-bottom),idiv(top+bottom,top-bottom),0,
		0,0,                      -idiv(far+near,far-near),   -idiv(2*imul(far,near),far-near),
		0,0,                      DSf32(-1),                  0
	),p);
}
static inline void DSFrustumfImpl(float left,float right,float bottom,float top,float near,float far,DSPortFunction *p) { DSFrustumf32Impl(DSf32(left),DSf32(right),DSf32(bottom),DSf32(top),DSf32(near),DSf32(far),p); }

static inline void DSPerspectivef32Impl(int fovy,int32_t aspect,int32_t near,int32_t far,DSPortFunction *p)
{
	int32_t ymax=imul(near,itan(fovy>>1));
	int32_t ymin=-ymax;
	int32_t xmin=imul(ymin,aspect);
	int32_t xmax=imul(ymax,aspect);

	DSFrustumf32Impl(xmin,xmax,ymin,ymax,near,far,p);
}
static inline void DSPerspectivefImpl(float fovy,float aspect,float near,float far,DSPortFunction *p) { DSPerspectivef32Impl(iangle(fovy),DSf32(aspect),DSf32(near),DSf32(far),p); }

/* Utility function which generates a picking matrix for selection
 x 2D x of center  (touch x normally)
 y 2D y of center  (touch y normally)
 width width in pixels of the window (3 or 4 is a good number)
 height height in pixels of the window (3 or 4 is a good number)
 viewport the current viewport (normaly {0, 0, 255, 191}) */
static inline void DSPickMatrixImpl(int x,int y,int width,int height,const int viewport[4],DSPortFunction *p)
{
	DSMultMatrix4x4Impl(imat4x4(
		DSf32(viewport[2])/width,0, 0,DSf32(viewport[2]+((viewport[0]-x)<<1))/width,
		0,DSf32(viewport[3])/height,0,DSf32(viewport[3]+((viewport[1]-y)<<1))/height,
		0,0,DSf32(1),               0,
		0,0,0,                      DSf32(1)
	),p);
}

// http://nocash.emubase.de/gbatek.htm#ds3dpolygonlightparameters
static inline void DSLightImpl(int n,uint16_t color,uint32_t dir,DSPortFunction *p)
{
	uint32_t nummask=(n&3)<<30;
	p(&LIGHT_VECTOR,nummask|dir);
	p(&LIGHT_COLOR,nummask|color);
}
static inline void DSLight3n10Impl(int n,uint16_t color,int16_t x,int16_t y,int16_t z,DSPortFunction *p) { DSLightImpl(n,color,DSPack10(x,y,z),p); }
static inline void DSLight3fImpl(int id,uint16_t color,float x,float y,float z,DSPortFunction *p) { DSLight3n10Impl(id,color,DSfloatton10(x),DSfloatton10(y),DSfloatton10(z),p); }
static inline void DSLight3b3fImpl(int id,uint8_t r,uint8_t g,uint8_t b,float x,float y,float z,DSPortFunction *p) { DSLight3fImpl(id,DSPackRGB5(r,g,b),x,y,z,p); }

static inline void DSMaterialDiffuseAndAmbientImpl(uint16_t diffuse,uint16_t ambient,DSPortFunction *p) { p(&DIF_AMB,DSPack16(diffuse,ambient)); }
static inline void DSMaterialDiffuseAndAmbient6bImpl(uint8_t dr,uint8_t dg,uint8_t db,uint8_t ar,uint8_t ag,uint8_t ab,DSPortFunction *p) { DSMaterialDiffuseAndAmbientImpl(DSPackRGB5(dr,dg,db),DSPackRGB5(ar,ag,ab),p); }
static inline void DSMaterialDiffuseAndAmbient3bImpl(uint8_t r,uint8_t g,uint8_t b,DSPortFunction *p) { DSMaterialDiffuseAndAmbientImpl(DSPackRGB5(r,g,b),DSPackRGB5(r,g,b),p); }

static inline void DSMaterialSpecularAndEmissionImpl(uint8_t shiny,uint16_t specular,uint16_t emission,DSPortFunction *p) { p(&SPE_EMI,DSPack16(specular,emission)|(shiny?0x8000:0)); }
static inline void DSMaterialSpecularAndEmission6bImpl(uint8_t shiny,uint8_t sr,uint8_t sg,uint8_t sb,uint8_t er,uint8_t eg,uint8_t eb,DSPortFunction *p) { DSMaterialSpecularAndEmissionImpl(shiny,DSPackRGB5(sr,sg,sb),DSPackRGB5(er,eg,eb),p); }

static inline void DSMaterialDefaultShininessTableImpl(DSPortFunction *p)
{
	for(int i=0;i<32;i++) p(&SHININESS,(i*8)|((i*8+2)<<8)|((i*8+4)<<8)|((i*8+6)<<8));
}



//
// Direct-access functions.
//

static inline void DSDirect(volatile uint32_t *port,uint32_t value) { *port=value; }

static inline void DSPolygonAttributes(uint32_t format) { DSPolygonAttributesImpl(format,DSDirect); }
static inline void DSSetTexture(uint32_t texture) { DSSetTextureImpl(texture,DSDirect); }
static inline void DSSetPaletteOffset(uint32_t offs,uint32_t format) { DSSetPaletteOffsetImpl(offs,format,DSDirect); }
static inline void DSSetPalette(void *ptr,uint32_t format) { DSSetPaletteImpl(ptr,format,DSDirect); }
static inline void DSBegin(int mode) { DSBeginImpl(mode,DSDirect); }
static inline void DSEnd() { DSEndImpl(DSDirect); }
static inline void DSVertex(uint32_t xy,uint32_t z) { DSVertexImpl(xy,z,DSDirect); }
static inline void DSVertex3v16(int16_t x,int16_t y,int16_t z) { DSVertex3v16Impl(x,y,z,DSDirect); }
static inline void DSVertex3f(float x,float y,float z) { DSVertex3fImpl(x,y,z,DSDirect); }
static inline void DSVertex3v(const ivec3_t v) { DSVertex3vImpl(v,DSDirect); }
static inline void DSVertexXY(uint32_t xy) { DSVertexXYImpl(xy,DSDirect); }
static inline void DSVertexXYv16(int16_t x,int16_t y) { DSVertexXYv16Impl(x,y,DSDirect); }
static inline void DSVertexXYf(float x,float y) { DSVertexXYfImpl(x,y,DSDirect); }
static inline void DSVertex2f(float x,float y) { DSVertex2fImpl(x,y,DSDirect); }
static inline void DSVertexXZ(uint32_t xz) { DSVertexXZImpl(xz,DSDirect); }
static inline void DSVertexXZv16(int16_t x,int16_t z) { DSVertexXZv16Impl(x,z,DSDirect); }
static inline void DSVertexXZf(float x,float z) { DSVertexXZfImpl(x,z,DSDirect); }
static inline void DSVertexYZ(uint32_t yz) { DSVertexYZImpl(yz,DSDirect); }
static inline void DSVertexYZv16(int16_t y,int16_t z) { DSVertexYZv16Impl(y,z,DSDirect); }
static inline void DSVertexYZf(float y,float z) { DSVertexYZfImpl(y,z,DSDirect); }
static inline void DSVertex10(uint32_t xyz) { DSVertex10Impl(xyz,DSDirect); }
static inline void DSVertex103f(float x,float y,float z) { DSVertex103fImpl(x,y,z,DSDirect); }
static inline void DSVertexDiff(uint32_t xyz) { DSVertexDiffImpl(xyz,DSDirect); }
static inline void DSVertexDiff3n10(int16_t x,int16_t y,int16_t z) { DSVertexDiff3n10Impl(x,y,z,DSDirect); }
static inline void DSVertexDiff3f(float x,float y,float z) { DSVertexDiff3fImpl(x,y,z,DSDirect); }
static inline void DSColor(uint16_t color) { DSColorImpl(color,DSDirect); }
static inline void DSColor3b(uint8_t r,uint8_t g,uint8_t b) { DSColor3bImpl(r,g,b,DSDirect); }
static inline void DSColor3f(float r,float g,float b) { DSColor3fImpl(r,g,b,DSDirect); }
static inline void DSNormal(uint32_t normal) { DSNormalImpl(normal,DSDirect); }
static inline void DSNormal3n10(int16_t x,int16_t y,int16_t z) { DSNormal3n10Impl(x,y,z,DSDirect); }
static inline void DSNormal3f(float x,float y,float z) { DSNormal3fImpl(x,y,z,DSDirect); }
static inline void DSTexCoord(uint32_t coords) { DSTexCoordImpl(coords,DSDirect); }
static inline void DSTexCoord2t16(uint16_t u,uint16_t v) { DSTexCoord2t16Impl(u,v,DSDirect); }
static inline void DSTexCoord2f(float u,float v) { DSTexCoord2fImpl(u,v,DSDirect); }
static inline void DSPushMatrix() { DSPushMatrixImpl(DSDirect); }
static inline void DSPopMatrix(int num) { DSPopMatrixImpl(num,DSDirect); }
static inline void DSRestoreMatrix(int index) { DSRestoreMatrixImpl(index,DSDirect); }
static inline void DSStoreMatrix(int index) { DSStoreMatrixImpl(index,DSDirect); }
static inline void DSMatrixMode(int mode) { DSMatrixModeImpl(mode,DSDirect); }
static inline void DSLoadIdentity() { DSLoadIdentityImpl(DSDirect); }
static inline void DSLoadMatrix4x3(const imat4x3_t m) { DSLoadMatrix4x3Impl(m,DSDirect); }
static inline void DSLoadMatrix4x4(const imat4x4_t m) { DSLoadMatrix4x4Impl(m,DSDirect); }
static inline void DSMultMatrix3x3(const imat3x3_t m) { DSMultMatrix3x3Impl(m,DSDirect); }
static inline void DSMultMatrix4x3(const imat4x3_t m) { DSMultMatrix4x3Impl(m,DSDirect); }
static inline void DSMultMatrix4x4(const imat4x4_t m) { DSMultMatrix4x4Impl(m,DSDirect); }
static inline void DSScalef32(int32_t x,int32_t y,int32_t z) { DSScalef32Impl(x,y,z,DSDirect); }
static inline void DSScalef(float x,float y,float z) { DSScalefImpl(x,y,z,DSDirect); }
static inline void DSScaleUniformf32(int32_t factor) { DSScaleUniformf32Impl(factor,DSDirect); }
static inline void DSScaleUniformf(float factor) { DSScaleUniformfImpl(factor,DSDirect); }
static inline void DSTranslatef32(int32_t x,int32_t y,int32_t z) { DSTranslatef32Impl(x,y,z,DSDirect); }
static inline void DSTranslatev(const ivec3_t v) { DSTranslatevImpl(v,DSDirect); }
static inline void DSTranslatef(float x,float y,float z) { DSTranslatefImpl(x,y,z,DSDirect); }
static inline void DSRotateXi(int angle) { DSRotateXiImpl(angle,DSDirect); }
static inline void DSRotateYi(int angle) { DSRotateYiImpl(angle,DSDirect); }
static inline void DSRotateZi(int angle) { DSRotateZiImpl(angle,DSDirect); }
static inline void DSRotateXf(float angle) { DSRotateXfImpl(angle,DSDirect); }
static inline void DSRotateYf(float angle) { DSRotateYfImpl(angle,DSDirect); }
static inline void DSRotateZf(float angle) { DSRotateZfImpl(angle,DSDirect); }
static inline void DSRotatev(int angle,ivec3_t axis,DSPortFunction *p) { DSRotatevImpl(angle,axis,DSDirect); }
static inline void DSRotatef32i(int angle,int32_t x,int32_t y,int32_t z,DSPortFunction *p) { DSRotatef32iImpl(angle,x,y,z,DSDirect); }
static inline void DSRotatef32f(float angle,int32_t x,int32_t y,int32_t z) { DSRotatef32fImpl(angle,x,y,z,DSDirect); }
static inline void DSRotatef(float angle,float x,float y,float z) { DSRotatefImpl(angle,x,y,z,DSDirect); }
static inline void DSOrthof32(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far) { DSOrthof32Impl(left,right,bottom,top,near,far,DSDirect); }
static inline void DSOrthof(float left,float right,float bottom,float top,float near, float far) { DSOrthofImpl(left,right,bottom,top,near,far,DSDirect); }
static inline void DS2DProjection(int fractionbits) { DS2DProjectionImpl(fractionbits,DSDirect); }
static inline void DSLookAtv(ivec3_t eye,ivec3_t lookat,ivec3_t up) { DSLookAtvImpl(eye,lookat,up,DSDirect); }
static inline void DSLookAtf32(int32_t eyex,int32_t eyey,int32_t eyez,int32_t lookatx,int32_t lookaty,int32_t lookatz,int32_t upx,int32_t upy,int32_t upz) { DSLookAtf32Impl(eyex,eyey,eyez,lookatx,lookaty,lookatz,upx,upy,upz,DSDirect); }
static inline void DSLookAtf(float eyex,float eyey,float eyez,float lookatx,float lookaty,float lookatz,float upx,float upy,float upz) { DSLookAtfImpl(eyex,eyey,eyez,lookatx,lookaty,lookatz,upx,upy,upz,DSDirect); }
static inline void DSFrustumf32(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far) { DSFrustumf32Impl(left,right,bottom,top,near,far,DSDirect); }
static inline void DSFrustumf(float left,float right,float bottom,float top,float near,float far) { DSFrustumfImpl(left,right,bottom,top,near,far,DSDirect); }
static inline void DSPerspectivef32(int fovy,int32_t aspect,int32_t near,int32_t far) { DSPerspectivef32Impl(fovy,aspect,near,far,DSDirect); }
static inline void DSPerspectivef(float fovy,float aspect,float near,float far) { DSPerspectivefImpl(fovy,aspect,near,far,DSDirect); }
static inline void DSLight(int n,uint16_t color,uint32_t dir) { DSLightImpl(n,color,dir,DSDirect); }
static inline void DSLight3n10(int n,uint16_t color,int16_t x,int16_t y,int16_t z) { DSLight3n10Impl(n,color,x,y,z,DSDirect); }
static inline void DSLight3f(int id,uint16_t color,float x,float y,float z) { DSLight3fImpl(id,color,x,y,z,DSDirect); }
static inline void DSLight3b3f(int id,uint8_t r,uint8_t g,uint8_t b,float x,float y,float z) { DSLight3b3fImpl(id,r,g,b,x,y,z,DSDirect); }
static inline void DSMaterialDiffuseAndAmbient(uint16_t diffuse,uint16_t ambient) { DSMaterialDiffuseAndAmbientImpl(diffuse,ambient,DSDirect); }
static inline void DSMaterialDiffuseAndAmbient6b(uint8_t dr,uint8_t dg,uint8_t db,uint8_t ar,uint8_t ag,uint8_t ab) { DSMaterialDiffuseAndAmbient6bImpl(dr,dg,db,ar,ag,ab,DSDirect); }
static inline void DSMaterialDiffuseAndAmbient3b(uint8_t r,uint8_t g,uint8_t b) { DSMaterialDiffuseAndAmbient3bImpl(r,g,b,DSDirect); }
static inline void DSMaterialSpecularAndEmission(uint8_t shiny,uint16_t specular,uint16_t emission) { DSMaterialSpecularAndEmissionImpl(shiny,specular,emission,DSDirect); }
static inline void DSMaterialSpecularAndEmission6b(uint8_t shiny,uint8_t sr,uint8_t sg,uint8_t sb,uint8_t er,uint8_t eg,uint8_t eb) { DSMaterialSpecularAndEmission6bImpl(shiny,sr,sg,sb,er,eg,eb,DSDirect); }
static inline void DSMaterialDefaultShininessTable() { DSMaterialDefaultShininessTableImpl(DSDirect); }



//
// Display list functions.
//

void DSStartList(uint32_t *list,int size);
int DSFinishList();
void DSAppendList(const uint32_t *list);
void DSCallList(const uint32_t *list);

void DSList(volatile uint32_t *port,uint32_t value);

static inline void DSListPolygonAttributes(uint32_t format) { DSPolygonAttributesImpl(format,DSList); }
static inline void DSListSetTexture(uint32_t texture) { DSSetTextureImpl(texture,DSList); }
static inline void DSListSetPaletteOffset(uint32_t offs,uint32_t format) { DSSetPaletteOffsetImpl(offs,format,DSList); }
static inline void DSListSetPalette(void *ptr,uint32_t format) { DSSetPaletteImpl(ptr,format,DSList); }
static inline void DSListBegin(int mode) { DSBeginImpl(mode,DSList); }
static inline void DSListEnd() { DSEndImpl(DSList); }
static inline void DSListVertex(uint32_t xy,uint32_t z) { DSVertexImpl(xy,z,DSList); }
static inline void DSListVertex3v16(int16_t x,int16_t y,int16_t z) { DSVertex3v16Impl(x,y,z,DSList); }
static inline void DSListVertex3f(float x,float y,float z) { DSVertex3fImpl(x,y,z,DSList); }
static inline void DSListVertex3v(const ivec3_t v) { DSVertex3vImpl(v,DSList); }
static inline void DSListVertexXY(uint32_t xy) { DSVertexXYImpl(xy,DSList); }
static inline void DSListVertexXYv16(int16_t x,int16_t y) { DSVertexXYv16Impl(x,y,DSList); }
static inline void DSListVertexXYf(float x,float y) { DSVertexXYfImpl(x,y,DSList); }
static inline void DSListVertex2f(float x,float y) { DSVertex2fImpl(x,y,DSList); }
static inline void DSListVertexXZ(uint32_t xz) { DSVertexXZImpl(xz,DSList); }
static inline void DSListVertexXZv16(int16_t x,int16_t z) { DSVertexXZv16Impl(x,z,DSList); }
static inline void DSListVertexXZf(float x,float z) { DSVertexXZfImpl(x,z,DSList); }
static inline void DSListVertexYZ(uint32_t yz) { DSVertexYZImpl(yz,DSList); }
static inline void DSListVertexYZv16(int16_t y,int16_t z) { DSVertexYZv16Impl(y,z,DSList); }
static inline void DSListVertexYZf(float y,float z) { DSVertexYZfImpl(y,z,DSList); }
static inline void DSListVertex10(uint32_t xyz) { DSVertex10Impl(xyz,DSList); }
static inline void DSListVertex103f(float x,float y,float z) { DSVertex103fImpl(x,y,z,DSList); }
static inline void DSListVertexDiff(uint32_t xyz) { DSVertexDiffImpl(xyz,DSList); }
static inline void DSListVertexDiff3n10(int16_t x,int16_t y,int16_t z) { DSVertexDiff3n10Impl(x,y,z,DSList); }
static inline void DSListVertexDiff3f(float x,float y,float z) { DSVertexDiff3fImpl(x,y,z,DSList); }
static inline void DSListColor(uint16_t color) { DSColorImpl(color,DSList); }
static inline void DSListColor3b(uint8_t r,uint8_t g,uint8_t b) { DSColor3bImpl(r,g,b,DSList); }
static inline void DSListColor3f(float r,float g,float b) { DSColor3fImpl(r,g,b,DSList); }
static inline void DSListNormal(uint32_t normal) { DSNormalImpl(normal,DSList); }
static inline void DSListNormal3n10(int16_t x,int16_t y,int16_t z) { DSNormal3n10Impl(x,y,z,DSList); }
static inline void DSListNormal3f(float x,float y,float z) { DSNormal3fImpl(x,y,z,DSList); }
static inline void DSListTexCoord(uint32_t coords) { DSTexCoordImpl(coords,DSList); }
static inline void DSListTexCoord2t16(uint16_t u,uint16_t v) { DSTexCoord2t16Impl(u,v,DSList); }
static inline void DSListTexCoord2f(float u,float v) { DSTexCoord2fImpl(u,v,DSList); }
static inline void DSListPushMatrix() { DSPushMatrixImpl(DSList); }
static inline void DSListPopMatrix(int num) { DSPopMatrixImpl(num,DSList); }
static inline void DSListRestoreMatrix(int index) { DSRestoreMatrixImpl(index,DSList); }
static inline void DSListStoreMatrix(int index) { DSStoreMatrixImpl(index,DSList); }
static inline void DSListMatrixMode(int mode) { DSMatrixModeImpl(mode,DSList); }
static inline void DSListLoadIdentity() { DSLoadIdentityImpl(DSList); }
static inline void DSListLoadMatrix4x3(const imat4x3_t m) { DSLoadMatrix4x3Impl(m,DSList); }
static inline void DSListLoadMatrix4x4(const imat4x4_t m) { DSLoadMatrix4x4Impl(m,DSList); }
static inline void DSListMultMatrix3x3(const imat3x3_t m) { DSMultMatrix3x3Impl(m,DSList); }
static inline void DSListMultMatrix4x3(const imat4x3_t m) { DSMultMatrix4x3Impl(m,DSList); }
static inline void DSListMultMatrix4x4(const imat4x4_t m) { DSMultMatrix4x4Impl(m,DSList); }
static inline void DSListScalef32(int32_t x,int32_t y,int32_t z) { DSScalef32Impl(x,y,z,DSList); }
static inline void DSListScalef(float x,float y,float z) { DSScalefImpl(x,y,z,DSList); }
static inline void DSListScaleUniformf32(int32_t factor) { DSScaleUniformf32Impl(factor,DSList); }
static inline void DSListScaleUniformf(float factor) { DSScaleUniformfImpl(factor,DSList); }
static inline void DSListTranslatef32(int32_t x,int32_t y,int32_t z) { DSTranslatef32Impl(x,y,z,DSList); }
static inline void DSListTranslatev(const ivec3_t v) { DSTranslatevImpl(v,DSList); }
static inline void DSListTranslatef(float x,float y,float z) { DSTranslatefImpl(x,y,z,DSList); }
static inline void DSListRotateXi(int angle) { DSRotateXiImpl(angle,DSList); }
static inline void DSListRotateYi(int angle) { DSRotateYiImpl(angle,DSList); }
static inline void DSListRotateZi(int angle) { DSRotateZiImpl(angle,DSList); }
static inline void DSListRotateXf(float angle) { DSRotateXfImpl(angle,DSList); }
static inline void DSListRotateYf(float angle) { DSRotateYfImpl(angle,DSList); }
static inline void DSListRotateZf(float angle) { DSRotateZfImpl(angle,DSList); }
static inline void DSListRotatev(int angle,ivec3_t axis,DSPortFunction *p) { DSRotatevImpl(angle,axis,DSList); }
static inline void DSListRotatef32i(int angle,int32_t x,int32_t y,int32_t z,DSPortFunction *p) { DSRotatef32iImpl(angle,x,y,z,DSList); }
static inline void DSListRotatef32f(float angle,int32_t x,int32_t y,int32_t z) { DSRotatef32fImpl(angle,x,y,z,DSList); }
static inline void DSListRotatef(float angle,float x,float y,float z) { DSRotatefImpl(angle,x,y,z,DSList); }
static inline void DSListOrthof32(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far) { DSOrthof32Impl(left,right,bottom,top,near,far,DSList); }
static inline void DSListOrthof(float left,float right,float bottom,float top,float near, float far) { DSOrthofImpl(left,right,bottom,top,near,far,DSList); }
static inline void DSList2DProjection(int fractionbits) { DS2DProjectionImpl(fractionbits,DSList); }
static inline void DSListLookAtv(ivec3_t eye,ivec3_t lookat,ivec3_t up) { DSLookAtvImpl(eye,lookat,up,DSList); }
static inline void DSListLookAtf32(int32_t eyex,int32_t eyey,int32_t eyez,int32_t lookatx,int32_t lookaty,int32_t lookatz,int32_t upx,int32_t upy,int32_t upz) { DSLookAtf32Impl(eyex,eyey,eyez,lookatx,lookaty,lookatz,upx,upy,upz,DSList); }
static inline void DSListLookAtf(float eyex,float eyey,float eyez,float lookatx,float lookaty,float lookatz,float upx,float upy,float upz) { DSLookAtfImpl(eyex,eyey,eyez,lookatx,lookaty,lookatz,upx,upy,upz,DSList); }
static inline void DSListFrustumf32(int32_t left,int32_t right,int32_t bottom,int32_t top,int32_t near,int32_t far) { DSFrustumf32Impl(left,right,bottom,top,near,far,DSList); }
static inline void DSListFrustumf(float left,float right,float bottom,float top,float near,float far) { DSFrustumfImpl(left,right,bottom,top,near,far,DSList); }
static inline void DSListPerspectivef32(int fovy,int32_t aspect,int32_t near,int32_t far) { DSPerspectivef32Impl(fovy,aspect,near,far,DSList); }
static inline void DSListPerspectivef(float fovy,float aspect,float near,float far) { DSPerspectivefImpl(fovy,aspect,near,far,DSList); }
static inline void DSListLight(int n,uint16_t color,uint32_t dir) { DSLightImpl(n,color,dir,DSList); }
static inline void DSListLight3n10(int n,uint16_t color,int16_t x,int16_t y,int16_t z) { DSLight3n10Impl(n,color,x,y,z,DSList); }
static inline void DSListLight3f(int id,uint16_t color,float x,float y,float z) { DSLight3fImpl(id,color,x,y,z,DSList); }
static inline void DSListLight3b3f(int id,uint8_t r,uint8_t g,uint8_t b,float x,float y,float z) { DSLight3b3fImpl(id,r,g,b,x,y,z,DSList); }
static inline void DSListMaterialDiffuseAndAmbient(uint16_t diffuse,uint16_t ambient) { DSMaterialDiffuseAndAmbientImpl(diffuse,ambient,DSList); }
static inline void DSListMaterialDiffuseAndAmbient6b(uint8_t dr,uint8_t dg,uint8_t db,uint8_t ar,uint8_t ag,uint8_t ab) { DSMaterialDiffuseAndAmbient6bImpl(dr,dg,db,ar,ag,ab,DSList); }
static inline void DSListMaterialDiffuseAndAmbient3b(uint8_t r,uint8_t g,uint8_t b) { DSMaterialDiffuseAndAmbient3bImpl(r,g,b,DSList); }
static inline void DSListMaterialSpecularAndEmission(uint8_t shiny,uint16_t specular,uint16_t emission) { DSMaterialSpecularAndEmissionImpl(shiny,specular,emission,DSList); }
static inline void DSListMaterialSpecularAndEmission6b(uint8_t shiny,uint8_t sr,uint8_t sg,uint8_t sb,uint8_t er,uint8_t eg,uint8_t eb) { DSMaterialSpecularAndEmission6bImpl(shiny,sr,sg,sb,er,eg,eb,DSList); }
static inline void DSListMaterialDefaultShininessTable() { DSMaterialDefaultShininessTableImpl(DSList); }




//
// Matrix readback functions.
//

static inline imat4x4_t DSGetPositionMatrix()
{
	imat4x4_t res;

	DSMatrixMode(DS_PROJECTION);
	DSPushMatrix();
	DSLoadIdentity();
	DSWaitUntilEngineNotBusy();
	for(int i=0;i<16;i++) res.m[i]=CLIPMTX_RESULT[i];
	DSPopMatrix(1);

	return res;
}

static inline imat4x4_t DSGetProjectionMatrix()
{
	imat4x4_t res;

	DSMatrixMode(DS_POSITION);
	DSPushMatrix();
	DSLoadIdentity();
	DSWaitUntilEngineNotBusy();
	for(int i=0;i<16;i++) res.m[i]=CLIPMTX_RESULT[i];
	DSPopMatrix(1);

	return res;
}

static inline imat3x3_t DSGetVectorMatrix()
{
	imat3x3_t res;

	DSWaitUntilEngineNotBusy();
	for(int i=0;i<9;i++) res.m[i]=VECMTX_RESULT[i];

	return res;
}



//
// Texture handling and allocation functions.
//

uint32_t DSTextureSize(uint32_t flags);
uint16_t *DSTextureAddress(uint32_t texture);

uint32_t DSAllocTexture(uint32_t flags);
void DSFreeAllTextures();
void DSCopyTexture(uint32_t texture,void *data);
uint32_t DSAllocAndCopyTexture(uint32_t flags,void *data);



//
// Fog functions.
//

void DSSetFogWithCallback(uint8_t r,uint8_t g,uint8_t b,uint8_t a,
int32_t start,int32_t end,int32_t near,int32_t far,
int32_t (*callback)(int32_t z,int32_t start,int32_t end));
void DSSetFogLinearf32(uint8_t r,uint8_t g,uint8_t b,uint8_t a,int32_t start,int32_t end,int32_t near,int32_t far);
void DSSetFogLinearf(uint8_t r,uint8_t g,uint8_t b,uint8_t a,float start,float end,float near,float far);



//
// Outline and toon rendering functions.
//

// http://nocash.emubase.de/gbatek.htm#ds3dtoonedgefog
static inline void DSSetOutlineColor(int id,uint16_t color,DSPortFunction *p) { EDGE_COLOR[id]=color; }
static inline void DSSetOutlineColor3b(int id,uint8_t r,uint8_t g,uint8_t b,DSPortFunction *p) { DSSetOutlineColor(id,DSPackRGB5(r,g,b),p); }

static inline void DSSetToonTable(const uint16_t *table,DSPortFunction *p) { for(int i=0;i<32;i++) TOON_TABLE[i]=table[i]; }
static inline void DSSetToonTableRange(int start,int end,uint16_t color,DSPortFunction *p) { for(int i=start;i<=end;i++) TOON_TABLE[i]=color; }
static inline void DSSetToonTableRange3b(int start,int end,uint8_t r,uint8_t g,uint8_t b,DSPortFunction *p) { DSSetToonTableRange(start,end,DSPackRGB5(r,g,b),p); }

#endif
