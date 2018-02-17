#if defined (_MSC_VER_)
#include "stdafx.h"
#endif


#include <transform.h>
#include <quaternion.h>

namespace pbrt
{
	float Clamp(float in, float min, float max)
	{
		return std::min(std::max(in, min), max);
	}

	quaternion::quaternion(const transform &t)
	{
		matrix4x4 m = t.GetMatrix();

		float trace = m.m[0][0] + m.m[1][1] + m.m[2][2]; // I removed + 1.0f; see discussion with Ethan
		
		if( trace > 0 ) {// I changed M_EPSILON to 0
		   float s = 0.5f / std::sqrt(trace + 1.0f);
		   w = 0.25f / s;
		   v.x = ( m.m[2][1] - m.m[1][2] ) * s;
		   v.y = ( m.m[0][2] - m.m[2][0] ) * s;
		   v.z = ( m.m[1][0] - m.m[0][1] ) * s;
		 } 
		 else 
		 {
		   if ( m.m[0][0] > m.m[1][1] && m.m[0][0] > m.m[2][2] ) 
		   {
		     float s = 2.0f * sqrtf( 1.0f + m.m[0][0] - m.m[1][1] - m.m[2][2]);
		     w = (m.m[2][1] - m.m[1][2] ) / s;
		     v.x = 0.25f * s;
		     v.y = (m.m[0][1] + m.m[1][0] ) / s;
		     v.z = (m.m[0][2] + m.m[2][0] ) / s;
		   } 
		   else if (m.m[1][1] > m.m[2][2]) 
		   {
		     float s = 2.0f * sqrtf( 1.0f + m.m[1][1] - m.m[0][0] - m.m[2][2]);
		     w = (m.m[0][2] - m.m[2][0] ) / s;
		     v.x = (m.m[0][1] + m.m[1][0] ) / s;
		     v.y = 0.25f * s;
		     v.z = (m.m[1][2] + m.m[2][1] ) / s;
		   } 
		   else 
		   {
		     float s = 2.0f * sqrtf( 1.0f + m.m[2][2] - m.m[0][0] - m.m[1][1] );
		     w = (m.m[1][0] - m.m[0][1] ) / s;
		     v.x = (m.m[0][2] + m.m[2][0] ) / s;
		     v.y = (m.m[1][2] + m.m[2][1] ) / s;
		     v.z = 0.25f * s;
		   }
    	}
	}

	//http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
	quaternion & quaternion::operator += (const quaternion &q)
	{
		v += q.v;
		w += q.w;

		return *this;
	}

	transform	quaternion::ToTransform() const
	{
		float m[4][4];

		m[0][0] = 1.0f - 2.0f * (v.y * v.y + v.z * v.z);
		m[0][1] = 2.0f * (v.x * v.y + v.z * w);
		m[0][2] = 2.0f * (v.x * v.z - v.y * w);
		m[0][3] = 0;
		m[1][0] = 2.0f * (v.x * v.y - v.z * w);
		m[1][1] = 1.0f - 2.0f * (v.x * v.x + v.z * v.z);
		m[1][2] = 2 * (v.y * v.z + v.x * w);
		m[1][3] = 0;
		m[2][0] = 2.0f * (v.z * v.z + v.y * w);
		m[2][1] = 2.0f * (v.y * v.z - v.x * w);
		m[2][2] = 1.0f - 2.0f * (v.x * v.x + v.y * v.y);
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;

		return transform(m);
	}

	void quaternion::Flip()
	{
		//this might be a bug, not understanding quaternions that well
		v.x = -v.x;
		v.y = -v.y;
		v.z = -v.z;		
	}

	quaternion Slerp(float t, const quaternion &q1, const quaternion &q2)
	{
		float cosTheta=Dot(q1, q2);
         if (cosTheta> 0.9995f)
         {
            return Normalize((1 - t) * q1 + t * q2);
         }
         else 
         {
            float theta=std::acos(Clamp(cosTheta, -1, 1));
            float thetap=theta * t;
            quaternion qperp=Normalize(q2 - q1 * cosTheta);
            return q1 * std::cos(thetap) + qperp * std::sin(thetap);
         }
	}


}