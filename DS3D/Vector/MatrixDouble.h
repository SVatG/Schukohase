#ifndef __MATRIX_DOUBLE_H__
#define __MATRIX_DOUBLE_H__

#include "VectorDouble.h"



// Definitions

typedef struct { double m[4]; } dmat2x2_t;
typedef struct { double m[6]; } dmat3x2_t;
typedef struct { double m[9]; } dmat3x3_t;
typedef struct { double m[12]; } dmat4x3_t;
typedef struct { double m[16]; } dmat4x4_t;

#define dmat2x2one dmat2x2(1,0, 0,1)
#define dmat3x2one dmat3x2(1,0,0, 0,1,0)
#define dmat3x3one dmat3x3(1,0,0, 0,1,0, 0,0,1)
#define dmat4x3one dmat4x3(1,0,0,0, 0,1,0,0, 0,0,1,0)
#define dmat4x4one dmat4x4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)



// Individual element constructors

static inline dmat2x2_t dmat2x2(double a11,double a12,
                              double a21,double a22)
{ return (dmat2x2_t){a11,a21,a12,a22}; }

static inline dmat3x2_t dmat3x2(double a11,double a12,double a13,
                              double a21,double a22,double a23)
{ return (dmat3x2_t){a11,a21,a12,a22,a13,a23}; }

static inline dmat3x3_t dmat3x3(double a11,double a12,double a13,
                              double a21,double a22,double a23,
                              double a31,double a32,double a33)
{ return (dmat3x3_t){a11,a21,a31,a12,a22,a32,a13,a23,a33}; }

static inline dmat4x3_t dmat4x3(double a11,double a12,double a13,double a14,
                              double a21,double a22,double a23,double a24,
                              double a31,double a32,double a33,double a34)
{ return (dmat4x3_t){a11,a21,a31,a12,a22,a32,a13,a23,a33,a14,a24,a34}; }

static inline dmat4x4_t dmat4x4(double a11,double a12,double a13,double a14,
                              double a21,double a22,double a23,double a24,
                              double a31,double a32,double a33,double a34,
                              double a41,double a42,double a43,double a44)
{ return (dmat4x4_t){a11,a21,a31,a41,a12,a22,a32,a42,a13,a23,a33,a43,a14,a24,a34,a44}; }



// Individual element extractors

static inline double dmat2x2_11(dmat2x2_t m) { return m.m[0]; }
static inline double dmat2x2_21(dmat2x2_t m) { return m.m[1]; }
static inline double dmat2x2_12(dmat2x2_t m) { return m.m[2]; }
static inline double dmat2x2_22(dmat2x2_t m) { return m.m[3]; }

static inline double dmat3x2_11(dmat3x2_t m) { return m.m[0]; }
static inline double dmat3x2_21(dmat3x2_t m) { return m.m[1]; }
static inline double dmat3x2_12(dmat3x2_t m) { return m.m[2]; }
static inline double dmat3x2_22(dmat3x2_t m) { return m.m[3]; }
static inline double dmat3x2_13(dmat3x2_t m) { return m.m[4]; }
static inline double dmat3x2_23(dmat3x2_t m) { return m.m[5]; }

static inline double dmat3x3_11(dmat3x3_t m) { return m.m[0]; }
static inline double dmat3x3_21(dmat3x3_t m) { return m.m[1]; }
static inline double dmat3x3_31(dmat3x3_t m) { return m.m[2]; }
static inline double dmat3x3_12(dmat3x3_t m) { return m.m[3]; }
static inline double dmat3x3_22(dmat3x3_t m) { return m.m[4]; }
static inline double dmat3x3_32(dmat3x3_t m) { return m.m[5]; }
static inline double dmat3x3_13(dmat3x3_t m) { return m.m[6]; }
static inline double dmat3x3_23(dmat3x3_t m) { return m.m[7]; }
static inline double dmat3x3_33(dmat3x3_t m) { return m.m[8]; }

