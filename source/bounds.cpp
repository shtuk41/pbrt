#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

namespace pbrt
{
	template <typename T>
	bounds3<T>::bounds3()
	{
		T minNum = std::numeric_limits<T>::lowest();
		T maxNum = std::numeric_limits<T>::max();
		pMin = point3<T>(maxNum,maxNum,maxNum);
		pMax = point3<T>(minNum,minNum,minNum);
	}

	template <typename T>
	bounds3<T>::bounds3(const pbrt::point3<T> &p):pMin(p), pMax(p) {}

	template <typename T>
	bounds3<T>::bounds3(const pbrt::point3<T> &p1, const pbrt::point3<T> &p2) 
		: pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z,p2.z)),
		  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z,p2.z)) {}


	template <typename T>
	const point3<T> & bounds3<T>::operator[](int i) const
	{
		assert(i >= 0 && i <= 1);

		if (i == 0)
			return pMin;
		else
			return pMax;
	}

	template <typename T>
	point3<T> & bounds3<T>::operator[](int i)
	{
		assert(i >= 0 && i <= 1);

		if (i == 0)
			return pMin;
		else
			return pMax;

	}

	template <typename T>
	point3<T> bounds3<T>::Corner(int corner) const
	{
		return point3<T>((*this)[(corner & 1)].x,
						(*this)[(corner & 2) ? 1 : 0].y,
						(*this)[(corner & 4) ? 1 : 0].z);

	}

}