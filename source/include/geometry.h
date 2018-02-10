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

		double v1x = v1.x;
		double v1y = v1.y;
		double v1z = v1.z;

		double v2x = v2.x;
		double v2y = v2.y;
		double v2z = v2.z;

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

	 template <typename T>
	 class normal3
	 {
		public:
			explicit normal3<T>(const vector3<T> &v);
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