static inline double dmat4x3_11(dmat4x3_t m) { return m.m[0]; }
static inline double dmat4x3_21(dmat4x3_t m) { return m.m[1]; }
static inline double dmat4x3_31(dmat4x3_t m) { return m.m[2]; }
static inline double dmat4x3_12(dmat4x3_t m) { return m.m[3]; }
static inline double dmat4x3_22(dmat4x3_t m) { return m.m[4]; }
static inline double dmat4x3_32(dmat4x3_t m) { return m.m[5]; }
static inline double dmat4x3_13(dmat4x3_t m) { return m.m[6]; }
static inline double dmat4x3_23(dmat4x3_t m) { return m.m[7]; }
static inline double dmat4x3_33(dmat4x3_t m) { return m.m[8]; }
static inline double dmat4x3_14(dmat4x3_t m) { return m.m[6]; }
static inline double dmat4x3_24(dmat4x3_t m) { return m.m[7]; }
static inline double dmat4x3_34(dmat4x3_t m) { return m.m[8]; }

static inline double dmat4x4_11(dmat4x4_t m) { return m.m[0]; }
static inline double dmat4x4_21(dmat4x4_t m) { return m.m[1]; }
static inline double dmat4x4_31(dmat4x4_t m) { return m.m[2]; }
static inline double dmat4x4_41(dmat4x4_t m) { return m.m[3]; }
static inline double dmat4x4_12(dmat4x4_t m) { return m.m[4]; }
static inline double dmat4x4_22(dmat4x4_t m) { return m.m[5]; }
static inline double dmat4x4_32(dmat4x4_t m) { return m.m[6]; }
static inline double dmat4x4_42(dmat4x4_t m) { return m.m[7]; }
static inline double dmat4x4_13(dmat4x4_t m) { return m.m[8]; }
static inline double dmat4x4_23(dmat4x4_t m) { return m.m[9]; }
static inline double dmat4x4_33(dmat4x4_t m) { return m.m[10]; }
static inline double dmat4x4_43(dmat4x4_t m) { return m.m[11]; }
static inline double dmat4x4_14(dmat4x4_t m) { return m.m[12]; }
static inline double dmat4x4_24(dmat4x4_t m) { return m.m[13]; }
static inline double dmat4x4_34(dmat4x4_t m) { return m.m[14]; }
static inline double dmat4x4_44(dmat4x4_t m) { return m.m[15]; }




// Column vector constructors

static inline dmat2x2_t dmat2x2vec2(dvec2_t x,dvec2_t y)
{
	return dmat2x2(x.x,y.x,
	              x.y,y.y);
}

static inline dmat3x2_t dmat3x2vec2(dvec2_t x,dvec2_t y,dvec2_t z)
{
	return dmat3x2(x.x,y.x,z.x,
	              x.y,y.y,z.y);
}

static inline dmat3x3_t dmat3x3vec3(dvec3_t x,dvec3_t y,dvec3_t z)
{
	return dmat3x3(x.x,y.x,z.x,
	              x.y,y.y,z.y,
	              x.z,y.z,z.z);
}

static inline dmat4x3_t dmat4x3vec3(dvec3_t x,dvec3_t y,dvec3_t z,dvec3_t w)
{
	return dmat4x3(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z);
}

static inline dmat4x4_t dmat4x4vec4(dvec4_t x,dvec4_t y,dvec4_t z,dvec4_t w)
{
	return dmat4x4(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z,
	              x.w,y.z,z.w,w.w);
}



// Column vector extractors

static inline dvec2_t dmat2x2_x(dmat2x2_t m) { return dvec2(m.m[0],m.m[1]); }
static inline dvec2_t dmat2x2_y(dmat2x2_t m) { return dvec2(m.m[2],m.m[3]); }

static inline dvec2_t dmat3x2_x(dmat3x2_t m) { return dvec2(m.m[0],m.m[1]); }
static inline dvec2_t dmat3x2_y(dmat3x2_t m) { return dvec2(m.m[2],m.m[3]); }
static inline dvec2_t dmat3x2_z(dmat3x2_t m) { return dvec2(m.m[4],m.m[5]); }

static inline dvec3_t dmat3x3_x(dmat3x3_t m) { return dvec3(m.m[0],m.m[1],m.m[2]); }
static inline dvec3_t dmat3x3_y(dmat3x3_t m) { return dvec3(m.m[3],m.m[4],m.m[5]); }
static inline dvec3_t dmat3x3_z(dmat3x3_t m) { return dvec3(m.m[6],m.m[7],m.m[8]); }

