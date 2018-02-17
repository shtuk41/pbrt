#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

#include <animatedtransform.h>

namespace pbrt
{
	animatedtransform::animatedtransform(const transform *startTransform,
                     					float startTime, 
                     					const transform *endTransform, 
                     					float endTime)
         :  startTransform(startTransform), 
         	endTransform(endTransform),
            startTime(startTime), 
            endTime(endTime),
            actuallyAnimated(*startTransform !=*endTransform) 
    {
         assert(Decompose(startTransform->GetMatrix(), &T[0], &R[0], &S[0]) == true);
         assert(Decompose(endTransform->GetMatrix(), &T[1], &R[1], &S[1]) == true);
         //FlipR[1] if needed to select shortest path 106
         if (Dot(R[0], R[1]) < 0)
         {
         	R[1].Flip();
         }

         hasRotation=Dot(R[0], R[1]) <0.9995f;
     }

     bool animatedtransform::Decompose(const matrix4x4 &m, vector3f *T, quaternion *Rquat, matrix4x4 *S)
     {
     	//Extract translation T from transformation matrix

     		T->x= m.m[0][3];
     		T->y= m.m[1][3];
     		T->z= m.m[2][3];

     	//Compute new transformation matrix M without translation	

     		matrix4x4 M = m;

     		for (int i = 0; i < 3; ++i)
     		{
     			M.m[i][3] = M.m[3][i] = 0.0f;
     		}

     		M.m[3][3]=1.0f;

     	//Extract rotation R from transformation matrix

     		float norm;
     		int count = 0;

     		matrix4x4 R = M;
     		do
     		{
     			//Compute next matrix Rnext in series
     			matrix4x4 Rnext;
     			matrix4x4 Rit;

     			bool success = Inverse(Transpose(R), Rit);

     			if (!success)
     				return false;

     			for (int i = 0; i < 4; ++i)
     			{
     				for (int j = 0; j < 4; ++j)
     				{
     					Rnext.m[i][j] = 0.5f * (R.m[i][j] + Rit.m[i][j]);
     				}
     			}	

     			//Compute norm of difference between R and Rnext
     			norm = 0;
     			for (int i = 0; i <3; ++i)
     			{
     				float n =  std::abs(R.m[i][0] - Rnext.m[i][0]) +
                     std::abs(R.m[i][1] - Rnext.m[i][1]) +
                     std::abs(R.m[i][2] - Rnext.m[i][2]);
     				 norm = std::max(norm, n);
     			}

     			R = Rnext;

     		} while (++count < 100 && norm > 0.0001);

     		*Rquat = quaternion(R);

     		//Compute scale Susing rotation and original matrix

     		matrix4x4 Rinv;
     		bool success = Inverse(R,Rinv);	

     		if (!success)
     				return false;

     		*S = matrix4x4::Mul(Rinv, M);

     		return true;


     }
}