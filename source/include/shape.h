#pragma once

#include <TemplateInst.h>
#include <transform.h>

namespace pbrt
{

	class surfaceinteraction;

	class shape
	{
	public:
		 shape(const transform *ObjectToWorld,
	                     const transform *WorldToObject, 
	                     bool reverseOrientation);

		 const transform *ObjectToWorld, *WorldToObject;
		 const bool reverseOrientation;
		 const bool transformSwapsHandedness;
		 virtual bounds3f ObjectBound() const = 0;
		 bounds3f WorldBound() const;
		 virtual bool Intersect(const ray &r, float *tHit, surfaceinteraction *isect, bool testAlphaTexture=true) const;
		 virtual bool IntersectP(const ray &ray, bool testAlphaTexture) const;
		 virtual float Area() const = 0;
	};

}