static inline dvec3_t dmat4x3_x(dmat4x3_t m) { return dvec3(m.m[0],m.m[1],m.m[2]); }
static inline dvec3_t dmat4x3_y(dmat4x3_t m) { return dvec3(m.m[3],m.m[4],m.m[5]); }
static inline dvec3_t dmat4x3_z(dmat4x3_t m) { return dvec3(m.m[6],m.m[7],m.m[8]); }
static inline dvec3_t dmat4x3_w(dmat4x3_t m) { return dvec3(m.m[9],m.m[10],m.m[11]); }

static inline dvec4_t dmat4x4_x(dmat4x4_t m) { return dvec4(m.m[0],m.m[1],m.m[2],m.m[3]); }
static inline dvec4_t dmat4x4_y(dmat4x4_t m) { return dvec4(m.m[4],m.m[5],m.m[6],m.m[7]); }
static inline dvec4_t dmat4x4_z(dmat4x4_t m) { return dvec4(m.m[8],m.m[9],m.m[10],m.m[11]); }
static inline dvec4_t dmat4x4_w(dmat4x4_t m) { return dvec4(m.m[12],m.m[13],m.m[14],m.m[15]); }





// Upgrade constructors

static inline dmat3x2_t dmat3x2affine2x2(dmat2x2_t m)
{
	dvec2_t x=dmat2x2_x(m),y=dmat2x2_y(m);
	return dmat3x2( x.x, y.x, 0,
	               x.y, y.y, 0);
}

static inline dmat3x3_t dmat3x3affine2x2(dmat2x2_t m)
{
	dvec2_t x=dmat2x2_x(m),y=dmat2x2_y(m);
	return dmat3x3( x.x, y.x, 0,
	               x.y, y.y, 0,
	                 0,   0, 1);
}

static inline dmat3x3_t dmat3x3affine3x2(dmat3x2_t m)
{
	dvec2_t x=dmat3x2_x(m),y=dmat3x2_y(m),z=dmat3x2_z(m);
	return dmat3x3( x.x, y.x, z.x,
	               x.y, y.y, z.y,
	                 0,   0,   1);
}

static inline dmat4x3_t dmat4x3affine3x3(dmat3x3_t m)
{
	dvec3_t x=dmat3x3_x(m),y=dmat3x3_y(m),z=dmat3x3_z(m);
	return dmat4x3( x.x, y.x, z.x, 0,
	               x.y, y.y, z.y, 0,
	               x.z, y.z, z.z, 0);
}

static inline dmat4x4_t dmat4x4affine3x3(dmat3x3_t m)
{
	dvec3_t x=dmat3x3_x(m),y=dmat3x3_y(m),z=dmat3x3_z(m);
	return dmat4x4( x.x, y.x, z.x, 0,
	               x.y, y.y, z.y, 0,
	               x.z, y.z, z.z, 0,
	                 0,   0,   0, 1);
}

static inline dmat4x4_t dmat4x4affine4x3(dmat4x3_t m)
{
	dvec3_t x=dmat4x3_x(m),y=dmat4x3_y(m),z=dmat4x3_z(m),w=dmat4x3_w(m);
	return dmat4x4( x.x, y.x, z.x, w.x,
	               x.y, y.y, z.y, w.y,
	               x.z, y.z, z.z, w.z,
	                 0,   0,   0,   1);
}



// Downgrade extractors

static inline dmat2x2_t dmat3x2_mat2x2(dmat3x2_t m) { return dmat2x2vec2(dmat3x2_x(m),dmat3x2_y(m)); }
static inline dmat2x2_t dmat3x3_mat2x2(dmat3x3_t m) { return dmat2x2vec2(dvec3_xy(dmat3x3_x(m)),dvec3_xy(dmat3x3_y(m))); }
static inline dmat3x2_t dmat3x3_mat3x2(dmat3x3_t m) { return dmat3x2vec2(dvec3_xy(dmat3x3_x(m)),dvec3_xy(dmat3x3_y(m)),dvec3_xy(dmat3x3_z(m))); }
static inline dmat3x3_t dmat4x3_mat3x3(dmat4x3_t m) { return dmat3x3vec3(dmat4x3_x(m),dmat4x3_y(m),dmat4x3_z(m)); }
static inline dmat3x3_t dmat4x4_mat3x3(dmat4x4_t m) { return dmat3x3vec3(dvec4_xyz(dmat4x4_x(m)),dvec4_xyz(dmat4x4_y(m)),dvec4_xyz(dmat4x4_z(m))); }
static inline dmat4x3_t dmat4x4_mat4x3(dmat4x4_t m) { return dmat4x3vec3(dvec4_xyz(dmat4x4_x(m)),dvec4_xyz(dmat4x4_y(m)),dvec4_xyz(dmat4x4_z(m)),dvec4_xyz(dmat4x4_w(m))); }




