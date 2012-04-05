#include "Tunnel.h"

#include "DS3D/DS3D.h"
#include "DS3D/Utils.h"

#define NumSections 16
#define NumParts 7
#define PartSize 1024

typedef struct TunnelSection
{
	int part,hue;
	int32_t x,y;
} TunnelSection;

TunnelSection tunnel[NumSections];
int lastendsection,currhue;
int32_t x,y,sx,sy,sdx,sdy,sa;

uint32_t parts[NumParts][PartSize];

static void MakeParts()
{
	int rsq=isqrt(F(0.5));

	DSStartList(parts[0],PartSize);

	DSListBegin(DS_QUAD_STRIP);
	for(int i=0;i<=16;i++)
	{
		int sin_a=isin(F(i)/16);
		int cos_a=icos(F(i)/16);
		DSListNormal3n10(DSf32ton10(-cos_a),DSf32ton10(-sin_a),0);
		DSListVertex3v16(cos_a,sin_a,F(0));
		DSListVertex3v16(cos_a,sin_a,F(-1));
	}
	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	DSListNormal3f(0,0,1);
	for(int i=0;i<=16;i++)
	{
		int sin_a=isin(F(i)/16);
		int cos_a=icos(F(i)/16);
		DSListVertex3v16(cos_a,sin_a,F(0));
		DSListVertex3v16(imul(cos_a,F(3.9)),imul(sin_a,F(3.9)),F(0));
	}
	DSListEnd();

	if(DSFinishList()>PartSize) for(;;);



	DSStartList(parts[1],PartSize);

	DSListBegin(DS_QUADS);

	DSListNormal3f(-1,0,0);
	DSListVertex3f(1,1,0);
	DSListVertex3f(1,1,-1);
	DSListVertex3f(1,-1,-1);
	DSListVertex3f(1,-1,0);

	DSListNormal3f(0,-1,0);
	DSListVertex3f(1,1,0);
	DSListVertex3f(1,1,-1);
	DSListVertex3f(-1,1,-1);
	DSListVertex3f(-1,1,0);

	DSListNormal3f(1,0,0);
	DSListVertex3f(-1,1,0);
	DSListVertex3f(-1,1,-1);
	DSListVertex3f(-1,-1,-1);
	DSListVertex3f(-1,-1,0);

	DSListNormal3f(0,1,0);
	DSListVertex3f(1,-1,0);
	DSListVertex3f(1,-1,-1);
	DSListVertex3f(-1,-1,-1);
	DSListVertex3f(-1,-1,0);

	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	DSListNormal3f(0,0,1);
	DSListVertex3f(1,1,0);
	DSListVertex3f(3,3,0);
	DSListVertex3f(-1,1,0);
	DSListVertex3f(-3,3,0);
	DSListVertex3f(-1,-1,0);
	DSListVertex3f(-3,-3,0);
	DSListVertex3f(1,-1,0);
	DSListVertex3f(3,-3,0);
	DSListVertex3f(1,1,0);
	DSListVertex3f(3,3,0);
	DSListEnd();

	if(DSFinishList()>PartSize) for(;;);




	const float a=1.2;
	DSStartList(parts[2],PartSize);

	DSListBegin(DS_QUADS);

	DSListNormal3f(-rsq,-rsq,0);
	DSListVertex3f(a,0,0);
	DSListVertex3f(a,0,-1);
	DSListVertex3f(0,a,-1);
	DSListVertex3f(0,a,0);

	DSListNormal3f(rsq,-rsq,0);
	DSListVertex3f(-a,0,0);
	DSListVertex3f(-a,0,-1);
	DSListVertex3f(0,a,-1);
	DSListVertex3f(0,a,0);

	DSListNormal3f(-rsq,rsq,0);
	DSListVertex3f(a,0,0);
	DSListVertex3f(a,0,-1);
	DSListVertex3f(0,-a,-1);
	DSListVertex3f(0,-a,0);

	DSListNormal3f(rsq,rsq,0);
	DSListVertex3f(-a,0,0);
	DSListVertex3f(-a,0,-1);
	DSListVertex3f(0,-a,-1);
	DSListVertex3f(0,-a,0);

	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	DSListNormal3f(0,0,1);
	DSListVertex3f(a,0,0);
	DSListVertex3f(3,0,0);
	DSListVertex3f(0,a,0);
	DSListVertex3f(0,3,0);
	DSListVertex3f(-a,0,0);
	DSListVertex3f(-3,0,0);
	DSListVertex3f(0,-a,0);
	DSListVertex3f(0,-3,0);
	DSListVertex3f(a,0,0);
	DSListVertex3f(3,0,0);
	DSListEnd();

	if(DSFinishList()>PartSize) for(;;);



	const float b=0.7;
	DSStartList(parts[3],PartSize);

	DSListBegin(DS_QUADS);

	DSListNormal3f(0,-1,0);
	DSListVertex3f(3,b,0);
	DSListVertex3f(3,b,-1);
	DSListVertex3f(-3,b,-1);
	DSListVertex3f(-3,b,0);

	DSListNormal3f(0,1,0);
	DSListVertex3f(3,-b,0);
	DSListVertex3f(3,-b,-1);
	DSListVertex3f(-3,-b,-1);
	DSListVertex3f(-3,-b,0);

	DSListNormal3f(0,0,1);
	DSListVertex3f(3,3,0);
	DSListVertex3f(3,b,0);
	DSListVertex3f(-3,b,0);
	DSListVertex3f(-3,3,0);

	DSListVertex3f(3,-3,0);
	DSListVertex3f(3,-b,0);
	DSListVertex3f(-3,-b,0);
	DSListVertex3f(-3,-3,0);

	DSListEnd();

	if(DSFinishList()>PartSize) for(;;);



	DSStartList(parts[4],PartSize);

	DSListBegin(DS_QUADS);

	DSListNormal3f(0,-1,0);
	DSListVertex3f(b,3,0);
	DSListVertex3f(b,3,-1);
	DSListVertex3f(b,-3,-1);
	DSListVertex3f(b,-3,0);

	DSListNormal3f(0,1,0);
	DSListVertex3f(-b,3,0);
	DSListVertex3f(-b,3,-1);
	DSListVertex3f(-b,-3,-1);
	DSListVertex3f(-b,-3,0);

	DSListNormal3f(0,0,1);
	DSListVertex3f(3,3,0);
	DSListVertex3f(b,3,0);
	DSListVertex3f(b,-3,0);
	DSListVertex3f(3,-3,0);

	DSListVertex3f(-3,3,0);
	DSListVertex3f(-b,3,0);
	DSListVertex3f(-b,-3,0);
	DSListVertex3f(-3,-3,0);

	DSListEnd();

	if(DSFinishList()>PartSize) for(;;);



	const int32_t r=F(0.7);
	DSStartList(parts[5],PartSize);

	DSListBegin(DS_QUAD_STRIP);
	for(int i=0;i<=16;i++)
	{
		int sin_a=isin(F(i)/16);
		int cos_a=icos(F(i)/16);
		DSListNormal3n10(DSf32ton10(-cos_a),DSf32ton10(-sin_a),0);
		DSListVertex3v16(imul(cos_a,r),imul(sin_a,r),F(0));
		DSListVertex3v16(imul(cos_a,r),imul(sin_a,r),F(-1));
	}
	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	DSListNormal3f(0,0,1);
	for(int i=0;i<=16;i++)
	{
		int sin_a=isin(F(i)/16);
		int cos_a=icos(F(i)/16);
		DSListVertex3v16(imul(cos_a,r),imul(sin_a,r),F(0));
		DSListVertex3v16(imul(cos_a,F(3.9)),imul(sin_a,F(3.9)),F(0));
	}
	DSListEnd();

	if(DSFinishList()>PartSize) for(;;);




	DSStartList(parts[6],PartSize);

	DSListBegin(DS_QUADS);
	for(int i=0;i<3;i++)
	{
		int sin_a1=isin(F(i)/3+1024);
		int cos_a1=icos(F(i)/3+1024);
		int sin_a2=isin(F(i+1)/3+1024);
		int cos_a2=icos(F(i+1)/3+1024);
		int sin_a3=isin((F(i)+F(0.5))/3+1024);
		int cos_a3=icos((F(i)+F(0.5))/3+1024);
		DSListNormal3n10(DSf32ton10(-cos_a3),DSf32ton10(-sin_a3),0);
		DSListVertex3v16(cos_a1,sin_a1,F(0));
		DSListVertex3v16(cos_a1,sin_a1,F(-1));
		DSListVertex3v16(cos_a2,sin_a2,F(-1));
		DSListVertex3v16(cos_a2,sin_a2,F(0));
	}
	DSListEnd();

	DSListBegin(DS_QUAD_STRIP);
	DSListNormal3f(0,0,1);
	for(int i=0;i<=3;i++)
	{
		int sin_a=isin(F(i)/3+1024);
		int cos_a=icos(F(i)/3+1024);
		DSListVertex3v16(cos_a,sin_a,F(0));
		DSListVertex3v16(imul(cos_a,F(3.9)),imul(sin_a,F(3.9)),F(0));
	}
	DSListEnd();

	if(DSFinishList()>PartSize) for(;;);
}

