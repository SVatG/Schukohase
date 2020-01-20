#ifndef __MATRIX_FIXED_H__
#define __MATRIX_FIXED_H__

#include "VectorFixed.h"



// Definitions

typedef struct { int32_t m[4]; } imat2x2_t;
typedef struct { int32_t m[6]; } imat3x2_t;
typedef struct { int32_t m[9]; } imat3x3_t;
typedef struct { int32_t m[12]; } imat4x3_t;
typedef struct { int32_t m[16]; } imat4x4_t;

#define imat2x2one imat2x2(F(1),0, 0,F(1))
#define imat3x2one imat3x2(F(1),0,0, 0,F(1),0)
#define imat3x3one imat3x3(F(1),0,0, 0,F(1),0, 0,0,F(1))
#define imat4x3one imat4x3(F(1),0,0,0, 0,F(1),0,0, 0,0,F(1),0)
#define imat4x4one imat4x4(F(1),0,0,0, 0,F(1),0,0, 0,0,F(1),0, 0,0,0,F(1))



// Individual element constructors

static inline imat2x2_t imat2x2(int32_t a11,int32_t a12,
                              int32_t a21,int32_t a22)
{ return (imat2x2_t){a11,a21,a12,a22}; }

static inline imat3x2_t imat3x2(int32_t a11,int32_t a12,int32_t a13,
                              int32_t a21,int32_t a22,int32_t a23)
{ return (imat3x2_t){a11,a21,a12,a22,a13,a23}; }

static inline imat3x3_t imat3x3(int32_t a11,int32_t a12,int32_t a13,
                              int32_t a21,int32_t a22,int32_t a23,
                              int32_t a31,int32_t a32,int32_t a33)
{ return (imat3x3_t){a11,a21,a31,a12,a22,a32,a13,a23,a33}; }

static inline imat4x3_t imat4x3(int32_t a11,int32_t a12,int32_t a13,int32_t a14,
                              int32_t a21,int32_t a22,int32_t a23,int32_t a24,
                              int32_t a31,int32_t a32,int32_t a33,int32_t a34)
{ return (imat4x3_t){a11,a21,a31,a12,a22,a32,a13,a23,a33,a14,a24,a34}; }

static inline imat4x4_t imat4x4(int32_t a11,int32_t a12,int32_t a13,int32_t a14,
                              int32_t a21,int32_t a22,int32_t a23,int32_t a24,
                              int32_t a31,int32_t a32,int32_t a33,int32_t a34,
                              int32_t a41,int32_t a42,int32_t a43,int32_t a44)
{ return (imat4x4_t){a11,a21,a31,a41,a12,a22,a32,a42,a13,a23,a33,a43,a14,a24,a34,a44}; }



// Individual element extractors

static inline int32_t imat2x2_11(imat2x2_t m) { return m.m[0]; }
static inline int32_t imat2x2_21(imat2x2_t m) { return m.m[1]; }
static inline int32_t imat2x2_12(imat2x2_t m) { return m.m[2]; }
static inline int32_t imat2x2_22(imat2x2_t m) { return m.m[3]; }

static inline int32_t imat3x2_11(imat3x2_t m) { return m.m[0]; }
static inline int32_t imat3x2_21(imat3x2_t m) { return m.m[1]; }
static inline int32_t imat3x2_12(imat3x2_t m) { return m.m[2]; }
static inline int32_t imat3x2_22(imat3x2_t m) { return m.m[3]; }
static inline int32_t imat3x2_13(imat3x2_t m) { return m.m[4]; }
static inline int32_t imat3x2_23(imat3x2_t m) { return m.m[5]; }

static inline int32_t imat3x3_11(imat3x3_t m) { return m.m[0]; }
static inline int32_t imat3x3_21(imat3x3_t m) { return m.m[1]; }
static inline int32_t imat3x3_31(imat3x3_t m) { return m.m[2]; }
static inline int32_t imat3x3_12(imat3x3_t m) { return m.m[3]; }
static inline int32_t imat3x3_22(imat3x3_t m) { return m.m[4]; }
static inline int32_t imat3x3_32(imat3x3_t m) { return m.m[5]; }
static inline int32_t imat3x3_13(imat3x3_t m) { return m.m[6]; }
static inline int32_t imat3x3_23(imat3x3_t m) { return m.m[7]; }
static inline int32_t imat3x3_33(imat3x3_t m) { return m.m[8]; }

