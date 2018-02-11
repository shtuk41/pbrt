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

		bool HasNaNs() const;

		T x;
		T y;
		T z;
	 };

	 template <typename T>
	 inline normal3<T> FaceForward(const normal3<T> &n, const vector3<T> &v)
	 {
		 return (Dot(n,v) < 0.0f ? -n : n);
	 }
}

#include "normal.cpp"