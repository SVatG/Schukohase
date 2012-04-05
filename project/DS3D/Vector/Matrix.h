#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vector.h"



// Definitions

typedef struct { float m[4]; } mat2x2_t;
typedef struct { float m[6]; } mat3x2_t;
typedef struct { float m[9]; } mat3x3_t;
typedef struct { float m[12]; } mat4x3_t;
typedef struct { float m[16]; } mat4x4_t;

#define mat2x2one mat2x2(1,0, 0,1)
#define mat3x2one mat3x2(1,0,0, 0,1,0)
#define mat3x3one mat3x3(1,0,0, 0,1,0, 0,0,1)
#define mat4x3one mat4x3(1,0,0,0, 0,1,0,0, 0,0,1,0)
#define mat4x4one mat4x4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)



// Individual element constructors

static inline mat2x2_t mat2x2(float a11,float a12,
                              float a21,float a22)
{ return (mat2x2_t){a11,a21,a12,a22}; }

static inline mat3x2_t mat3x2(float a11,float a12,float a13,
                              float a21,float a22,float a23)
{ return (mat3x2_t){a11,a21,a12,a22,a13,a23}; }

static inline mat3x3_t mat3x3(float a11,float a12,float a13,
                              float a21,float a22,float a23,
                              float a31,float a32,float a33)
{ return (mat3x3_t){a11,a21,a31,a12,a22,a32,a13,a23,a33}; }

static inline mat4x3_t mat4x3(float a11,float a12,float a13,float a14,
                              float a21,float a22,float a23,float a24,
                              float a31,float a32,float a33,float a34)
{ return (mat4x3_t){a11,a21,a31,a12,a22,a32,a13,a23,a33,a14,a24,a34}; }

static inline mat4x4_t mat4x4(float a11,float a12,float a13,float a14,
                              float a21,float a22,float a23,float a24,
                              float a31,float a32,float a33,float a34,
                              float a41,float a42,float a43,float a44)
{ return (mat4x4_t){a11,a21,a31,a41,a12,a22,a32,a42,a13,a23,a33,a43,a14,a24,a34,a44}; }



// Individual element extractors

static inline float mat2x2_11(mat2x2_t m) { return m.m[0]; }
static inline float mat2x2_21(mat2x2_t m) { return m.m[1]; }
static inline float mat2x2_12(mat2x2_t m) { return m.m[2]; }
static inline float mat2x2_22(mat2x2_t m) { return m.m[3]; }

static inline float mat3x2_11(mat3x2_t m) { return m.m[0]; }
static inline float mat3x2_21(mat3x2_t m) { return m.m[1]; }
static inline float mat3x2_12(mat3x2_t m) { return m.m[2]; }
static inline float mat3x2_22(mat3x2_t m) { return m.m[3]; }
static inline float mat3x2_13(mat3x2_t m) { return m.m[4]; }
static inline float mat3x2_23(mat3x2_t m) { return m.m[5]; }

static inline float mat3x3_11(mat3x3_t m) { return m.m[0]; }
static inline float mat3x3_21(mat3x3_t m) { return m.m[1]; }
static inline float mat3x3_31(mat3x3_t m) { return m.m[2]; }
static inline float mat3x3_12(mat3x3_t m) { return m.m[3]; }
static inline float mat3x3_22(mat3x3_t m) { return m.m[4]; }
static inline float mat3x3_32(mat3x3_t m) { return m.m[5]; }
static inline float mat3x3_13(mat3x3_t m) { return m.m[6]; }
static inline float mat3x3_23(mat3x3_t m) { return m.m[7]; }
static inline float mat3x3_33(mat3x3_t m) { return m.m[8]; }