static inline int32_t imat4x3_11(imat4x3_t m) { return m.m[0]; }
static inline int32_t imat4x3_21(imat4x3_t m) { return m.m[1]; }
static inline int32_t imat4x3_31(imat4x3_t m) { return m.m[2]; }
static inline int32_t imat4x3_12(imat4x3_t m) { return m.m[3]; }
static inline int32_t imat4x3_22(imat4x3_t m) { return m.m[4]; }
static inline int32_t imat4x3_32(imat4x3_t m) { return m.m[5]; }
static inline int32_t imat4x3_13(imat4x3_t m) { return m.m[6]; }
static inline int32_t imat4x3_23(imat4x3_t m) { return m.m[7]; }
static inline int32_t imat4x3_33(imat4x3_t m) { return m.m[8]; }
static inline int32_t imat4x3_14(imat4x3_t m) { return m.m[6]; }
static inline int32_t imat4x3_24(imat4x3_t m) { return m.m[7]; }
static inline int32_t imat4x3_34(imat4x3_t m) { return m.m[8]; }

static inline int32_t imat4x4_11(imat4x4_t m) { return m.m[0]; }
static inline int32_t imat4x4_21(imat4x4_t m) { return m.m[1]; }
static inline int32_t imat4x4_31(imat4x4_t m) { return m.m[2]; }
static inline int32_t imat4x4_41(imat4x4_t m) { return m.m[3]; }
static inline int32_t imat4x4_12(imat4x4_t m) { return m.m[4]; }
static inline int32_t imat4x4_22(imat4x4_t m) { return m.m[5]; }
static inline int32_t imat4x4_32(imat4x4_t m) { return m.m[6]; }
static inline int32_t imat4x4_42(imat4x4_t m) { return m.m[7]; }
static inline int32_t imat4x4_13(imat4x4_t m) { return m.m[8]; }
static inline int32_t imat4x4_23(imat4x4_t m) { return m.m[9]; }
static inline int32_t imat4x4_33(imat4x4_t m) { return m.m[10]; }
static inline int32_t imat4x4_43(imat4x4_t m) { return m.m[11]; }
static inline int32_t imat4x4_14(imat4x4_t m) { return m.m[12]; }
static inline int32_t imat4x4_24(imat4x4_t m) { return m.m[13]; }
static inline int32_t imat4x4_34(imat4x4_t m) { return m.m[14]; }
static inline int32_t imat4x4_44(imat4x4_t m) { return m.m[15]; }




// Column vector constructors

static inline imat2x2_t imat2x2vec2(ivec2_t x,ivec2_t y)
{
	return imat2x2(x.x,y.x,
	              x.y,y.y);
}

static inline imat3x2_t imat3x2vec2(ivec2_t x,ivec2_t y,ivec2_t z)
{
	return imat3x2(x.x,y.x,z.x,
	              x.y,y.y,z.y);
}

static inline imat3x3_t imat3x3vec3(ivec3_t x,ivec3_t y,ivec3_t z)
{
	return imat3x3(x.x,y.x,z.x,
	              x.y,y.y,z.y,
	              x.z,y.z,z.z);
}

static inline imat4x3_t imat4x3vec3(ivec3_t x,ivec3_t y,ivec3_t z,ivec3_t w)
{
	return imat4x3(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z);
}

static inline imat4x4_t imat4x4vec4(ivec4_t x,ivec4_t y,ivec4_t z,ivec4_t w)
{
	return imat4x4(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z,
	              x.w,y.z,z.w,w.w);
}



// Column vector extractors

static inline ivec2_t imat2x2_x(imat2x2_t m) { return ivec2(m.m[0],m.m[1]); }
static inline ivec2_t imat2x2_y(imat2x2_t m) { return ivec2(m.m[2],m.m[3]); }

static inline ivec2_t imat3x2_x(imat3x2_t m) { return ivec2(m.m[0],m.m[1]); }
static inline ivec2_t imat3x2_y(imat3x2_t m) { return ivec2(m.m[2],m.m[3]); }
static inline ivec2_t imat3x2_z(imat3x2_t m) { return ivec2(m.m[4],m.m[5]); }

