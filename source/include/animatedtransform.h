#pragma once

#include <transform.h>
#include <quaternion.h>
#include <TemplateInst.h>

namespace pbrt
{
	struct derivativeterm
	{
		derivativeterm(float c = 0, float x = 0, float y = 0, float z = 0) :
			kc(c), kx(x), ky(y), kz(z) {}

			float kc, kx, ky, kz;

			float Eval(const point3f &p) const
			{
				return kc + kx * p.x + ky * p.y + kz * p.z;
			}
	};

	class animatedtransform
	{
	public:
		animatedtransform(const transform *startTransform,
                     float startTime, const transform *endTransform, float endTime);
		bool Decompose(const matrix4x4 &m, vector3f *T, quaternion *Rquat, matrix4x4 *S);
		void Interpolate(float time, transform *t) const;

		//Ray operator()(const Ray &r) const;
     	//RayDifferential operator()(const RayDifferential &r) const;
     	//Point3f operator()(Float time, const Point3f &p) const;
     	//Vector3f operator()(Float time, const Vector3f &v) const;	

     	bounds3f MotionBounds(const bounds3f &b) const;
     	bounds3f BoundPointMotion(const point3f &p) const;

	private:
		const transform *startTransform, *endTransform;
	    const float startTime, endTime;
	    const bool actuallyAnimated;
	    vector3f T[2];
	    quaternion R[2];
	    matrix4x4 S[2];
	    bool hasRotation;
	    derivativeterm c1[3];
	    derivativeterm c2[3];
	    derivativeterm c3[3];
	    derivativeterm c4[3];
	    derivativeterm c5[3];
	};
}