void InitTunnel()
{
	DISPCNT_A=DISPCNT_MODE_0|DISPCNT_ON|DISPCNT_3D|DISPCNT_BG0_ON;

	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_ANTIALIAS|DS_FOG);
	DSClearParams(0,0,0,31,63);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspectivef(65,256.0/192.0,0.1,16);

	DSSetFogLinearf(0,0,0,31,1,10,0.1,16);

	MakeParts();

	lastendsection=-1;
	currhue=0;
	x=y=0;
	sx=sy=0;
	sa=0;
}

void RunTunnel(int t)
{
	DSMatrixMode(DS_POSITION_AND_VECTOR);
	DSLoadIdentity();

	DSLight3f(0,0x7fff,0.4,-0.7,-1);
//	DSMaterialDiffuseAndAmbient(0x3def,0x3def);
	DSMaterialDiffuseAndAmbient6b(15,15,15,16,16,16);

	DSPolygonAttributes(DS_POLY_MODE_MODULATION|DS_POLY_CULL_NONE|DS_POLY_LIGHT0|DS_POLY_FOG|DS_POLY_ALPHA(31));

	int32_t z=t*529;
	int startsection=z>>12;
	int endsection=startsection+NumSections-1;
	int fraction=z&0xfff;

	int32_t tx1=tunnel[startsection%NumSections].x;
	int32_t ty1=tunnel[startsection%NumSections].y;
	int32_t tx2=tunnel[(startsection+1)%NumSections].x;
	int32_t ty2=tunnel[(startsection+1)%NumSections].y;

	int32_t tx=imul(tx1,F(1)-fraction)+imul(tx2,fraction);
	int32_t ty=imul(ty1,F(1)-fraction)+imul(ty2,fraction);

	int32_t dx=tx-x;
	int32_t dy=ty-y;
	x+=dx>>4;
	y+=dy>>4;

	DSMatrixMode(DS_PROJECTION);
	DSPushMatrix();

	ivec3_t forward=ivec3norm(ivec3(dx,dy,F(1)));
	ivec3_t side=ivec3norm(ivec3cross(ivec3(0,F(1),0),forward));
	ivec3_t up=ivec3cross(forward,side);
	DSMultMatrix3x3(imat3x3vec3(side,up,forward));

	DSMatrixMode(DS_POSITION_AND_VECTOR);
	DSLoadIdentity();

	for(int i=lastendsection+1;i<=endsection;i++)
	{
		sa+=(isin(t*8))/20;
		sdx=imul(icos(sa),F(0.2));
		sdy=imul(isin(sa),F(0.2));
		sx+=sdx;
		sy+=sdy;

		if(Random()%10!=0)
		{
			int part=Random()%NumParts;
			tunnel[i%NumSections].part=part;
			tunnel[i%NumSections].hue=currhue;
			tunnel[i%NumSections].x=sx;
			tunnel[i%NumSections].y=sy;
			currhue=(currhue+30)%360;
		}
		else
		{
			tunnel[i%NumSections].part=NumParts;
			tunnel[i%NumSections].hue=0;
			tunnel[i%NumSections].x=sx;
			tunnel[i%NumSections].y=sy;
		}
	}
	lastendsection=endsection;

	for(int i=0;i<NumSections;i++)
	{
		int section=(startsection+i)%NumSections;

		int hue=tunnel[section].hue;
		DSMaterialDiffuseAndAmbient(MakeHSV(hue,F(1),F(0.4)),MakeHSV(hue,F(1),F(0.7)));

		DSLoadIdentity();
		DSTranslatef32(tunnel[section].x-x,tunnel[section].y-y,-F(i)+fraction);
		//DSScalef(0.5,0.5,0.5);

//		int type=Hash32(i)%;
		if(tunnel[section].part<NumParts)
		DSCallList(parts[tunnel[section].part]);
	}

	DSMatrixMode(DS_PROJECTION);
	DSPopMatrix(0);

	DSSwapBuffers(0);
}


