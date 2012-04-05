#ifndef __VECTOR_FIXED_H__
#define __VECTOR_FIXED_H__

#include "../Utils.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif




// Definitions

typedef struct { int32_t x,y; } ivec2_t;
typedef struct { int32_t x,y,z; } ivec3_t;
typedef struct { int32_t x,y,z,w; } ivec4_t;

#define ivec2zero ivec2(0,0)
#define ivec3zero ivec3(0,0,0)
#define ivec4zero ivec4(0,0,0,0)



// Constructors

static inline ivec2_t ivec2(int32_t x,int32_t y) { return (ivec2_t){x,y}; }
static inline ivec3_t ivec3(int32_t x,int32_t y,int32_t z) { return (ivec3_t){x,y,z}; }
static inline ivec4_t ivec4(int32_t x,int32_t y,int32_t z,int32_t w) { return (ivec4_t){x,y,z,w}; }

static inline ivec2_t ivec2cyl(int32_t r,int angle)
{
	return ivec2(imul(r,icos(angle)),imul(r,isin(angle)));
}

static inline ivec4_t ivec4vec3(ivec3_t v) { return ivec4(v.x,v.y,v.z,F(1)); }


// Extractors

static inline ivec2_t ivec3_xy(ivec3_t v) { return ivec2(v.x,v.y); }
static inline ivec2_t ivec3_xz(ivec3_t v) { return ivec2(v.x,v.z); }
static inline ivec2_t ivec3_yz(ivec3_t v) { return ivec2(v.y,v.z); }

static inline ivec3_t ivec4_xyz(ivec4_t v) { return ivec3(v.x,v.y,v.z); }



// Unary operations

static inline ivec2_t ivec2neg(ivec2_t v) { return ivec2(-v.x,-v.y); }
static inline ivec3_t ivec3neg(ivec3_t v) { return ivec3(-v.x,-v.y,-v.z); }
static inline ivec4_t ivec4neg(ivec4_t v) { return ivec4(-v.x,-v.y,-v.z,-v.w); }



// Arithmetic operations

static inline ivec2_t ivec2add(ivec2_t a,ivec2_t b) { return ivec2(a.x+b.x,a.y+b.y); }
static inline ivec3_t ivec3add(ivec3_t a,ivec3_t b) { return ivec3(a.x+b.x,a.y+b.y,a.z+b.z); }
static inline ivec4_t ivec4add(ivec4_t a,ivec4_t b) { return ivec4(a.x+b.x,a.y+b.y,a.z+b.z,a.w+b.w); }

static inline ivec2_t ivec2add3(ivec2_t a,ivec2_t b,ivec2_t c) { return ivec2(a.x+b.x+c.x,a.y+b.y+c.y); }
static inline ivec3_t ivec3add3(ivec3_t a,ivec3_t b,ivec3_t c) { return ivec3(a.x+b.x+c.x,a.y+b.y+c.y,a.z+b.z+c.z); }
static inline ivec4_t ivec4add3(ivec4_t a,ivec4_t b,ivec4_t c) { return ivec4(a.x+b.x+c.x,a.y+b.y+c.y,a.z+b.z+c.z,a.w+b.w+c.w); }

static inline ivec2_t ivec2sub(ivec2_t a,ivec2_t b) { return ivec2(a.x-b.x,a.y-b.y); }
static inline ivec3_t ivec3sub(ivec3_t a,ivec3_t b) { return ivec3(a.x-b.x,a.y-b.y,a.z-b.z); }
static inline ivec4_t ivec4sub(ivec4_t a,ivec4_t b) { return ivec4(a.x-b.x,a.y-b.y,a.z-b.z,a.w-b.w); }

