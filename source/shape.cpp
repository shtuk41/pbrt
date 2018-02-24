#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

#include <shape.h>

namespace pbrt
{

	shape::shape(const transform *ObjectToWorld,
                const transform *WorldToObject, bool reverseOrientation)
         		: ObjectToWorld(ObjectToWorld), WorldToObject(WorldToObject),
         		reverseOrientation(reverseOrientation),
           		transformSwapsHandedness(ObjectToWorld-> SwapsHandedness()) {}

    bounds3f shape::WorldBound() const
    {
    	return (*ObjectToWorld)(ObjectBound());
    }   

    bool shape::IntersectP(const ray &r, bool testAlphaTexture=true) const
    {
    	float tHit = ray.tMax;
    	SurfaceInteraction isect;
    	return Intersect(ray, &tHit, &isect, testAlphaTexture);
    }   		
}
