#if defined (_MSC_VER_)
#include "stdafx.h"
#endif


#include <animatedtransform.h>
#include <interval.h>

static float Clamp(float in, float min, float max)
{
    return std::min(std::max(in, min), max);
}

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
            actuallyAnimated(*startTransform != *endTransform)
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

     void animatedtransform::Interpolate(float time, transform *t) const
     {
        //handle boundary conditions for matrix interpolation

        if (!actuallyAnimated || time <= startTime){
            *t = *startTransform;
            return;
        }

        if (time >= endTime)
        {
            *t = *endTransform;
            return;
        }

        float dt = (time - startTime) / (endTime - startTime);

        //interpolate translation at dt 

        vector3f trans = (1 - dt) * T[0] + dt * T[1];

        //interpolate rotation at dt

        quaternion rotate = Slerp(dt, R[0], R[1]);

        //interpolate sclae at dt

        matrix4x4 scale;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                scale.m[i][j] = Lerp(dt, S[0].m[i][j], S[1].m[i][j]);
            }
        }

        //compute interpolated matrix as product of interpolated components
        *t = Translate(trans) * rotate.ToTransform() * transform(scale);
     }

     bounds3f animatedtransform::MotionBounds(const bounds3f &b) const
     {
        if (!actuallyAnimated)
        {
            return (*startTransform)(b);
        }

        if (hasRotation == false)
        {
            return Intersect((*startTransform)(b), (*endTransform)(b));
        }

        //Return motion bounds accounting for animated rotation 108〉

        bounds3f bounds;

        for (int corner = 0; corner < 8; ++corner)
        {
            bounds = Intersect(bounds, BoundPointMotion(b.Corner(corner)));
        }

        return bounds;
     }

     bounds3f animatedtransform::BoundPointMotion(const point3f &p) const
     {
        bounds3f bounds((*startTransform)(p), (*endTransform)(p));
        float cosTheta=Dot(R[0], R[1]);
        float theta=std::acos(Clamp(cosTheta, -1, 1));
        for (int c=0; c <3; ++c) 
        {
            //〈Find any motion derivative zeros for the component c 111〉
            float zeros[4];
            int nZeros = 0;
            IntervalFindZeros(c1[c].Eval(p), c2[c].Eval(p), c3[c].Eval(p), c4[c].Eval(p),
                       c5[c].Eval(p), theta,
                       interval(0., 1.), zeros, &nZeros, 8);


            //〈Expand bounding box for any motion derivative zeros found 111〉
            for (int i=0; i <nZeros; ++i) 
            {
                //point3f pz=(*this)(Lerp(zeros[i], startTime, endTime), p);
                
                point3f pz;
                bounds=Union(bounds, pz);
            }  
        }

        
        return bounds;
     }
}