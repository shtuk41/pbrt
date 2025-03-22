#pragma once

#include <float.h>
#include <point.h>
#include <vector.h>

namespace pbrt
{
	class medium;

	class ray
	{
		public:
			ray();
			ray(const point3<float> &o, const vector3<float> &d, float tMax, float time, const medium *medium_c);
			point3<float> operator() (float t) const;
			point3<float> o;
			vector3<float> d;
			mutable float tMax;
			float time;
			const medium *medium_in;
	};

	class raydifferential : public ray
	{
	public:
		raydifferential();
		raydifferential(const point3<float> &o, const vector3<float> &d, float tMax, float time, const medium *medium_c);
		raydifferential(const ray &r);
		void ScaleDifferentials(float s);

		bool	hasDifferentials;
		point3<float>	rxOrigin;
		point3<float> ryOrigin;
		vector3<float> rxDirection;
		vector3<float> ryDirection;
	};
}

#include <ray.cpp>