// Translation constructors

static inline dmat3x2_t dmat3x2translate(dvec2_t v)
{
	return dmat3x2(1,0,v.x,
	              0,1,v.y);
}

static inline dmat4x3_t dmat4x3translate(dvec3_t v)
{
	return dmat4x3(1,0,0,v.x,
	              0,1,0,v.y,
	              0,0,1,v.z);
}
static inline dmat4x4_t dmat4x4translate(dvec3_t v) { return dmat4x4affine4x3(dmat4x3translate(v)); }



// Scaling constructors

static inline dmat2x2_t dmat2x2scale(double x,double y)
{
	return dmat2x2(x,0,
	              0,y);
}
static inline dmat3x2_t dmat3x2scale(double x,double y) { return dmat3x2affine2x2(dmat2x2scale(x,y)); }

static inline dmat3x3_t dmat3x3scale(double x,double y,double z)
{
	return dmat3x3(x,0,0,
	              0,y,0,
	              0,0,z);
}
static inline dmat4x3_t dmat4x3scale(double x,double y,double z) { return dmat4x3affine3x3(dmat3x3scale(x,y,z)); }
static inline dmat4x4_t dmat4x4scale(double x,double y,double z) { return dmat4x4affine3x3(dmat3x3scale(x,y,z)); }



// Rotation constructors

static inline dmat2x2_t dmat2x2rotate(double a)
{
	return dmat2x2(cos(a),-sin(a),
	              sin(a), cos(a));
}
static inline dmat3x2_t dmat3x2rotate(double a) { return dmat3x2affine2x2(dmat2x2rotate(a)); }

static inline dmat3x3_t dmat3x3rotatex(double a)
{
	return dmat3x3(1,      0,       0,
	              0,cos(a),-sin(a),
	              0,sin(a), cos(a));
}
static inline dmat4x3_t dmat4x3rotatex(double a) { return dmat4x3affine3x3(dmat3x3rotatex(a)); }
static inline dmat4x4_t dmat4x4rotatex(double a) { return dmat4x4affine3x3(dmat3x3rotatex(a)); }

static inline dmat3x3_t dmat3x3rotatey(double a)
{
	return dmat3x3( cos(a), 0,sin(a),
	                     0, 1,      0,
	              -sin(a), 0,cos(a));
}
static inline dmat4x3_t dmat4x3rotatey(double a) { return dmat4x3affine3x3(dmat3x3rotatey(a)); }
static inline dmat4x4_t dmat4x4rotatey(double a) { return dmat4x4affine3x3(dmat3x3rotatey(a)); }

static inline dmat3x3_t dmat3x3rotatez(double a)
{
	return dmat3x3(cos(a),-sin(a),0,
	              sin(a), cos(a),0,
	                    0,       0,1);
}
static inline dmat4x3_t dmat4x3rotatez(double a) { return dmat4x3affine3x3(dmat3x3rotatez(a)); }
static inline dmat4x4_t dmat4x4rotatez(double a) { return dmat4x4affine3x3(dmat3x3rotatez(a)); }

dmat3x3_t dmat3x3rotate(double angle,dvec3_t axis);
dmat4x3_t dmat4x3rotate(double angle,dvec3_t axis);
dmat4x4_t dmat4x4rotate(double angle,dvec3_t axis);



// Perspective constructors