static inline float mat4x3_11(mat4x3_t m) { return m.m[0]; }
static inline float mat4x3_21(mat4x3_t m) { return m.m[1]; }
static inline float mat4x3_31(mat4x3_t m) { return m.m[2]; }
static inline float mat4x3_12(mat4x3_t m) { return m.m[3]; }
static inline float mat4x3_22(mat4x3_t m) { return m.m[4]; }
static inline float mat4x3_32(mat4x3_t m) { return m.m[5]; }
static inline float mat4x3_13(mat4x3_t m) { return m.m[6]; }
static inline float mat4x3_23(mat4x3_t m) { return m.m[7]; }
static inline float mat4x3_33(mat4x3_t m) { return m.m[8]; }
static inline float mat4x3_14(mat4x3_t m) { return m.m[6]; }
static inline float mat4x3_24(mat4x3_t m) { return m.m[7]; }
static inline float mat4x3_34(mat4x3_t m) { return m.m[8]; }

static inline float mat4x4_11(mat4x4_t m) { return m.m[0]; }
static inline float mat4x4_21(mat4x4_t m) { return m.m[1]; }
static inline float mat4x4_31(mat4x4_t m) { return m.m[2]; }
static inline float mat4x4_41(mat4x4_t m) { return m.m[3]; }
static inline float mat4x4_12(mat4x4_t m) { return m.m[4]; }
static inline float mat4x4_22(mat4x4_t m) { return m.m[5]; }
static inline float mat4x4_32(mat4x4_t m) { return m.m[6]; }
static inline float mat4x4_42(mat4x4_t m) { return m.m[7]; }
static inline float mat4x4_13(mat4x4_t m) { return m.m[8]; }
static inline float mat4x4_23(mat4x4_t m) { return m.m[9]; }
static inline float mat4x4_33(mat4x4_t m) { return m.m[10]; }
static inline float mat4x4_43(mat4x4_t m) { return m.m[11]; }
static inline float mat4x4_14(mat4x4_t m) { return m.m[12]; }
static inline float mat4x4_24(mat4x4_t m) { return m.m[13]; }
static inline float mat4x4_34(mat4x4_t m) { return m.m[14]; }
static inline float mat4x4_44(mat4x4_t m) { return m.m[15]; }




// Column vector constructors

static inline mat2x2_t mat2x2vec2(vec2_t x,vec2_t y)
{
	return mat2x2(x.x,y.x,
	              x.y,y.y);
}

static inline mat3x2_t mat3x2vec2(vec2_t x,vec2_t y,vec2_t z)
{
	return mat3x2(x.x,y.x,z.x,
	              x.y,y.y,z.y);
}

static inline mat3x3_t mat3x3vec3(vec3_t x,vec3_t y,vec3_t z)
{
	return mat3x3(x.x,y.x,z.x,
	              x.y,y.y,z.y,
	              x.z,y.z,z.z);
}

static inline mat4x3_t mat4x3vec3(vec3_t x,vec3_t y,vec3_t z,vec3_t w)
{
	return mat4x3(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z);
}

static inline mat4x4_t mat4x4vec4(vec4_t x,vec4_t y,vec4_t z,vec4_t w)
{
	return mat4x4(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z,
	              x.w,y.z,z.w,w.w);
}



// Column vector extractors

static inline vec2_t mat2x2_x(mat2x2_t m) { return vec2(m.m[0],m.m[1]); }
static inline vec2_t mat2x2_y(mat2x2_t m) { return vec2(m.m[2],m.m[3]); }

static inline vec2_t mat3x2_x(mat3x2_t m) { return vec2(m.m[0],m.m[1]); }
static inline vec2_t mat3x2_y(mat3x2_t m) { return vec2(m.m[2],m.m[3]); }
static inline vec2_t mat3x2_z(mat3x2_t m) { return vec2(m.m[4],m.m[5]); }

static inline vec3_t mat3x3_x(mat3x3_t m) { return vec3(m.m[0],m.m[1],m.m[2]); }
static inline vec3_t mat3x3_y(mat3x3_t m) { return vec3(m.m[3],m.m[4],m.m[5]); }
static inline vec3_t mat3x3_z(mat3x3_t m) { return vec3(m.m[6],m.m[7],m.m[8]); }