static inline ivec2_t ivec2mul(ivec2_t v,int32_t s) { return ivec2(imul(v.x,s),imul(v.y,s)); }
static inline ivec3_t ivec3mul(ivec3_t v,int32_t s) { return ivec3(imul(v.x,s),imul(v.y,s),imul(v.z,s)); }
static inline ivec4_t ivec4mul(ivec4_t v,int32_t s) { return ivec4(imul(v.x,s),imul(v.y,s),imul(v.z,s),imul(v.w,s)); }

static inline ivec2_t ivec2div(ivec2_t v,int32_t s) { return ivec2(idiv(v.x,s),idiv(v.y,s)); }
static inline ivec3_t ivec3div(ivec3_t v,int32_t s) { return ivec3(idiv(v.x,s),idiv(v.y,s),idiv(v.z,s)); }
static inline ivec4_t ivec4div(ivec4_t v,int32_t s) { return ivec4(idiv(v.x,s),idiv(v.y,s),idiv(v.z,s),idiv(v.w,s)); }



// Norms

static inline int32_t ivec2dot(ivec2_t a,ivec2_t b) { return imul(a.x,b.x)+imul(a.y,b.y); }
static inline int32_t ivec3dot(ivec3_t a,ivec3_t b) { return imul(a.x,b.x)+imul(a.y,b.y)+imul(a.z,b.z); }
static inline int32_t ivec4dot(ivec4_t a,ivec4_t b) { return imul(a.x,b.x)+imul(a.y,b.y)+imul(a.z,b.z)+imul(a.w,b.w); }

static inline int32_t ivec2sq(ivec2_t v) { return ivec2dot(v,v); }
static inline int32_t ivec3sq(ivec3_t v) { return ivec3dot(v,v); }
static inline int32_t ivec4sq(ivec4_t v) { return ivec4dot(v,v); }

static inline int32_t ivec2abs(ivec2_t v) { return isqrt(ivec2sq(v)); }
static inline int32_t ivec3abs(ivec3_t v) { return isqrt(ivec3sq(v)); }
static inline int32_t ivec4abs(ivec4_t v) { return isqrt(ivec4sq(v)); }

static inline int32_t ivec2distsq(ivec2_t a,ivec2_t b) { return ivec2sq(ivec2sub(a,b)); }
static inline int32_t ivec3distsq(ivec3_t a,ivec3_t b) { return ivec3sq(ivec3sub(a,b)); }
static inline int32_t ivec4distsq(ivec4_t a,ivec4_t b) { return ivec4sq(ivec4sub(a,b)); }

static inline int32_t ivec2dist(ivec2_t a,ivec2_t b) { return ivec2abs(ivec2sub(a,b)); }
static inline int32_t ivec3dist(ivec3_t a,ivec3_t b) { return ivec3abs(ivec3sub(a,b)); }
static inline int32_t ivec4dist(ivec4_t a,ivec4_t b) { return ivec4abs(ivec4sub(a,b)); }

#ifdef USE_FIXEDPOINT64
static inline int64_t ivec2dot64(ivec2_t a,ivec2_t b) { return imul64(a.x,b.x)+imul64(a.y,b.y); }
static inline int64_t ivec3dot64(ivec3_t a,ivec3_t b) { return imul64(a.x,b.x)+imul64(a.y,b.y)+imul64(a.z,b.z); }
static inline int64_t ivec4dot64(ivec4_t a,ivec4_t b) { return imul64(a.x,b.x)+imul64(a.y,b.y)+imul64(a.z,b.z)+imul64(a.w,b.w); }

static inline int64_t ivec2sq64(ivec2_t v) { return ivec2dot64(v,v); }
static inline int64_t ivec3sq64(ivec3_t v) { return ivec3dot64(v,v); }
static inline int64_t ivec4sq64(ivec4_t v) { return ivec4dot64(v,v); }

static inline int64_t ivec2abs64(ivec2_t v) { return isqrt64(ivec2sq64(v)); }
static inline int64_t ivec3abs64(ivec3_t v) { return isqrt64(ivec3sq64(v)); }
static inline int64_t ivec4abs64(ivec4_t v) { return isqrt64(ivec4sq64(v)); }

