#pragma once

#include <float.h>
#include "TemplateInst.h"

namespace pbrt
{
	class medium;

	class ray
	{
		public:
			ray();
			ray(const point3f &o, const vector3f &d, float tMax, float time, const medium *medium_c);
			point3f operator() (float t) const;
			point3f o;
			vector3f d;
			mutable float tMax;
			float time;
			const medium *medium_in;
	};

	class raydifferential : public ray
	{
	public:
		raydifferential();
		raydifferential(const point3f &o, const vector3f &d, float tMax, float time, const medium *medium_c);
		raydifferential(const ray &r);
		void ScaleDifferentials(float s);

		bool	hasDifferentials;
		point3f	rxOrigin;
		point3f ryOrigin;
		vector3f rxDirection;
		vector3f ryDirection;
	};
}