static inline vec3_t mat4x3_x(mat4x3_t m) { return vec3(m.m[0],m.m[1],m.m[2]); }
static inline vec3_t mat4x3_y(mat4x3_t m) { return vec3(m.m[3],m.m[4],m.m[5]); }
static inline vec3_t mat4x3_z(mat4x3_t m) { return vec3(m.m[6],m.m[7],m.m[8]); }
static inline vec3_t mat4x3_w(mat4x3_t m) { return vec3(m.m[9],m.m[10],m.m[11]); }

static inline vec4_t mat4x4_x(mat4x4_t m) { return vec4(m.m[0],m.m[1],m.m[2],m.m[3]); }
static inline vec4_t mat4x4_y(mat4x4_t m) { return vec4(m.m[4],m.m[5],m.m[6],m.m[7]); }
static inline vec4_t mat4x4_z(mat4x4_t m) { return vec4(m.m[8],m.m[9],m.m[10],m.m[11]); }
static inline vec4_t mat4x4_w(mat4x4_t m) { return vec4(m.m[12],m.m[13],m.m[14],m.m[15]); }





// Upgrade constructors

static inline mat3x2_t mat3x2affine2x2(mat2x2_t m)
{
	vec2_t x=mat2x2_x(m),y=mat2x2_y(m);
	return mat3x2( x.x, y.x, 0,
	               x.y, y.y, 0);
}

static inline mat3x3_t mat3x3affine2x2(mat2x2_t m)
{
	vec2_t x=mat2x2_x(m),y=mat2x2_y(m);
	return mat3x3( x.x, y.x, 0,
	               x.y, y.y, 0,
	                 0,   0, 1);
}

static inline mat3x3_t mat3x3affine3x2(mat3x2_t m)
{
	vec2_t x=mat3x2_x(m),y=mat3x2_y(m),z=mat3x2_z(m);
	return mat3x3( x.x, y.x, z.x,
	               x.y, y.y, z.y,
	                 0,   0,   1);
}

static inline mat4x3_t mat4x3affine3x3(mat3x3_t m)
{
	vec3_t x=mat3x3_x(m),y=mat3x3_y(m),z=mat3x3_z(m);
	return mat4x3( x.x, y.x, z.x, 0,
	               x.y, y.y, z.y, 0,
	               x.z, y.z, z.z, 0);
}

static inline mat4x4_t mat4x4affine3x3(mat3x3_t m)
{
	vec3_t x=mat3x3_x(m),y=mat3x3_y(m),z=mat3x3_z(m);
	return mat4x4( x.x, y.x, z.x, 0,
	               x.y, y.y, z.y, 0,
	               x.z, y.z, z.z, 0,
	                 0,   0,   0, 1);
}

static inline mat4x4_t mat4x4affine4x3(mat4x3_t m)
{
	vec3_t x=mat4x3_x(m),y=mat4x3_y(m),z=mat4x3_z(m),w=mat4x3_w(m);
	return mat4x4( x.x, y.x, z.x, w.x,
	               x.y, y.y, z.y, w.y,
	               x.z, y.z, z.z, w.z,
	                 0,   0,   0,   1);
}



// Downgrade extractors

static inline mat2x2_t mat3x2_mat2x2(mat3x2_t m) { return mat2x2vec2(mat3x2_x(m),mat3x2_y(m)); }
static inline mat2x2_t mat3x3_mat2x2(mat3x3_t m) { return mat2x2vec2(vec3_xy(mat3x3_x(m)),vec3_xy(mat3x3_y(m))); }
static inline mat3x2_t mat3x3_mat3x2(mat3x3_t m) { return mat3x2vec2(vec3_xy(mat3x3_x(m)),vec3_xy(mat3x3_y(m)),vec3_xy(mat3x3_z(m))); }
static inline mat3x3_t mat4x3_mat3x3(mat4x3_t m) { return mat3x3vec3(mat4x3_x(m),mat4x3_y(m),mat4x3_z(m)); }
static inline mat3x3_t mat4x4_mat3x3(mat4x4_t m) { return mat3x3vec3(vec4_xyz(mat4x4_x(m)),vec4_xyz(mat4x4_y(m)),vec4_xyz(mat4x4_z(m))); }
static inline mat4x3_t mat4x4_mat4x3(mat4x4_t m) { return mat4x3vec3(vec4_xyz(mat4x4_x(m)),vec4_xyz(mat4x4_y(m)),vec4_xyz(mat4x4_z(m)),vec4_xyz(mat4x4_w(m))); }