static inline int64_t ivec2distsq64(ivec2_t a,ivec2_t b) { return ivec2sq64(ivec2sub(a,b)); }
static inline int64_t ivec3distsq64(ivec3_t a,ivec3_t b) { return ivec3sq64(ivec3sub(a,b)); }
static inline int64_t ivec4distsq64(ivec4_t a,ivec4_t b) { return ivec4sq64(ivec4sub(a,b)); }

static inline int64_t ivec2dist64(ivec2_t a,ivec2_t b) { return ivec2abs64(ivec2sub(a,b)); }
static inline int64_t ivec3dist64(ivec3_t a,ivec3_t b) { return ivec3abs64(ivec3sub(a,b)); }
static inline int64_t ivec4dist64(ivec4_t a,ivec4_t b) { return ivec4abs64(ivec4sub(a,b)); }
#endif

static inline ivec2_t ivec2norm(ivec2_t v)
{
	int32_t abs=ivec2abs(v);
	if(abs==0) return ivec2zero;
	else return ivec2div(v,abs);
}

static inline ivec3_t ivec3norm(ivec3_t v)
{
	int32_t abs=ivec3abs(v);
	if(abs==0) return ivec3zero;
	else return ivec3div(v,abs);
}

static inline ivec4_t ivec4norm(ivec4_t v)
{
	int32_t abs=ivec4abs(v);
	if(abs==0) return ivec4zero;
	else return ivec4div(v,abs);
}

static inline ivec2_t ivec2setlength(ivec2_t v,int32_t length) { return ivec2mul(ivec2norm(v),length); }
static inline ivec3_t ivec3setlength(ivec3_t v,int32_t length) { return ivec3mul(ivec3norm(v),length); }
static inline ivec4_t ivec4setlength(ivec4_t v,int32_t length) { return ivec4mul(ivec4norm(v),length); }



// Blending

static inline ivec2_t ivec2midpoint(ivec2_t a,ivec2_t b) { return ivec2((a.x+b.x)/2,(a.y+b.y)/2); }
static inline ivec3_t ivec3midpoint(ivec3_t a,ivec3_t b) { return ivec3((a.x+b.x)/2,(a.y+b.y)/2,(a.z+b.z)/2); }
static inline ivec4_t ivec4midpoint(ivec4_t a,ivec4_t b) { return ivec4((a.x+b.x)/2,(a.y+b.y)/2,(a.z+b.z)/2,(a.w+b.w)/2); }

static inline ivec2_t ivec2mix(ivec2_t a,ivec2_t b,int32_t x) { return ivec2add(a,ivec2mul(ivec2sub(b,a),x)); }
static inline ivec3_t ivec3mix(ivec3_t a,ivec3_t b,int32_t x) { return ivec3add(a,ivec3mul(ivec3sub(b,a),x)); }
static inline ivec4_t ivec4mix(ivec4_t a,ivec4_t b,int32_t x) { return ivec4add(a,ivec4mul(ivec4sub(b,a),x)); }



// 2D specifics

static inline ivec2_t ivec2perp(ivec2_t v) { return ivec2(-v.y,v.x); }

static inline int32_t ivec2pdot(ivec2_t a,ivec2_t b) { return ivec2dot(a,ivec2perp(b)); }
#ifdef USE_FIXEDPOINT64
static inline int32_t ivec2pdot64(ivec2_t a,ivec2_t b) { return ivec2dot64(a,ivec2perp(b)); }
#endif

static inline ivec2_t ivec2rot(ivec2_t v,int angle)
{
	return ivec2(
	imul(v.x,icos(angle))-imul(v.y,isin(angle)),
	imul(v.x,isin(angle))+imul(v.y,icos(angle)));
}



// 3D specifics

ivec3_t ivec3cross(ivec3_t a,ivec3_t b);

#endif

