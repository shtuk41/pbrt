#pragma once

#include <cmath>
#include <algorithm>

namespace pbrt
{
	template <typename T>
	class vector2
	{
		public:
			T x;
			T y;
	};

	template <typename T>
	class normal3;

	template <typename T>
	class vector3
	{
		public:
			vector3() { x = y = z = 0;}
			vector3(T x, T y, T z);
			vector3(const normal3<T> &n);
			T operator [] (int i) const;
			vector3<T> operator+(const vector3<T> &v) const;
			vector3<T> & operator+=(const vector3<T> &v);
			vector3<T> operator-(const vector3<T> &v) const;
			vector3<T> & operator-=(const vector3<T> &v);
			vector3<T> operator*(T s) const;
			vector3<T> & operator*=(T s);
			vector3<T> operator/(T f) const;
			vector3<T> & operator/=(T f);
			vector3<T> operator-() const;
			float LengthSquared() const;
			float Length() const;

			bool HasNaNs() const;

			T x;
			T y;
			T z;
	};

	template <typename T> 
	inline vector3<T> operator*(T s, const vector3<T> &v) 
	{ 
		return v * s; 
	}

	template <typename T> 
	inline vector3<T> Abs(T s, const vector3<T> &v) 
	{ 
		return vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z)); 
	}

	template <typename T>
	inline T Dot(const vector3<T> &v1, const vector3<T> &v2)
	{
		//v1 * v2 = |v| * |w| * cos Q
		//|v| - length of vector
		//Q - angle between v and w

		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template <typename T>
	inline T AbsDot(const vector3<T> &v1, const vector3<T> &v2)
	{
		return std::abs(Dot(v1, v2));
	}

	template <typename T>
	inline vector3<T> Cross(const vector3<T> &v1, const vector3<T> &v2)
	{
		//|v x w| = |v| * |w| * sin Q

		T v1x = v1.x;
		T v1y = v1.y;
		T v1z = v1.z;

		T v2x = v2.x;
		T v2y = v2.y;
		T v2z = v2.z;

		return vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z), (v1x * v2y) - (v1y * v2x));

	}

	template <typename T>
	inline vector3<T> Normalize(const vector3<T> &v) 
	{
		return v / v.Length();
	}

	template <typename T>
	inline T MinComponent(const vector3<T> &v)
	{
		return std::min(v.x, std::min(v.y, v.z));
	}

	template <typename T>
	inline T MaxComponent(const vector3<T> &v)
	{
		return std::max(v.x, std::max(v.y, v.z));
	}

	template <typename T>
	inline int MaxDiminesion(const vector3<T> &v)
	{
		return (v.x > v.y) ? ((v.x> v.z) ? 0 : 2) :
			 ((v.y> v.z) ? 1 : 2);
	}

	template <typename T>
	inline vector3<T> Min(const vector3<T> &p1, const vector3<T> &p2)
	{
		return vector3<T>(std::min(p1.x, p2.x), std::min(p1.y,p2.y), std::min(p1.z, p2.z));
	}

	template <typename T>
	vector3<T> Max(const vector3<T> &p1, const vector3<T> &p2)
	{
		return vector3<T>(std::max(p1.x, p2.x), std::max(p1.y,p2.y), std::max(p1.z, p2.z));
	}

	template <typename T>
	vector3<T> Permute(const vector3<T> &v, int x, int y, int z)
	{
		return vector3<T>(v[x], v[y], v[z]);
	}

	template <typename T>
	inline void CoordinateSystem(const vector3<T> &v1, vector3<T> *v2, vector3<T> *v3)
	{
		//PBRT CHapter 2 Physically Based Rendering: From Theory to Implementation, Third Edition
		//The implementation of this function assumes that the vector passed in, v1, has already been normalized. 
		//It first constructs a perpendicular vector by zeroing one of the components of the original vector, 
		//swapping the remaining two, and negating one of them. Inspection of the two cases should make clear 
		//that v2 will be normalized and that the dot product (v1• v2) must be equal to zero. 
		//Given these two perpendicular vectors, a single cross product gives the third, 
		//which by definition will be perpendicular to the first two.

		if (std::abs(v1.x)> std::abs(v1.y))
		{
				 *v2=vector3<T>(-v1.z, 0, v1.x) /
					  std::sqrt(v1.x * v1.x + v1.z * v1.z);
		}
		else
		{
				 *v2=vector3<T>(0, v1.z, -v1.y) /
					  std::sqrt(v1.y * v1.y + v1.z * v1.z);
		}
    
		*v3=Cross(v1, *v2);
	}
}

 #include "vector.cpp"