static inline ivec3_t imat3x3_x(imat3x3_t m) { return ivec3(m.m[0],m.m[1],m.m[2]); }
static inline ivec3_t imat3x3_y(imat3x3_t m) { return ivec3(m.m[3],m.m[4],m.m[5]); }
static inline ivec3_t imat3x3_z(imat3x3_t m) { return ivec3(m.m[6],m.m[7],m.m[8]); }

static inline ivec3_t imat4x3_x(imat4x3_t m) { return ivec3(m.m[0],m.m[1],m.m[2]); }
static inline ivec3_t imat4x3_y(imat4x3_t m) { return ivec3(m.m[3],m.m[4],m.m[5]); }
static inline ivec3_t imat4x3_z(imat4x3_t m) { return ivec3(m.m[6],m.m[7],m.m[8]); }
static inline ivec3_t imat4x3_w(imat4x3_t m) { return ivec3(m.m[9],m.m[10],m.m[11]); }

static inline ivec4_t imat4x4_x(imat4x4_t m) { return ivec4(m.m[0],m.m[1],m.m[2],m.m[3]); }
static inline ivec4_t imat4x4_y(imat4x4_t m) { return ivec4(m.m[4],m.m[5],m.m[6],m.m[7]); }
static inline ivec4_t imat4x4_z(imat4x4_t m) { return ivec4(m.m[8],m.m[9],m.m[10],m.m[11]); }
static inline ivec4_t imat4x4_w(imat4x4_t m) { return ivec4(m.m[12],m.m[13],m.m[14],m.m[15]); }





// Upgrade constructors

static inline imat3x2_t imat3x2affine2x2(imat2x2_t m)
{
	ivec2_t x=imat2x2_x(m),y=imat2x2_y(m);
	return imat3x2( x.x, y.x, 0,
	               x.y, y.y, 0);
}

static inline imat3x3_t imat3x3affine2x2(imat2x2_t m)
{
	ivec2_t x=imat2x2_x(m),y=imat2x2_y(m);
	return imat3x3( x.x, y.x, 0,
	               x.y, y.y, 0,
	                 0,   0, F(1));
}

static inline imat3x3_t imat3x3affine3x2(imat3x2_t m)
{
	ivec2_t x=imat3x2_x(m),y=imat3x2_y(m),z=imat3x2_z(m);
	return imat3x3( x.x, y.x, z.x,
	               x.y, y.y, z.y,
	                 0,   0,   F(1));
}

static inline imat4x3_t imat4x3affine3x3(imat3x3_t m)
{
	ivec3_t x=imat3x3_x(m),y=imat3x3_y(m),z=imat3x3_z(m);
	return imat4x3( x.x, y.x, z.x, 0,
	               x.y, y.y, z.y, 0,
	               x.z, y.z, z.z, 0);
}

static inline imat4x4_t imat4x4affine3x3(imat3x3_t m)
{
	ivec3_t x=imat3x3_x(m),y=imat3x3_y(m),z=imat3x3_z(m);
	return imat4x4( x.x, y.x, z.x, 0,
	               x.y, y.y, z.y, 0,
	               x.z, y.z, z.z, 0,
	                 0,   0,   0, F(1));
}

static inline imat4x4_t imat4x4affine4x3(imat4x3_t m)
{
	ivec3_t x=imat4x3_x(m),y=imat4x3_y(m),z=imat4x3_z(m),w=imat4x3_w(m);
	return imat4x4( x.x, y.x, z.x, w.x,
	               x.y, y.y, z.y, w.y,
	               x.z, y.z, z.z, w.z,
	                 0,   0,   0,   F(1));
}



// Downgrade extractors

