#pragma once

#include <cmath>
#include <algorithm>

namespace pbrt
{



	template <typename T>
	class point3;

	template <typename T>
	class point2
	{
	public:
		explicit point2(const point3<T> &p);

		bool HasNaNs() const;

		T x;
		T y;
	};

	template <typename T>
	class vector3;

	template <typename T>
	class point3
	{
	public:
		point3();
		point3(T x, T y, T z);
	
		template <typename U>
		explicit point3(const point3<U> &p);
	
		//for some reason explicit not allowed
#if defined(__GNUC__) || defined(__GNUG__)                 
		template <typename U>
		explicit operator vector3<U>() const
		{
                    return vector3<U> (x, y, z);
		}
#endif		

		point3<T> operator+(const vector3<T> &v) const;
		point3<T>& operator+=(const vector3<T> &v);
		vector3<T> operator-(const point3<T> &p) const;
		point3<T> operator-(const vector3<T> &v);
		point3<T> & operator-=(const vector3<T> &v);
		point3<T> operator+(const point3<T> &p) const;
		point3<T> operator/(T s) const;

		bool HasNaNs() const;

		T x;
		T y;
		T z;
	};

	template <typename T>
	inline float Distance(const point3<T> &p1, const point3<T> &p2)
	{
		return (p1 - p2).Length();
	}

	template <typename T>
	inline float DistanceSquared(const point3<T> &p1, const point3<T> &p2)
	{
		return (p1 - p2).LengthSquared();
	}


	template <typename T>
	inline point3<T> Lerp(float t, const point3<T> &p0, const point3<T> &p1)
	{
		return (1 - t) * p0 + t * p1;
	}

	template <typename T>
	inline T Lerp(float t, const T &p0, const T &p1)
	{
		return (1 - t) * p0 + t * p1;
	}

	 template <typename T>
	 inline point3<T> Min(const point3<T> &p1, const point3<T> &p2)
	 {
		 return point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
	 }

	  template <typename T>
	 inline point3<T> Max(const point3<T> &p1, const point3<T> &p2)
	 {
		 return point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
	 }

	 template <typename T>
	 inline point3<T> Floor(const point3<T> &p)
	 {
		 return point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
	 }

	  template <typename T>
	 inline point3<T> Ceil(const point3<T> &p)
	 {
		 return point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
	 }

	 template <typename T>
	 inline point3<T> Abs(const point3<T> &p)
	 {
		 return point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
	 }

	 template <typename T>
	 inline point3<T> Permute(const point3<T> &p, int x, int y, int z)
	 {
		 return point3<T>(p[x],p[y],p[z]);
	 }

	 
 }

 #include "point.cpp"