// Translation constructors

static inline mat3x2_t mat3x2translate(vec2_t v)
{
	return mat3x2(1,0,v.x,
	              0,1,v.y);
}

static inline mat4x3_t mat4x3translate(vec3_t v)
{
	return mat4x3(1,0,0,v.x,
	              0,1,0,v.y,
	              0,0,1,v.z);
}
static inline mat4x4_t mat4x4translate(vec3_t v) { return mat4x4affine4x3(mat4x3translate(v)); }



// Scaling constructors

static inline mat2x2_t mat2x2scale(float x,float y)
{
	return mat2x2(x,0,
	              0,y);
}
static inline mat3x2_t mat3x2scale(float x,float y) { return mat3x2affine2x2(mat2x2scale(x,y)); }

static inline mat3x3_t mat3x3scale(float x,float y,float z)
{
	return mat3x3(x,0,0,
	              0,y,0,
	              0,0,z);
}
static inline mat4x3_t mat4x3scale(float x,float y,float z) { return mat4x3affine3x3(mat3x3scale(x,y,z)); }
static inline mat4x4_t mat4x4scale(float x,float y,float z) { return mat4x4affine3x3(mat3x3scale(x,y,z)); }



// Rotation constructors

static inline mat2x2_t mat2x2rotate(float a)
{
	return mat2x2(cosf(a),-sinf(a),
	              sinf(a), cosf(a));
}
static inline mat3x2_t mat3x2rotate(float a) { return mat3x2affine2x2(mat2x2rotate(a)); }

static inline mat3x3_t mat3x3rotatex(float a)
{
	return mat3x3(1,      0,       0,
	              0,cosf(a),-sinf(a),
	              0,sinf(a), cosf(a));
}
static inline mat4x3_t mat4x3rotatex(float a) { return mat4x3affine3x3(mat3x3rotatex(a)); }
static inline mat4x4_t mat4x4rotatex(float a) { return mat4x4affine3x3(mat3x3rotatex(a)); }

static inline mat3x3_t mat3x3rotatey(float a)
{
	return mat3x3( cosf(a), 0,sinf(a),
	                     0, 1,      0,
	              -sinf(a), 0,cosf(a));
}
static inline mat4x3_t mat4x3rotatey(float a) { return mat4x3affine3x3(mat3x3rotatey(a)); }
static inline mat4x4_t mat4x4rotatey(float a) { return mat4x4affine3x3(mat3x3rotatey(a)); }

static inline mat3x3_t mat3x3rotatez(float a)
{
	return mat3x3(cosf(a),-sinf(a),0,
	              sinf(a), cosf(a),0,
	                    0,       0,1);
}
static inline mat4x3_t mat4x3rotatez(float a) { return mat4x3affine3x3(mat3x3rotatez(a)); }
static inline mat4x4_t mat4x4rotatez(float a) { return mat4x4affine3x3(mat3x3rotatez(a)); }

mat3x3_t mat3x3rotate(float angle,vec3_t axis);
mat4x3_t mat4x3rotate(float angle,vec3_t axis);
mat4x4_t mat4x4rotate(float angle,vec3_t axis);



// Perspective constructors

static inline mat4x4_t mat4x4perspectiveinternal(float fx,float fy,float znear,float zfar)
{
	return mat4x4(fx, 0,                        0,                        0,
	               0,fy,                        0,                        0,
				   0, 0,(zfar+znear)/(znear-zfar),2*zfar*znear/(znear-zfar),
				   0, 0,                       -1,                        0);
}