static inline imat2x2_t imat3x2_mat2x2(imat3x2_t m) { return imat2x2vec2(imat3x2_x(m),imat3x2_y(m)); }
static inline imat2x2_t imat3x3_mat2x2(imat3x3_t m) { return imat2x2vec2(ivec3_xy(imat3x3_x(m)),ivec3_xy(imat3x3_y(m))); }
static inline imat3x2_t imat3x3_mat3x2(imat3x3_t m) { return imat3x2vec2(ivec3_xy(imat3x3_x(m)),ivec3_xy(imat3x3_y(m)),ivec3_xy(imat3x3_z(m))); }
static inline imat3x3_t imat4x3_mat3x3(imat4x3_t m) { return imat3x3vec3(imat4x3_x(m),imat4x3_y(m),imat4x3_z(m)); }
static inline imat3x3_t imat4x4_mat3x3(imat4x4_t m) { return imat3x3vec3(ivec4_xyz(imat4x4_x(m)),ivec4_xyz(imat4x4_y(m)),ivec4_xyz(imat4x4_z(m))); }
static inline imat4x3_t imat4x4_mat4x3(imat4x4_t m) { return imat4x3vec3(ivec4_xyz(imat4x4_x(m)),ivec4_xyz(imat4x4_y(m)),ivec4_xyz(imat4x4_z(m)),ivec4_xyz(imat4x4_w(m))); }




// Translation constructors

static inline imat3x2_t imat3x2translate(ivec2_t v)
{
	return imat3x2(F(1),0,v.x,
	              0,F(1),v.y);
}

static inline imat4x3_t imat4x3translate(ivec3_t v)
{
	return imat4x3(F(1),0,0,v.x,
	              0,F(1),0,v.y,
	              0,0,F(1),v.z);
}
static inline imat4x4_t imat4x4translate(ivec3_t v) { return imat4x4affine4x3(imat4x3translate(v)); }



// Scaling constructors

static inline imat2x2_t imat2x2scale(int32_t x,int32_t y)
{
	return imat2x2(x,0,
	              0,y);
}
static inline imat3x2_t imat3x2scale(int32_t x,int32_t y) { return imat3x2affine2x2(imat2x2scale(x,y)); }

static inline imat3x3_t imat3x3scale(int32_t x,int32_t y,int32_t z)
{
	return imat3x3(x,0,0,
	              0,y,0,
	              0,0,z);
}
static inline imat4x3_t imat4x3scale(int32_t x,int32_t y,int32_t z) { return imat4x3affine3x3(imat3x3scale(x,y,z)); }
static inline imat4x4_t imat4x4scale(int32_t x,int32_t y,int32_t z) { return imat4x4affine3x3(imat3x3scale(x,y,z)); }



// Rotation constructors

static inline imat2x2_t imat2x2rotate(int a)
{
	return imat2x2(icos(a),-isin(a),
	              isin(a), icos(a));
}
static inline imat3x2_t imat3x2rotate(int a) { return imat3x2affine2x2(imat2x2rotate(a)); }

static inline imat3x3_t imat3x3rotatex(int a)
{
	return imat3x3(F(1),      0,       0,
	              0,icos(a),-isin(a),
	              0,isin(a), icos(a));
}
static inline imat4x3_t imat4x3rotatex(int a) { return imat4x3affine3x3(imat3x3rotatex(a)); }
static inline imat4x4_t imat4x4rotatex(int a) { return imat4x4affine3x3(imat3x3rotatex(a)); }

static inline imat3x3_t imat3x3rotatey(int a)
{
	return imat3x3( icos(a), 0,isin(a),
	                     0, F(1),      0,
	              -isin(a), 0,icos(a));
}
static inline imat4x3_t imat4x3rotatey(int a) { return imat4x3affine3x3(imat3x3rotatey(a)); }
static inline imat4x4_t imat4x4rotatey(int a) { return imat4x4affine3x3(imat3x3rotatey(a)); }

static inline imat3x3_t imat3x3rotatez(int a)
{
	return imat3x3(icos(a),-isin(a),0,
	              isin(a), icos(a),0,
	                    0,       0,F(1));
}
static inline imat4x3_t imat4x3rotatez(int a) { return imat4x3affine3x3(imat3x3rotatez(a)); }
static inline imat4x4_t imat4x4rotatez(int a) { return imat4x4affine3x3(imat3x3rotatez(a)); }

imat3x3_t imat3x3rotate(int angle,ivec3_t axis);
imat4x3_t imat4x3rotate(int angle,ivec3_t axis);
imat4x4_t imat4x4rotate(int angle,ivec3_t axis);



// Perspective constructors

/*static inline imat4x4_t imat4x4perspectiveinternal(int32_t fx,int32_t fy,int32_t znear,int32_t zfar)
{
	return imat4x4(fx, 0,                        0,                        0,
	               0,fy,                        0,                        0,
				   0, 0,idiv((zfar+znear),(znear-zfar)),idiv(imul(2*zfar,znear),(znear-zfar)),
				   0, 0,                       -F(1),                        0);
}*/

