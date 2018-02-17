#pragma once

#include <cmath>
#include <transform.h>
#include <TemplateInst.h>

namespace pbrt
{

	class quaternion
	{
	public:
		quaternion() : v(0,0,0), w(1) {}
		quaternion(const transform &t);

		quaternion & operator+=(const quaternion &q);
		transform  ToTransform() const;
		void Flip();

		vector3f v;
		float w;
	};

	inline float Dot(const quaternion &q1, const quaternion &q2)
	{
		return Dot(q1.v,q2.v) + q1.w * q2.w;
	}

	inline quaternion operator/(quaternion q1, float t)
	{
		q1.v/=t;
		q1.w/=t;

		return q1;
	}

	inline quaternion Normalize(const quaternion &q)
	{
		return q / std::sqrt(Dot(q,q));
	}

	inline quaternion operator*(float t, quaternion q)
	{
		q.v *= t;
		q.w *= t;

		return q;			
	}

	inline quaternion operator*(quaternion q, float t)
	{
		q.v *= t;
		q.w *= t;

		return q;			
	}

	inline quaternion operator+(quaternion q1, quaternion q2)
	{
		q1.v += q2.v;
		q1.w += q2.w;

		return q1;
	}

	inline quaternion operator-(quaternion q1, quaternion q2)
	{
		q1.v -= q2.v;
		q1.w -= q2.w;

		return q1;
	}

	quaternion Slerp(float t, const quaternion &q1, const quaternion &q2);

}