static inline dmat4x4_t dmat4x4perspectiveinternal(double fx,double fy,double znear,double zfar)
{
	return dmat4x4(fx, 0,                        0,                        0,
	               0,fy,                        0,                        0,
				   0, 0,(zfar+znear)/(znear-zfar),2*zfar*znear/(znear-zfar),
				   0, 0,                       -1,                        0);
}

static inline dmat4x4_t dmat4x4horizontalperspective(double fovx,double aspect,double znear,double zfar)
{
	double f=1/tan(fovx*M_PI/180/2);
	return dmat4x4perspectiveinternal(f,f*aspect,znear,zfar);
}

static inline dmat4x4_t dmat4x4verticalperspective(double fovy,double aspect,double znear,double zfar)
{
	double f=1/tan(fovy*M_PI/180/2);
	return dmat4x4perspectiveinternal(f/aspect,f,znear,zfar);
}

static inline dmat4x4_t dmat4x4minperspective(double fov,double aspect,double znear,double zfar)
{
	if(aspect<1) return dmat4x4horizontalperspective(fov,aspect,znear,zfar);
	else return dmat4x4verticalperspective(fov,aspect,znear,zfar);
}

static inline dmat4x4_t dmat4x4maxperspective(double fov,double aspect,double znear,double zfar)
{
	if(aspect>1) return dmat4x4horizontalperspective(fov,aspect,znear,zfar);
	else return dmat4x4verticalperspective(fov,aspect,znear,zfar);
}

static inline dmat4x4_t dmat4x4diagonalperspective(double fov,double aspect,double znear,double zfar)
{
	double f=1/tan(fov*M_PI/180/2);
	return dmat4x4perspectiveinternal(f*sqrt(1/(aspect*aspect)+1),f*sqrt(aspect*aspect+1),znear,zfar);
}




// Multiplication

dmat2x2_t dmat2x2mul(dmat2x2_t a,dmat2x2_t b);
dmat3x3_t dmat3x3mul(dmat3x3_t a,dmat3x3_t b);
dmat4x4_t dmat4x4mul(dmat4x4_t a,dmat4x4_t b);

dmat3x2_t dmat3x2affinemul(dmat3x2_t a,dmat3x2_t b);
dmat3x3_t dmat3x3affinemul(dmat3x3_t a,dmat3x3_t b);
dmat4x3_t dmat4x3affinemul(dmat4x3_t a,dmat4x3_t b);
dmat4x4_t dmat4x4affinemul(dmat4x4_t a,dmat4x4_t b);




// Transpose

static inline dmat2x2_t dmat2x2transpose(dmat2x2_t m)
{
	return dmat2x2(m.m[0],m.m[1],
	              m.m[2],m.m[3]);
}

static inline dmat3x3_t dmat3x3transpose(dmat3x3_t m)
{
	return dmat3x3(m.m[0],m.m[1],m.m[2],
	              m.m[3],m.m[4],m.m[5],
	              m.m[6],m.m[7],m.m[8]);
}

static inline dmat4x4_t dmat4x4transpose(dmat4x4_t m)
{
	return dmat4x4( m.m[0], m.m[1], m.m[2], m.m[3],
	               m.m[4], m.m[5], m.m[6], m.m[7],
	               m.m[8], m.m[9],m.m[10],m.m[11],
	              m.m[12],m.m[13],m.m[14],m.m[15]);
}



// Inverse

dmat2x2_t dmat2x2inverse(dmat2x2_t m);
dmat3x3_t dmat3x3inverse(dmat3x3_t m);
dmat4x4_t dmat4x4inverse(dmat4x4_t m);

dmat3x2_t dmat3x2affineinverse(dmat3x2_t m);
dmat4x3_t dmat4x3affineinverse(dmat4x3_t m);
dmat3x3_t dmat3x3affineinverse(dmat3x3_t m);
dmat4x4_t dmat4x4affineinverse(dmat4x4_t m);



// Vector transformation

dvec2_t dmat2x2transform(dmat2x2_t m,dvec2_t v);
dvec2_t dmat3x2transform(dmat3x2_t m,dvec2_t v);
dvec3_t dmat3x3transform(dmat3x3_t m,dvec3_t v);
dvec3_t dmat4x3transform(dmat4x3_t m,dvec3_t v);
dvec4_t dmat4x4transform(dmat4x4_t m,dvec4_t v);

#endif

