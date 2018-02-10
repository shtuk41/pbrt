
#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

#include "ray.h"

namespace pbrt
{
	ray::ray() : tMax(FLT_MAX), time(0.0f), medium_in(nullptr) {}
	ray::ray(const point3f &o, const vector3<float> &d, float tMax = FLT_MAX, float time = 0.0f, const medium *medium = nullptr):
		o(o), d(d), tMax(tMax), time(time), medium_in(medium) { }
	point3f ray::operator() (float t) const
	{
		return o + d * t;
	}

	raydifferential::raydifferential()
	{
		hasDifferentials = false;
	}

	raydifferential::raydifferential(const point3f &o, const vector3f &d, float tMax = FLT_MAX, float time = 0.0f, const medium *medium_c = nullptr):
		ray(o,d,tMax,time,medium_c)
		{
			hasDifferentials = false;
		}

	raydifferential::raydifferential(const ray &r) : ray(r)
	{
		hasDifferentials = false;
	}

	void raydifferential::ScaleDifferentials(float s)
	{
		rxOrigin	=	o + (rxOrigin - o) * s;
		ryOrigin	=	o + (ryOrigin - o) * s;
        rxDirection	=	d + (rxDirection - d) * s;
        ryDirection	=	d + (ryDirection - d) * s;
	}
}	