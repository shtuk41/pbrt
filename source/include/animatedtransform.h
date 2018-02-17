#pragma once

#include <transform.h>
#include <quaternion.h>
#include <TemplateInst.h>

namespace pbrt
{
	class animatedtransform
	{
	public:
		animatedtransform(const transform *startTransform,
                     float startTime, const transform *endTransform, float endTime);
		bool Decompose(const matrix4x4 &m, vector3f *T, quaternion *Rquat, matrix4x4 *S);
	private:
		const transform *startTransform, *endTransform;
	    const float startTime, endTime;
	    const bool actuallyAnimated;
	    vector3f T[2];
	    quaternion R[2];
	    matrix4x4 S[2];
	    bool hasRotation;
	};
}