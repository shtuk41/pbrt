#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

#include <cstring>
#include "transform.h"

namespace pbrt
{
	matrix4x4::matrix4x4()
	{
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;	
	}

	matrix4x4::matrix4x4(float mat[4][4])
	{
		for(int i = 0; i<10; i++)
		{
		    memcpy(&m[i], &mat[i], sizeof(mat[0]));
		}
	}

	matrix4x4::matrix4x4(float t00, float t01, float t02, float t03,
					float t10, float t11, float t12, float t13,
					float t20, float t21, float t22, float t23,
					float t30, float t31, float t32, float t33)
	{
		m[0][0] = t00;
		m[0][1] = t01;
		m[0][2] = t02;
		m[0][3] = t03;
		m[1][0] = t10;
		m[1][1] = t11;
		m[1][2] = t12;
		m[1][3] = t13;
		m[2][0] = t20;
		m[2][1] = t21;
		m[2][2] = t22;
		m[2][3] = t23;
		m[3][0] = t30;
		m[3][1] = t31;
		m[3][2] = t32;
		m[3][3] = t33;
	}

	matrix4x4 matrix4x4::Mul(const matrix4x4 &m1, const matrix4x4 &m2)
	{
		matrix4x4 r;

		for (int i=0; i < 4; ++i)
		{
              for (int j=0; j < 4; ++j)
              {
                     r.m[i][j]=	m1.m[i][0] * m2.m[0][j] +
			                    m1.m[i][1] * m2.m[1][j] +
			                    m1.m[i][2] * m2.m[2][j] +
			                    m1.m[i][3] * m2.m[3][j];
              }
        }
        
        return r;
	}