/*static inline imat4x4_t imat4x4horizontalperspective(int32_t fovx,int32_t aspect,int32_t znear,int32_t zfar)
{
	int32_t f=F(1)/tan(imul(fovx,M_PI)/180/2);
	return imat4x4perspectiveinternal(f,imul(f,aspect),znear,zfar);
}*/

/*static inline imat4x4_t imat4x4verticalperspective(int32_t fovy,int32_t aspect,int32_t znear,int32_t zfar)
{
	int32_t f=F(1)/tan(imul(fovy,M_PI)/180/2);
	return imat4x4perspectiveinternal(idiv(f,aspect),f,znear,zfar);
}*/

/*static inline imat4x4_t imat4x4minperspective(int32_t fov,int32_t aspect,int32_t znear,int32_t zfar)
{
	if(aspect<F(1)) return imat4x4horizontalperspective(fov,aspect,znear,zfar);
	else return imat4x4verticalperspective(fov,aspect,znear,zfar);
}*/

/*static inline imat4x4_t imat4x4maxperspective(int32_t fov,int32_t aspect,int32_t znear,int32_t zfar)
{
	if(aspect>F(1)) return imat4x4horizontalperspective(fov,aspect,znear,zfar);
	else return imat4x4verticalperspective(fov,aspect,znear,zfar);
}*/

/*static inline imat4x4_t imat4x4diagonalperspective(int32_t fov,int32_t aspect,int32_t znear,int32_t zfar)
{
	int32_t f=F(1)/tan(imul(fov,M_PI)/180/2);
	return imat4x4perspectiveinternal(imul(f,isqrt(F(1)/(imul(aspect,aspect))+F(1))),imul(f,isqrt(imul(aspect,aspect)+F(1))),znear,zfar);
}*/




// Multiplication

imat2x2_t imat2x2mul(imat2x2_t a,imat2x2_t b);
imat3x3_t imat3x3mul(imat3x3_t a,imat3x3_t b);
imat4x4_t imat4x4mul(imat4x4_t a,imat4x4_t b);

imat3x2_t imat3x2affinemul(imat3x2_t a,imat3x2_t b);
imat3x3_t imat3x3affinemul(imat3x3_t a,imat3x3_t b);
imat4x3_t imat4x3affinemul(imat4x3_t a,imat4x3_t b);
imat4x4_t imat4x4affinemul(imat4x4_t a,imat4x4_t b);




// Transpose

static inline imat2x2_t imat2x2transpose(imat2x2_t m)
{
	return imat2x2(m.m[0],m.m[1],
	              m.m[2],m.m[3]);
}

static inline imat3x3_t imat3x3transpose(imat3x3_t m)
{
	return imat3x3(m.m[0],m.m[1],m.m[2],
	              m.m[3],m.m[4],m.m[5],
	              m.m[6],m.m[7],m.m[8]);
}

static inline imat4x4_t imat4x4transpose(imat4x4_t m)
{
	return imat4x4( m.m[0], m.m[1], m.m[2], m.m[3],
	               m.m[4], m.m[5], m.m[6], m.m[7],
	               m.m[8], m.m[9],m.m[10],m.m[11],
	              m.m[12],m.m[13],m.m[14],m.m[15]);
}



// Inverse

imat2x2_t imat2x2inverse(imat2x2_t m);
imat3x3_t imat3x3inverse(imat3x3_t m);
imat4x4_t imat4x4inverse(imat4x4_t m);

imat3x2_t imat3x2affineinverse(imat3x2_t m);
imat4x3_t imat4x3affineinverse(imat4x3_t m);
imat3x3_t imat3x3affineinverse(imat3x3_t m);
imat4x4_t imat4x4affineinverse(imat4x4_t m);



// Vector transformation

ivec2_t imat2x2transform(imat2x2_t m,ivec2_t v);
ivec2_t imat3x2transform(imat3x2_t m,ivec2_t v);
ivec3_t imat3x3transform(imat3x3_t m,ivec3_t v);
ivec3_t imat4x3transform(imat4x3_t m,ivec3_t v);
ivec4_t imat4x4transform(imat4x4_t m,ivec4_t v);

#endif

