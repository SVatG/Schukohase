#include "DS3Dextra.h"

#include <string.h>



Vector TransformVector3x3(Matrix3x3 m,Vector v)
{
	Vector res=
	{
		(imul(v.x,m.m[0])+imul(v.y,m.m[3])+imul(v.z,m.m[6])),
		(imul(v.x,m.m[1])+imul(v.y,m.m[4])+imul(v.z,m.m[7])),
		(imul(v.x,m.m[2])+imul(v.y,m.m[5])+imul(v.z,m.m[8]))
	};
	return res;
}

Vector TransformVector4x3(Matrix4x3 m,Vector v)
{
	Vector res=
	{
		(imul(v.x,m.m[0])+imul(v.y,m.m[3])+imul(v.z,m.m[6]))+m.m[9],
		(imul(v.x,m.m[1])+imul(v.y,m.m[4])+imul(v.z,m.m[7]))+m.m[10],
		(imul(v.x,m.m[2])+imul(v.y,m.m[5])+imul(v.z,m.m[8]))+m.m[11]
	};
	return res;
}

Vector TransformVector4x4(Matrix4x4 m,Vector v)
{
	Vector res=
	{
		(imul(v.x,m.m[0])+imul(v.y,m.m[4])+imul(v.z,m.m[8]))+m.m[12],
		(imul(v.x,m.m[1])+imul(v.y,m.m[5])+imul(v.z,m.m[9]))+m.m[13],
		(imul(v.x,m.m[2])+imul(v.y,m.m[6])+imul(v.z,m.m[10]))+m.m[14]
	};
	return res;
}

Matrix3x3 MatrixInverse3x3(Matrix3x3 m)
{
	Matrix3x3 res;
	int32_t det=imul3(m.m[0],m.m[4],m.m[8])-imul3(m.m[0],m.m[5],m.m[7])+
	            imul3(m.m[1],m.m[5],m.m[6])-imul3(m.m[1],m.m[3],m.m[8])+
			    imul3(m.m[2],m.m[3],m.m[7])-imul3(m.m[2],m.m[4],m.m[6]);
	// singular if det==0
	det=idiv(DSf32(1),det);

	res.m[0]=imul((imul(m.m[4],m.m[8])-imul(m.m[5],m.m[7])),det);
	res.m[3]=-imul((imul(m.m[3],m.m[8])-imul(m.m[5],m.m[6])),det);
	res.m[6]=imul((imul(m.m[3],m.m[7])-imul(m.m[4],m.m[6])),det);

	res.m[1]=-imul((imul(m.m[1],m.m[8])-imul(m.m[2],m.m[7])),det);
	res.m[4]=imul((imul(m.m[0],m.m[8])-imul(m.m[2],m.m[6])),det);
	res.m[7]=-imul((imul(m.m[0],m.m[7])-imul(m.m[1],m.m[6])),det);

	res.m[2]=imul((imul(m.m[1],m.m[5])-imul(m.m[2],m.m[4])),det);
	res.m[5]=-imul((imul(m.m[0],m.m[5])-imul(m.m[2],m.m[3])),det);
	res.m[8]=imul((imul(m.m[0],m.m[4])-imul(m.m[1],m.m[3])),det);

	return res;
}

Matrix4x3 MatrixInverse4x3(Matrix4x3 m)
{
	Matrix4x3 res;
	int32_t det=imul3(m.m[0],m.m[4],m.m[8])-imul3(m.m[0],m.m[5],m.m[7])+
	            imul3(m.m[1],m.m[5],m.m[6])-imul3(m.m[1],m.m[3],m.m[8])+
			    imul3(m.m[2],m.m[3],m.m[7])-imul3(m.m[2],m.m[4],m.m[6]);
	// singular if det==0
	det=idiv(DSf32(1),det);

	res.m[0]=imul((imul(m.m[4],m.m[8])-imul(m.m[5],m.m[7])),det);
	res.m[3]=-imul((imul(m.m[3],m.m[8])-imul(m.m[5],m.m[6])),det);
	res.m[6]=imul((imul(m.m[3],m.m[7])-imul(m.m[4],m.m[6])),det);

	res.m[1]=-imul((imul(m.m[1],m.m[8])-imul(m.m[2],m.m[7])),det);
	res.m[4]=imul((imul(m.m[0],m.m[8])-imul(m.m[2],m.m[6])),det);
	res.m[7]=-imul((imul(m.m[0],m.m[7])-imul(m.m[1],m.m[6])),det);

	res.m[2]=imul((imul(m.m[1],m.m[5])-imul(m.m[2],m.m[4])),det);
	res.m[5]=-imul((imul(m.m[0],m.m[5])-imul(m.m[2],m.m[3])),det);
	res.m[8]=imul((imul(m.m[0],m.m[4])-imul(m.m[1],m.m[3])),det);

	res.m[9]=-(imul(m.m[9],res.m[0])+imul(m.m[10],res.m[3])+imul(m.m[11],res.m[6]));
	res.m[10]=-(imul(m.m[9],res.m[1])+imul(m.m[10],res.m[4])+imul(m.m[11],res.m[7]));
	res.m[11]=-(imul(m.m[9],res.m[2])+imul(m.m[10],res.m[5])+imul(m.m[11],res.m[8]));

	return res;
}

Matrix4x4 FastMatrixInverse4x4(Matrix4x4 m)
{
	Matrix4x4 res;
	int32_t det=imul3(m.m[0],m.m[5],m.m[10])-imul3(m.m[0],m.m[6],m.m[9])+
	            imul3(m.m[1],m.m[6],m.m[8])-imul3(m.m[1],m.m[4],m.m[10])+
			    imul3(m.m[2],m.m[4],m.m[9])-imul3(m.m[2],m.m[5],m.m[8]);
	// singular if det==0
	det=idiv(DSf32(1),det);

	res.m[0]=imul((imul(m.m[5],m.m[10])-imul(m.m[6],m.m[9])),det);
	res.m[4]=-imul((imul(m.m[4],m.m[10])-imul(m.m[6],m.m[8])),det);
	res.m[8]=imul((imul(m.m[4],m.m[9])-imul(m.m[5],m.m[8])),det);

	res.m[1]=-imul((imul(m.m[1],m.m[10])-imul(m.m[2],m.m[9])),det);
	res.m[5]=imul((imul(m.m[0],m.m[10])-imul(m.m[2],m.m[8])),det);
	res.m[9]=-imul((imul(m.m[0],m.m[9])-imul(m.m[1],m.m[8])),det);

	res.m[2]=imul((imul(m.m[1],m.m[6])-imul(m.m[2],m.m[5])),det);
	res.m[6]=-imul((imul(m.m[0],m.m[6])-imul(m.m[2],m.m[4])),det);
	res.m[10]=imul((imul(m.m[0],m.m[5])-imul(m.m[1],m.m[4])),det);

	res.m[12]=-(imul(m.m[12],res.m[0])+imul(m.m[13],res.m[4])+imul(m.m[14],res.m[8]));
	res.m[13]=-(imul(m.m[12],res.m[1])+imul(m.m[13],res.m[5])+imul(m.m[14],res.m[9]));
	res.m[14]=-(imul(m.m[12],res.m[2])+imul(m.m[13],res.m[6])+imul(m.m[14],res.m[10]));

	res.m[3]=res.m[7]=res.m[11]=0;
	res.m[15]=DSf32(1);

	return res;
}



