#pragma once

#include <TemplateInst.h>

namespace pbrt
{

	class shape
	{
	public:
		 Shape::Shape(const Transform *ObjectToWorld,
	                     const Transform *WorldToObject, bool reverseOrientation);

		 const transform *ObjectToWorld, *WorldToObject;
		 const bool reverseOrientation;
		 const bool transformSwapsHandedness;
		 virtual bounds3f ObjectBound() const = 0;
		 bounds3f WorldBound() const;
		 virtual bool Intersect(const ray &r, float *tHit, SurfaceInteraction *isect, bool testAlphaTexture=true) const;
		 virtual bool IntersectP(const ray &r, bool testAlphaTexture=true) const;
		 virtual float Area() const = 0;
	};

}