static inline mat4x4_t mat4x4horizontalperspective(float fovx,float aspect,float znear,float zfar)
{
	float f=1/tan(fovx*M_PI/180/2);
	return mat4x4perspectiveinternal(f,f*aspect,znear,zfar);
}

static inline mat4x4_t mat4x4verticalperspective(float fovy,float aspect,float znear,float zfar)
{
	float f=1/tan(fovy*M_PI/180/2);
	return mat4x4perspectiveinternal(f/aspect,f,znear,zfar);
}

static inline mat4x4_t mat4x4minperspective(float fov,float aspect,float znear,float zfar)
{
	if(aspect<1) return mat4x4horizontalperspective(fov,aspect,znear,zfar);
	else return mat4x4verticalperspective(fov,aspect,znear,zfar);
}

static inline mat4x4_t mat4x4maxperspective(float fov,float aspect,float znear,float zfar)
{
	if(aspect>1) return mat4x4horizontalperspective(fov,aspect,znear,zfar);
	else return mat4x4verticalperspective(fov,aspect,znear,zfar);
}

static inline mat4x4_t mat4x4diagonalperspective(float fov,float aspect,float znear,float zfar)
{
	float f=1/tan(fov*M_PI/180/2);
	return mat4x4perspectiveinternal(f*sqrtf(1/(aspect*aspect)+1),f*sqrtf(aspect*aspect+1),znear,zfar);
}




// Multiplication

mat2x2_t mat2x2mul(mat2x2_t a,mat2x2_t b);
mat3x3_t mat3x3mul(mat3x3_t a,mat3x3_t b);
mat4x4_t mat4x4mul(mat4x4_t a,mat4x4_t b);

mat3x2_t mat3x2affinemul(mat3x2_t a,mat3x2_t b);
mat3x3_t mat3x3affinemul(mat3x3_t a,mat3x3_t b);
mat4x3_t mat4x3affinemul(mat4x3_t a,mat4x3_t b);
mat4x4_t mat4x4affinemul(mat4x4_t a,mat4x4_t b);




// Transpose

static inline mat2x2_t mat2x2transpose(mat2x2_t m)
{
	return mat2x2(m.m[0],m.m[1],
	              m.m[2],m.m[3]);
}

static inline mat3x3_t mat3x3transpose(mat3x3_t m)
{
	return mat3x3(m.m[0],m.m[1],m.m[2],
	              m.m[3],m.m[4],m.m[5],
	              m.m[6],m.m[7],m.m[8]);
}

static inline mat4x4_t mat4x4transpose(mat4x4_t m)
{
	return mat4x4( m.m[0], m.m[1], m.m[2], m.m[3],
	               m.m[4], m.m[5], m.m[6], m.m[7],
	               m.m[8], m.m[9],m.m[10],m.m[11],
	              m.m[12],m.m[13],m.m[14],m.m[15]);
}



// Inverse

mat2x2_t mat2x2inverse(mat2x2_t m);
mat3x3_t mat3x3inverse(mat3x3_t m);
mat4x4_t mat4x4inverse(mat4x4_t m);

mat3x2_t mat3x2affineinverse(mat3x2_t m);
mat4x3_t mat4x3affineinverse(mat4x3_t m);
mat3x3_t mat3x3affineinverse(mat3x3_t m);
mat4x4_t mat4x4affineinverse(mat4x4_t m);



// Vector transformation

vec2_t mat2x2transform(mat2x2_t m,vec2_t v);
vec2_t mat3x2transform(mat3x2_t m,vec2_t v);
vec3_t mat3x3transform(mat3x3_t m,vec3_t v);
vec3_t mat4x3transform(mat4x3_t m,vec3_t v);
vec4_t mat4x4transform(mat4x4_t m,vec4_t v);

#endif

