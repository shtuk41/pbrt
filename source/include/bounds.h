#pragma once

#include <limits>
#include <point.h>

namespace pbrt
{

	template <typename T>
	class bounds2
	{

	public:

	};

	template <typename T>
	class bounds3
	{
	public:
		bounds3();
		bounds3(const point3<T> &p);
		bounds3(const point3<T> &p1, const point3<T> &p2);

		const point3<T> & operator[](int i) const;
		point3<T> & operator[](int i);

		point3<T> Corner(int corner) const;

		point3<T>	pMin;
		point3<T>	pMax;
	};

	template <typename T>
	inline bounds3<T> Union(const bounds3<T> &b, const point3<T> &p)
	{
		return bounds3<T>(point3<T>(std::min(b.pMin.x, p.x),
									std::min(b.pMin.y, p.y),
									std::min(b.pMin.z, p.z)),
							point3<T>(std::max(b.pMax.x, p.x),
									std::max(b.pMax.y, p.y),
									std::max(b.pMax.z, p.z)));

	}

}

#include <bounds.cpp>