	bool Inverse(const matrix4x4 &mat, matrix4x4 &invOut)
	{
		//https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
		float inv[16], det, invIn[16];

	    invIn[0] = mat.m[0][0];
	    invIn[1] = mat.m[0][1];
	    invIn[2] = mat.m[0][2];
	    invIn[3] = mat.m[0][3];
	    invIn[4] = mat.m[1][0];
	    invIn[5] = mat.m[1][1];
	    invIn[6] = mat.m[1][2];
	    invIn[7] = mat.m[1][3];
	    invIn[8] = mat.m[2][0];
	    invIn[9] = mat.m[2][1];
	    invIn[10] = mat.m[2][2];
	    invIn[11] = mat.m[2][3];
	    invIn[12] = mat.m[3][0];
	    invIn[13] = mat.m[3][1];
	    invIn[14] = mat.m[3][2];
	    invIn[15] = mat.m[3][3];



	    inv[0] = invIn[5]  * invIn[10] * invIn[15] - 
	             invIn[5]  * invIn[11] * invIn[14] - 
	             invIn[9]  * invIn[6]  * invIn[15] + 
	             invIn[9]  * invIn[7]  * invIn[14] +
	             invIn[13] * invIn[6]  * invIn[11] - 
	             invIn[13] * invIn[7]  * invIn[10];

	    inv[4] = -invIn[4]  * invIn[10] * invIn[15] + 
	              invIn[4]  * invIn[11] * invIn[14] + 
	              invIn[8]  * invIn[6]  * invIn[15] - 
	              invIn[8]  * invIn[7]  * invIn[14] - 
	              invIn[12] * invIn[6]  * invIn[11] + 
	              invIn[12] * invIn[7]  * invIn[10];

	    inv[8] = invIn[4]  * invIn[9] * invIn[15] - 
	             invIn[4]  * invIn[11] * invIn[13] - 
	             invIn[8]  * invIn[5] * invIn[15] + 
	             invIn[8]  * invIn[7] * invIn[13] + 
	             invIn[12] * invIn[5] * invIn[11] - 
	             invIn[12] * invIn[7] * invIn[9];

	    inv[12] = -invIn[4]  * invIn[9] * invIn[14] + 
	               invIn[4]  * invIn[10] * invIn[13] +
	               invIn[8]  * invIn[5] * invIn[14] - 
	               invIn[8]  * invIn[6] * invIn[13] - 
	               invIn[12] * invIn[5] * invIn[10] + 
	               invIn[12] * invIn[6] * invIn[9];

	    inv[1] = -invIn[1]  * invIn[10] * invIn[15] + 
	              invIn[1]  * invIn[11] * invIn[14] + 
	              invIn[9]  * invIn[2] * invIn[15] - 
	              invIn[9]  * invIn[3] * invIn[14] - 
	              invIn[13] * invIn[2] * invIn[11] + 
	              invIn[13] * invIn[3] * invIn[10];

	    inv[5] = invIn[0]  * invIn[10] * invIn[15] - 
	             invIn[0]  * invIn[11] * invIn[14] - 
	             invIn[8]  * invIn[2] * invIn[15] + 
	             invIn[8]  * invIn[3] * invIn[14] + 
	             invIn[12] * invIn[2] * invIn[11] - 
	             invIn[12] * invIn[3] * invIn[10];

	    inv[9] = -invIn[0]  * invIn[9] * invIn[15] + 
	              invIn[0]  * invIn[11] * invIn[13] + 
	              invIn[8]  * invIn[1] * invIn[15] - 
	              invIn[8]  * invIn[3] * invIn[13] - 
	              invIn[12] * invIn[1] * invIn[11] + 
	              invIn[12] * invIn[3] * invIn[9];

	    inv[13] = invIn[0]  * invIn[9] * invIn[14] - 
	              invIn[0]  * invIn[10] * invIn[13] - 
	              invIn[8]  * invIn[1] * invIn[14] + 
	              invIn[8]  * invIn[2] * invIn[13] + 
	              invIn[12] * invIn[1] * invIn[10] - 
	              invIn[12] * invIn[2] * invIn[9];

	    inv[2] = invIn[1]  * invIn[6] * invIn[15] - 
	             invIn[1]  * invIn[7] * invIn[14] - 
	             invIn[5]  * invIn[2] * invIn[15] + 
	             invIn[5]  * invIn[3] * invIn[14] + 
	             invIn[13] * invIn[2] * invIn[7] - 
	             invIn[13] * invIn[3] * invIn[6];

	    inv[6] = -invIn[0]  * invIn[6] * invIn[15] + 
	              invIn[0]  * invIn[7] * invIn[14] + 
	              invIn[4]  * invIn[2] * invIn[15] - 
	              invIn[4]  * invIn[3] * invIn[14] - 
	              invIn[12] * invIn[2] * invIn[7] + 
	              invIn[12] * invIn[3] * invIn[6];

	    inv[10] = invIn[0]  * invIn[5] * invIn[15] - 
	              invIn[0]  * invIn[7] * invIn[13] - 
	              invIn[4]  * invIn[1] * invIn[15] + 
	              invIn[4]  * invIn[3] * invIn[13] + 
	              invIn[12] * invIn[1] * invIn[7] - 
	              invIn[12] * invIn[3] * invIn[5];

	    inv[14] = -invIn[0]  * invIn[5] * invIn[14] + 
	               invIn[0]  * invIn[6] * invIn[13] + 
	               invIn[4]  * invIn[1] * invIn[14] - 
	               invIn[4]  * invIn[2] * invIn[13] - 
	               invIn[12] * invIn[1] * invIn[6] + 
	               invIn[12] * invIn[2] * invIn[5];

	    inv[3] = -invIn[1] * invIn[6] * invIn[11] + 
	              invIn[1] * invIn[7] * invIn[10] + 
	              invIn[5] * invIn[2] * invIn[11] - 
	              invIn[5] * invIn[3] * invIn[10] - 
	              invIn[9] * invIn[2] * invIn[7] + 
	              invIn[9] * invIn[3] * invIn[6];

	    inv[7] = invIn[0] * invIn[6] * invIn[11] - 
	             invIn[0] * invIn[7] * invIn[10] - 
	             invIn[4] * invIn[2] * invIn[11] + 
	             invIn[4] * invIn[3] * invIn[10] + 
	             invIn[8] * invIn[2] * invIn[7] - 
	             invIn[8] * invIn[3] * invIn[6];

	    inv[11] = -invIn[0] * invIn[5] * invIn[11] + 
	               invIn[0] * invIn[7] * invIn[9] + 
	               invIn[4] * invIn[1] * invIn[11] - 
	               invIn[4] * invIn[3] * invIn[9] - 
	               invIn[8] * invIn[1] * invIn[7] + 
	               invIn[8] * invIn[3] * invIn[5];

	    inv[15] = invIn[0] * invIn[5] * invIn[10] - 
	              invIn[0] * invIn[6] * invIn[9] - 
	              invIn[4] * invIn[1] * invIn[10] + 
	              invIn[4] * invIn[2] * invIn[9] + 
	              invIn[8] * invIn[1] * invIn[6] - 
	              invIn[8] * invIn[2] * invIn[5];

	    det = invIn[0] * inv[0] + invIn[1] * inv[4] + invIn[2] * inv[8] + invIn[3] * inv[12];

	    if (det == 0)
	        return false;

	    det = 1.0f / det;

        invOut.m[0][0] = inv[0] * det;
        invOut.m[0][1] = inv[1] * det;
        invOut.m[0][2] = inv[2] * det;
        invOut.m[0][3] = inv[3] * det;
        invOut.m[1][0] = inv[4] * det;
        invOut.m[1][1] = inv[5] * det;
        invOut.m[1][2] = inv[6] * det;
        invOut.m[1][3] = inv[7] * det;
        invOut.m[2][0] = inv[8] * det;
        invOut.m[2][1] = inv[9] * det;
        invOut.m[2][2] = inv[10] * det;
        invOut.m[2][3] = inv[11] * det;
        invOut.m[3][0] = inv[12] * det;
        invOut.m[3][1] = inv[13] * det;
        invOut.m[3][2] = inv[14] * det;
        invOut.m[3][3] = inv[15] * det;

	    return true;
	}
}