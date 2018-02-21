#pragma once

#include <assert.h>
#include <algorithm>

namespace pbrt
{
	template <typename T>
	class vector3;

	template <typename T>
	 class normal3
	 {
		public:
		explicit	normal3(const pbrt::vector3<T> &v); 

		normal3 & operator*=(T a);
		normal3 operator-() const;

		bool HasNaNs() const;

		T x;
		T y;
		T z;
	 };

	 template <typename T>
	 inline normal3<T> FaceForward(const normal3<T> &n, const vector3<T> &v)
	 {
		 return (Dot(vector3<T>(n),v) < 0.0f ? -n : n);
	 }

	template <typename T>
	bool operator!=(const normal3<T> &n1, const normal3<T> &n2)
	{
		return  (n1.x != n2.x || n1.y != n2.y || n1.z != n2.z);
	}
}

#include "normal.cpp"